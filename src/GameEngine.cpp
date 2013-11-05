#include "GameEngine.h"
#include <algorithm>

using namespace std;

GameEngine::GameEngine(Dim2 dim = {DEFAULT_BOARD_I, DEFAULT_BOARD_J})
{
    board_ = make_shared<Board>(dim);
}

GameEngine::~GameEngine()
{
    //dtor
}

void GameEngine::init(int numFunnimals)
{                                       // add pieces to the board and container
    Address a = randomAddress();
    if (0 != numFunnimals){
        // Fill with numFunnimals at random spots
        for(;numFunnimals > 0; --numFunnimals) {
            while(!(board_->empty(a))){
                a = randomAddress();
            }
            addRandomFunnimalToBoard(a);
        }
    } else {
        // Fill with random funnimals at random spots till spot is not empty
        while(board_->empty(a)) {
            addRandomFunnimalToBoard(a);
            a = randomAddress();
        }
    }
}

void GameEngine::step()
{
    for (Funnimal f: funnimals_) {
        auto child = f->move();
        if (child) {
            tempFunnimals_.push_back(child);
        }
    }
    funnimals_.erase(remove_if(funnimals_.begin(), funnimals_.end(), [](Funnimal f) {
        return (f->getLP() <= 0);
    }), funnimals_.end());
    for (Funnimal f: tempFunnimals_) {
        funnimals_.push_back(f);
    }
    tempFunnimals_.clear();
}

void GameEngine::printBoard()
{
    cout << endl;
    for (int i = 0; i < DEFAULT_BOARD_I; ++i) {
        for (int j = 0; j < DEFAULT_BOARD_J; ++j) {
            if(board_->empty( {i,j})) {
                cout << '.';
            }
            else {
                board_->at( {i,j})->printLetter();
            }
        }
        cout << endl;
    }
    cout << endl;
}

void GameEngine::printFunnimals()
{
    cout << endl << "State of the funnimals:" << endl;
    cout << endl << "There are " << funnimals_.size() << "funnimals registered" <<endl;
    int i = 1;
    for (Funnimal f: funnimals_){
        cout << i++ << ' ';
        f->print();
    }
    cout << "End of funnimal printout" << endl << endl ;
}

//void GameEngine::report()
//{
//
//}

void GameEngine::addRandomFunnimalToBoard(Address a)
{
    Funnimal f = randomFunnimal();
    f->setAddress(a);
    board_->add(f, a);
    funnimals_.push_back(f);
}

Funnimal GameEngine::randomFunnimal()
{
    Funnimal f;
    int i = pick_a_number(1,3);
    switch (i) {
    case 1:
        f = make_shared<annimal>();
        break;
    case 2:
        f = make_shared<bnnimal>();
        break;
    case 3:
        f = make_shared<onnimal>();
        break;
    default:
        break;
    }
    f->setMB(board_);
    return f;
}

Address GameEngine::randomAddress()
{
    int i = pick_a_number(0, DEFAULT_BOARD_I - 1);
    int j = pick_a_number(0, DEFAULT_BOARD_J - 1);
    return Address(i, j);
}
