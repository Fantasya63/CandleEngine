#pragma once

namespace Candle
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& framentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const; // Usually for debug cause you down wast time unbinding, you just bind the next stuff

	private:
		uint32_t m_RendererID; 
	};
}

