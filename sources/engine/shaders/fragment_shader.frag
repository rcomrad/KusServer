#version 450

layout(location = 0) in vec2 inUv;
layout(location = 1) in flat int in_texture_index;

layout (location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform sampler2D sprite[3];


void main()
{
	outColor = texture(sprite[in_texture_index], inUv); 
}