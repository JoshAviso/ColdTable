#pragma once

#include <stdexcept>
#include <memory>

namespace ColdTable
{
	class Base;
	class Logger;

	// Application Side Classes
	class Window;
	class GameLoop;
	class Display;

	// Graphics Engine Classes
	class GraphicsEngine;
	class GraphicsDevice;
	class SwapChain;
	class DeviceContext;
	class VertexBuffer;
	class ConstantBuffer;
	class Shader;

	// ECS Engine Classes
	class ECSEngine;
	class GameObject;
	class Component;
	class GameSystem;

	class Renderable;

	// Shorthand definitions
	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;

	using GraphicsDevicePtr = std::shared_ptr<GraphicsDevice>;
	using SwapChainPtr = std::shared_ptr<SwapChain>;
	using DeviceContextPtr = std::shared_ptr<DeviceContext>;
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
	using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;
	using RenderablePtr = std::shared_ptr<Renderable>;
	using ShaderPtr = std::shared_ptr<Shader>;
}