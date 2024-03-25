#pragma once

#include "Candle/Renderer/Texture.h"
#include "glad/glad.h"

namespace Candle
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();


		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void Bind(uint32_t slot) const override;

		virtual void SetData(void* data, uint32_t size) override;
	private:
		// TODO: Strip in runtime?
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;

		GLenum m_InternalFormat, m_DataFormat;
	};
}
