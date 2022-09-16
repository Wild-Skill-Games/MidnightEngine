#pragma once

namespace MidnightEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// TODO: u might need 2 make multiples of these functions for different types of uniforms

		// virtual void UploadUniformBuffer()

		static Shader *Create(const std::string &filepath);
		static Shader *Create(const std::string &vertexShader, const std::string &fragmentShader);
	};
}