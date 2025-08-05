#pragma once
#include <d3d11.h>
#include <list>
#include <vector>
#include <ColdTable/Math/Vec3.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>

#include "ColdTable/Editor/FaceObject.h"

namespace ColdTable
{

	class VertexBuffer : public Base, public std::enable_shared_from_this<VertexBuffer>
	{
	public:
		explicit VertexBuffer(VertexBufferDesc desc);
		virtual ~VertexBuffer() override;

	private:
		UINT GetVertexCount();
		void LoadVertices(const void* list, UINT vertexSize, UINT listSize, ShaderPtr shader);
		void UpdateVertexData();
		UINT _vertexSize;
		UINT _listSize;
		
	private:

		ID3D11Buffer* _buffer;
		ID3D11Buffer* _stagingBuffer;
		ID3D11InputLayout* _layout;
		ShaderPtr _shader;
		bool _canUpdateVertex = false;
		bool _isDirty = false;

		std::vector<VertexObjectPtr> _vertexObjects;
		std::vector<VertexPtr> _vertices;
		std::vector<Vertex> _stagingVerts;
		std::vector<FaceObjectPtr> _faceObjects;

	private:
		friend class DeviceContext;
		friend class Renderable;
		friend class Mesh;
		friend class GraphicsEngine;
		friend class VertexObject;
		friend class Cube;
		friend class EdgeObject;
		friend class FaceObject;
		friend class Cylinder;
		friend class Stair;
		friend class GameObject;
	};
}
 