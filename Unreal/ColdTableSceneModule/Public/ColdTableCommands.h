#pragma once

#include "CoreMinimal.h"
#include "EditorStyleSet.h"


#include "Framework/Commands/Commands.h"
#include "Styling/SlateStyle.h"

//#include "ColdTableCommands.generated.h"

class FColdTableCommands : public TCommands<FColdTableCommands>
{
public:
	FColdTableCommands() : TCommands<FColdTableCommands>(
		TEXT("ColdTableCommands"),
		NSLOCTEXT("Contexts", "ColdTableCommands", "ColdTable Commands"),
		NAME_None,
		FEditorStyle::GetStyleSetName()
	){}

	TSharedPtr<FUICommandInfo> ImportColdTableScene;
	TSharedPtr<FUICommandInfo> ExportColdTableScene;

	virtual void RegisterCommands() override;
};