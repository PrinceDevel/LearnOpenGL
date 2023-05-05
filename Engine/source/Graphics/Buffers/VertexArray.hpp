#pragma once

#include <memory>

#include "Graphics/Buffers/Buffer.hpp"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& pVertBuffs);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& pIndBuffs);
	void DrawElements() const;

	inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return mVertexBuffers; }
	inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }

	inline unsigned int ID() const { return mVertexArrayID; }

private:
	unsigned int mVertexArrayID;
	std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
	std::shared_ptr<IndexBuffer> mIndexBuffer;

};