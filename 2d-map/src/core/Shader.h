#pragma once

#include <string>

class Shader {
public:
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~Shader();
	void Bind() const;
	void Unbind() const;
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	std::string ParseShader(const std::string& source);
private:
	unsigned int m_RendererId;
	std::string m_VertexFilePath;
	std::string m_FragmentFilePath;
};