#include "GLManager.hh"
#include "ShaderManager/ShaderManager.hh"

#include "log.hh"
#include "SceneGraph/Node/Test/TestNode.hh"
#include "SceneGraph/Node/Test/CubeNode.hh"

int main(int argc, char **argv)
{
  GLManager * manager = GLManager::GetInstance();

  manager->InitOpenGL(WIDTH, HEIGHT, "Playground");

  TestNode *t = new TestNode(0x02);

  CubeNode *c = new CubeNode();

  manager->AddNode(t);
  manager->AddNode(c);

  t->VTranslate(1, 1, 1);
  c->VTranslate(1, 1, -1);

  // Ensure we can capture the escape key being pressed below
  // glfwEnable( GLFW_STICKY_KEYS );

  // Dark blue background
  glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

  do {
    manager->Loop();
  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
         glfwGetWindowParam( GLFW_OPENED ) );

  manager->Kill();

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
