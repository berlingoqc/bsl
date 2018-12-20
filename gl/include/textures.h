#ifndef TEXTURE_H
#define TEXTURE_H

#include "header.h"

#include <SOIL/SOIL.h>
#include <vector>


namespace bsl::gl
{

	#define ERROR_TEXTURE 999999

	typedef unsigned char uchar;

	struct TextureFileInfo
	{
		int channel;
		int height;
		int width;
	};
	
	class MyTexture
	{
	private:
		int w, h, channel;

		uint	wrap_s;
		uint	wrap_t;
		uint	min_filter;
		uint	mag_filter;
		uint	img_format;

	public:
		MyTexture(uint wraps, uint wrapt, uint minfilter, uint magfilter, uint img_format);

		uchar*		GetContent(std::string filepath);
		uchar*		GetContent(uchar* data, int size);

		uint		GetTexture(uchar* data);
		uint		GetTexture(std::string filename);
		uint		GetTextureSky(std::vector<std::string> faces);
		uint		GetTextureSky(std::vector<char*> faces, std::vector<int> sizes);
		TextureFileInfo getLastTextureInfo() 
		{
			return { channel,h,w };
		}

		void setMinFilter(uint minfilter)
		{
			min_filter = minfilter;
		}
		
	};
}


#endif // TEXTURE_H