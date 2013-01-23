#include "Scene.h"

bool Scene::Render()
{
	m_RootNode.VRenderChildren(this);

	return true;
}

bool Scene::Update(const double elapsedTime)
{
	m_RootNode.VOnUpdate(this, elapsedTime);
	
	m_Camera.VOnUpdate(this, elapsedTime);

	return true;
}

bool Scene::AddNode(ISceneNode * node)
{
	m_RootNode.VAddChild(node);
	m_lastAddedNode = node;
	return true;
}

bool Scene::AddNode(const char * name)
{
	if (strcmp(name, "Test") == 0)
	{
		TestNode * node = new TestNode(
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f);
		m_RootNode.VAddChild(node);
		m_lastAddedNode = node;
		return true;
	}
	
	return false;
}