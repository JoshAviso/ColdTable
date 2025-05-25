#pragma once
#include <memory>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/Shader.h>

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

		RenderablePtr tempRenderable{};
		RenderablePtr tempQuad1{};
		RenderablePtr tempQuad2{};
		RenderablePtr tempQuad3{};
		ShaderPtr tempShader{};
		ConstantBufferPtr tempConstantBuffer{};

	private:
		std::unique_ptr<Logger> _loggerPtr{};
		std::unique_ptr<GraphicsEngine> _graphicsEngine{};
		std::unique_ptr<Display> _display{};
		bool _isRunning{ true };

	private:
		Rect tempWindowSize{};
	};
}

