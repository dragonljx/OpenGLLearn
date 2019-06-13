
/*
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "Data.h"
#include "Shader.h"
using namespace std;
using namespace glm;

void SetViewport(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float screenWidth = 800;
float screenHeight = 600;
vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
vec3 pos = vec3{ 0.0f ,0.0f ,-3.0f };
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
float lastX = 400, lastY = 300;
bool firstMouse = true;
float yaws = -90.0f;
float pitchs = 0.0f;
float fov = 45.0f;

//箱子场景
int main0() {

#pragma region 初始化

	//创建窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置使用核心模式
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Window", NULL, NULL);

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
	Shader myShader("test.vert", "test.frag");
	myShader.use();
#pragma endregion

#pragma region 模型
	unsigned int VBO, VAO, EBO;
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
	//顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	////颜色
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion

#pragma region 纹理
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data1 = stbi_load("../Asset/Images/container.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理
	glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0);

	unsigned char* data2 = stbi_load("../Asset/Images/awesomeface.png", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理

	myShader.setInt("texture2", 1);
	myShader.setFloat("weights", 0.3);
	stbi_image_free(data1);//清理贴图数据
	stbi_image_free(data2);//清理贴图数据

#pragma endregion

#pragma region Transform
	//mat4 trans = mat4(1.0f);
	//trans = rotate(trans, radians(90.0f), vec3(0.0, 0.0, 1.0));
	//trans = scale(trans, vec3(0.5, 0.5, 0.5));
	//myShader.setMatrix("transform", trans);
	//unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));

#pragma endregion

#pragma region 坐标系统
	//模型矩阵
	mat4 model = mat4(1.0f);

	//透视矩阵
	mat4 projection = mat4(1.0f);


	model = rotate(model, (float)glfwGetTime() * radians(0.1f), vec3(0.5f, 1.0f, 0.0f));
	myShader.setMatrix("model", model);

	//观察矩阵
	mat4 view = mat4(1.0f);

#pragma endregion

	glEnable(GL_DEPTH_TEST);//启动深度测试
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
	glfwSetCursorPosCallback(window, mouse_callback);//注册鼠标移动回调函数
	glfwSetScrollCallback(window, scroll_callback);//鼠标滚轮回调
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//启动线框绘制模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//恢复默认绘制模式
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//绘制
		myShader.use();
		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; i++)
		{
			mat4 model = mat4(1.0f);
			model = translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader.setMatrix("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		myShader.setMatrix("view", view);
		projection = perspective(radians(fov), screenWidth / screenHeight, 0.1f, 100.0f);
		myShader.setMatrix("projection", projection);

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36); // 不使用索引绘制的方法
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaws += xoffset;
	pitchs += yoffset;

	if (pitchs > 89.0f)
		pitchs = 89.0f;

	if (pitchs < -89.0f)
		pitchs = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaws)) * cos(glm::radians(pitchs));
	front.y = sin(glm::radians(pitchs));
	front.z = sin(glm::radians(yaws)) * cos(glm::radians(pitchs));
	cameraFront = glm::normalize(front);
}
void ProcessInput(GLFWwindow* window)
{
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;

	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;

	}
}
void SetViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= yoffset;
	}
	if (fov<=1.0f)
	{
		fov = 1.0f;
	}
	if (fov >= 45.0f)
	{
		fov = 45.0f;
	}
}

*/