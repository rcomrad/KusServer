#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv; 
layout(location = 2) in int in_texture_index;

layout(location = 0) out vec2 outUv;
layout(location = 1) out int out_texture_index;


void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	outUv = uv;
	out_texture_index = in_texture_index;
}