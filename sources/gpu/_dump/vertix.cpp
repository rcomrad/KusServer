// #include "vertix.hpp"

// #include "kernel/framework/logger/basic/include_me.hpp"

// namespace gpu::logic
// {

// std::vector<vk::VertexInputBindingDescription>
// Vertex::getBindingDescriptions()
// {
//     std::vector<vk::VertexInputBindingDescription> result(1);
//     result[0].binding   = 0;
//     result[0].stride    = sizeof(Vertex);
//     result[0].inputRate = vk::VertexInputRate::eVertex;
//     return result;
// }

// std::vector<vk::VertexInputAttributeDescription>
// Vertex::getAttributeDescriptions()
// {
//     std::vector<vk::VertexInputAttributeDescription> result(1);
//     result[0].binding  = 0;
//     result[0].location = 0;
//     result[0].format   = vk::Format::eR32G32Sfloat;
//     result[0].offset   = offsetof(Vertex, position);

//     // result[1].binding  = 0;
//     // result[1].location = 1;
//     // result[1].format   = vk::Format::eR32G32B32Sfloat;
//     // result[1].offset   = offsetof(Vertex, color);
//     return result;
// }

// } // namespace gpu::logic
