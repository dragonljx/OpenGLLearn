#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"


//template<typename tt,typename void*>
class CreateGame
{
public:
	CreateGame();
	std::vector<GLFWwindow*> allScene;
	Camera camera;
	bool firstMouse = true;
	float lastX = 0;
	float lastY = 0;
private:
	float deltaTime = 0;
	float lastFrame = 0;
public:
	GLFWwindow* CreateScene(int width, int height, const char* name);
	float GetDeltaTime();
	void Processinput();
	static void test(void* vv, char* text);

};
