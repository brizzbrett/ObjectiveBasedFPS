#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const GLvoid* data, GLsizeiptr size, GLenum m, GLsizei c, GLsizei s):
mode(m),count(c),stride(s)
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

void VertexBuffer::configureVertexAttributes(GLenum vertexPosition)
{
	if (vertexPosition != -1)
	{
		glEnableVertexAttribArray(vertexPosition);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, stride, NULL);
	}
}
void VertexBuffer::renderVertexBuffer()
{
	glDrawArrays(mode, 0, count);
}