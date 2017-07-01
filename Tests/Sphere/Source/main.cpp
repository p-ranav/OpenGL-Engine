#pragma once

// User-defined Headers
#include "Managers\engine_manager.h"
#include "Rendering\Models\sphere.h"

int main(int argc, char **argv)
{
	// Initialize the Engine Manager
	Managers::EngineManager* engine = new Managers::EngineManager();
	engine->Init();

	// Setup camera's initial position
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 5));

	// Setup Cube's Vertex and Fragment Shaders
	engine->GetShaderManager()->CreateProgram("sphere_shader", "Shaders\\sphere_vertex_shader.glsl", "Shaders\\sphere_fragment_shader.glsl");

	// Create the Cube and set its shader program
	Rendering::Models::Sphere* sphere = new Rendering::Models::Sphere();
	sphere->SetProgram(engine->GetShaderManager()->GetShader("sphere_shader"));

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	sphere->Create(1, 32, 32);

	// Add cube to Engine's Model Manager
	engine->GetModelManager()->AddModel3D("sphere", sphere);

	// Run the Engine
	engine->Run();

	// Delete the Engine Object when rendering loop is finished
	delete engine;
	return 0;
}