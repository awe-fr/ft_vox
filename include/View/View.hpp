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

        ViewMap *getViewMap(void);
        WindowApp *getWindowApp(void);
        PlayerInfo *getPlayerInfo(void);
        GLuint &getProgramId(void);
        GLuint &getTextu(void);
        GLuint &getProjectionId(void);
        GLuint &getViewId(void);
        GLuint &getModelId(void);
    
    private:
        ViewMap *_map;
        WindowApp *_window_app;
        PlayerInfo *_player_info;
        GLuint _program_id;
        GLuint _textu;
        GLuint _projection_id;
        GLuint _view_id;
        GLuint _model_id;
};

GLuint  LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint  loadpng(const char *path);
void    getDeltaTime(void);