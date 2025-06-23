#pragma once

#include <intsafe.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <ColdTable/Math/Vertex.h>
#include <ColdTable/Graphics/GraphicsEnums.h>
#include <ColdTable/Math/Mat4.h>
#include <ColdTable/Math/Quaternion.h>

#include "ColdTable/Input/IInputListener.h"

namespace ColdTable
{
	struct RenderableDesc
	{
		Vertex* vertexList;
		UINT vertexCount;
		EGeometryDrawmode drawMode;
		MaterialPtr material;
		//ShaderPtr shader;
	};

	class Renderable : public IInputListener
	{
	public:
		explicit Renderable(const RenderableDesc& desc);
		explicit Renderable(const RenderableDesc& desc, const ShaderPtr& shader);
		virtual ~Renderable();

		virtual void LoadVertices(const Vertex* vertexList, UINT listSize);
		virtual void LoadVerticesInIndex(const Vertex* vertexList, UINT listSize, const IndexBufferPtr& indexBuffer);
		virtual void Update(const d64 deltaTime);
		void SetShader(ShaderPtr shader);
		void SetTexture(TexturePtr texture);

	public:
		Vec3 localPosition = Vec3::Zero;
		Vec3 localScale = Vec3::Identity;
		Quaternion localRotation = Quaternion::Identity;
		Mat4 transformMat() const;
		void OnKeyDown(int key) override;
		void OnKeyUp(int key) override;
		void OnMouseMove(Vec2 delta) override;
		void OnLeftMouseDown(Vec2 pos) override;
		void OnRightMouseUp(Vec2 pos) override;

	protected:
		VertexBufferPtr _vertexBuffer;
		IndexBufferPtr _indexBuffer;
		EGeometryDrawmode _drawMode;

		MaterialPtr _material;
		ShaderPtr _shader;
		TexturePtr _texture = nullptr;

		const Vertex* vertexListRef;

		bool tempMovingVertical = false;
		bool tempMovingPositive = true;
		float elapsedTime = 0;
		Vec3 targetPosition = { 2.0, 0.0, 0.0 };
		Vec3 lastPosition = { -2.0f, 0.0f, 0.0f };
		Vec3 targetScale = { 10.0f, 0.01f, 10.0f };
		Vec3 lastScale = { 1.0f };

	public:
		Vec3 rotationAxis{};
		float rotationSpeed = 0.0f;

	public:
		Vec3 aabb_min{0, 0, 0};
		Vec3 aabb_max{0, 0, 0};

	private:
		friend class DeviceContext;
		friend class GraphicsEngine;
		friend class Ray;
	};
}

