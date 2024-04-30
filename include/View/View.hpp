#pragma once

#include "ViewVars.hpp"

class View
{
    public:
        View(void);
        ~View(void);
    
    private:
};

GLuint  LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint  loadpng(const char *path);