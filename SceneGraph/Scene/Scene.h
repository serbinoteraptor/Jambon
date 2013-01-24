#pragma once

#include <SceneGraph/Node/CameraNode.h>
#include <SceneGraph/Node/RootNode.h>
#include <SceneGraph/Node/Test/TestNode.h>


class Scene
{
public:
  Scene();
  virtual ~Scene() {};

private:
  CameraNode  _camera;
  RootNode    _root_node;
  // _last_added_node point on the last element which will be detroyed.
  ISceneNode* _last_added_node;

public :
  CameraNode & GetCamera (void) { return _camera; }
  bool Render();
  bool Update(const double elapsedTime);
  bool AddNode(ISceneNode * node);
  bool AddNode(std::string const& name);

  ISceneNode * GetLastAddedNode () { assert(this->_last_added_node != NULL); return _last_added_node; }
};
