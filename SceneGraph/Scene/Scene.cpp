#include "Scene.h"
#include <cstddef>

Scene::Scene()
{
  this->_last_added_node = NULL;
}

bool Scene::Render()
{
  _root_node.VRenderChildren(this);

  return true;
}

bool Scene::Update(const double elapsedTime)
{
  _root_node.VOnUpdate(this, elapsedTime);

  _camera.VOnUpdate(this, elapsedTime);

  return true;
}

bool Scene::AddNode(ISceneNode * node)
{
  _root_node.VAddChild(node);
  _last_added_node = node;
  return true;
}

bool Scene::AddNode(std::string const& name)
{
  if (name == "Test")
  {
    TestNode * node = new TestNode(
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      0.0f,  1.0f, 0.0f);
    _root_node.VAddChild(node);
    _last_added_node = node;
    return true;
  }

  return false;
}
