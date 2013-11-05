#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "Util.h"
#include "Parameters.h"

class funnimal;
typedef std::shared_ptr<funnimal> Funnimal;
typedef std::vector<Funnimal> FunnimalVec;
typedef std::vector<FunnimalVec> Funnimal2DArray;
typedef std::pair<int, int> Dim2;

class Board: public std::enable_shared_from_this<Board>
{
    public:
        Board(unsigned int I = DEFAULT_BOARD_I,
              unsigned int J = DEFAULT_BOARD_I);  // TODO
        Board(Dim2 dim);  // TODO
        ~Board();  // TODO
        std::shared_ptr<Board> getPtr(void);
        void print();  // TODO

        Address add(Funnimal f, Address a);
        Funnimal remove(Address a);
        Funnimal move(Address from, Address to);

        bool empty(Address a);
        int occupancy(); // TODO: returns the percent of the board occupied
        bool isValid(Address a);
        Funnimal at(Address a);

 // TODO: remove this
        std::pair<int, int> getDim(){return dimensions_;};
    private:
        Funnimal2DArray contents_;
        Dim2 dimensions_;
};

typedef std::shared_ptr<Board> BoardPtr;

#endif // BOARD_H
