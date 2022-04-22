#include"CompiledHeader.h"
#include"BufferLayout.h"

namespace Engine {
	BufferLayoutElement::BufferLayoutElement(const std::string& _name, int _count, GLenum type, GLboolean _normalized)
		: offset(0), name(_name), normalized(_normalized), openGLType(type), count(_count) {
		size = getSizeOfOpenGLType(type) * count;
	}

	int BufferLayoutElement::getSizeOfOpenGLType(GLenum type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		std::cout << "Unknown type!\n";
		ASSERT(false);
		return 0;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferLayoutElement>& newElements) : elements(newElements), stride(0) {
		/*Calculate offset and stride*/
		int prevoiusOffest = 0;
		for (size_t i = 0; i < elements.size(); i++) {
			auto& element = elements[i];
			element.offset = prevoiusOffest;
			prevoiusOffest += element.size;
			stride += element.size;
		}
	}
}