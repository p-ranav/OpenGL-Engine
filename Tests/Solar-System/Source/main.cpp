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
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 300));

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

	std::map<std::string, std::string> textures = {
		std::make_pair("sun", "Textures\\Sun.dds"),
		std::make_pair("mercury", "Textures\\Mercury.dds"),
		std::make_pair("venus", "Textures\\Venus.dds"),
		std::make_pair("earth", "Textures\\Earth.dds"),
		std::make_pair("moon", "Textures\\Moon.dds"),
		std::make_pair("mars", "Textures\\Mars.dds"),
		std::make_pair("jupiter", "Textures\\Jupiter.dds"),
		std::make_pair("saturn", "Textures\\Saturn.dds"),
		std::make_pair("uranus", "Textures\\Uranus.dds"),
		std::make_pair("neptune", "Textures\\Neptune.dds"),
	};

	// Load and Set Textures from Textures Map
	for (auto const& texture : textures)
		system->SetTexture(texture.first, Rendering::Utilities::LoadDDSTexture(texture.second));

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