#include <vector>
#include <iostream>
#include <functional>
#include <cassert>
#include <algorithm>
// #include <GLHeaders.h>

// They are only 2 normales, depending on which side it's oriented.
// Normales can be store for each face or as a list on Mesh.
// In order to bench, normales are duplicated to see wich way is the fastest
// and/or the most flexible.
// That just increase loading time and memory, but doesn't impact performance.

// XXX: Wait for GLHeaders.h

namespace glm
{
  namespace detail
  {
    template<typename T>
    struct tvec3 : public std::vector<T>
    {
      tvec3(T, T, T){};
    };

    template<typename T>
    struct tvec2 : public std::vector<T>
    {
      tvec2(T, T) {};
    };
  }
}

#define GLfloat float

template<typename T>
std::vector<T> const&
prefiled_vector(T&& value, int count)
{
  static std::vector<T> ret;
  if (ret.size() == count)
    return ret;

  ret.clear();

  //std::fill_n(ret, count, value);
  for(int i = 0; i < count; ++i)
    ret.push_back(value);

  return ret;
}

struct Sommet
{
  int v, vn, vt;

  Sommet(std::string const& init):
    v(-1),
    vn(-1),
    vt(-1)
  {
    // Use an function to avoid exception in ctor.
    this->Load(init);
  }

  Sommet(int v, int vn, int vt):
    v(-1),
    vn(-1),
    vt(-1)
  {
  }

  void Load(std::string const& init)
  {
    try
    {
      int slashs = std::count(init.begin(), init.end(), '/');
      switch(slashs)
      {
        case 0:
          v = std::stoi(init);
          break;
        case 1:
          //XXX: Is that really safe ?
          std::sscanf(init.c_str(), "%d/%d", &this->v, &this->vn);
          break;
        case 2:
          //XXX: Cleary not the safest method. But it should work in most of the cases.
          std::sscanf(init.c_str(), "%d/%d/%d", &this->v, &this->vn, &this->vt);
          if (this->vt == -1)
            std::sscanf(init.c_str(), "%d//%d", &this->v, &this->vt);
      }
    }
    catch (std::exception const& e)
    {
      //XXX: Suxx case...
    }

  }
};

template <int i>
struct Polygon
{
  std::vector<Sommet> sommets;

public:
  Polygon(std::vector<int> const& v,
          std::vector<int> const& vt = prefiled_vector(-1, i),
          std::vector<int> const& vn = prefiled_vector(-1, i))
  {
    assert(v.size() == i);
    assert(vn.size() == i);
    assert(vt.size() == i);

    for (int k = 0; k < i; ++k)
      this->sommets.push_back(Sommet(v[k], vt[k], vn[k]));
  }

  Polygon(std::vector<Sommet> const& v)
    : sommets(v)
  {
    assert(v.size() == i);
  }
};
typedef Polygon<3> Triangle;

class Mesh
{
  typedef std::vector<glm::detail::tvec3<GLfloat>> Vvec3;
  typedef std::vector<glm::detail::tvec2<GLfloat>> Vvec2;

private:
  std::string _name;
  Vvec3 _vertices;
  Vvec3 _normales;
  Vvec2 _textures;
  std::vector<Triangle> _faces;

  void Load(std::string const& file, Mesh* next);

  void AddVertex(glm::detail::tvec3<GLfloat> const& v)
  { this->_vertices.push_back(v); }

  void AddVertex(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f)
  { this->_vertices.push_back(glm::detail::tvec3<GLfloat>(x, y, z)); }

  void AddNormal(glm::detail::tvec3<GLfloat> const& v)
  { this->_normales.push_back(v); }

  void AddNormal(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f)
  { this->_normales.push_back(glm::detail::tvec3<GLfloat>(x, y, z)); }

  void AddTexture(glm::detail::tvec2<GLfloat> const& v)
  { this->_textures.push_back(v); }

  void AddTexture(GLfloat u = 0.0f, GLfloat v = 0.0f)
  { this->_textures.push_back(glm::detail::tvec2<GLfloat>(u, v)); }

public:
  Vvec3 const&
  Vertices() const { return this->_vertices; }

  Vvec3 const&
  Normales() const { return this->_normales; }

  Vvec2 const&
  Textures() const { return this->_textures; }
};

int
main(int argc, char** argv)
{

}
