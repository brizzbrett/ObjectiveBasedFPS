#pragma once

#include "MUtils.hpp"
#include "Shader.hpp"

/**
* Mesh class
*/
class Mesh
{

protected:

	GLuint vao;
	GLuint vertbuffer; /**<vertex buffer object, stores the vertex data of this mesh */
	GLuint indexbuffer; /**<index buffer object, stores the order to draw the triangles  */

	int vertCount; /**<number of vertices the mesh has  */
	int indicesCount; /**< number of indices the mesh has  */

public:

	std::vector<Vertex> vertices; /**<array for vertices in mesh  */
	std::vector<GLuint> indices; /**<array for the index of each group fo verts in order*/
	std::vector<Texture> textures;

	/**
	* @brief Mesh Constructor - stores a reference to vertex and index and texture
	* @param verts stores a reference to an array of vertices
	* @param inds store a reference to an array of indices
	* @param texts stores a reference to an array of Textures
	*/
	Mesh(std::vector<Vertex> &verts, std::vector<GLuint> &inds, std::vector<Texture> &texels);

	/**
	* Mesh Destructor
	*/
	~Mesh();

	/**
	* @brief Renders vertices
	*/
	void Render(Shader* s);

	/*
	* @brief Getter: the vertex buffer
	* @return vertbuffer
	*/
	int getVertBuffer() { return vertbuffer; };

	/*
	* @brief Getter: the index buffer
	* @return indexbuffer
	*/
	int getIndexBuffer() { return indexbuffer; };

	/*
	* @brief Getter: the vertices count
	* @return vertCount
	*/
	int getVertCount() { return vertCount; };

	/*
	* @brief Getter: the indices count
	* @return indicesCount
	*/
	int getIndicesCount() { return indicesCount; };




};