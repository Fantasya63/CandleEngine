#include "cdpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Candle
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		
		CD_CORE_ASSERT(data, "Error loading texture");
		m_Width = width;
		m_Height = height;

		// Generate Textures
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		
		// Allocate Data
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		// Min and Max filters
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Upload Data
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		// Free up memory
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	
	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}
	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}
