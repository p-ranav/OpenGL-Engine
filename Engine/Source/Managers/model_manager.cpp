// User-defined Headers
#include "model_manager.h"

// Construct some models to render
Managers::ModelManager::ModelManager()
{
	//triangle game object
	Rendering::Models::Triangle* triangle = new Rendering::Models::Triangle();
	triangle->SetProgram(ShaderManager::GetShader("colorShader"));
	triangle->Create();
	model_map_["triangle"] = triangle;

	// quad game object
	Rendering::Models::Quad* quad = new Rendering::Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("colorShader"));
	quad->Create();
	model_map_["quad"] = quad;
}

// Delete models in the internal map and clear the map
Managers::ModelManager::~ModelManager()
{
	for (auto model : model_map_)
		delete model.second;
	model_map_.clear();
}

// Fetch model from internal map (by name) and call model.Destroy()
void Managers::ModelManager::DeleteModel(const std::string& model_name)
{
	Rendering::ObjectInterface* model = model_map_[model_name];
	model->Destroy();
	model_map_.erase(model_name);
}

// Fetch model from internal map (by name) and return a const reference to this model
const Rendering::ObjectInterface& Managers::ModelManager::GetModel(const std::string& model_name) const
{
	return (*model_map_.at(model_name));
}

// Call model.Update() for each model in the internal map
void Managers::ModelManager::Update()
{
	for (auto model : model_map_)
		model.second->Update();
}

// Call model.Draw() for each model in the internal map
void Managers::ModelManager::Draw()
{
	for (auto model : model_map_)
		model.second->Draw();
}