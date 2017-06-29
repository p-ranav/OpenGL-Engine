// User-defined Headers
#include "scene_manager.h"

// SceneManager Default Constructor - Construct shader manager and model manager here
Managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	shader_manager_ = new ShaderManager();
	shader_manager_->CreateProgram("colorShader", "Shaders\\vertex_shader.glsl", "Shaders\\fragment_shader.glsl");
	model_manager_ = new ModelManager();
}

// Delete shader manager and model manager here
Managers::SceneManager::~SceneManager()
{
	delete shader_manager_;
	delete model_manager_;
}

/**
 * Call model manager's Update() which updates every model in the
 * model manager's internal map
 */ 
void Managers::SceneManager::NotifyBeginFrame() {
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
}

// Nothing to do here (for now)
void Managers::SceneManager::NotifyEndFrame()
{}

// Nothing to do here (for now)
void Managers::SceneManager::NotifyReshape(int width, int height, int previous_width, int previous_height)
{}