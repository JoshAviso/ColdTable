#pragma once
#include <intsafe.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Core/Logger.h>

#include "Logger.h"
#include "ColdTable/Math/Rect.h"
#include <ColdTable/Graphics/GraphicsEnums.h>
#include <ColdTable/Math/Vertex.h>

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

	struct RenderableDesc
	{
		BaseDesc base;
		Vertex* vertexList;
		UINT vertexCount;
		EGeometryDrawmode drawMode;
		ShaderPtr shader;
	};

	struct QuadDesc
	{
		BaseDesc base;
		ShaderPtr shader;
		Vertex vert1;
		Vertex vert2;
		Vertex vert3;
		Vertex vert4;
	};

	struct VertexBufferDesc
	{
		BaseDesc base;
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
		const wchar_t* vertexShaderSourceFile;
		const wchar_t* pixelShaderSourceFile;
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
