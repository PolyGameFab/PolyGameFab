//
// Created by lapor on 7/26/2024.
//

#ifndef SHADER_H
#define SHADER_H

namespace Lypo
{
    enum ShaderType
    {
        Vertex, Fragment
    };

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;
    };
}

#endif //SHADER_H
