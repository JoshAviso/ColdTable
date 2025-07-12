#pragma once
#include <vector>
#include <ColdTable/Editor/IEditorPickable.h>

#include "ColdTable/ECS/Components/Transform.h"
#include "ColdTable/Math/Vertex.h"

namespace ColdTable
{
    class EdgeObject;
    class VertexObject: public IEditorPickable
    {
    public:
        VertexObject(VertexBufferPtr owner);
        VertexObject(VertexBufferPtr owner, unsigned int vertexIndex);
        VertexObject(VertexBufferPtr owner, unsigned int vertexIndex, Vec3 pos);
        void AddVertex(unsigned int vertexIndex);

        Transform transform;

        void Translate(Vec3 translation) override;
        void Rotate(Vec3 axis, float degree) override;
        void Scale(Vec3 scale) override;
        Vec3 getActualPos();

        VertexPtr vert();

        VertexBufferPtr _owner;
        std::vector<unsigned int> _vertexIndices{};
        Vec3 tempPos;

        void AddEdge(EdgeObject* edge);
        std::vector<EdgeObject*> _owningEdges{};
    };
	using VertexObjectPtr = std::shared_ptr<VertexObject>;
}
