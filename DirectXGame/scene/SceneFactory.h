#pragma once
#include "Scene.h"
#include <map>
#include "SceneName.h"

class SceneFactory {
public:

	Scene* CreateScene(SceneName name);

private:
	
};
