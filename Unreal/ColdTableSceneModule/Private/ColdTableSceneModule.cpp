#include "ColdTableSceneModule.h"

#include "AssetToolsModule.h"
#include "ColdTableCommands.h"
#include "ColdTableComponentType.h"
#include "ColdTableRigidbodyType.h"
#include "DesktopPlatformModule.h"
#include "FileHelpers.h"
#include "IDesktopPlatform.h"
#include "JsonObjectConverter.h"
#include "LevelEditor.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StaticMeshActor.h"
#include "Factories/WorldFactory.h"
#include "Modules/ModuleManager.h"
#include "Logging/LogMacros.h"
#include "UObject/SavePackage.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogColdTableSceneEditor, Log, All);
IMPLEMENT_MODULE(FColdTableSceneModule, ColdTableSceneModule)

void FColdTableSceneModule::StartupModule()
{
    UE_LOG(LogColdTableSceneEditor, Log, TEXT("ColdTableSceneModule module started"));

    FLevelEditorModule& levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    FColdTableCommands::Register();
    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

    // Import Command Register
    TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList);
    CommandList->MapAction(
        FColdTableCommands::Get().ImportColdTableScene,
        FExecuteAction::CreateRaw(this, &FColdTableSceneModule::ImportScene),
        FCanExecuteAction()
    );

    // Export Command Register
    CommandList->MapAction(
        FColdTableCommands::Get().ExportColdTableScene,
        FExecuteAction::CreateRaw(this, &FColdTableSceneModule::ExportSceneToSaladFile),
        FCanExecuteAction()
    );

    MenuExtender->AddMenuExtension(
        "FileProject",
        EExtensionHook::After,
        CommandList,
        FMenuExtensionDelegate::CreateRaw(this, &FColdTableSceneModule::AddMenuEntry)
    );

    levelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FColdTableSceneModule::ShutdownModule()
{
    UE_LOG(LogColdTableSceneEditor, Log, TEXT("ColdTableSceneModule module shutting down"));

    // Unregister any registered stuff here
}

void FColdTableSceneModule::AddMenuEntry(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.AddMenuEntry(FColdTableCommands::Get().ImportColdTableScene);
    MenuBuilder.AddMenuEntry(FColdTableCommands::Get().ExportColdTableScene);
}

void FColdTableSceneModule::ImportScene()
{
    FString FilePath = OpenFilePicker();
    if (!FilePath.IsEmpty())
    {
        FColdTableSceneData ImportScene;
        if (LoadColdTableSceneFromFile(FilePath, ImportScene))
        {
            UE_LOG(LogTemp, Log, TEXT("Successfully loaded scene %s"), *ImportScene.SceneName);
            for (const auto& obj : ImportScene.Objects)
            {
	            UE_LOG(LogTemp, Log, TEXT("Name: %s, Enabled: %s"), *obj.Name, obj.Enabled ? TEXT("True") : TEXT("False"));
                UE_LOG(LogTemp, Log, TEXT("Position: (%f, %f, %f), Scale: (%f, %f, %f), Rotation:(%f, %f, %f, %f)"), 
                    obj.Transform.Position.X, obj.Transform.Position.Y, obj.Transform.Position.Z, 
                    obj.Transform.Scale.X, obj.Transform.Scale.Y, obj.Transform.Scale.Z, 
                    obj.Transform.Rotation.W, obj.Transform.Rotation.X, obj.Transform.Rotation.Y, obj.Transform.Rotation.Z);
	            UE_LOG(LogTemp, Log, TEXT("Number of Components: %d"), obj.Components.Num());

	            for (const auto& Component : obj.Components)
	            {
	                UE_LOG(LogTemp, Log, TEXT("Component Type: %d, Enabled: %s, MeshID: %s, MatID: %s, RBType: %d, Mass: %f"), (int32)Component.ComponentType, Component.Enabled ? TEXT("True") : TEXT("False"), *Component.MeshID, *Component.MaterialID, (int32)Component.BodyType, Component.Mass);
	               
	            }
            }
            GenerateScene(ImportScene);
        }
    }
}

bool FColdTableSceneModule::LoadColdTableSceneFromFile(const FString& FilePath, FColdTableSceneData& OutData)
{
    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to import scene file: %s"), *FilePath);
        return false;
    }
    UE_LOG(LogTemp, Log, TEXT("Imported Json: %s"), *JsonString);
    if (!FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &OutData, 0, 0))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse salad file from: %s"), *FilePath);
        return false;
    }
    return true;
}

