#pragma once
#include <memory>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/EngineShader.h>

#include "ColdTable/Graphics/Renderables/Quad.h"
#include "ColdTable/Input/IInputListener.h"
#include "ColdTable/Resource/Texture/TextureManager.h"

namespace ColdTable
{
	class GameLoop: public Base
	{
	public:
		explicit GameLoop(const GameDesc& desc);
		virtual ~GameLoop() override;

		virtual void Run() final;

	private:
		void onInternalStartup();
		void onInternalCallback();

	private:
		ShaderPtr tempShader{};
		ConstantBufferPtr tempLightBuffer{};

		float tempVertexArray[36];

	private:
		std::unique_ptr<GraphicsEngine> _graphicsEngine{};
		std::unique_ptr<Display> _display{};
		bool _isRunning{ true };

		TextureManager* _textureManager{};

	private:
		QuadPtr tempQ1{};
		QuadPtr tempQ2{};
		QuadPtr tempQ3{};

		CameraPtr tempCam{};


	private:
		Rect tempWindowSize{};
		ComputeShaderPtr tempComputeShader;
	};
}

