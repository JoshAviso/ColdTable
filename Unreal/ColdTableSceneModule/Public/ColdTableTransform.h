#pragma once

#include "CoreMinimal.h"

#include "ColdTableTransform.generated.h"

USTRUCT()
struct FColdTableTransform
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere)
	FVector3f Position;
	UPROPERTY(EditAnywhere)
	FVector3f Scale;
	UPROPERTY(EditAnywhere)
	FQuat4f Rotation;
};