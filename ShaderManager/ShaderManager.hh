#pragma once

#include <GLHeaders.hh>

#include <map>
#include <string>

#ifdef DEBUG
#include <iostream>
#define LOG(x)	std::cout << (x) << std::endl;
#else
#define LOG(X)
#endif

typedef std::map<std::string, int> ShaderMap;

class ShaderManager
{
public :
	static ShaderManager * GetInstance(void);
	static void Kill();
	bool ParseShaderDir(const char * path);

private :
	static ShaderManager * m_pManager;
	ShaderManager();
	~ShaderManager();

};
