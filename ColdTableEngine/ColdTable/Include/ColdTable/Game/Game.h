#pragma once
#include <memory>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/Shader.h>

namespace ColdTable
{
	class Game: public Base
	{
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game() override;

		virtual void Run() final;

	private:
		void onInternalStartup();
		void onInternalCallback();

		VertexBufferPtr tempBuffer{};
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

