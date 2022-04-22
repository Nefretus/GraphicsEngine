#include"CompiledHeader.h"
#include "VertexArray.h"
#include"VertexBuffer.h"
#include"ErrorCheckMacro.h"

namespace Engine {
    VertexArray::VertexArray() : indexBuffer(nullptr) {
        GLCall(glCreateVertexArrays(1, &ID));
        glBindVertexArray(ID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &ID);
    }

    void VertexArray::bind() const {
        glBindVertexArray(ID);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::addIndexBuffer(const std::shared_ptr<IndexBuffer>& _indexBuffer) {
        bind();
        if (indexBuffer)
            indexBuffer->unbind();
        _indexBuffer->bind();
        indexBuffer = _indexBuffer;
        unbind(); // for safety
    }

    void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO) {
        bind();
        if (vertexBuffer)
            vertexBuffer->unbind();
        VBO->bind();
        if (VBO->getLayout().getElements().size() == 0) {
            std::cout << "You need to set the layout before adding vertex buffer!\n";
            ASSERT(false);
        }
        const auto& layout = VBO->getLayout();
        for (size_t i = 0; i < layout.getElements().size(); i++) {
            glEnableVertexAttribArray(i);
            const auto& element = layout.getElements().at(i);
            GLCall(glVertexAttribPointer(i, element.count, element.openGLType, element.normalized, layout.getStride(), (const void*)element.offset));
        }
        vertexBuffer = VBO;
        unbind(); // for safety
    }
}
