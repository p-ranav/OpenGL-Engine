/* DDS loader written by Jon Watte 2002 */
/* Permission granted to use freely, as long as Jon Watte */
/* is held harmless for all possible damages resulting from */
/* your use or failure to use this code. */
/* No warranty is expressed or implied. Use at your own risk, */
/* or not at all. */

// User-defined Headers
#include "texture_loader.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

#define GL_COMPRESSED_RGB_S3TC_DXT1 0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5 0x83F3

struct DDSLoadInfo {
	bool compressed;
	bool swap;
	bool palette;
	unsigned int div_size;
	unsigned int block_bytes;
	GLenum internal_format;
	GLenum external_format;
	GLenum type;
};

DDSLoadInfo loadInfoDXT1 = {
	true, false, false, 4, 8, GL_COMPRESSED_RGBA_S3TC_DXT1
};
DDSLoadInfo loadInfoDXT3 = {
	true, false, false, 4, 16, GL_COMPRESSED_RGBA_S3TC_DXT3
};
DDSLoadInfo loadInfoDXT5 = {
	true, false, false, 4, 16, GL_COMPRESSED_RGBA_S3TC_DXT5
};
DDSLoadInfo loadInfoBGRA8 = {
	false, false, false, 1, 4, GL_RGBA8, GL_BGRA, GL_UNSIGNED_BYTE
};
DDSLoadInfo loadInfoBGR8 = {
	false, false, false, 1, 3, GL_RGB8, GL_BGR, GL_UNSIGNED_BYTE
};
DDSLoadInfo loadInfoBGR5A1 = {
	false, true, false, 1, 2, GL_RGB5_A1, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV
};
DDSLoadInfo loadInfoBGR565 = {
	false, true, false, 1, 2, GL_RGB5, GL_RGB, GL_UNSIGNED_SHORT_5_6_5
};
DDSLoadInfo loadInfoIndex8 = {
	false, false, true, 1, 1, GL_RGB8, GL_BGRA, GL_UNSIGNED_BYTE
};

