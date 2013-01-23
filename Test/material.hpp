#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Load a .TGA file using GLFW's own loader
GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

template <int n>
class C
{
public :
	const static int csi;
	C(void) { printf("A\n"); }
};

template <int n>
const int C<n>::csi = n;

#endif