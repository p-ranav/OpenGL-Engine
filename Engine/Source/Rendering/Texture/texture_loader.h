#pragma once
// User-defined Headers
#include "bmp_headers.h"

// External Headers
#include "glew.h"

// System Headers
#include <fstream>
#include <iostream>
#include <string>

namespace Rendering
{
	class TextureLoader
	{
	public:
		unsigned int LoadTexture(const std::string& filename, unsigned int width, unsigned int height);

	private:
		void LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
	};

}