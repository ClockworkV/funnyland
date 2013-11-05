#ifndef FUNNIMAL_H
#define FUNNIMAL_H

#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include "Board.h"
#include "Parameters.h"

typedef std::list<Funnimal> FunnimalList;
typedef std::vector<Funnimal> FunnimalVec;
typedef std::vector<FunnimalVec> Funnimal2DArray;

class funnimal: public std::enable_shared_from_this<funnimal>
{
    public:
// creation and initialization
        funnimal(BoardPtr mb = nullptr, Address a = invalidAddress, int LP = INITIAL_FUNNYMAL_LP);

        Funnimal setAddress(Address a);
        Address getAddress() const;
        void setMB(BoardPtr mb);
// actions
        Funnimal move();
        void compete(Funnimal oponnent);
        void competeWithAll();
        Funnimal mate(Funnimal partner);
// reports
        int getLP();
        std::ostream& print(std::ostream& os = std::cout) const;
        void printLetter(std::ostream& os = std::cout) const;


    private:
        void resetMemory();
        Dir selectDirection() const;
        FunnimalList getAllNeighbours(Address a) const;
        Address getNextAddress(const Address a) const;
        void pay(int price);
        void die();
        void placeChild(Address initialLocation);

// shared by all funnimals but implemented differently by each sub-class
        virtual Funnimal spawn() = 0;
        virtual int getCompetitionNumber() = 0;
        virtual void printType(std::ostream& os = std::cout) const = 0;

// private data fields
        BoardPtr mb_;
        Address addr_;
        int LP_;

// turn memory values
        bool hasMated_;
        Funnimal partner_;
        Funnimal child_;
};

#endif // FUNNIMAL_H
