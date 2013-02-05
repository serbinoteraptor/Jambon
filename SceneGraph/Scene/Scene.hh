#pragma once

#include <SceneGraph/Node/CameraNode.hh>
#include <SceneGraph/Node/RootNode.hh>
#include <SceneGraph/Node/Test/TestNode.hh>


class Scene
{
public:
  Scene();
  virtual ~Scene() {};

private:
  CameraNode  _camera;
  RootNode    _root_node;

public :
  CameraNode & GetCamera (void) { return _camera; }
  bool Render();
  bool Update(const double elapsedTime);
  bool AddNode(ISceneNode * node);
  bool AddNode(std::string const& name);
};

namespace factory
{
  TestNode*
  newTestNode(unsigned char rgb);

  TestNode*
  addTestNode(Scene& sc, unsigned char rgb);
}
