#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> &verts, std::vector<GLuint> &inds, std::vector<Texture> &texels) :
vertices(verts), indices(inds), textures(texels)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertbuffer);
	glGenBuffers(1, &indexbuffer);

	vertices.reserve(1000);
	indices.reserve(1000);
	textures.reserve(1000);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texels));

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertbuffer);
	glDeleteBuffers(1, &indexbuffer);

	vertbuffer = 0;
	indexbuffer = 0;	
}

void Mesh::Render(Shader* s)
{
	

	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); 

		std::stringstream ss;
		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse")
			ss << diffuseNr++; 
		else if (name == "texture_specular")
			ss << specularNr++; 

		number = ss.str();

		glUniform1f(glGetUniformLocation(s->getProgram(), ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);
	// Draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}