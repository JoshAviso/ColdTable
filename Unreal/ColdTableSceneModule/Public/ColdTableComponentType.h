#pragma once

#include "CoreMinimal.h"

#include "ColdTableComponentType.generated.h"

UENUM()
enum EColdTableComponentType {
    None = 0,
    Rigidbody = 3,
    Material= 4,
    Mesh = 5,
};