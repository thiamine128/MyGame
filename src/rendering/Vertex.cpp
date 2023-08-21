#include "Vertex.h"

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) : position(x, y, z), normal(nx, ny, nz), texCoord(u, v)
{

}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord) : position(position), normal(normal), texCoord(texCoord)
{

}
