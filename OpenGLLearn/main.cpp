//#include "CreateGame.h"
//#include "Shader.h"
//#include "Model.h"
//
//CreateGame game;
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//void SetViewport(GLFWwindow* window, int width, int height);
//void MouseCallback(GLFWwindow* window, double xpos, double ypos);
//
//int main() {
//
//	GLFWwindow* window = game.CreateScene(800, 600, "xxxx");
//
//	glfwSetFramebufferSizeCallback(window, SetViewport);//设置窗口回调
//	glfwSetCursorPosCallback(window, MouseCallback);//鼠标移动回调
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
//
//	glEnable(GL_DEPTH_TEST);
//	Shader ourShader("default.vert", "default.frag");
//	Model ourModel("../Asset/models/nanosuit/nanosuit.obj");
//	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
//
//	while (!glfwWindowShouldClose(window))
//	{
//		game.GetDeltaTime();
//		game.Processinput();
//		glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		ourShader.use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("view", view);
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		ourModel.Draw(ourShader);
//
//		glfwSwapBuffers(window);//交换缓冲
//		glfwPollEvents();
//
//	}
//	return 0;
//}
//
//
//
//
//void SetViewport(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//void MouseCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (game.firstMouse)
//	{
//		game.lastX = xpos;
//		game.lastY = ypos;
//		game.firstMouse = false;
//	}
//
//	float xoffset = xpos - game.lastX;
//	float yoffset = game.lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	game.lastX = xpos;
//	game.lastY = ypos;
//
//	game.camera.ProcessMouseMovement(xoffset, yoffset);
//}