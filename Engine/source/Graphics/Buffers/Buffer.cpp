#include "precompiled.hpp"
#include "Buffer.hpp"

#include <glad/glad.h>

///////////////////////////////////////////////////////
/////////////////// Vertex Buffer /////////////////////
///////////////////////////////////////////////////////
VertexBuffer::VertexBuffer(float* vertices, unsigned int size) {
	glGenBuffers(1, &mBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &mBufferID);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
}
void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



///////////////////////////////////////////////////////
/////////////////// Index Buffer //////////////////////
///////////////////////////////////////////////////////
IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count) : mCount(count) {
	glGenBuffers(1, &mBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &mBufferID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
}
void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetCount() const {
	return mCount;
}