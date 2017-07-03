#pragma once

// User-defined Headers
#include "Managers\engine_manager.h"
#include "Rendering\Models\cube.h"
#include "Utilities\utilities.h"

int main(int argc, char **argv) 
{
	// Initialize the Engine Manager
	Managers::EngineManager* engine = new Managers::EngineManager();
	engine->Init();

	// Setup camera's initial position
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 5));

	// Setup Cube's Vertex and Fragment Shaders
	engine->GetShaderManager()->CreateProgram("cubeShader", "Shaders\\cube_vertex_shader.glsl", "Shaders\\cube_fragment_shader.glsl");

	// Create the Cube and set its shader program
	Rendering::Models::Cube* cube = new Rendering::Models::Cube();
	cube->SetProgram(engine->GetShaderManager()->GetShader("cubeShader"));
	cube->Create();

	unsigned int texture = Rendering::Utilities::LoadBMPTexture("Textures\\Crate.bmp");
	cube->SetTexture("Crate", texture);

	// Add cube to Engine's Model Manager
	engine->GetModelManager()->AddModel3D("cube", cube);

	// Run the Engine
	engine->Run();

	// Delete the Engine Object when rendering loop is finished
	delete engine;
	return 0;
}
