#pragma once

#include <thread>
#include <mutex>
#include <stdbool.h>

#include <Model/Model.hpp>
#include <View/View.hpp>

struct CustomVec {
    std::array<int, 2> _older;
    std::array<int, 2> _new;
};

class Controller
{
    public:
        Controller(void);
        ~Controller(void);

        void isOkayToBind(int i, int j, ViewChunk *chunk, bool reset);
        void loop(void);
        std::vector<CustomVec> queue;
        bool    _closeThread;
    private:
        static void updateMap(Controller *control, std::array<int, 2> prev_pos, std::array<int, 2> new_pos);
        static void routineThread(Controller *control, std::array<int, 2> *current_pos, PlayerInfo *player, WindowApp *app);
        Model   *_model;
        View    *_view;
};