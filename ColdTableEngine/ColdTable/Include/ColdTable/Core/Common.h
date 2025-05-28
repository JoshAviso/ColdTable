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

	};

	struct WindowDesc
	{
		BaseDesc base;
		Rect size{};
	};

	struct DisplayDesc
	{
		BaseDesc base;
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

	struct ECSEngineDesc
	{
		BaseDesc base;
	};

	struct RenderableDesc
	{
		Vertex* vertexList;
		UINT vertexCount;
		EGeometryDrawmode drawMode;
		ShaderPtr shader;
	};

	struct QuadDesc
	{
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
		GraphicsDevicePtr sourceDevice;
		const wchar_t* vertexShaderSourceFile;
		const wchar_t* pixelShaderSourceFile;
	};

	struct GameDesc
	{
		BaseDesc base;
		Rect windowSize{1280, 720};
		Logger::LogLevel logLevel = Logger::LogLevel::Error();
	};

	struct SwapChainDesc
	{
		BaseDesc base;
		void* windowHandle;
		Rect windowSize;
	};

	__declspec(align(16))
	struct ConstantBufferContent
	{
		unsigned int m_time;
	};
}
