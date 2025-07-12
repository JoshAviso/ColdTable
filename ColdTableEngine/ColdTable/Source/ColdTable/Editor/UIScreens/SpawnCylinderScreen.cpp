#include "SpawnCylinderScreen.h"

void ColdTable::SpawnCylinderScreen::SpawnCylinder()
{
	GameObjectPtr sylinder = GameObjectManager::CreateGameObject("Cylinder");
	CylinderDesc cylinderDesc{
		_sideCount,
		_length,
		_radius,
		_isHorizontal,
	};
	sylinder->renderable = std::make_shared<Cylinder>(cylinderDesc, GraphicsEngine::Instance->CreateIndexBuffer(), ShaderLibrary::GetShader("BlankShader"));
}
