#pragma once

// User-defined Headers
#include "Managers\engine_manager.h"
#include "Rendering\Models\earth.h"

int main(int argc, char **argv)
{
	// Initialize the Engine Manager
	Managers::EngineManager* engine = new Managers::EngineManager();
	engine->Init();

	// Setup camera's initial position
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 3));

	// Setup Cube's Vertex and Fragment Shaders
	engine->GetShaderManager()->CreateProgram("earth_shader", "Shaders\\earth_vertex_shader.glsl", "Shaders\\earth_fragment_shader.glsl");

	// Setup Earth's Texture
	unsigned int earth_texture_id = engine->GetTextureLoader()->LoadDDSTexture("Textures\\Earth.dds");

	// Create the Cube and set its shader program
	Rendering::Models::Earth* earth = new Rendering::Models::Earth();
	earth->SetProgram(engine->GetShaderManager()->GetShader("earth_shader"));
	earth->SetTexture("earth", earth_texture_id);

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	earth->Create(1, 32, 32);

	// Add cube to Engine's Model Manager
	engine->GetModelManager()->AddModel3D("earth", earth);

	// Run the Engine
	engine->Run();

	// Delete the Engine Object when rendering loop is finished
	delete engine;
	return 0;
}