GLuint Rendering::TextureLoader::LoadDDSTexture(std::string filename) {
	// Open DDS File
	FILE * f = fopen(filename.c_str(), "r");
	if (f == nullptr)
		return 0;

	DDSHeader hdr;
	size_t s = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int mipMapCount = 0;
	//  DDS is so simple to read, too
	fread(&hdr, sizeof(hdr), 1, f);
	assert(hdr.dwMagic == DDS_MAGIC);
	assert(hdr.dwSize == 124);

	if (hdr.dwMagic != DDS_MAGIC || hdr.dwSize != 124 ||
		!(hdr.dwFlags & DDSD_PIXELFORMAT) || !(hdr.dwFlags & DDSD_CAPS)) {
		return 0;
	}

	unsigned int xSize = hdr.dwWidth;
	unsigned int ySize = hdr.dwHeight;
	assert(!(xSize & (xSize - 1)));
	assert(!(ySize & (ySize - 1)));

	DDSLoadInfo * load_info;

	if (PF_IS_DXT1(hdr.sPixelFormat)) {
		load_info = &loadInfoDXT1;
	}
	else if (PF_IS_DXT3(hdr.sPixelFormat)) {
		load_info = &loadInfoDXT3;
	}
	else if (PF_IS_DXT5(hdr.sPixelFormat)) {
		load_info = &loadInfoDXT5;
	}
	else if (PF_IS_BGRA8(hdr.sPixelFormat)) {
		load_info = &loadInfoBGRA8;
	}
	else if (PF_IS_BGR8(hdr.sPixelFormat)) {
		load_info = &loadInfoBGR8;
	}
	else if (PF_IS_BGR5A1(hdr.sPixelFormat)) {
		load_info = &loadInfoBGR5A1;
	}
	else if (PF_IS_BGR565(hdr.sPixelFormat)) {
		load_info = &loadInfoBGR565;
	}
	else if (PF_IS_INDEX8(hdr.sPixelFormat)) {
		load_info = &loadInfoIndex8;
	}
	else {
		return 0;
	}

	x = xSize;
	y = ySize;
	bool hasMipmaps_;
	GLenum format, cFormat;
	unsigned int size;

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	mipMapCount = (hdr.dwFlags & DDSD_MIPMAPCOUNT) ? hdr.dwMipMapCount : 1;
	if (mipMapCount > 1) {
		hasMipmaps_ = true;
	}
	if (load_info->compressed) {
		size_t size = std::max(load_info->div_size, x) / load_info->div_size * 
			std::max(load_info->div_size, y) / load_info->div_size * load_info->block_bytes;
		assert(size == hdr.dwPitchOrLinearSize);
		assert(hdr.dwFlags & DDSD_LINEARSIZE);
		unsigned char * data = (unsigned char *)malloc(size);
		if (!data) {
			return 0;
		}
		format = cFormat = load_info->internal_format;
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			fread(data, 1, size, f);
			glCompressedTexImage2D(GL_TEXTURE_2D, ix, load_info->internal_format, x, y, 
				0, static_cast<GLsizei>(size), data);
			x = (x + 1) >> 1;
			y = (y + 1) >> 1;
			size = std::max(load_info->div_size, x) / load_info->div_size * 
				std::max(load_info->div_size, y) / load_info->div_size * load_info->block_bytes;
		}
		free(data);
	}
	else if (load_info->palette) {
		//  currently, we unpack palette into BGRA
		//  I'm not sure we always get pitch...
		assert(hdr.dwFlags & DDSD_PITCH);
		assert(hdr.sPixelFormat.dwRGBBitCount == 8);
		size_t size = hdr.dwPitchOrLinearSize * ySize;
		//  And I'm even less sure we don't get padding on the smaller MIP levels...
		assert(size == x * y * load_info->block_bytes);
		format = load_info->external_format;
		cFormat = load_info->internal_format;
		unsigned char * data = (unsigned char *)malloc(size);
		unsigned int palette[256];
		unsigned int * unpacked = (unsigned int *)malloc(size * sizeof(unsigned int));
		fread(palette, 4, 256, f);
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			fread(data, 1, size, f);
			for (unsigned int zz = 0; zz < size; ++zz) {
				unpacked[zz] = palette[data[zz]];
			}
			glPixelStorei(GL_UNPACK_ROW_LENGTH, y);
			glTexImage2D(GL_TEXTURE_2D, ix, load_info->internal_format, x, y, 
				0, load_info->external_format, load_info->type, unpacked);
			x = (x + 1) >> 1;
			y = (y + 1) >> 1;
			size = x * y * load_info->block_bytes;
		}
		free(data);
		free(unpacked);
	}
	else {
		if (load_info->swap) {
			glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
		}
		size = x * y * load_info->block_bytes;
		format = load_info->external_format;
		cFormat = load_info->internal_format;
		unsigned char * data = (unsigned char *)malloc(size);
		//fixme: how are MIP maps stored for 24-bit if pitch != ySize*3 ?
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			fread(data, 1, size, f);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, y);
			glTexImage2D(GL_TEXTURE_2D, ix, load_info->internal_format, x, y, 
				0, load_info->external_format, load_info->type, data);
			x = (x + 1) >> 1;
			y = (y + 1) >> 1;
			size = x * y * load_info->block_bytes;
		}
		free(data);
		glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount - 1);

	return true;
}

// Loead BMP texture from file
unsigned int Rendering::TextureLoader::Load2DBMPTexture(const std::string& filename, unsigned int width, unsigned int height) {
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
void Rendering::TextureLoader::LoadBMPFromFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data) {
	// Read from file
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good()) {
		std::cout << "Texture Loader: Cannot open texture file ";
		width = 0;
		height = 0;
		return;
	}

	// Reads the headers
	Texture::BMPHeader h; Texture::BMPHeaderInfo h_info;
	file.read((char*)&(h.type[0]), sizeof(char));
	file.read((char*)&(h.type[1]), sizeof(char));
	file.read((char*)&(h.f_length), sizeof(int));
	file.read((char*)&(h.reserved1), sizeof(short));
	file.read((char*)&(h.reserved2), sizeof(short));
	file.read((char*)&(h.off_bits), sizeof(int));
	file.read((char*)&(h_info), sizeof(Texture::BMPHeaderInfo));

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