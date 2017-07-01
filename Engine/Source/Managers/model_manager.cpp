// User-defined Headers
#include "model_manager.h"

// Construct some models to render
Managers::ModelManager::ModelManager() {}

// Delete models in the internal map and clear the map
Managers::ModelManager::~ModelManager() {
	// Delete 3D models
	for (auto model : model_map_3d_)
		delete model.second;
	model_map_3d_.clear();

	// Delete 2D models
	for (auto model : model_map_2d_)
		delete model.second;
	model_map_2d_.clear();
}

// Fetch model from internal map (by name) and call model.Destroy()
void Managers::ModelManager::DeleteModel2D(const std::string& model_name) {
	Rendering::ObjectInterface* model = model_map_2d_[model_name];
	model->Destroy();
	model_map_2d_.erase(model_name);
}

// Fetch model from internal map (by name) and return a const reference to this model
const Rendering::ObjectInterface& Managers::ModelManager::GetModel2D(const std::string& model_name) const {
	return (*model_map_2d_.at(model_name));
}

// Fetch model from internal map (by name) and call model.Destroy()
void Managers::ModelManager::DeleteModel3D(const std::string& model_name) {
	Rendering::ObjectInterface* model = model_map_3d_[model_name];
	model->Destroy();
	model_map_3d_.erase(model_name);
}

// Fetch model from internal map (by name) and return a const reference to this model
const Rendering::ObjectInterface& Managers::ModelManager::GetModel3D(const std::string& model_name) const {
	return (*model_map_3d_.at(model_name));
}

// Call model.Update() for each model in the internal map
void Managers::ModelManager::Update() {
	for (auto model : model_map_2d_)
		model.second->Update();
	for (auto model : model_map_3d_)
		model.second->Update();
}

// Call model.Draw() for each 2d model in the internal map
void Managers::ModelManager::Draw() {
	for (auto model : model_map_2d_)
		model.second->Draw();
}

// Call model.Draw() for each 3d model in the internal map
void Managers::ModelManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) {
	for (auto model : model_map_3d_)
		model.second->Draw(projection_matrix, view_matrix);
}

void Managers::ModelManager::AddModel2D(const std::string& model_name, Rendering::ObjectInterface* object) {
	model_map_2d_[model_name.c_str()] = object;
}

void Managers::ModelManager::AddModel3D(const std::string& model_name, Rendering::ObjectInterface* object) {
	model_map_3d_[model_name.c_str()] = object;
}