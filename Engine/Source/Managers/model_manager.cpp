#include "model_manager.h"

using namespace Managers;
using namespace Rendering;

ModelManager::ModelManager()
{
	//triangle game object
	Models::Triangle* triangle = new Models::Triangle();
	triangle->SetProgram(ShaderManager::GetShader("colorShader"));
	triangle->Create();
	model_map_["triangle"] = triangle;

	// quad game object
	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("colorShader"));
	quad->Create();
	model_map_["quad"] = quad;
}

ModelManager::~ModelManager()
{
	//auto -it's a map iterator
	for (auto model : model_map_)
	{
		delete model.second;
	}
	model_map_.clear();
}

void ModelManager::DeleteModel(const std::string& gameModelName)
{
	ObjectInterface* model = model_map_[gameModelName];
	model->Destroy();
	model_map_.erase(gameModelName);
}

const ObjectInterface& ModelManager::GetModel(const std::string& gameModelName) const
{
	return (*model_map_.at(gameModelName));
}

void ModelManager::Update()
{
	//auto -it's a map iterator
	for (auto model : model_map_)
	{
		model.second->Update();
	}
}

void ModelManager::Draw()
{
	//auto -it's a map iterator
	for (auto model : model_map_)
	{
		model.second->Draw();
	}
}