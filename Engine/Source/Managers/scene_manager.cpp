#include "scene_manager.h"

Managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	shader_manager_ = new ShaderManager();
	shader_manager_->CreateProgram("colorShader", "Shaders\\vertex_shader.glsl", "Shaders\\fragment_shader.glsl");
	model_manager_ = new ModelManager();
}

Managers::SceneManager::~SceneManager()
{
	delete shader_manager_;
	delete model_manager_;
}

void Managers::SceneManager::NotifyBeginFrame() {
	model_manager_->Update();
}

void Managers::SceneManager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	model_manager_->Draw();
}

void Managers::SceneManager::NotifyEndFrame()
{}

void Managers::SceneManager::NotifyReshape(int width, int height, int previous_width, int previous_height)
{}