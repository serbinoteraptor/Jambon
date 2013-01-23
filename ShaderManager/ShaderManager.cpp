#include "ShaderManager.h"

ShaderManager * ShaderManager::m_pManager = NULL;

ShaderManager * ShaderManager::GetInstance(void)
{
	if (m_pManager == NULL)
		m_pManager = new ShaderManager();

	return m_pManager;
}

void ShaderManager::Kill()
{
	if (m_pManager != NULL)
	{
		delete m_pManager;
		m_pManager = NULL;
	}
}

ShaderManager::ShaderManager()
{
	//ParseShaderDir("Shad");
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::ParseShaderDir(const char * path)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(path, &FindFileData);

	do
	{
		if (! (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			LOG(FindFileData.cFileName);
		}
	}
	while (FindNextFile(hFind, &FindFileData) != 0);

	return true;
}