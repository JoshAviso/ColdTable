#pragma once
#include <ColdTable/Core/Core.h>
#include <ColdTable/Core/Logger.h>

#include "Logger.h"
#include "ColdTable/Math/Rect.h"

namespace ColdTable
{
	struct BaseDesc
	{
		Logger& logger;
	};

	struct WindowDesc
	{
		BaseDesc base;
		Rect size{};
	};

	struct DisplayDesc
	{
		WindowDesc window;
		GraphicsDevicePtr graphicsDevice;
	};

	struct GraphicsEngineDesc
	{
		BaseDesc base;
	};

	struct GraphicsDeviceDesc
	{
		BaseDesc base;
	};

	struct VertexBufferDesc
	{
		BaseDesc base;
		GraphicsDevicePtr graphicsDevice;
	};

	struct ConstantBufferDesc
	{
		BaseDesc base;
		GraphicsDevicePtr graphicsDevice;
	};

	struct ShaderDesc
	{
		BaseDesc base;
		GraphicsDevicePtr sourceDevice;
		wchar_t* vertexShaderSourceFile;
		wchar_t* pixelShaderSourceFile;
	};

	struct GameDesc
	{
		Rect windowSize{1280, 720};
		Logger::LogLevel logLevel = Logger::LogLevel::Error();
	};

	struct SwapChainDesc
	{
		void* windowHandle;
		Rect windowSize;
	};

	__declspec(align(16))
	struct ConstantBufferContent
	{
		unsigned int m_time;
	};
}
