#version 450

layout(set = 0, binding = 0) uniform UBO {
	mat4 projection;
} ubo;

struct InstanceData
{
    vec3 color;
    vec2 position;
};

layout(set = 0, binding = 1) readonly buffer InstanceDataBuffer {
	InstanceData instance_data_array[];
} dynamic_model_data;


layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexTextCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTextCoord;

void main() {

    vec2 instancePos = dynamic_model_data.instance_data_array[gl_InstanceIndex].position;
    vec3 instanceColor = dynamic_model_data.instance_data_array[gl_InstanceIndex].color;

    gl_Position = ubo.projection * vec4(vertexPosition + instancePos, 0.0, 1.0);
    fragColor = instanceColor;
    fragTextCoord = vertexTextCoord;    
}