#include "Entity.hpp"

Entity::Entity(VertexBuffer* vbuff, VertexBuffer* cbuff, glm::vec3 pos) :
vertexBuffer(vbuff),colorBuffer(cbuff), position(pos)
{

}
Entity::~Entity()
{

}