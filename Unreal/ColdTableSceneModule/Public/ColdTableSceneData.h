
#pragma once
#include "CoreMinimal.h"
#include "ColdTableObjectData.h"

#include "ColdTableSceneData.generated.h"

USTRUCT()
struct FColdTableSceneData {
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere)
	FString SceneName;
	UPROPERTY(EditAnywhere)
	TArray<FColdTableObjectData> Objects;
};