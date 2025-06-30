#ifndef VERTEX_USINGS_HPP
#define VERTEX_USINGS_HPP

#include "vertex.hpp"
#include "vertex2d_p1_uv1.hpp"
#include "vertex3d_p1_uv1.hpp"
namespace kusengine
{
namespace render
{

using Vertex2DP1UV1 = Vertex<Vertex2DAttributesP1UV1, Vertex2DDescriptionP1UV1>;

using Vertex3DP1UV1 = Vertex<Vertex3DAttributesP1UV1, Vertex3DDescriptionP1UV1>;

}; // namespace render
}; // namespace kusengine

#endif // VERTEX_USINGS_HPP
