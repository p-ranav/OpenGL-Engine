#pragma once

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