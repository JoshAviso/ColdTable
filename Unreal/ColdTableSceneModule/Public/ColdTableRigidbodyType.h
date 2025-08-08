#pragma once

//#include "CoreMinimal.h"

//#include "ColdTableRigidbodyType.generated.h"

UENUM()
enum EColdTableRigidbodyType
{
    RigidbodyTypeNone = -1,
    Static = 0,
    Kinematic = 1,
    Dynamic = 2,
};