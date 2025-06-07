#pragma once
#include <memory>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/EngineShader.h>

#include "ColdTable/Graphics/Renderables/Quad.h"

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

		ShaderPtr tempShader{};
		ConstantBufferPtr tempConstantBuffer{};

		float tempVertexArray[36];

	private:
		std::unique_ptr<GraphicsEngine> _graphicsEngine{};
		std::unique_ptr<Display> _display{};
		bool _isRunning{ true };

	private:
		QuadPtr tempQ1{};
		QuadPtr tempQ2{};
		QuadPtr tempQ3{};


	private:
		Rect tempWindowSize{};
		ComputeShaderPtr tempComputeShader;
	};
}

