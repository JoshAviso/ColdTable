#pragma once

#include "Modules/ModuleManager.h"
#include "ColdTableSceneData.h"

class FColdTableSceneModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void AddMenuEntry(FMenuBuilder& MenuBuilder);

    void ImportScene();

    bool LoadColdTableSceneFromFile(const FString& FilePath, FColdTableSceneData& OutData);
    FString OpenFilePicker();
    bool OpenFileSaveDialog(FString& outputString);
    bool DeleteExisting(const FString& AssetPath);

    void GenerateScene(const FColdTableSceneData& data);
    UWorld* CreateNewLevel(const FString& PackagePath, const FString& LevelName);
    AActor* CreateActor(UWorld* World, const FColdTableObjectData& objectData);

    void ExportSceneToSaladFile();
    FColdTableSceneData GenerateOutputDataFromCurrentScene();
    bool SerializeToString(const FColdTableSceneData& data, FString& output);
    TSharedPtr<FJsonObject> VectorToJson(const FVector3f& vec);
    TSharedPtr<FJsonObject> QuatToJson(const FQuat4f& quat);

};
