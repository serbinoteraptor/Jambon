#include "Mesh.hpp"

#include "../utility/string.hpp"
// #include "utility/string.hpp"

#include <fstream>
#include <string>
#include <iostream>

void Mesh::Load(std::string const& filename, Mesh* next)
{
  std::ifstream file(filename, std::ios::in);

  if (!file.good())
  {
    std::cout << "File doesn't exist or is corrupted." << std::endl;
    //throw std::exception("File doesn't exist or is corrupted.");
  }
  std::string line;

  while (std::getline(file, line))
  {
    if (line.length() == 0)
      continue;

    if (line[0] == 'o')
    {
      // XXX: A obj file can contain more than one mesh.
      // For the moment, just break and ignore other objects.
      // The best way is probably an .obj parser that can generate as many Mesh
      // from a .obj, using regular setters.
      if (this->_name.length() > 0)
        break;

      char name[256];
      std::sscanf(line.c_str(), "o %s", name);
      this->_name = name;
    }
    else if (line[0] == 'v') // Vertex, normal, texture.
    {
      if (line[1] == ' ') // Vertex.
      {
        GLfloat x, y, z = -1;
        std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
        this->_vertices.push_back({x, y, z});
      }
      else if (line[1] == 'n') // Normale.
      {
        GLfloat x, y, z = -1;
        std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
        this->_normales.push_back({x, y, z});
      }
      else if (line[1] == 't') // Texture.
      {
        GLfloat u, v = -1;
        std::sscanf(line.c_str(), "v %f %f", &u, &v);
        this->_textures.push_back({u, v});
      }
      else
      {
        //XXX: file is bad formed.
      }
    }
    else if (line[0] == 'f') // Face
    {
      char res[3][32];
      int c = sscanf(line.c_str(), "f %s %s %s", res[0], res[1], res[2]);

      Sommet s0(res[0]), s1(res[1]), s2(res[2]);

      this->_faces.push_back(Triangle({s0, s1, s2}));
    }
    else if (line[0] == 'm') // Material.
    {

    }
  }
}
