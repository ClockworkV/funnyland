#include <iostream>
#include "Board.h"
#include "Funnimal.h"
#include "Annimal.h"

#include "GameEngine.h"

using namespace std;

int main()
{
    randomize(200);

    GameEngine GE({DEFAULT_BOARD_I, DEFAULT_BOARD_J});
    GE.init();
    GE.printBoard();
    GE.printFunnimals();

    for (int i = 0; i < 10 ; ++i) {
        GE.step();
        GE.printBoard();
    }
    return 0;
}