FString FColdTableSceneModule::OpenFilePicker()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        TArray<FString> OutFiles;
        const void* ParentWindowHandle = nullptr;
        bool bOpened = DesktopPlatform->OpenFileDialog(
            ParentWindowHandle,
            TEXT("Choose Salad File to Import"),
            TEXT(""),
            TEXT(""),
            TEXT("Salad files (*.salad)|*.salad"),
            EFileDialogFlags::None,
            OutFiles
        );

        if (bOpened && OutFiles.Num() > 0)
        {
            return OutFiles[0];
        }
    }
    return FString();
}

bool FColdTableSceneModule::OpenFileSaveDialog(FString& OutFilePath)
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (!DesktopPlatform)
        return false;

    const void* ParentWindowHandle = (FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr));

    const FString DefaultPath = FPaths::ProjectSavedDir();
    const FString DefaultFile = FString(TEXT("NewScene.salad"));
    const FString FileTypes = TEXT("ColdTable Scene Files (*.salad)|*.salad");

    TArray<FString> OutFiles;
    bool bOpened = DesktopPlatform->SaveFileDialog(
        ParentWindowHandle,
        TEXT("Save ColdTable Scene As"),
        DefaultPath,
        DefaultFile,
        FileTypes,
        EFileDialogFlags::None,
        OutFiles
    );

    if (bOpened && OutFiles.Num() > 0)
    {
        OutFilePath = OutFiles[0];
        return true;
    }
    return false;
}

bool FColdTableSceneModule::DeleteExisting(const FString& AssetPath)
{
    // Find the existing asset
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(*AssetPath);

    if (ExistingAsset.IsValid())
    {
        // Load the object from the asset data
        UObject* AssetObject = ExistingAsset.GetAsset();
        if (AssetObject)
        {
            // Prompt or force delete the asset, here forcing deletion programmatically
            TArray<UObject*> AssetsToDelete = { AssetObject };
            ObjectTools::DeleteObjects(AssetsToDelete, false);

            return true;
        }
    }
    return false;
}

void FColdTableSceneModule::GenerateScene(const FColdTableSceneData& data)
{
    FString PackagePath = TEXT("/Game/Levels");
    UWorld* newScene = CreateNewLevel(PackagePath, data.SceneName);
    if (newScene == nullptr) return;

    for (auto ObjectData : data.Objects)
    {
        CreateActor(newScene, ObjectData);
    }

    // Mark package dirty to indicate unsaved changes
    UPackage* Package = newScene->GetOutermost();
    if (Package)
    {
        Package->SetDirtyFlag(true);

        // Save the level package
        FString PackageFileName = FPackageName::LongPackageNameToFilename(Package->GetName(), FPackageName::GetMapPackageExtension());
        FSavePackageArgs SaveArgs;
    	bool bSaved = UPackage::SavePackage(
            Package,
            newScene,
            *PackageFileName,
            SaveArgs
        );

        if (!bSaved) { UE_LOG(LogTemp, Error, TEXT("Failed to save package: %s"), *PackageFileName); }
        else { UE_LOG(LogTemp, Log, TEXT("Successfully saved package: %s"), *PackageFileName); }

        // Open the newly created level in the editor viewport to make it the active scene
        FString LevelPackageName = Package->GetName();
        bool bOpened = FEditorFileUtils::LoadMap(LevelPackageName, false, true);

        if (!bOpened)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to open level in editor: %s"), *LevelPackageName);
            FMessageDialog::Open(EAppMsgType::Ok, FText::Format(NSLOCTEXT("GenerateScene", "LoadLevelFailed", "Failed to open level '{0}' in editor."), FText::FromString(LevelPackageName)));
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Level opened in editor: %s"), *LevelPackageName);
        }
    }
}

UWorld* FColdTableSceneModule::CreateNewLevel(const FString& PackagePath, const FString& LevelName)
{
    FString PackageName = PackagePath + TEXT("/") + LevelName;
    FString LevelPath = PackageName + TEXT(".") + LevelName;
    FEditorFileUtils::LoadMap(TEXT("/Game/Maps/EmptyMap")); // load an empty map 
    DeleteExisting(LevelPath);

    UWorldFactory* WorldFactory = NewObject<UWorldFactory>();
    FAssetToolsModule& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
    UObject* NewLevelAsset = AssetToolModule.Get().CreateAsset(LevelName, PackagePath, UWorld::StaticClass(), WorldFactory);

    if (NewLevelAsset)
    {
        return Cast<UWorld>(NewLevelAsset);
    }
    return nullptr;
}

