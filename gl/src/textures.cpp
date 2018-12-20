#include "textures.h"

namespace bsl::gl
{
	inline static bool isPowerOf2(int v) {
		return (v & (v - 1)) == 0;
	}
	MyTexture::MyTexture(uint wraps, uint wrapt, uint minfilter, uint magfilter, uint imgformat)
	{
		w = 0;
		h = 0;
		channel = 0;
		wrap_s = wraps;
		wrap_t = wrapt;
		min_filter = minfilter;
		mag_filter = magfilter;
		img_format = imgformat;
	}



	uchar* MyTexture::GetContent(std::string filename)
	{
		uchar*	img = SOIL_load_image(filename.c_str(), &w, &h, &channel, SOIL_LOAD_AUTO);
		return img;
	}

	uchar* MyTexture::GetContent(uchar* data,int size) {
		uchar* d = SOIL_load_image_from_memory(data, size, &w, &h, &channel, 4);
		printf("%d %d %d\n", w, h, channel);
		return d;
	}

	uint MyTexture::GetTexture(uchar* data)
	{
		uint text;

		glGenTextures(1, &text);
		glBindTexture(GL_TEXTURE_2D, text);
		//Texture wrapping				
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		// texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture 

		return text;
	}

	uint MyTexture::GetTexture(std::string filename)
	{
		uchar* img = GetContent(filename);
		if (img == nullptr)
		{
			return ERROR_TEXTURE;
		}
		uint u = GetTexture(img);
		SOIL_free_image_data(img);
		return u;
	}

	uint MyTexture::GetTextureSky(std::vector<char*> faces, std::vector<int> sizes) {
		GLuint textureID;
		unsigned char* image;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		//wrapping
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		//filtering
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		for (GLuint i = 0; i < faces.size(); i++)
		{
			image = SOIL_load_image_from_memory((unsigned char*)faces[i], sizes[i], &w, &h, &channel, 4);;
			if (channel != 4) {
				printf("Erreur la texture doit avoir 4 channel");
				return ERROR_TEXTURE;
			}
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


		return textureID;
	}

	uint MyTexture::GetTextureSky(std::vector<std::string> faces)
	{
		GLuint textureID;
		unsigned char* image;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		//wrapping
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		//filtering
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		for (GLuint i = 0; i < faces.size(); i++)
		{
			image = GetContent(faces[i]);
			if(channel != 4) {
				printf("Erreur la texture doit avoir 3 channel");
				SOIL_free_image_data(image);
				return ERROR_TEXTURE;
			}
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textureID;
	}
}
