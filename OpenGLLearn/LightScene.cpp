//#define STB_IMAGE_IMPLEMENTATION
//
//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include "stb_image.h"
//#include "Data.h"
//#include "Shader.h"
//#include "Camera.h"
//
//
//glm::vec3 cubePositions[] = {
//	glm::vec3(0.0f,  0.0f,  0.0f),
//	glm::vec3(2.0f,  5.0f, -15.0f),
//	glm::vec3(-1.5f, -2.2f, -2.5f),
//	glm::vec3(-3.8f, -2.0f, -12.3f),
//	glm::vec3(2.4f, -0.4f, -3.5f),
//	glm::vec3(-1.7f,  3.0f, -7.5f),
//	glm::vec3(1.3f, -2.0f, -2.5f),
//	glm::vec3(1.5f,  2.0f, -2.5f),
//	glm::vec3(1.5f,  0.2f, -1.5f),
//	glm::vec3(-1.3f,  1.0f, -1.5f)
//};
//
//
//
//void SetViewport(GLFWwindow* window, int width, int height);
//void ProcessInput(GLFWwindow* window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//unsigned int loadTexture(char const* path);
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//Camera myCamera;
//
//
//int main() {
//#pragma region 初始化
//
//	//创建窗口
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版本号
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//设置使用核心模式
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", NULL, NULL);
//
//	if (window == NULL)
//	{
//		std::cout << "GLFW创建窗口失败！" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);//指定窗口context
//	glfwSetFramebufferSizeCallback(window, SetViewport);//设置窗口回调
//
//	//初始化glad
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD!" << std::endl;
//		return -1;
//	}
//
//#pragma endregion
//
//
//	unsigned int VAO, VBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);	
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	unsigned int lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//
//
//	// 摄像机
//	myCamera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));
//	glm::mat4 projection = glm::mat4(1.0f);
//	projection = glm::perspective(glm::radians(myCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//
//	// 贴图
//	unsigned int texture = loadTexture("../Asset/Images/container2.png");
//	unsigned int specularMap = loadTexture("../Asset/Images/container2_specular.png");
//
//	// shader
//	Shader myShader = Shader("default.vert", "default.frag");
//	Shader lightShader = Shader("lightShader.vert", "lightShader.frag");
//	myShader.use();
//
//
//	// 默认材质
//	myShader.setVec3("light.position", myCamera.Position);
//	myShader.setVec3("light.direction", myCamera.Front);
//	myShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//	myShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//	myShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
//	myShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
//	myShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//	myShader.setFloat("light.constant", 1.0f);
//	myShader.setFloat("light.linear", 0.09f);
//	myShader.setFloat("light.quadratic", 0.032f);
//	// material properties
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	myShader.setInt("material.diffuse", 0);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, specularMap);
//	myShader.setInt("material.specular", 1);
//	myShader.setFloat("material.shininess", 64.0f);
//	// view/projection transformations
//	glm::mat4 view = myCamera.GetViewMatrix();
//	myShader.setMat4("projection", projection);
//	myShader.setMat4("view", view);
//
//	// world transformation
//	glm::mat4 model = glm::mat4(1.0f);
//	myShader.setMat4("model", model);
//	// 漫反射贴图
//
//	// 灯光
//	lightShader.use();
//	model = glm::translate(model, lightPos);
//	model = glm::scale(model, glm::vec3(0.2f));
//	lightShader.setMatrix("model", model);
//	lightShader.setMatrix("projection", projection);
//	
//	//启动上下文属性
//	glEnable(GL_DEPTH_TEST);//启动深度测试
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
//	glfwSetCursorPosCallback(window, mouse_callback);//鼠标移动回调
//
//	//循环
//	while (!glfwWindowShouldClose(window))
//	{
//		//时间
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		//按键触发
//		ProcessInput(window);
//		//背景和清除缓存
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//		lightShader.use();
//		lightShader.setMatrix("view", myCamera.GetViewMatrix());
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//		myShader.use();
//		myShader.setVec3("viewPos", myCamera.Position);
// 		myShader.setMatrix("view", myCamera.GetViewMatrix());
//		model = glm::mat4(1.0f);
//		glBindVertexArray(VAO);
//
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			// calculate the model matrix for each object and pass it to shader before drawing
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			myShader.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		glBindVertexArray(0);
//
//
//
//		glfwSwapBuffers(window);//交换缓冲
//		glfwPollEvents();
//
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}
//
//void SetViewport(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//};
//
//void ProcessInput(GLFWwindow* window)
//{
//
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	{
//		myCamera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	{
//		myCamera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
//
//	}
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		myCamera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
//
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	{
//
//		myCamera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
//
//	}
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	myCamera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//unsigned int loadTexture(char const* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
