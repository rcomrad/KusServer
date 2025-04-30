#version 450

layout(binding = 0) uniform UBO {
	mat4 projection;
} ubo;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexColor;

layout(location = 0) out vec3 fragColor;

void main() {
	gl_Position = ubo.projection * vec4(vertexPosition, 0, 1.0);
	
	fragColor = vertexColor;
}