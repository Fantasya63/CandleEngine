#include "cdpch.h"
#include "Shader.h"
#include "Candle/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Candle
{
	Ref<Shader> Candle::Shader::Create(const std::string& filepath)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(filepath);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Candle::Shader::Create(const std::string& name, const std::string& filepath)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, filepath);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Candle::Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// --------------------------- Shader Library ---------------------------------
	
	void ShaderLibrary::Add(const std::string& name, Ref<Shader>& shader)
	{
		CD_CORE_ASSERT(!Exists(name), "Shader already exist");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(Ref<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}


	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}


	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		CD_CORE_ASSERT(Exists(name), "Shader does not exist.");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}