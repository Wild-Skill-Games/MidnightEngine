// Basic texture shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordonate;
			
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TextureCoordonate;

void main()
{
	v_TextureCoordonate = a_TextureCoordonate;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoordonate;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TextureCoordonate);
}