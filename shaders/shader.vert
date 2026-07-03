#version 450

layout (location = 0) out vec2 uv;


layout(push_constant) uniform Push {
  vec2 scaler;
  vec2 offset;
} push;



vec4 vertices[6] = {
    // Bottom left
    vec4(0,  1, 0.0, 1.0),

    // Top Left
    vec4(0, 0, 0.0, 0.0),

    // Top Right
    vec4( 1, 0, 1.0, 0.0),

    // Top Right
    vec4( 1, 0, 1.0, 0.0),

    // Bottom Right
    vec4( 1,  1, 1.0, 1.0),

    // Bottom Left
    vec4(0,  1, 0.0, 1.0),
};

void main()
{
    gl_Position = vec4(vertices[gl_VertexIndex].xy * push.scaler + push.offset, 1.0, 1.0);
    uv = vertices[gl_VertexIndex].zw;
}