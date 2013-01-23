#include "GLManager.h"
#include "ShaderManager\ShaderManager.h"


int main(int argc, char **argv)
{
	GLManager * manager = GLManager::GetInstance();
	manager->InitOpenGL(1024, 768, "Playground");

	manager->AddNode("Test");
	manager->GetLastAddedNode()->VTranslate(1, 1, 1);

	manager->AddNode("Test2");
	manager->GetLastAddedNode()->VTranslate(-1, -1, -1);

	// Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

	// Dark blue background
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

    do{
		manager->Loop();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
           glfwGetWindowParam( GLFW_OPENED ) );

	manager->Kill();
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
