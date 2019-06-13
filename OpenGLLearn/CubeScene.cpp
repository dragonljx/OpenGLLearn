
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
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
float lastX = 400, lastY = 300;
bool firstMouse = true;
float yaws = -90.0f;
float pitchs = 0.0f;
float fov = 45.0f;

//���ӳ���
int main0() {

#pragma region ��ʼ��

	//��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���ð汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ʹ�ú���ģʽ
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Window", NULL, NULL);

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
	Shader myShader("test.vert", "test.frag");
	myShader.use();
#pragma endregion

#pragma region ģ��
	unsigned int VBO, VAO, EBO;
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
	//����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	////��ɫ
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion

#pragma region ����
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
	glGenerateMipmap(GL_TEXTURE_2D);//���ɶ༶��Զ����
	glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0);

	unsigned char* data2 = stbi_load("../Asset/Images/awesomeface.png", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);//���ɶ༶��Զ����

	myShader.setInt("texture2", 1);
	myShader.setFloat("weights", 0.3);
	stbi_image_free(data1);//������ͼ����
	stbi_image_free(data2);//������ͼ����

#pragma endregion

#pragma region Transform
	//mat4 trans = mat4(1.0f);
	//trans = rotate(trans, radians(90.0f), vec3(0.0, 0.0, 1.0));
	//trans = scale(trans, vec3(0.5, 0.5, 0.5));
	//myShader.setMatrix("transform", trans);
	//unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));

#pragma endregion

#pragma region ����ϵͳ
	//ģ�;���
	mat4 model = mat4(1.0f);

	//͸�Ӿ���
	mat4 projection = mat4(1.0f);


	model = rotate(model, (float)glfwGetTime() * radians(0.1f), vec3(0.5f, 1.0f, 0.0f));
	myShader.setMatrix("model", model);

	//�۲����
	mat4 view = mat4(1.0f);

#pragma endregion

	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//�������
	glfwSetCursorPosCallback(window, mouse_callback);//ע������ƶ��ص�����
	glfwSetScrollCallback(window, scroll_callback);//�����ֻص�
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����߿����ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//�ָ�Ĭ�ϻ���ģʽ
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//����
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
		//glDrawArrays(GL_TRIANGLES, 0, 36); // ��ʹ���������Ƶķ���
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