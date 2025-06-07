#pragma once

#include <intsafe.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <ColdTable/Math/Vertex.h>
#include <ColdTable/Graphics/GraphicsEnums.h>
#include <ColdTable/Math/Mat4.h>
#include <ColdTable/Math/Quaternion.h>

namespace ColdTable
{
	class Renderable
	{
	public:
		explicit Renderable(const RenderableDesc& desc);
		virtual ~Renderable();

		virtual void LoadVertices(const Vertex* vertexList, UINT listSize);
		virtual void LoadVerticesInIndex(const Vertex* vertexList, UINT listSize, const IndexBufferPtr& indexBuffer);
		virtual void Update(const d64 deltaTime);
		void SetShader(ShaderPtr shader);

	public:
		Vec3 localPosition = Vec3::Zero;
		Vec3 localScale = Vec3::Identity;
		Quaternion localRotation = Quaternion::Identity;
		Mat4 transformMat() const;

	private:
		VertexBufferPtr _vertexBuffer;
		IndexBufferPtr _indexBuffer;
		EGeometryDrawmode _drawMode;
		ShaderPtr _shader;

		const Vertex* vertexListRef;

	private:
		friend class DeviceContext;

	};
}

