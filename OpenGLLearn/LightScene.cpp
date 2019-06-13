#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "Data.h"
#include "Shader.h"
#include "Camera.h"

void SetViewport(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
glm::vec3 lightPos = glm::vec3(1.0f, 2.0f, 2.0f);

Camera myCamera;


int main() {
#pragma region ��ʼ��

	//��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���ð汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ʹ�ú���ģʽ
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "GLFW��������ʧ�ܣ�" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//ָ������context
	glfwSetFramebufferSizeCallback(window, SetViewport);//���ô��ڻص�

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

#pragma endregion

	Shader myShader = Shader("default.vert", "default.frag");
	Shader lightShader = Shader("lightShader.vert", "lightShader.frag");

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	myCamera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	myShader.use();

	//ģ��λ��
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	myShader.setMatrix("model", model);
	myShader.setMatrix("projection", projection);
	myShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	myShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	myShader.setVec3("lightPos", lightPos);
	myShader.setVec3("viewPos", myCamera.Position);
	lightShader.use();
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 3.0f));
	lightShader.setMatrix("model", model);
	lightShader.setMatrix("projection", projection);

	//��������������
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//�������
	glfwSetCursorPosCallback(window, mouse_callback);//����ƶ��ص�

	//ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//ʱ��
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//��������
		ProcessInput(window);
		//�������������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.use();
 		myShader.setMatrix("view", myCamera.GetViewMatrix());
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader.use();
		lightShader.setMatrix("view", myCamera.GetViewMatrix());
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(0);



		glfwSwapBuffers(window);//��������
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void SetViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};

void ProcessInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		myCamera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		myCamera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		myCamera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		myCamera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);

	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	myCamera.ProcessMouseMovement(xoffset, yoffset);
}
