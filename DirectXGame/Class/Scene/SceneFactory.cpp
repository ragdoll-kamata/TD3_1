#include "SceneFactory.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Clear.h"
#include "Over.h"

Scene* SceneFactory::CreateScene(SceneName name) { 
	std::map<SceneName, Scene*> SceneMap{
	    {SceneName::TitleScene, new TitleScene()},
	    {SceneName::GameScene,  new GameScene()},
	    {SceneName::ClearScene, new Clear()},
	    {SceneName::OverScene,  new Over() },
	};

	return SceneMap[name];
}
