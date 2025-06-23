#pragma once

#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Game/EngineTime.h>
#include <ColdTable/Resource/Material/Material.h>
#include <vector>
#include <ColdTable/Input/IInputListener.h>

namespace ColdTable
{
	struct CircleObject
	{
		Vec2 circleVec{ 1, 1 };
		Vec2 circlePos{ 0,0 };
	};

	class GraphicsEngine final: public Base , public IInputListener
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		RenderablePtr CheckHitObject(Ray ray);

		void RegisterRenderable(RenderablePtr renderable);
		void UnregisterRenderable(RenderablePtr renderable);

		void RegisterMesh(MeshPtr mesh);
		void UnregisterMesh(MeshPtr mesh);

		void RegisterLight(const DirectionalLightPtr& light);
		void UnregisterLight(const DirectionalLightPtr& light);

		void RegisterLight(const SpotLightPtr& light);
		void UnregisterLight(const SpotLightPtr& light);

		void RegisterLight(const PointLightPtr& light);
		void UnregisterLight(const PointLightPtr& light);

		void RegisterComputeShader(ComputeShaderPtr computeShader);

		GraphicsDevicePtr GetGraphicsDevice() noexcept;
		//void UpdateConstantBuffer(const ConstantBufferPtr& constantBuffer, ConstantBufferContent content);

		void SetViewportSize(Rect size);
		ShaderPtr CreateShader(const wchar_t* vertexShaderSrc, const wchar_t* pixelShaderSrc);
		ComputeShaderPtr CreateComputeShader(const wchar_t* sourceFile, const float* inputArray);
		void BindComputeShader(ComputeShaderPtr computeShader);

		void BindMaterial(MaterialPtr material);

		MaterialPtr CreateMaterial(ShaderPtr shader);
		VertexBufferPtr CreateVertexBuffer();
		ConstantBufferPtr CreateConstantBuffer();
		IndexBufferPtr CreateIndexBuffer();

	private:
		void UseShader(const ShaderPtr& shader);
		void Render(CameraPtr camera, SwapChain& swapChain, ConstantBufferPtr perObjectBuffer, ConstantBufferPtr lightBuffer, Rect viewportSize);

		void DispatchComputeShader(ComputeShaderPtr computeShader, UINT xThreads, UINT yThreads, UINT zThreads);
		void AwaitComputeShaderFinish();

		std::shared_ptr<GraphicsDevice> _graphicsDevice{};
		DeviceContextPtr _deviceContext{};

		std::vector<RenderablePtr> _renderables{};
		std::vector<MeshPtr> _meshes{};
		std::vector<DirectionalLightPtr> _directionalLights{};
		std::vector<SpotLightPtr> _spotLights{};
		std::vector<PointLightPtr> _pointLights{};

		ID3D11Query* _computeShaderQuery;

		double runningTime = 0.0;
		double animationTime = 2.0;
		bool transitioningToOriginalPosition = false;
		bool slowingDownAnim = false;

		friend class GameLoop;

		std::vector<CircleObject> _circles{};

		float circleSpeed = 5.0f;
		float circleRad = 50.0f;

		Rect screensize{};

		void OnKeyUp(int key) override;
		void OnKeyDown(int key) override;
	};
}

