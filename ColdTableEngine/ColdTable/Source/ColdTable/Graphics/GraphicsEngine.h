#pragma once

#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Game/EngineTime.h>
#include <ColdTable/Resource/Material/Material.h>
#include <vector>
#include <ColdTable/Input/IInputListener.h>
#include <ColdTable/Math/Ray.h>

#include "ColdTable/Editor/IEditorPickable.h"

#include <ColdTable/Game/Display.h>

namespace ColdTable
{
	struct GraphicsEngineDesc
	{
		BaseDesc base;
		Rect windowSize{};
	};
	class GraphicsEngine final: public Base, public IInputListener
	{
	public:
		/* ========== Public Utility Functions ========== */
		IEditorPickablePtr CheckHitObject(Ray ray);
		void SetPickupMode(EPickableType mode);

		void RegisterCamera(CameraPtr camera);
		void UnregisterCamera(CameraPtr camera);

		void RegisterLight(const LightSourcePtr& light);
		void UnregisterLight(const LightSourcePtr& light);

		void RegisterComputeShader(ComputeShaderPtr computeShader);

		GraphicsDevicePtr GetGraphicsDevice() noexcept;

		ShaderPtr CreateShader(const wchar_t* vertexShaderSrc, const wchar_t* pixelShaderSrc);
		ComputeShaderPtr CreateComputeShader(const wchar_t* sourceFile, const float* inputArray);
		void BindComputeShader(ComputeShaderPtr computeShader);

		MaterialPtr CreateMaterial(ShaderPtr shader);
		VertexBufferPtr CreateVertexBuffer();
		IndexBufferPtr CreateIndexBuffer();

		/* =========== Public References =========== */
		Display* GetDisplay() const noexcept { return _display.get(); }

	private:
		/* ========== Friended Classes and Functions ========== */
		void Render();
		friend class GameLoop;
		
	public:
		/* =========== Initialization and Private Members ========== */
		static GraphicsEngine* Instance;
		static void Initialize(const GraphicsEngineDesc& desc);

	private:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;
		
		std::unique_ptr<Display>	_display;
		Rect						_windowSize{};

	private:
		/* ========= Private Helper Functions ========= */
		void PassPerFrameConstantBuffers();
		void RenderObjects();
		void RenderUI();

		CameraPtr ActiveCamera() const noexcept {
			return _cameras.empty() ? nullptr : _cameras.back();
		}

		std::shared_ptr<GraphicsDevice>		_graphicsDevice{};
		DeviceContextPtr					_deviceContext{};
		ConstantBufferPtr					_lightingBuffer{};
		ConstantBufferPtr					_objectBuffer{};
		ConstantBufferPtr					_cameraBuffer{};

		std::vector<CameraPtr>				_cameras{};
		std::vector<LightSourcePtr>			_lights{};

		void OnKeyDown(int key) override;

	public:
		EPickableType _pickupMode = EPickableType::PickupObject;
		float closestDist{};

		friend class EditorUIManager;
		friend class MeshManager;
	};
}

