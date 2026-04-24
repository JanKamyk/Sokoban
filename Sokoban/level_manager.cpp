#include "level_manager.h"

void level_manager::loadlevel() {

    int row_c = 0, col_c = 0;

    string path = "levels/level" + to_string(current_level) + ".txt";

    levelfile.open(path);

    if (levelfile.is_open()) {
        char inchar;
        while (levelfile.get(inchar)) {
            if (inchar == '\n') {
                col_c = 0;
                row_c++;
            }
            else {
                levelmap[col_c][row_c] = inchar;
                col_c++;
            }
        }
    }
    levelfile.close();

}

void level_manager::update_level() {
    current_level++;
}