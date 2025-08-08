
#include "ColdTableCommands.h"

#define LOCTEXT_NAMESPACE "FColdTableCommands"

void FColdTableCommands::RegisterCommands()
{
	UI_COMMAND(ImportColdTableScene, "Import ColdTable Scene File", "Imports ColdTable .salad files",
		EUserInterfaceActionType::Button, FInputGesture())
	UI_COMMAND(ExportColdTableScene, "Export Level to ColdTable Scene File", "Exports ColdTable .salad files",
		EUserInterfaceActionType::Button, FInputGesture())
}


#undef LOCTEXT_NAMESPACE