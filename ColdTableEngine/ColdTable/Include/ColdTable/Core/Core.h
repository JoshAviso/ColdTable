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
	class IndexBuffer;
	class ConstantBuffer;
	class EngineShader;
	class ComputeShader;

	// ECS Engine Classes
	class ECSEngine;
	class GameObject;
	class Component;
	class GameSystem;

	class Renderable;
	class Quad;

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
	using IndexBufferPtr = std::shared_ptr<IndexBuffer>;
	using RenderablePtr = std::shared_ptr<Renderable>;
	using ShaderPtr = std::shared_ptr<EngineShader>;
	using ComputeShaderPtr = std::shared_ptr<ComputeShader>;
	using QuadPtr = std::shared_ptr<Quad>;

	class Cube;
	using CubePtr = std::shared_ptr<Cube>;

	class IEditorPickable;
	using IEditorPickablePtr = std::shared_ptr<IEditorPickable>;
	
	class InputSystem;
	using InputSystemPtr = std::shared_ptr<InputSystem>;

	class IInputListener;
	using InputListenerPtr = std::shared_ptr<IInputListener>;

	class IUIScreen;
	using UIScreenPtr = std::shared_ptr<IUIScreen>;

	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;

	class Resource;
	using ResourcePtr = std::shared_ptr<Resource>;

	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;

	class Material;
	using MaterialPtr = std::shared_ptr<Material>;

	class LightSource;
	using LightSourcePtr = std::shared_ptr<LightSource>;

	class DirectionalLight;
	using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;

	class PointLight;
	using PointLightPtr = std::shared_ptr<PointLight>;

	class SpotLight;
	using SpotLightPtr = std::shared_ptr<SpotLight>;

	class Mesh;
	using MeshPtr = std::shared_ptr<Mesh>;

	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
}