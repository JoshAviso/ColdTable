#pragma once

#include "CoreMinimal.h"

#include "ColdTableComponentData.generated.h"
USTRUCT()
struct FColdTableComponentData {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 ComponentType;
	UPROPERTY(EditAnywhere)
	bool Enabled;
	UPROPERTY(EditAnywhere)
	int32 BodyType;
	UPROPERTY(EditAnywhere)
	float Mass;
	UPROPERTY(EditAnywhere)
	FString MeshID;
	UPROPERTY(EditAnywhere)
	FString MaterialID;
};