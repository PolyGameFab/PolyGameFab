//
// Created by lapor on 7/19/2024.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/rendering/VertexBuffer.hpp"
#include "core/rendering/IndexBuffer.hpp"
#include "core/rendering/VertexArray.hpp"
#include "core/rendering/BufferUtils.h"
#include "core/rendering/Texture.h"
#include "core/rendering/shader.h"
#include "platform/opengl/opengl_shader.h"
#include "platform/opengl/GLCheck.h"

unsigned int createBasicShader();
unsigned int createTextureShader();

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error in glad load" << std::endl;
        return -1;
    }

    //from learnopengl.com
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

/*    unsigned int shaderProgram = createBasicShader();
    unsigned int textureShader = createTextureShader();*/


    std::string fragmentPath = "../LypoEngine/assets/shaders/basicColorShader.frag.glsl";
    std::string vertexPath = "../LypoEngine/assets/shaders/basicColorShader.vert.glsl";

    std::shared_ptr<Lypo::OpenglShader> colorShader = std::make_shared<Lypo::OpenglShader>(vertexPath, fragmentPath);

    fragmentPath = "../LypoEngine/assets/shaders/textureShader.frag.glsl";
    vertexPath = "../LypoEngine/assets/shaders/textureShader.vert.glsl";

    std::shared_ptr<Lypo::OpenglShader> textureShader = std::make_shared<Lypo::OpenglShader>(vertexPath, fragmentPath);

    std::shared_ptr<Lypo::VertexArray> vertexArray;
    std::shared_ptr<Lypo::VertexArray> squareVA;

    vertexArray.reset(Lypo::VertexArray::create());

    float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    std::shared_ptr<Lypo::VertexBuffer> vertexBuffer = std::shared_ptr<Lypo::VertexBuffer>(Lypo::VertexBuffer::create(vertices, sizeof(vertices)));
    Lypo::BufferLayout layout = {
            { Lypo::ShaderDataType::Float3, "a_Position" },
            { Lypo::ShaderDataType::Float4, "a_Color" }
    };
    vertexBuffer->setLayout(layout);

    vertexArray->addVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };
    std::shared_ptr<Lypo::IndexBuffer> indexBuffer;
    indexBuffer.reset(Lypo::IndexBuffer::create(indices, sizeof(indices)));
    vertexArray->setIndexBuffer(indexBuffer);

    squareVA.reset(Lypo::VertexArray::create());

    float squareVertices[5 * 4] = {
            -0.75f, -0.75f, 0.0f,  0.0f, 0.0f,
            0.75f, -0.75f, 0.0f,  1.0f, 0.0f,
            0.75f,  0.75f, 0.0f,  1.0f, 1.0f,
            -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
    };

    std::shared_ptr<Lypo::VertexBuffer> squareVB = std::shared_ptr<Lypo::VertexBuffer>(Lypo::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
    squareVB->setLayout({
                                {Lypo::ShaderDataType::Float3, "a_Position"},
                                { Lypo::ShaderDataType::Float2, "a_TexCoord" }
                        });
    squareVA->addVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    std::shared_ptr<Lypo::IndexBuffer> squareIB;
    squareIB.reset(Lypo::IndexBuffer::create(squareIndices, sizeof(squareIndices)));
    squareVA->setIndexBuffer(squareIB);

    std::shared_ptr<Lypo::Texture2D> m_Texture = Lypo::Texture2D::Create("../LypoEngine/assets/textures/Checkerboard.png");

    textureShader->bind();
    textureShader->uploadUniformInt("u_Texture", 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //vertex buffer

        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);


        m_Texture->bind();
        textureShader->bind();
        squareVA->bind();
        glDrawElements(GL_TRIANGLES, squareVA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);


        colorShader->bind();
        vertexArray->bind();
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int createBasicShader()
{
    // Shader creation for test
    const char *vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

unsigned int createTextureShader()
{
    // Shader creation for test
    const char *vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSource =  R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}