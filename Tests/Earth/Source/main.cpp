#pragma once

// User-defined Headers
#include "Managers\engine_manager.h"
#include "Rendering\Models\skybox.h"
#include "Rendering\Models\earth.h"
#include "Rendering\Texture\stb_image.h"

// External Headers
#include "SOIL2.h"

GLuint LoadDDSTextureUsingSOIL(const std::string& file)
{
	GLuint textureID = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

unsigned int LoadCubeMapTexture(std::vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
			spdlog::get("console")->info("Cube Map Texture Face {0} successfully loaded!", faces[i]);
		}
		else {
			spdlog::get("console")->error("Failed to load cube map face at path : {0}", faces[i]);
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

int main(int argc, char **argv)
{
	// Initialize the Engine Manager
	Managers::EngineManager* engine = new Managers::EngineManager();
	engine->Init();

	// Setup camera's initial position
	engine->GetCameraManager()->SetPosition(glm::vec3(0, 0, 10));

	// Setup Earth's Vertex and Fragment Shaders
	engine->GetShaderManager()->CreateProgram("earth_shader", "Shaders\\earth_vertex_shader.glsl", "Shaders\\earth_fragment_shader.glsl");
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
	unsigned int skybox_texture_id = LoadCubeMapTexture(faces);
	skybox->SetTexture("skybox_texture", skybox_texture_id);
	skybox->Create();

	// Create the Earth and set its shader program
	Rendering::Models::Earth* earth = new Rendering::Models::Earth();

	// Set the Earth's Program
	earth->SetProgram(engine->GetShaderManager()->GetShader("earth_shader"));
	
	// Setup Earth's Texture
	GLuint earth_texture = LoadDDSTextureUsingSOIL("Textures\\Earth.dds");
	earth->SetTexture("earth", earth_texture);

	// Create a icosphere of radius 1 with 32 slices and 32 stacks
	earth->Create(0.3f, 32, 32);

	// Add cube to Engine's Model Manager
	engine->GetModelManager()->AddModel3D("skybox", skybox);
	engine->GetModelManager()->AddModel3D("earth", earth);

	// Run the Engine
	engine->Run();

	// Delete the Engine Object when rendering loop is finished
	delete engine;
	return 0;
}