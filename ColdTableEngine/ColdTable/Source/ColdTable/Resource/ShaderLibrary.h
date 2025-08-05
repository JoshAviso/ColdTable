#pragma once
#include <map>
#include <string>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/GraphicsEngine.h>

namespace ColdTable
{
	class ShaderLibrary
	{
	private:
		ShaderLibrary();
		static ShaderLibrary* Instance;
		std::map<std::string, ShaderPtr> _internalShaders;
	
	public:
		static void Initialize();
		static ShaderPtr CreateShader(std::string key, const wchar_t* vertex_shader_src, const wchar_t* pixel_shader_src);
		static ShaderPtr GetShader(std::string key);
	};
}

