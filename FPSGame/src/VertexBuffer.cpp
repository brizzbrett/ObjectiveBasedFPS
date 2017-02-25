#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const GLvoid* data, GLsizeiptr size, GLenum m, GLsizei c, GLsizei s, Shader* sr):
mode(m),count(c),stride(s),shader(sr)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vertexBufferID);
	vertexBufferID = 0;
}

void VertexBuffer::configureVertexAttributes()
{
	if (shader->getVertexAttrib() != -1)
	{
		glEnableVertexAttribArray(shader->getVertexAttrib());
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(shader->getVertexAttrib(), 3, GL_FLOAT, GL_FALSE, stride, NULL);
	}
}
void VertexBuffer::renderVertexBuffer()
{
	glDrawArrays(mode, 0, count);
}
void VertexBuffer::renderIndexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferID);

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}