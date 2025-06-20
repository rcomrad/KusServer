#version 450

layout(set = 0, binding = 0) uniform UBO {
	mat4 projection;
} ubo;

struct InstanceData
{
    vec4 color;
    mat4 model;
};


layout(set = 0, binding = 1) readonly buffer InstanceDataBuffer {
	InstanceData instance_data_array[];
} dynamic_model_data;


layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexTextCoord;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTextCoord;

void main() 
{
    mat4 model = dynamic_model_data.instance_data_array[gl_InstanceIndex].model;

    gl_Position = ubo.projection * model * vec4(vertexPosition, 0.0, 1.0);

    fragColor = dynamic_model_data.instance_data_array[gl_InstanceIndex].color;

    fragTextCoord = vertexTextCoord;    
}