#pragma once
#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{
public:
	// 程序ID
	unsigned int ID;

	// 构造器读取并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix(const std::string& name, glm::mat4 value) const;

	void setVec3(const std::string& name, const glm::vec3& value) const;

	void setVec3(const std::string& name, float x, float y, float z) const;

	void setMat2(const std::string& name, const glm::mat2& mat) const;

	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};
