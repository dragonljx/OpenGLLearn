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

#pragma region 初始化

	//创建窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置使用核心模式
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);

	if (window == NULL)
	{
		cout << "GLFW创建窗口失败！" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//指定窗口context
	glfwSetFramebufferSizeCallback(window, SetViewport);//设置窗口回调

	//初始化glad
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
	//	cout << "顶点着色器错误：\n" << infoLog << endl;
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
	//	cout << "片元着色器错误：\n" << infoLog << endl;
	//}
	//glUseProgram(shaderProgram); //激活

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
#pragma endregion

#pragma region 模型
	unsigned int VBO, VAO,EBO;
	//顶点缓冲对象：Vertex Buffer Object，VBO
	glGenBuffers(1, &VBO);

	//顶点数组对象：Vertex Array Object，VAO
	glGenVertexArrays(1, &VAO);

	//索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
	glGenBuffers(1, &EBO);

	//模型数组流程
	//1.绑定VAO
	glBindVertexArray(VAO);
	//2.把顶点数组复制到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//3.设置索引
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//4.设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion

#pragma region 纹理

#pragma endregion


	Shader myShader("test.vert", "test.frag");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//启动线框绘制模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//恢复默认绘制模式
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//绘制
		//glUseProgram(shaderProgram);
		myShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3); // 不使用索引绘制的方法
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