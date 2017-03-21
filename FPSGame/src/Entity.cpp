#include "Entity.hpp"

Entity::Entity(VertexBuffer* vbuff, glm::vec3 pos) :
vertexBuffer(vbuff), position(pos)
{

}
Entity::~Entity()
{

}