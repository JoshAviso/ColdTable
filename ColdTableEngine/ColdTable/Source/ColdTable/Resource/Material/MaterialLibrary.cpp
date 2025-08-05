#include <ColdTable/Resource/Material/MaterialLibrary.h>

#include "ColdTable/Resource/ShaderLibrary.h"

ColdTable::MaterialLibrary* ColdTable::MaterialLibrary::Instance = nullptr;
ColdTable::MaterialLibrary::MaterialLibrary()
{
}


void ColdTable::MaterialLibrary::Initialize()
{
	if (Instance != nullptr) return;
	Instance = new MaterialLibrary();

	ShaderPtr blankShader = ShaderLibrary::GetShader("BlankShader");
	MaterialPtr blankMat = MaterialLibrary::CreateMaterial("Default", blankShader, nullptr, CULL_MODE_BACK);
}

ColdTable::MaterialPtr ColdTable::MaterialLibrary::CreateMaterial(std::string key, ShaderPtr shader, TexturePtr texture, ECULL_MODE cull_mode)
{
	if (Instance == nullptr) return nullptr;
	if (Instance->_managedMaterials.count(key) >= 1) {
		Logger::Log(Logger::LogLevel::Warning, ("Trying to create existing material: " + key).c_str());
		return nullptr;
	}

	MaterialPtr material = GraphicsEngine::Instance->CreateMaterial(shader);
	material->SetCullMode(cull_mode);
	if (texture != nullptr) material->AddTexture(texture);
	Instance->_managedMaterials[key] = material;
	return material;
}

ColdTable::MaterialPtr ColdTable::MaterialLibrary::GetMaterial(std::string key)
{
	if (Instance == nullptr) return nullptr;
	if (Instance->_managedMaterials.count(key) <= 0) {
		Logger::Log(Logger::LogLevel::Warning, ("No material found with key: " + key).c_str());
		return nullptr;
	}

	return Instance->_managedMaterials[key];

}

ColdTable::String ColdTable::MaterialLibrary::GetMaterialKey(MaterialPtr mat)
{
	if (Instance == nullptr) return String();
	// Iterate over all key-value pairs in the map
	for (const auto& pair : Instance->_managedMaterials)  // Replace meshMap with your actual map variable name
	{
		if (pair.second == mat)  // Compare the MeshPtr values
		{
			return pair.first;    // Return key if value matches
		}
	}

	// Return empty string or some sentinel value if not found
	return ColdTable::String();
}
