#pragma once

// User-defined Headers
#include "Managers\engine_manager.h"
#include "Rendering\Models\skybox.h"
#include "Rendering\Models\solar_system.h"
#include "Utilities\utilities.h"

int main(int argc, char **argv)
{
	// Initialize the Engine Manager
	Managers::EngineManager* engine = new Managers::EngineManager();
	engine->Init();

	// Setup camera's initial position
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 10));

	// Setup Earth's Vertex and Fragment Shaders
	engine->GetShaderManager()->CreateProgram("earth_shader", "Shaders\\earth_vertex_shader.glsl", "Shaders\\earth_fragment_shader.glsl");
	engine->GetShaderManager()->CreateProgram("sun_shader", "Shaders\\sun_vertex_shader.glsl", "Shaders\\sun_fragment_shader.glsl");
	engine->GetShaderManager()->CreateProgram("skybox_shader", "Shaders\\skybox_vertex_shader.glsl", "Shaders\\skybox_fragment_shader.glsl");

	// Create the skybox and set its shader program
	Rendering::Models::Skybox* skybox = new Rendering::Models::Skybox();

	// Set the Skybox's Program
	skybox->SetProgram(engine->GetShaderManager()->GetShader("skybox_shader"));

	// Load Cube-Map for Skybox
	std::vector<std::string> faces = {
		"Textures\\SkyboxPositiveX.png",
		"Textures\\SkyboxNegativeX.png",
		"Textures\\SkyboxPositiveY.png",
		"Textures\\SkyboxNegativeY.png",
		"Textures\\SkyboxPositiveZ.png",
		"Textures\\SkyboxNegativeZ.png"
	};
	unsigned int skybox_texture_id = Rendering::Utilities::LoadCubeMapTexture(faces);
	skybox->SetTexture("skybox_texture", skybox_texture_id);
	skybox->Create();

	// Create the Earth and set its shader program
	Rendering::Models::SolarSystem* system = new Rendering::Models::SolarSystem();

	GLuint sun_texture = Rendering::Utilities::LoadDDSTexture("Textures\\Sun.dds");
	system->SetTexture("sun", sun_texture);

	GLuint earth_texture = Rendering::Utilities::LoadDDSTexture("Textures\\Earth.dds");
	system->SetTexture("earth", earth_texture);

	GLuint moon_texture = Rendering::Utilities::LoadDDSTexture("Textures\\Moon.dds");
	system->SetTexture("moon", moon_texture);

	// Set the Earth's Program
	system->SetProgram(engine->GetShaderManager()->GetShader("earth_shader"));

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	system->Create(0.3f, 32, 32);

	// Add cube to Engine's Model Manager
	engine->GetModelManager()->AddModel3D("skybox", skybox);
	engine->GetModelManager()->AddModel3D("system", system);

	// Run the Engine
	engine->Run();

	// Delete the Engine Object when rendering loop is finished
	delete engine;
	return 0;
}