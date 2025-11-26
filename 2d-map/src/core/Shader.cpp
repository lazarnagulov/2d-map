#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"
#include "GL/glew.h"

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath) 
	: m_VertexFilePath(vertexFilePath), m_FragmentFilePath(fragmentFilePath), m_RendererId(0) {
    std::string vertexShader = ParseShader(vertexFilePath);
    std::string fragmentShader = ParseShader(fragmentFilePath);
    m_RendererId = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererId);
}

void Shader::Bind() const {
    glUseProgram(m_RendererId);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


std::string Shader::ParseShader(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        std::cout << "Failed to open shader file: " + path << std::endl;

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();  
}