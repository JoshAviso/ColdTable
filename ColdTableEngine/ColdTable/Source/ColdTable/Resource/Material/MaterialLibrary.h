#pragma once
#include <map>
#include <string>
#include <unordered_map>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/GraphicsEngine.h>

namespace ColdTable
{
	class MaterialLibrary
	{
	private:
		MaterialLibrary();
		static MaterialLibrary* Instance;
		std::unordered_map<std::string, MaterialPtr> _managedMaterials;
		friend class MaterialComponent;
	
	public:
		static void Initialize();
		static MaterialPtr CreateMaterial(std::string key, ShaderPtr shader, TexturePtr texture, ECULL_MODE cull_mode);
		static MaterialPtr GetMaterial(std::string key);
		static String GetMaterialKey(MaterialPtr mat);
	};
}

