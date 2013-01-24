#pragma once
#ifndef __CTriangle__H__
#define __CTriangle__H__

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class cTriangle
{
  public :
  GLfloat bdv[9];
  glm::mat4 mat;
  GLuint vertexBuffer;

  public :
  cTriangle(GLfloat xx, GLfloat xy, GLfloat xz, GLfloat yx, GLfloat yy, GLfloat yz, GLfloat zx, GLfloat zy, GLfloat zz);
  cTriangle(const cTriangle & _input);
  ~cTriangle(void);

  glm::mat4 & GetMatrix(void)
  {
    return mat;
  }
  glm::mat4 GetMatrix(void) const { return mat; }
  void Render();
  void Rotate(const GLfloat &angle, const glm::detail::tvec3<GLfloat> &v)
  {
    mat = glm::rotate(mat, angle, v);
  }

  void Translate(const glm::detail::tvec3<GLfloat> &v)
  {
    mat = glm::translate(mat, v);
  }

  void Scale(const glm::detail::tvec3<GLfloat> &v)
  {
    mat = glm::scale(mat, v);
  }
  //cTriangle(const glm::mat3 & _input);
  //cTriangle(const glm::vec3 & x, const glm::vec3 & y, const glm::vec3 & z);

};

#endif	//__CTriangle__CPP__
