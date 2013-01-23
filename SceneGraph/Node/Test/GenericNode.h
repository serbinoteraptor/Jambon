#pragma once

#include <GLHeaders.h>

#include <vector>

class Mesh
{
protected:
  typedef std::vector<glm::detail::tvec3<GLfloat>> Vtvec3;
  typedef std::vector<glm::detail::tvec2<GLfloat>> Vtvec2;
  Vtvec3 vertices;
  Vtvec3 normales;
  Vtvec2 textures;
  //std::vector<glm::detail::tvec2<GLfloat>> faces;

public:
  void AddVertex(GLfloat x, GLfloat y, GLfloat z)
  {
    this->vertices.push_back(glm::detail::tvec3<GLfloat>(x, y, z));
  }
  void AddVertex(glm::detail::tvec3<GLfloat> const& v)
  {
    this->vertices.push_back(v);
  }

  void AddNormal(GLfloat x, GLfloat y, GLfloat z)
  {
    this->normales.push_back(glm::detail::tvec3<GLfloat>(x, y, z));
  }
  void AddNormal(glm::detail::tvec3<GLfloat> const& v)
  {
    this->normales.push_back(v);
  }

  void AddTexture(GLfloat u, GLfloat v)
  {
    this->textures.push_back(glm::detail::tvec2<GLfloat>(u, v));
  }
  void AddTexture(glm::detail::tvec2<GLfloat> const& v)
  {
    this->textures.push_back(v);
  }

  Vtvec3 const& GetVerticles() const { return this->vertices; }
  Vtvec3 const& GetNormales() const { return this->normales; }
  Vtvec2 const& GetTextures() const { return this->textures; }
}
