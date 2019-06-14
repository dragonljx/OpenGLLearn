#include "CreateGame.h"

CreateGame game;
void SetViewport(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);

int main() {

	GLFWwindow* window = game.CreateScene(800, 600, "xxxx");

	glfwSetFramebufferSizeCallback(window, SetViewport);//设置窗口回调
	glfwSetCursorPosCallback(window, MouseCallback);//鼠标移动回调

	while (!glfwWindowShouldClose(window))
	{
		game.Processinput();
		glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);//交换缓冲
		glfwPollEvents();

	}
	return 0;
}




void SetViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (game.firstMouse)
	{
		game.lastX = xpos;
		game.lastY = ypos;
		game.firstMouse = false;
	}

	float xoffset = xpos - game.lastX;
	float yoffset = game.lastY - ypos; // reversed since y-coordinates go from bottom to top

	game.lastX = xpos;
	game.lastY = ypos;

	game.camera.ProcessMouseMovement(xoffset, yoffset);
}