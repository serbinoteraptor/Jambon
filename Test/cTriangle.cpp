#include "cTriangle.h"

cTriangle::cTriangle(GLfloat xx, GLfloat xy, GLfloat xz, GLfloat yx, GLfloat yy, GLfloat yz, GLfloat zx, GLfloat zy, GLfloat zz)
{
  glGenBuffers(1, &vertexBuffer);

  //mat = glm::mat4(1.0f);
  bdv[0] = xx;
  bdv[1] = xy;
  bdv[2] = xz;
  bdv[3] = yx;
  bdv[4] = yy;
  bdv[5] = yz;
  bdv[6] = zx;
  bdv[7] = zy;
  bdv[8] = zz;

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(bdv), bdv, GL_STATIC_DRAW);
}

cTriangle::~cTriangle(void)
{
  glDeleteBuffers(1, &vertexBuffer);
}
cTriangle::cTriangle(const cTriangle & _input)
{
  memcpy(bdv, _input.bdv, 9 * sizeof(GLfloat));
  mat = _input.mat;
}

void cTriangle::Render()
{
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(
    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // From index 0 to 3 -> 1 triangle

  glDisableVertexAttribArray(0);
}
