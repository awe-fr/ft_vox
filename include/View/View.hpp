#pragma once

#include "ViewVars.hpp"
#include "ViewMap.hpp"
#include "WindowApp.hpp"
#include "PlayerInfo.hpp"
#include <Model/BlockMap.hpp>

class View
{
    public:
        View(BlockMap *block_map);
        ~View(void);
    
    private:
        ViewMap *_map;
        WindowApp *_window_app;
        PlayerInfo *_player_info;
};

GLuint  LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint  loadpng(const char *path);