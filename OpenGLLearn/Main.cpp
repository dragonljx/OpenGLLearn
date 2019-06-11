#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "Data.h"
#include "Shader.h"
using namespace std;

void SetViewport(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int main() {

#pragma region ��ʼ��

	//��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���ð汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ʹ�ú���ģʽ
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);

	if (window == NULL)
	{
		cout << "GLFW��������ʧ�ܣ�" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//ָ������context
	glfwSetFramebufferSizeCallback(window, SetViewport);//���ô��ڻص�

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD!" << endl;
		return -1;
	}

#pragma endregion

#pragma region Shader
	//unsigned vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	cout << "������ɫ������\n" << infoLog << endl;
	//}

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);


	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	cout << "ƬԪ��ɫ������\n" << infoLog << endl;
	//}
	//glUseProgram(shaderProgram); //����

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
#pragma endregion

#pragma region ģ��
	unsigned int VBO, VAO,EBO;
	//���㻺�����Vertex Buffer Object��VBO
	glGenBuffers(1, &VBO);

	//�����������Vertex Array Object��VAO
	glGenVertexArrays(1, &VAO);

	//�����������Element Buffer Object��EBO��Index Buffer Object��IBO
	glGenBuffers(1, &EBO);

	//ģ����������
	//1.��VAO
	glBindVertexArray(VAO);
	//2.�Ѷ������鸴�Ƶ������й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//3.��������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//4.���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion

#pragma region ����

#pragma endregion


	Shader myShader("test.vert", "test.frag");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����߿����ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//�ָ�Ĭ�ϻ���ģʽ
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//����
		//glUseProgram(shaderProgram);
		myShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3); // ��ʹ���������Ƶķ���
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void SetViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};