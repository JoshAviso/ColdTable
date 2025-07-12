#pragma once
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
    enum EPickableType
    {
        PickupObject, PickupVertex, PickupFace, PickupEdge
    };
    
    class IEditorPickable
    {
    public:
        virtual ~IEditorPickable() = default;

        virtual void Translate(Vec3 translation) = 0;
        virtual void Rotate(Vec3 axis, float degree) = 0;
    };
}