AActor* FColdTableSceneModule::CreateActor(UWorld* World, const FColdTableObjectData& objectData)
{
    if (!World) return nullptr;

    // Process data
    bool hasMesh = false; bool hasRB = false; bool hasMat = false;
    bool meshActive = false; bool RBActive = false; bool matActive = false;
    FString MeshID = ""; FString MaterialID = ""; float Mass = 0;
	EColdTableRigidbodyType RBType = EColdTableRigidbodyType::RigidbodyTypeNone;
    for (auto component : objectData.Components)
    {
        switch (component.ComponentType)
        {
        case EColdTableComponentType::Mesh:
            hasMesh = true;
            meshActive = component.Enabled;
            MeshID = component.MeshID;
            break;
        case EColdTableComponentType::Rigidbody:
            hasRB = true;
            RBActive = component.Enabled;
            Mass = component.Mass;
            RBType = (EColdTableRigidbodyType)component.BodyType;
            break;
        case EColdTableComponentType::Material:
            hasMat = true;
            matActive = component.Enabled;
            MaterialID = component.MaterialID;
            break;
        }
    }

    // Begin spawning
    FActorSpawnParameters SpawnParams;
    FVector Position = FVector(objectData.Transform.Position.X * 100, objectData.Transform.Position.Z * 100, objectData.Transform.Position.Y * 100);
    FVector Scale = FVector(objectData.Transform.Scale.X, objectData.Transform.Scale.Z, objectData.Transform.Scale.Y);
    FQuat Quat = FQuat(objectData.Transform.Rotation.X, objectData.Transform.Rotation.Z, objectData.Transform.Rotation.Y, objectData.Transform.Rotation.W);
    if (!hasMesh)
    {
        AActor* NewActor = World->SpawnActor<AActor>(Position, Quat.Rotator(), SpawnParams);
        if (NewActor) NewActor->SetActorScale3D(Scale);
        return NewActor;
    }

    AStaticMeshActor* NewActor = World->SpawnActor<AStaticMeshActor>(Position, Quat.Rotator(), SpawnParams);
    if (NewActor)
    {
        NewActor->SetActorLabel(objectData.Name);
        NewActor->SetActorHiddenInGame(!objectData.Enabled);

        if (MeshID == "Plane") NewActor->SetActorScale3D(Scale * 10);
        else NewActor->SetActorScale3D(Scale);
        /* Handle mesh assignment */
        FString TargetMesh;
        if (MeshID == "Cube")           TargetMesh = TEXT("/Engine/BasicShapes/Cube.Cube");
        else if (MeshID == "Cylinder")  TargetMesh = TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
        else if (MeshID == "Capsule")   TargetMesh = TEXT("/Engine/BasicShapes/Capsule.Capsule");
        else if (MeshID == "Sphere")    TargetMesh = TEXT("/Engine/BasicShapes/Sphere.Sphere");
        else if (MeshID == "Plane")     TargetMesh = TEXT("/Engine/BasicShapes/Plane.Plane");
        else                            TargetMesh = TEXT("");

        UStaticMesh* ObjectMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *TargetMesh));
        if (ObjectMesh)
        {
            NewActor->GetStaticMeshComponent()->SetStaticMesh(ObjectMesh);
            NewActor->SetActorEnableCollision(true);
            NewActor->GetStaticMeshComponent()->SetVisibility(meshActive);
        }
        /* End mesh assignment */

        /* Handle RB Addon */
        if (hasRB)
        {
            // Get the PrimitiveComponent to configure physics on
            UPrimitiveComponent* PrimComp = NewActor->GetStaticMeshComponent();
            if (PrimComp)
            {
                // Decide collision settings and whether to simulate physics
                bool bSimulatePhysics = (RBType != EColdTableRigidbodyType::Static);
                ECollisionEnabled::Type CollisionType = ECollisionEnabled::QueryAndPhysics;

                // Configure physics and collision on the primitive component
                PrimComp->SetActive(RBActive);
                PrimComp->SetCollisionEnabled(CollisionType);
                PrimComp->SetSimulatePhysics(bSimulatePhysics);

                switch (RBType)
                {
                case EColdTableRigidbodyType::Static:
                    PrimComp->SetMobility(EComponentMobility::Static);
                    PrimComp->SetSimulatePhysics(false);
                    break;

                case EColdTableRigidbodyType::Kinematic:
                    PrimComp->SetMobility(EComponentMobility::Movable);
                    PrimComp->SetSimulatePhysics(true);
                    PrimComp->SetEnableGravity(false);

                    PrimComp->BodyInstance.bLockXTranslation = true;
                    PrimComp->BodyInstance.bLockYTranslation = true;
                    PrimComp->BodyInstance.bLockZTranslation = true;
                    break;

                case EColdTableRigidbodyType::Dynamic:
                    PrimComp->SetMobility(EComponentMobility::Movable);
                    PrimComp->SetSimulatePhysics(true);
                    PrimComp->SetEnableGravity(true);
                    break;

                default:
                    break;
                }

                PrimComp->SetMassOverrideInKg(NAME_None, Mass, true);
            } else
            {
                UE_LOG(LogTemp, Log, TEXT("No PrimComp"));
            }
        }
    }
    return NewActor;
}

