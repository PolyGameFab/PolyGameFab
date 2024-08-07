#pragma once

#include "lypch.h"

namespace Lypo {

        enum class ShaderDataType
        {
            None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
        };

        static uint32_t shaderDataTypeSize(ShaderDataType type)
        {
            switch (type)
            {
                case ShaderDataType::Float:    return 4;
                case ShaderDataType::Float2:   return 4 * 2;
                case ShaderDataType::Float3:   return 4 * 3;
                case ShaderDataType::Float4:   return 4 * 4;
                case ShaderDataType::Mat3:     return 4 * 3 * 3;
                case ShaderDataType::Mat4:     return 4 * 4 * 4;
                case ShaderDataType::Int:      return 4;
                case ShaderDataType::Int2:     return 4 * 2;
                case ShaderDataType::Int3:     return 4 * 3;
                case ShaderDataType::Int4:     return 4 * 4;
                case ShaderDataType::Bool:     return 1;
            }

            //TODO: log error: Unknown ShaderDataType
            return 0;
        }

        struct BufferElement
        {
            std::string Name;
            ShaderDataType Type;
            uint32_t Size;
            uint32_t Offset;
            bool Normalized;

            BufferElement() {}

            BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
                    : Name(name), Type(type), Size(shaderDataTypeSize(type)), Offset(0), Normalized(normalized)
            {
            }

            uint32_t getComponentCount() const
            {
                switch (Type)
                {
                    case ShaderDataType::Float:   return 1;
                    case ShaderDataType::Float2:  return 2;
                    case ShaderDataType::Float3:  return 3;
                    case ShaderDataType::Float4:  return 4;
                    case ShaderDataType::Mat3:    return 3 * 3;
                    case ShaderDataType::Mat4:    return 4 * 4;
                    case ShaderDataType::Int:     return 1;
                    case ShaderDataType::Int2:    return 2;
                    case ShaderDataType::Int3:    return 3;
                    case ShaderDataType::Int4:    return 4;
                    case ShaderDataType::Bool:    return 1;
                }

                //TODO: log error: Unknown ShaderDataType
                return 0;
            }
        };

        class BufferLayout
        {
        public:
            BufferLayout() {}

            BufferLayout(const std::initializer_list<BufferElement>& elements)
                    : elements_(elements)
            {
                calculateOffsetsAndStride();
            }

            inline uint32_t getStride() const { return stride_; }
            inline const std::vector<BufferElement>& getElements() const { return elements_; }

            std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
            std::vector<BufferElement>::iterator end() { return elements_.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }
        private:
            void calculateOffsetsAndStride()
            {
                uint32_t offset = 0;
                stride_ = 0;
                for (auto& element : elements_)
                {
                    element.Offset = offset;
                    offset += element.Size;
                    stride_ += element.Size;
                }
            }
        private:
            std::vector<BufferElement> elements_;
            uint32_t stride_ = 0;
        };
}