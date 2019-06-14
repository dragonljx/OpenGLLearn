#pragma once
#include "Shader.h"
#include <vector>
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	/* �������� */
	std::vector<Vertex> vertices;
	std::vector<unsigned int > indices;
	std::vector<Texture> textures;
	/* ���� */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
private:
	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;
	/*  ����  */
	void setupMesh();
};
