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
	/**
	 * TextureLoader Class - Engine's main texture loading object
	 */
	class TextureLoader {
	public:
		/**
		 * Loads a (2D BMP) texture from file
		 * @param filename Name of the texture file
		 * @param width Width of the texture
		 * @param height Height of the texture
		 */
		unsigned int Load2DBMPTexture(const std::string& filename, unsigned int width, unsigned int height);

	private:
		/**
		* Internal Helper for LoadTexture(...)
		* @param filename Name of the texture file
		* @param width Width of the texture
		* @param height Height of the texture
		*/
		void LoadBMPFromFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
	};

}