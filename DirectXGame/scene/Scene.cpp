#include "Scene.h"

Scene::~Scene() {}

void Scene::Initialize(Blackout* blackout) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	blackout_ = blackout;

	Initialize2();
}

void Scene::Initialize2() {}

void Scene::Update()
{
}

void Scene::Draw()
{}

void Scene::Destroy() {}
