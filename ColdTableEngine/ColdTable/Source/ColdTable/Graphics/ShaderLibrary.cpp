#include "ShaderLibrary.h"

ColdTable::ShaderLibrary* ColdTable::ShaderLibrary::Instance = nullptr;
ColdTable::ShaderLibrary::ShaderLibrary()
{
}
bool ColdTable::ShaderLibrary::CreateShader(std::string key, const wchar_t* vertex_shader_src, const wchar_t* pixel_shader_src)
{
	if (Instance == nullptr) Instance = new ShaderLibrary();
	if (Instance->_internalShaders.count(key) >= 1) {
		Logger::Log(Logger::LogLevel::Warning, ("Trying to create existing shader: " + key).c_str());
		return false;
	}

	ShaderPtr shader = GraphicsEngine::Instance->CreateShader(vertex_shader_src, pixel_shader_src);
	Instance->_internalShaders[key] = shader;
	return true;
}

ColdTable::ShaderPtr ColdTable::ShaderLibrary::GetShader(std::string key)
{
	if (Instance == nullptr) Instance = new ShaderLibrary();
	if (Instance->_internalShaders.count(key) <= 0) {
		Logger::Log(Logger::LogLevel::Warning, ("No shader found with key: " + key).c_str());
		return nullptr;
	}

	return Instance->_internalShaders[key];

}
