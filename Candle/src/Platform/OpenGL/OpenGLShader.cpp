#include "cdpch.h"
#include "OpenGLShader.h"

#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace Candle
{
	namespace Utils
	{
		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || "pixel")
				return GL_FRAGMENT_SHADER;
			
			CD_CORE_ASSERT(false, "Unknown shader type!");
			return 0;
		}
	}


	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath)
	{
		m_Name = name;
		
		// Process
		std::string file = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = Preprocess(file);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		// Get the name from the file path
		std::filesystem::path path (filepath);
		m_Name = path.stem().string();

		// Process
		std::string file = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = Preprocess(file);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(shaderSources);
	
		m_Name = name;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}


	// Uniforms
	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	
	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}


	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
	}

	const std::string& OpenGLShader::GetName() const
	{
		return m_Name;
	}
	
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream stream (filepath, std::ios::in | std::ios::binary);

		if (stream)
		{
			stream.seekg(0, std::ios::end);
			size_t size = stream.tellg();
			if (size != -1)
			{
				result.resize(size);
				stream.seekg(0, std::ios::beg);
				stream.read(&result[0], size);
			}
			else
			{
				CD_CORE_ERROR("Error opening file: {0}", filepath);
			}
		}
		else
		{
			CD_CORE_ERROR("Error opening file: {0}", filepath);
		}

		return result;
	}


	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken);

		while (pos != std::string::npos)
		{

			// End of shader type declaration line
			size_t eol = source.find_first_of("\r\n", pos);
			CD_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			
			// Start of shader type name (after "#type " keyword)
			size_t begin = pos + typeTokenLength + 1;
		
			std::string type = source.substr(begin, eol - begin);
			CD_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid Shader type");
			
			//Start of shader code after shader type declaration line
			size_t nextlinePos = source.find_first_not_of("\r\n", eol);
			CD_CORE_ASSERT(nextlinePos != std::string::npos, "Syntax Error");

			// Start of the next shader type declaration line
			pos = source.find(typeToken, nextlinePos);
			shaderSources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextlinePos) : source.substr(nextlinePos, pos - nextlinePos);
		}

		return shaderSources;
	}


	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		CD_CORE_ASSERT(shaderSources.size() <= 2, "We only support atmost 2 shaders for now");

		GLuint program = glCreateProgram();
		std::array<GLuint, 2> glShaderIDs;
		unsigned int glShaderIndex = 0;
		
		///From https://www.khronos.org/opengl/wiki/Shader_Compilation

		for (auto& [shaderType, shaderSource] : shaderSources) {

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(shaderType);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = (const GLchar*)shaderSource.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength); // TODO: Change to opengl series?
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				CD_CORE_ERROR("{0}", infoLog.data());
				CD_CORE_ASSERT(false, "Shader Compilation error");

				break;
			}
			
			// Shader is compiled succesfully, we can now attach it to our program
			glAttachShader(program, shader);
			glShaderIDs[glShaderIndex++] = shader;
		}
		

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			
			// Don't leak shaders either.
			for (unsigned int i = 0; i < glShaderIndex; i++)
			{
				glDeleteShader(glShaderIDs[i]);
			}

			// Use the infoLog as you see fit.
			CD_CORE_ERROR("{0}", infoLog.data());
			CD_CORE_ASSERT(false, "Shader Linking error");
			return;
		}

		// Always detach shaders after a successful link.
		// Don't leak shaders either.
		for (unsigned int i = 0; i < glShaderIndex; i++)
		{
			glDetachShader(program, glShaderIDs[i]);
		}

		m_RendererID = program;
	}
}