void FColdTableSceneModule::ExportSceneToSaladFile()
{
    FString FilePath;
    if (!OpenFileSaveDialog(FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Export canceled or failed."));
        return;
    }

    // Your method to generate current scene data struct
    FColdTableSceneData SceneData = GenerateOutputDataFromCurrentScene();

    // Convert to JSON
    FString JsonString;
    if (!SerializeToString(SceneData, JsonString))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to serialize scene data to JSON"));
        return;
    }

    if (!FFileHelper::SaveStringToFile(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to write scene data to file"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("ColdTable scene exported successfully to %s"), *FilePath);
}

FColdTableSceneData FColdTableSceneModule::GenerateOutputDataFromCurrentScene()
{
    FColdTableSceneData SceneData;

    UWorld* World = nullptr; 
    
#if WITH_EDITOR
    if (GEditor) {
        World = GEditor->GetEditorWorldContext().World();
    }
#endif

    if (!World) return SceneData;
    
    SceneData.SceneName = FPackageName::GetShortName(World->GetMapName());
    for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr) {
        AActor* Actor = *ActorItr;
        if (!Actor) continue;

        FColdTableObjectData ObjData;

        ObjData.Name = Actor->GetActorLabel();
        ObjData.Enabled = !(Actor->IsHidden());

        FTransform Transform = Actor->GetActorTransform();
        FVector3f Position = FVector3f(Transform.GetLocation());
        ObjData.Transform.Position = FVector3f(Position.X, Position.Z, Position.Y) / 100.0f;
        FQuat4f Rot = FQuat4f(Transform.GetRotation());
        ObjData.Transform.Rotation = FQuat4f(Rot.X, Rot.Z, Rot.Y, Rot.W);
        FVector3f Scale = FVector3f(Transform.GetScale3D());
        ObjData.Transform.Scale = FVector3f(Scale.X, Scale.Z, Scale.Y);

        bool hasMesh = false; bool hasRB = false; bool hasMat = false;
        
        // Mesh Check
        UStaticMeshComponent* MeshComp = Actor->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComp && MeshComp->GetStaticMesh()) {
            hasMesh = true;

            FColdTableComponentData MeshComponent;
            MeshComponent.ComponentType = EColdTableComponentType::Mesh;
            MeshComponent.Enabled = MeshComp->IsVisible();
            MeshComponent.BodyType = 0;
            MeshComponent.Mass = 0;

            FString MeshPath = MeshComp->GetStaticMesh()->GetPathName();
            FString MeshID = "";
            // Convert mesh path to good id
            int32 dotIndex;
            if (MeshPath.FindLastChar('.', dotIndex)) {
                MeshID = MeshPath.Mid(dotIndex + 1);
            }

            MeshComponent.MeshID = MeshID;
            if (MeshID == "Plane")
                ObjData.Transform.Scale /= 10.0f;

            ObjData.Components.Add(MeshComponent);
        }

        // Physics Check for RB
        UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(MeshComp);
        if (PrimComp) {
            hasRB = true;

            FColdTableComponentData RBComponent;
            RBComponent.ComponentType = EColdTableComponentType::Rigidbody;
            RBComponent.Enabled = PrimComp->IsActive();

            RBComponent.Mass = PrimComp->GetMass();
            if (RBComponent.Mass < 0.00001f) RBComponent.Mass = 0;

            if (!PrimComp->IsSimulatingPhysics()) {
                RBComponent.BodyType = (int32)EColdTableRigidbodyType::Static;
            }
            else {
                bool noGravity = !PrimComp->IsGravityEnabled();
                bool translationLocked =
                    PrimComp->BodyInstance.bLockXTranslation &&
                    PrimComp->BodyInstance.bLockYTranslation &&
                    PrimComp->BodyInstance.bLockZTranslation;

                if (noGravity && translationLocked)
                    RBComponent.BodyType = (int32)EColdTableRigidbodyType::Kinematic;
                else
                    RBComponent.BodyType = (int32)EColdTableRigidbodyType::Dynamic;
            }

            ObjData.Components.Add(RBComponent);
        }

        // Material Logic here

        SceneData.Objects.Add(ObjData);
    }

    return SceneData;
}

