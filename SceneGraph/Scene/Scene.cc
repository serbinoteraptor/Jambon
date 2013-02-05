#include "Scene.hh"
#include "log.hh"

#include <cstddef>
#include <stdexcept>

Scene::Scene()
{
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

bool
Scene::AddNode(ISceneNode *node)
{
  return _root_node.VAddChild(node);
}

bool
Scene::AddNode(std::string const& name)
{
  if (name == "Test")
  {
    static unsigned char color = 0x01;

    if (color == 0x08)
      color = 0x01;

    LOG("seriously ?");
    TestNode * node = new TestNode(2 * color);

    LOG("seriously");
    return _root_node.VAddChild(node);
  }

  return nullptr;
}


namespace factory
{
  TestNode*
  newTestNode(unsigned char rgb)
  {
    return new TestNode(rgb);
  }

  TestNode*
  addTestNode(Scene& sc, unsigned char rgb)
  {
    TestNode* t = newTestNode(rgb);

    if (!sc.AddNode(t))
      throw std::runtime_error("couldn't add node to scene");

    return t;
  }
}
