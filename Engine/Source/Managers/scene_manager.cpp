//Scene_Manager.cpp
#include "scene_manager.h"

Managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	shader_manager_ = new ShaderManager();
	shader_manager_->CreateProgram("colorShader", "Shaders\\vertex_shader.glsl", "Shaders\\fragment_shader.glsl");
}

Managers::SceneManager::~SceneManager()
{
	delete shader_manager_;
}

void Managers::SceneManager::NotifyBeginFrame()
{}

void Managers::SceneManager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Managers::SceneManager::NotifyEndFrame()
{}

void Managers::SceneManager::NotifyReshape(int width, int height, int previous_width, int previous_height)
{}