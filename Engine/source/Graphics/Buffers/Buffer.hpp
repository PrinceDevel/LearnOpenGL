#pragma once
#include <vector>

#include "Logger/Logger.hpp"
#include "Maths.hpp"


/////////////////// Basic Stuffs //////////////////////////
//////////////////////////////////////////////////////////////////
enum class ShaderDataType : uint8_t {
	None = 0, 
	Float, Vec2F, Vec3F, Vec4F,
	Mat3F, Mat4F, 
	Int, Vec2I, Vec3I, Vec4I,
	Bool
};
static unsigned short ShaderDataTypeSize(ShaderDataType type) {
	switch (type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Vec2F:		return 8;
		case ShaderDataType::Vec3F:		return 12;
		case ShaderDataType::Vec4F:		return 16;
		case ShaderDataType::Mat3F:		return 36;
		case ShaderDataType::Mat4F:		return 64;
			
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Vec2I:		return 8;
		case ShaderDataType::Vec3I:		return 12;
		case ShaderDataType::Vec4I:		return 16;
		case ShaderDataType::Bool:		return 1;
	}
	return 0;
}
struct BufferElement {
	std::string mName;
	ShaderDataType mType;
	unsigned int mSize;
	unsigned int mOffset;
	bool mNormalized;
	BufferElement() = default;
	BufferElement(ShaderDataType type, const std::string& name)
		: mName(name), mType(type), mSize(ShaderDataTypeSize(mType)), mOffset(0), mNormalized(false) {}
	unsigned int GetComponentCount() const {
		switch (mType) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Vec2F:		return 2;
			case ShaderDataType::Vec3F:		return 3;
			case ShaderDataType::Vec4F:		return 4;
			case ShaderDataType::Mat3F:		return 9;
			case ShaderDataType::Mat4F:		return 16;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Vec2I:		return 2;
			case ShaderDataType::Vec3I:		return 3;
			case ShaderDataType::Vec4I:		return 4;
			case ShaderDataType::Bool:		return 1;
		}
		return 0;
	}
};


//////////////////////////////////////////////////////////////////
/////////////////// Buffer Layout Class //////////////////////////
//////////////////////////////////////////////////////////////////
class BufferLayout {
public:
	BufferLayout() {}
	BufferLayout(const std::initializer_list<BufferElement>& elements) 
		: mElements(elements) {
		CalculateOffsetsAndStride();
	}
    
	inline const std::vector<BufferElement>& GetElements() const { return mElements; }
	inline unsigned int GetStride() const { return mStride;  }

	std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
	std::vector<BufferElement>::iterator end() { return mElements.end(); }
	std::vector<BufferElement>::reverse_iterator rbegin() { return mElements.rbegin(); }
	std::vector<BufferElement>::reverse_iterator rend() { return mElements.rend(); }

	std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }
	std::vector<BufferElement>::const_reverse_iterator rbegin() const { return mElements.rbegin(); }
	std::vector<BufferElement>::const_reverse_iterator rend() const { return mElements.rend(); }

private:
	void CalculateOffsetsAndStride() {
		unsigned int offset = 0;
		mStride = 0;

		for (auto& elements : mElements) {
			elements.mOffset = offset;
			offset += elements.mSize;
			mStride += elements.mSize;
		}
	}

private:
	std::vector<BufferElement> mElements;
	unsigned int mStride = 0;
};

////////////////////////////////////////////////////////
/////////////////// Vertex Buffer /////////////////////
///////////////////////////////////////////////////////
class VertexBuffer {
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
		
	void SetLayout(const BufferLayout& layout) { mLayout = layout; }
	const BufferLayout& GetLayout() const { return mLayout; };

private:
	unsigned int mBufferID;
	BufferLayout mLayout;
};
	


///////////////////////////////////////////////////////
/////////////////// Index Buffer //////////////////////
///////////////////////////////////////////////////////
class IndexBuffer {
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;

private:
	unsigned int mBufferID;
	unsigned int mCount;
};