bool FColdTableSceneModule::SerializeToString(const FColdTableSceneData& data, FString& output)
{
    TSharedPtr<FJsonObject> JsonRoot = MakeShared<FJsonObject>();

    // Serialize simple fields, e.g. scene name, version etc.
    JsonRoot->SetStringField(TEXT("SceneName"), data.SceneName);

    // Serialize array of objects
    TArray<TSharedPtr<FJsonValue>> JsonObjectsArray;
    for (const FColdTableObjectData& Obj : data.Objects)
    {
        TSharedPtr<FJsonObject> JsonObj = MakeShared<FJsonObject>();
        JsonObj->SetStringField(TEXT("Name"), Obj.Name);
        JsonObj->SetBoolField(TEXT("Enabled"), Obj.Enabled);

        // Serialize Transform
        TSharedPtr<FJsonObject> JsonTransform = MakeShared<FJsonObject>();
        JsonTransform->SetObjectField(TEXT("Position"), VectorToJson(Obj.Transform.Position));
        JsonTransform->SetObjectField(TEXT("Rotation"), QuatToJson(Obj.Transform.Rotation));
        JsonTransform->SetObjectField(TEXT("Scale"), VectorToJson(Obj.Transform.Scale));

        JsonObj->SetObjectField(TEXT("Transform"), JsonTransform);

        // Serialize components
        TArray<TSharedPtr<FJsonValue>> JsonCompArray;
        for (auto& comp : Obj.Components) {
            TSharedPtr<FJsonObject> JsonComp = MakeShared<FJsonObject>();
            JsonComp->SetNumberField(TEXT("ComponentType"), comp.ComponentType);
            JsonComp->SetBoolField(TEXT("Enabled"), comp.Enabled);

            if (comp.ComponentType == EColdTableComponentType::Mesh)
                JsonComp->SetStringField(TEXT("MeshID"), comp.MeshID);
            if(comp.ComponentType == EColdTableComponentType::Material)
                JsonComp->SetStringField(TEXT("MaterialID"), comp.MaterialID);
            if (comp.ComponentType == EColdTableComponentType::Rigidbody) {
                JsonComp->SetNumberField(TEXT("BodyType"), comp.BodyType);
                JsonComp->SetNumberField(TEXT("Mass"), comp.Mass);
            }

            JsonCompArray.Add(MakeShared<FJsonValueObject>(JsonComp));
        }
        JsonObj->SetArrayField(TEXT("Components"), JsonCompArray) ;

        JsonObjectsArray.Add(MakeShared<FJsonValueObject>(JsonObj));
    }
    JsonRoot->SetArrayField(TEXT("Objects"), JsonObjectsArray);

    if (!JsonRoot.IsValid()) return false;

    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&output);
    return FJsonSerializer::Serialize(JsonRoot.ToSharedRef(), Writer);
}

TSharedPtr<FJsonObject> FColdTableSceneModule::VectorToJson(const FVector3f& vec)
{
    TSharedPtr<FJsonObject> JsonVec = MakeShared<FJsonObject>();
    JsonVec->SetNumberField(TEXT("x"), vec.X);
    JsonVec->SetNumberField(TEXT("y"), vec.Y);
    JsonVec->SetNumberField(TEXT("z"), vec.Z);
    return JsonVec;
}

TSharedPtr<FJsonObject> FColdTableSceneModule::QuatToJson(const FQuat4f& quat)
{
    TSharedPtr<FJsonObject> JsonQuat = MakeShared<FJsonObject>();
    JsonQuat->SetNumberField(TEXT("x"), quat.X);
    JsonQuat->SetNumberField(TEXT("y"), quat.Y);
    JsonQuat->SetNumberField(TEXT("z"), quat.Z);
    JsonQuat->SetNumberField(TEXT("w"), quat.W);
    return JsonQuat;
}



