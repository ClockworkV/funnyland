#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Board.h"
#include "Funnimal.h"
#include "Annimal.h"
#include "Bnnimal.h"
#include "Onnimal.h"

class GameEngine
{
    public:
        GameEngine(Dim2 dim);
        ~GameEngine();

        void init(int numFunnimals = 0);
        void step();
        void printBoard();
        void printFunnimals();
//        void report(); // TODO

    private:
        void addRandomFunnimalToBoard(Address a);
        Funnimal randomFunnimal();
        Address randomAddress();

        BoardPtr board_;
        FunnimalVec funnimals_;
        FunnimalVec tempFunnimals_;

};

#endif // GAMEENGINE_H
