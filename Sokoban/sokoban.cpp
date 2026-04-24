#include "sokoban.h"

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        cout << "SDL failed to initialize: " << SDL_GetError() << endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        cout << "SDL_Image failed to initialize: " << IMG_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        cout << "Window failed to initialize: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        cout << "Renderer failed to initialize: " << SDL_GetError() << endl;
        return false;
    }
    levelmanager = new level_manager();
    levelmanager->loadlevel();

    wall_tex = loadtexture("textures/wall.png");
    ground_tex = loadtexture("textures/ground.png");
    box_tex = loadtexture("textures/box.png");
    goal_tex = loadtexture("textures/goal.png");

    player = new Player(this);

    init_level();

    return true;
}

void Game::gameloop() {
    while (isrunning) {
        handleevents();
        update();
        draw();
    }
}


void Game::handleevents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isrunning = false;
        }


        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                player->move(1, 0);
                break;
            case SDLK_LEFT:
                player->move(-1, 0);
                break;
            case SDLK_DOWN:
                player->move(0, 1);
                break;
            case SDLK_UP:
                player->move(0, -1);
                break;
            case SDLK_r:
                destroy_boxes();
                init_level();
                break;
            case SDLK_s:
                go_to_next_level();
                break;
            default:
                break;
            }
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_ESCAPE]) {
        isrunning = false;
    }

    if (levelmanager->current_level == LEVEL_MAX_NUMBER) {
        isrunning = false;
    }
}

void Game::update() {

}

void Game::draw() {
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < TILE_ROWS; i++) {
        for (int j = 0; j < TILE_COLS; j++) {

            SDL_Rect rect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            if (levelmanager->levelmap[j][i] == 'x') {
                SDL_RenderCopy(renderer, wall_tex, NULL, &rect);
            }
            else if (levelmanager->levelmap[j][i] == 'g') {
                SDL_RenderCopy(renderer, goal_tex, NULL, &rect);
            }
            else {
                SDL_RenderCopy(renderer, ground_tex, NULL, &rect);
            }

            //SDL_RenderFillRect(renderer, &rect);
        }

    }

    for (int i = 0; i < boxes.size(); i++) {
        SDL_RenderCopy(renderer, box_tex, NULL, boxes[i]->get_rect());
    }

    player->draw(renderer);

    SDL_RenderPresent(renderer);
}

void Game::shutdown() {
    SDL_DestroyTexture(wall_tex);
    SDL_DestroyTexture(ground_tex);
    SDL_DestroyTexture(box_tex);
    SDL_DestroyTexture(goal_tex);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Game::loadtexture(string path) {
    SDL_Surface* temp_s = IMG_Load(path.c_str());
    if (temp_s == NULL) {
        cout << "Failed to load surface: " << IMG_GetError() << endl;
    }

    SDL_Texture* newtex = SDL_CreateTextureFromSurface(renderer, temp_s);
    if (newtex == NULL) {
        cout << "Failed to conver the texture: " << SDL_GetError() << endl;
    }

    SDL_FreeSurface(temp_s);

    return newtex;
}

bool Game::hitwall(int x, int y) {
    return levelmanager->levelmap[x][y] == 'x';
}

bool Game::can_push_box(Box* box, int x, int y) {

    if (hitwall(x, y)) {
        return false;
    }

    for (int i = 0; i < boxes.size(); i++) {
        if (boxes[i] == box) {
            continue;
        }
        else if (x == boxes[i]->get_pos().x and y == boxes[i]->get_pos().y) {
            return false;
        }
    }

    return true;
}

bool Game::box_updated(int move_x, int move_y, int player_x, int player_y) {

    Box* box_to_push = nullptr;

    for (int i = 0; i < boxes.size(); i++) {
        if (player_x == boxes[i]->get_pos().x and player_y == boxes[i]->get_pos().y) {
            box_to_push = boxes[i];
        }
    }

    if (box_to_push != nullptr) {

        int to_push_x = player_x + move_x;
        int to_push_y = player_y + move_y;

        if (can_push_box(box_to_push, to_push_x, to_push_y)) {

            bool in_goal = hit_goal(to_push_x, to_push_y);
            box_to_push->update(to_push_x, to_push_y, in_goal);
            if (all_goals_complete()) {
                go_to_next_level();
                return false;
            }
        }
        else {
            return false;
        }
    }

    return true;
}

bool Game::hit_goal(int x, int y) {
    return levelmanager->levelmap[x][y] == 'g';
}

bool Game::all_goals_complete()
{
    for (int i = 0; i < boxes.size(); i++) {
        if (!boxes[i]->get_in_goal()) {
            return false;
        }
    }

    return true;
}

void Game::destroy_boxes() {

    for (int i = 0; i < boxes.size(); i++) {
        delete boxes[i];
    }

    boxes.erase(boxes.begin(), boxes.end());
}

void Game::init_level() {
    for (int i = 0; i < TILE_ROWS; i++) {
        for (int j = 0; j < TILE_COLS; j++) {
            if (levelmanager->levelmap[j][i] == 'p') {
                player->reset(j, i);
            }
            else if (levelmanager->levelmap[j][i] == 'b') {
                boxes.emplace_back(new Box(j, i));
            }
        }
    }
}

void Game::go_to_next_level() {

    destroy_boxes();

    levelmanager->update_level();
    levelmanager->loadlevel();

    init_level();
}
