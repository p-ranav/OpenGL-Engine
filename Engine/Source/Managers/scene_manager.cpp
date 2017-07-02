// User-defined Headers
#include "scene_manager.h"

// External Headers
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"

// SceneManager Default Constructor - Construct shader manager and model manager here
Managers::SceneManager::SceneManager() {
	glEnable(GL_DEPTH_TEST);
}

// Delete shader manager and model manager here
Managers::SceneManager::~SceneManager() {
	delete shader_manager_;
	delete model_manager_;
}

/**
 * Call model manager's Update() which updates every model in the
 * model manager's internal map
 */ 
void Managers::SceneManager::NotifyBeginFrame() {
	// Translate camera to handle key press
	float cameraSpeed = 0.1f;
	camera_manager_->Translate(glm::vec3(Managers::CameraManager::KEY_D - Managers::CameraManager::KEY_A, 
		Managers::CameraManager::KEY_Q - Managers::CameraManager::KEY_E, 
		Managers::CameraManager::KEY_S - Managers::CameraManager::KEY_W) * cameraSpeed);
	if (Managers::CameraManager::MOUSE_STATE == 0) {
		camera_manager_->Rotate(Managers::CameraManager::MOUSE_ROTATION_X);
		camera_manager_->Rotate(Managers::CameraManager::MOUSE_ROTATION_Y);
	}
	model_manager_->Update();
}

/**
 * Clear OpenGL bits and call the model manager's Draw() which draws
 * every model in the model manager's internal map
 */
void Managers::SceneManager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	model_manager_->Draw();
	model_manager_->Draw(camera_manager_->GetProjectionMatrix(), 
		camera_manager_->GetViewMatrix());
}

// Nothing to do here (for now)
void Managers::SceneManager::NotifyEndFrame()
{}

// Nothing to do here (for now)
void Managers::SceneManager::NotifyReshape(int width, int height, int previous_width, int previous_height) {
	float aspect_ratio = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near_value = 0.1f, far_value = 100.0f;
	camera_manager_->SetProjectionMatrix(angle, aspect_ratio, near_value, far_value);
	camera_manager_->SetViewport(0, 0, width, height);
}

// Return internal model manager
Managers::ModelManager* Managers::SceneManager::GetModelManager() {
	return model_manager_;
}

// Set the shader manager
void Managers::SceneManager::SetShaderManager(Managers::ShaderManager*& shader_manager) {
	shader_manager_ = shader_manager;
}

// Set the model manager
void Managers::SceneManager::SetModelManager(Managers::ModelManager*& model_manager) {
	model_manager_ = model_manager;
}

// Set the camera manager
void Managers::SceneManager::SetCameraManager(Managers::CameraManager*& camera_manager) {
	camera_manager_ = camera_manager;
}