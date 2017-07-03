// User-defined Headers
#include "cube.h"

// Define PI for local use
#define PI 3.14159265

// Setup cube vertices, colors, vao and vbo
void Rendering::Models::Cube::Create() {
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices = {
		// Front Face
		0, 1, 2, 0, 2, 3,
		// Right Face
		4, 5, 6, 4, 6, 7,
		// Back Face
		8, 9, 10, 8, 10, 11,
		// Left Face
		12, 13, 14, 12, 14, 15,
		// Top Face
		16, 17, 18, 16, 18, 19,
		// Bottom Face
		20, 21, 22, 20, 22, 23 };

	// Front Face Vertices + Texture Coordinates
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(0, 1)));

	// Right Face Vertices + Texture Coordinates
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)));

	// Back Face Vertices + Texture Coordinates
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));

	// Left Face Vertices + Texture Coordinates
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));

	// Top Face Vertices + Texture Coordinates
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(0, 1)));

	// Bottom Face Vertices + Texture Coordinates
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 1)));

	// Bind vbo
	glGenBuffers(1, &vbo);
	// Array Buffer Size for Vertices = Number of Vertices * size of each vertex 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	// Bind ibo
	glGenBuffers(1, &ibo);
	// Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	rotation_speed = glm::vec3(90.0, 90.0, 90.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);
}

// Nothing to update. Boring cube is boring
void Rendering::Models::Cube::Update() {
	rotation = 0.01f * rotation_speed + rotation;
	rotation_sin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);
}

// Draw cube and incorporate rotation
void Rendering::Models::Cube::Draw(Managers::CameraManager* camera) {
	// Map shader variables
	glUseProgram(program);

	// Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("Crate"));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniform3f(glGetUniformLocation(program, "rotation"), rotation_sin.x, rotation_sin.y, rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &(camera->GetViewMatrix())[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &camera->GetProjectionMatrix()[0][0]);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

namespace Rendering
{
	namespace Texture
	{
		/**
		* BMPHeader Structure
		*/
		struct BMPHeader
		{
			unsigned char type[2];
			int f_length;
			short reserved1;
			short reserved2;
			int off_bits;
		};

		/**
		* BMPHeader Info
		*/
		struct BMPHeaderInfo
		{
			int size;
			int width;
			int height;
			short planes;
			short bit_count;
			int compresion;
			int size_image;
			int x_pexels_per_meter;
			int y_pexels_per_meter;
			int clr_used;
			int clr_important;
		};
	}
}

// Loead BMP texture from file
unsigned int Load2DBMPTexture(const std::string& filename, unsigned int width, unsigned int height) {
	unsigned char* data;
	// Internal helper
	LoadBMPFromFile(filename, width, height, data);

	// Create the OpenGL texture
	unsigned int gl_texture_object;
	glGenTextures(1, &gl_texture_object);
	glBindTexture(GL_TEXTURE_2D, gl_texture_object);

	// Filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	// When we work with textures of sizes not divisible by 4 we have to use the line reader
	// which loads the textures in OpenGL so as it can work with a 1 alligned memory (default is 4)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generates texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Eliminates the array from the RAM
	delete data;

	// Creates the mipmap hierarchy
	glGenerateMipmap(GL_TEXTURE_2D);

	// Returns the texture object
	return gl_texture_object;
}

// Internal helper for loading BMP
void LoadBMPFromFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data) {
	// Read from file
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()) {
		spdlog::get("console")->error("Cannot open texture file {0}", filename);
		width = 0;
		height = 0;
		return;
	}

	// Reads the headers
	Rendering::Texture::BMPHeader h; 
	Rendering::Texture::BMPHeaderInfo h_info;
	file.read((char*)&(h.type[0]), sizeof(char));
	file.read((char*)&(h.type[1]), sizeof(char));
	file.read((char*)&(h.f_length), sizeof(int));
	file.read((char*)&(h.reserved1), sizeof(short));
	file.read((char*)&(h.reserved2), sizeof(short));
	file.read((char*)&(h.off_bits), sizeof(int));
	file.read((char*)&(h_info), sizeof(Rendering::Texture::BMPHeaderInfo));

	// Assigning memory (a pixel has 3 components, R, G, B)
	data = new unsigned char[h_info.width*h_info.height * 3];

	// Check if the line contains 4 byte groups
	long padd = 0;
	if ((h_info.width * 3) % 4 != 0) padd = 4 - (h_info.width * 3) % 4;

	width = h_info.width;
	height = h_info.height;

	long pointer;
	unsigned char r, g, b;

	// Reading the matrix
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			// The BMP component order in the pixel is b, g, r (in Windows)
			file.read((char*)&b, 1);
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);

			pointer = (i*width + j) * 3;
			data[pointer] = r;
			data[pointer + 1] = g;
			data[pointer + 2] = b;
		}
		file.seekg(padd, std::ios_base::cur);
	}
	file.close();
}
