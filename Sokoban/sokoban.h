#pragma once

#include "utils.h"
#include "level_manager.h"
#include "player.h"
#include "box.h"

#include <vector>

/*
Sokoban to prosta gra 2d, w której zadaniem jest umieszczenie wszystkich pudeł na odpowiednich miejscach (w grze miejsca te są oznaczone gwiazdkami)
Gra zawiera 10 poziomów reprezentowanych w plikach tekstowych, które są przy ładowaniu parsowane i interpretowane graficznie dzięki bibliotekom SDL2 i SDL2image
Przypisanie klawiszy:
    -strzałki: poruszanie gracza po planszy
    -r: restart poziomu (gracz wraca do układu poziomu zapisanego w pliku tekstowym)
    -s: pominięcie poziomu (gracz przechodzi do następnego poziomu, jeśli to możliwe)
Uruchamianie gry:
    Należy wejść w folder projektu z kodem (folder nazywa się Sokoban), znaleźć oraz uruchomić plik Sokoban.exe
Możliwe niedogodności:
    -przy uruchomieniu gry pojawia się konsola, a gra za nią. Należy ją zminimalizować.
    -brak możliwości cofania się do poziomów
*/

class Game {

public:
    bool init();
    void gameloop();
    void shutdown();

    SDL_Texture* loadtexture(string path);
    bool hitwall(int x, int y);
    bool box_updated(int move_x, int move_y, int player_x, int player_y);

private:
    void handleevents();
    void update();
    void draw();

    bool hit_goal(int x, int y);
    bool all_goals_complete();
    void destroy_boxes();
    void init_level();
    void go_to_next_level();
    bool can_push_box(Box* box, int x, int y);

    bool isrunning = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Texture* wall_tex = nullptr;
    SDL_Texture* ground_tex = nullptr;
    SDL_Texture* box_tex = nullptr;
    SDL_Texture* goal_tex = nullptr;

    class level_manager* levelmanager;
    class Player* player;
    vector<Box*> boxes;
};

