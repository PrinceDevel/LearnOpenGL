#include "precompiled.hpp"
#include "VertexArray.hpp"
#include <glad/glad.h>


static GLenum ToOpenGLBase(ShaderDataType type) {
	switch (type) {
	case ShaderDataType::Float:
	case ShaderDataType::Vec2F:
	case ShaderDataType::Vec3F:
	case ShaderDataType::Vec4F:
	case ShaderDataType::Mat3F:
	case ShaderDataType::Mat4F:
		return GL_FLOAT;
	case ShaderDataType::Int:
	case ShaderDataType::Vec2I:
	case ShaderDataType::Vec3I:
	case ShaderDataType::Vec4I:
		return GL_INT;
	case ShaderDataType::Bool:
		return GL_BOOL;
	}
	return GL_NONE;
}

VertexArray::VertexArray() {
	glGenVertexArrays(1, &mVertexArrayID);
}
VertexArray::~VertexArray() {}

void VertexArray::Bind() const {
	glBindVertexArray(mVertexArrayID);
}
void VertexArray::Unbind() const {
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& pVertBuff) {
	glBindVertexArray(mVertexArrayID);
	pVertBuff->Bind();

	int index = 0;
	auto layout = pVertBuff->GetLayout();
	for (const auto& element : layout) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			element.GetComponentCount(),
			ToOpenGLBase(element.mType),
			element.mNormalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*) element.mOffset
		);
		index++;
	}

	mVertexBuffers.push_back(pVertBuff);
}
void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& pIndexBuff) {
	glBindVertexArray(mVertexArrayID);
	pIndexBuff->Bind();
	mIndexBuffer = pIndexBuff;
}

void VertexArray::DrawElements() const {
	glDrawElements(GL_TRIANGLES, GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}