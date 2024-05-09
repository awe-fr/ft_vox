#pragma once

#include <thread>
#include <stdbool.h>

#include <Model/Model.hpp>
#include <View/View.hpp>

class Controller
{
    public:
        Controller(void);
        ~Controller(void);

        void updateMap(Controller *control, std::array<int, 2> prev_pos, std::array<int, 2> new_pos);
        void isOkayToBind(int i, int j, ViewChunk *chunk, bool reset);
        void loop(void);
        bool    _closeThread;
        bool    _binder[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
    private:
        static void routineThread(Controller *control, std::array<int, 2> *current_pos, PlayerInfo *player, WindowApp *app);
        Model   *_model;
        View    *_view;
};