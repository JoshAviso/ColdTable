#pragma once

#include <stdexcept>
#include <memory>

namespace ColdTable
{
	class Base;
	class Window;
	class Display;
	class Game;

	class GraphicsEngine;
	class GraphicsDevice;
	class SwapChain;
	class DeviceContext;
	class VertexBuffer;
	class ConstantBuffer;
	class Shader;

	class Logger;

	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;

	using SwapChainPtr = std::shared_ptr<SwapChain>;
	using GraphicsDevicePtr = std::shared_ptr<GraphicsDevice>;
	using DeviceContextPtr = std::shared_ptr<DeviceContext>;
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
	using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;
	using ShaderPtr = std::shared_ptr<Shader>;
}