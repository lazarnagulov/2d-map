#pragma once

#include <string>

class Texture {
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
private:
	unsigned int m_RendererId;
	std::string m_FilePath;
	unsigned char* m_Buffer;
	int m_Width, m_Height, m_BPP;
};
