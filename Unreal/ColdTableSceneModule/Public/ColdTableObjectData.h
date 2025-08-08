#pragma once

#include "CoreMinimal.h"
#include "ColdTableComponentData.h"
#include "ColdTableTransform.h"

#include "ColdTableObjectData.generated.h"

USTRUCT()
struct FColdTableObjectData {
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	bool Enabled;
	UPROPERTY(EditAnywhere)
	FColdTableTransform Transform;
	UPROPERTY(EditAnywhere)
	TArray<FColdTableComponentData> Components;
};