#include "sokoban.h"

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

int main(int argc, char* argv[]) {

    Game game;
    if (game.init()) {
        game.gameloop();
    }

    game.shutdown();

    return 0;
}