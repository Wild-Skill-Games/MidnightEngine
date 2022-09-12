#pragma once

namespace MidnightEngine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}