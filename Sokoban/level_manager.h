#pragma once

#include "utils.h"

#include <fstream>
#include <string>

class level_manager {

public:
    void loadlevel();
    void update_level();
    char levelmap[TILE_ROWS][TILE_COLS] = { '0' };
    int current_level = 1;

private:
    ifstream levelfile;
};