#version 450

layout (location = 0) out vec2 uv;

layout(push_constant) uniform Push {
    vec2 coord_scaler;
    vec2 coord_offset;
    vec2 uv_scaler;
    vec2 uv_offset;
} push;

vec4 vertices[6] = {
    // Bottom left
    vec4(-1,  1, 0.0, 1.0),

    // Top Left
    vec4(-1, -1, 0.0, 0.0),

    // Top Right
    vec4( 1, -1, 1.0, 0.0),

    // Top Right
    vec4( 1, -1, 1.0, 0.0),

    // Bottom Right
    vec4( 1,  1, 1.0, 1.0),

    // Bottom Left
    vec4(-1,  1, 0.0, 1.0),
};

void main()
{
    gl_Position = vec4(vertices[gl_VertexIndex].xy * push.coord_scaler + push.coord_offset, 1.0, 1.0);
    uv = vertices[gl_VertexIndex].zw * push.uv_scaler + push.uv_offset;
}
