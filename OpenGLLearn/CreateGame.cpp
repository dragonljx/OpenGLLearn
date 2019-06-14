#include "CreateGame.h"

CreateGame::CreateGame()
{
	//��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���ð汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ʹ�ú���ģʽ

	//������
	camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));

}


GLFWwindow* CreateGame::CreateScene(int width, int height, const char* name)
{
	GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "GLFW��������ʧ�ܣ�" << std::endl;
		glfwTerminate();
		return NULL;
	}
	allScene.push_back(window);
	glfwMakeContextCurrent(window);//ָ������context

	if (allScene.size()==1)
	{
		//��ʼ��glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD!" << std::endl;
		}
	}

	lastX = width / 2.0f;
	lastY = height / 2.0f;
	return window;
}

float CreateGame::GetDeltaTime()
{
	//ʱ��
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return deltaTime;
}

void CreateGame::Processinput()
{
	for (size_t i = 0; i < allScene.size(); i++)
	{
			
		if (glfwGetKey(allScene[i], GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(allScene[i], true);
		}
		if (glfwGetKey(allScene[i], GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		}
		if (glfwGetKey(allScene[i], GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

		}
		if (glfwGetKey(allScene[i], GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);

		}
		if (glfwGetKey(allScene[i], GLFW_KEY_S) == GLFW_PRESS)
		{

			camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);

		}
	}
}

void CreateGame::test(void* vv, char* text)
{
	CreateGame* ptr = (CreateGame*)vv;

}

