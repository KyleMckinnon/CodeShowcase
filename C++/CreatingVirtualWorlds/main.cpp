
#include "core.h"
#include <math.h>
#include "cMesh.h"
#include "cCamera.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

using namespace std;
using namespace glm;

/////////////////////////////////////////////////////////////////////////////////////
// global variables
/////////////////////////////////////////////////////////////////////////////////////
cScene Scene;

unsigned int initWidth = 1920;
unsigned int initHeight = 1080;

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void resize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}

float speed = 0.1;
float rotSpeed = 0.0005;

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	// ignore key up (key release) events
	if (action == GLFW_RELEASE) 
		return;	

	// pointer to the currently selected camera..
	cCamera* pCamera = &Scene.m_Camera[Scene.m_cameraId];
	cLight* pLight = &Scene.m_Light[Scene.m_lightId];

	// process keyboard inputs here..
	switch (key)
	{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
		break;

		case GLFW_KEY_LEFT_SHIFT:
		{
			Scene.m_cameraId = Scene.m_cameraId < Scene.m_camera_count - 1 ? Scene.m_cameraId + 1 : 0;
		}
		break;

		case GLFW_KEY_4:
		{
			Scene.m_lightId = Scene.m_lightId < Scene.m_light_count - 1 ? Scene.m_lightId + 1 : 0;
		}
		break;

		case GLFW_KEY_1:
		{
			if (mods == 1)
				pLight->m_info.m_att.x = (pLight->m_info.m_att.x <= 0.9f) ? pLight->m_info.m_att.x+0.1f : 1.0f;
			else
				pLight->m_info.m_att.x = (pLight->m_info.m_att.x >= 0.1f) ? pLight->m_info.m_att.x-0.1f : 0.0f;
		}break;

		case GLFW_KEY_2:
		{
			if (mods == 1)
				pLight->m_info.m_att.y = (pLight->m_info.m_att.y <= 0.9f) ? pLight->m_info.m_att.y+0.1f : 1.0f;
			else
				pLight->m_info.m_att.y = (pLight->m_info.m_att.y >= 0.1f) ? pLight->m_info.m_att.y-0.1f : 0.0f;
		}break;

		case GLFW_KEY_3:
		{
			if (mods == 1)
				pLight->m_info.m_att.z = (pLight->m_info.m_att.z <= 0.9f) ? pLight->m_info.m_att.z+0.1f : 1.0f;
			else
				pLight->m_info.m_att.z = (pLight->m_info.m_att.z >= 0.1f) ? pLight->m_info.m_att.z-0.1f : 0.0f;
		}break;

		case GLFW_KEY_X:
		{
			if (mods == 1) // shift
				pLight->m_info.m_pos.x-=0.1f;
			else
				pLight->m_info.m_pos.x+= 0.1f;
		}break;
		case GLFW_KEY_Y:
		{
			if (mods == 1) // shift
				pLight->m_info.m_pos.y-= 0.1f;
			else
				pLight->m_info.m_pos.y+= 0.1f;
		}break;
		case GLFW_KEY_Z:
		{
			if (mods == 1) // shift
				pLight->m_info.m_pos.z-= 0.1f;
			else
				pLight->m_info.m_pos.z+= 0.1f;
		}break;

		// simple camera controls to help navigate the scene
		
		case GLFW_KEY_W:
		{
			// move camera forwards
			pCamera->m_pos += pCamera->m_dir * speed;
		}break;

		case GLFW_KEY_S:
		{
			// move camera back
			pCamera->m_pos -= pCamera->m_dir * speed;
		}break;

		case GLFW_KEY_LEFT:
		{
			// rotate camera about the yaw 
			pCamera->m_rot.y -= 1.0f;			
		}break;
		case GLFW_KEY_RIGHT:
		{
			// rotate camera about the yaw
			pCamera->m_rot.y += 1.0f;
		}break;
		case GLFW_KEY_UP:
		{
			// rotate camera about the pitch 
			pCamera->m_rot.x += 1.0f;
		}break;
		case GLFW_KEY_DOWN:
		{
			// rotate camera about the pitch
			pCamera->m_rot.x -= 1.0f;
		}break;

		default:
		{
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// renderScene
/////////////////////////////////////////////////////////////////////////////////////
void renderScene()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);

	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	////////////////////////////////////////////////////////////////////////////////
	// Render mesh objects here..
	////////////////////////////////////////////////////////////////////////////////
	Scene.render();

	glBindVertexArray(0);    



}

/////////////////////////////////////////////////////////////////////////////////////
// printDebugInfo() - print version info to console
/////////////////////////////////////////////////////////////////////////////////////
void printDebugInfo()
{
	// Print info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

#ifdef GL_SHADING_LANGUAGE_VERSION
	printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

	printf("Using GLEW version %s.\n", glewGetString(GLEW_VERSION));
	printf("------------------------------\n");
	printf("Press ESCAPE or 'X' or 'x' to exit.\n");
}

/////////////////////////////////////////////////////////////////////////////////////
// DebugOutput
// Used to output openGL debug info
// KHR_debug runs on all systems running openGL4.3 or later
/////////////////////////////////////////////////////////////////////////////////////
void DebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	cout << "debug call: " << msg << endl;
}

#include <stack>

void matrixStackPushPop_Example()
{
	stack<string> matrixStack;

	// torso
	string model = "Torso:";
	cout << model << "\n";

	// head
	matrixStack.push(model);
	model = model + "Head:";
	cout << model << "\n";

	// get back to the torso..
	model = matrixStack.top();
	matrixStack.pop();

}

/////////////////////////////////////////////////////////////////////////////////////
// main()
/////////////////////////////////////////////////////////////////////////////////////
int main() 
{
//	matrixStackPushPop_Example();

	// initialise glfw
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "GraphicsTemplate", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stdout, "Failed to create GLFW window!\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	
	// initialise glew
	glewInit();

	// print version info 
	printDebugInfo();

	glDebugMessageCallback(DebugOutput, NULL);

	// Set callback function for resizing the window
	glfwSetFramebufferSizeCallback(window, resize);

	// Set callback for keyboard events
	glfwSetKeyCallback(window, keyboard);

	resize(window, initWidth, initHeight);

	////////////////////////////////////////////////////
	// initialise scene - geometry and shaders etc
	////////////////////////////////////////////////////
	Scene.init(initWidth, initHeight);

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		renderScene();					// Render into the current buffer
		glfwSwapBuffers(window);		// Displays what was just rendered (using double buffering).

		glfwPollEvents();				// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}

