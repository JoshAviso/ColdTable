using UnrealBuildTool;

public class ColdTableSceneModule : ModuleRules
{
    public ColdTableSceneModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",       // Needed for editor functionality
            "Slate",          // For UI
            "SlateCore",
            "InputCore",
			"Json",
			"JsonUtilities", 
			"EditorStyle" //, "uLangCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Projects",
            // add more here if needed
        });

        if (Target.bBuildEditor == true)
        {
            // Editor module only
        }
    }
}
