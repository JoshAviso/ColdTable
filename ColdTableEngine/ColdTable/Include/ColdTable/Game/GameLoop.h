#pragma once
#include <memory>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/EngineShader.h>

#include "ColdTable/Graphics/Renderables/Quad.h"
#include "ColdTable/Input/IInputListener.h"
#include "ColdTable/Resource/Mesh/MeshManager.h"
#include "ColdTable/Resource/Texture/TextureManager.h"
#include <ColdTable/Editor/UIScreens/AboutScreen.h>

#include "DearImGUI/imgui.h"
#include "DearImGUI/imgui_impl_dx11.h"
#include "DearImGUI/imgui_impl_win32.h"
#include "DearImGUI/imgui.h"

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
		ConstantBufferPtr tempLightBuffer{};
		ConstantBufferPtr tempObjectBuffer{};

		float tempVertexArray[36];

	private:
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

