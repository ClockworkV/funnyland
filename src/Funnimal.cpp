#include "Funnimal.h"
#include <assert.h>

using namespace std;

// creation and initialization
funnimal::funnimal(BoardPtr mb,  Address a, int LP)
    :mb_(mb), addr_(a), LP_(LP)
{
    //ctor
}

Funnimal funnimal::setAddress(Address a)
{
    addr_ = a;
    return shared_from_this();
}

Address funnimal::getAddress() const
{
    return addr_;
}

void funnimal::setMB(BoardPtr mb)
{
    mb_ = mb;
}

// actions

Funnimal funnimal::move()
{
//    if (0 >= getLP()){die();return nullptr;};

    resetMemory();
    Funnimal child = nullptr;
    Funnimal partner = nullptr;

// select next address, and if occupied, mate with the resident and spawn child
    Address initialLocation = addr_;
    Address nextAddress = getNextAddress(initialLocation);
    if (!(mb_->empty(nextAddress))) {
        if((partner = mb_->at(nextAddress)) && (child = mate(partner))) {
            partner_ = partner;
            child_ = child;
            pay(PRICE_TO_MATE);
        }
    }

//check if annimal is dead, if child was created, set it's properties and place it on the board
    if (0 >= getLP()) {
        die();
        if (child_) {
            placeChild(initialLocation);
        }
        return child_;
    }

// find the funnimal's final destination: not occupied, not the initial location, and without going back at any step
    Address destination = hasMated_?getNextAddress(nextAddress):nextAddress;
    Address prevAddress = hasMated_?nextAddress:initialLocation;
    pay(PRICE_TO_MOVE);
    while (destination == initialLocation || destination == prevAddress || !(mb_->empty(destination))) {
        prevAddress = destination;
        destination = getNextAddress(destination);
        pay(PRICE_TO_MOVE);

        // check if during move annimal dies, if so, set child properties and place it on the board
        if (0 >= getLP()) {
            die();
            if (child_) {
                placeChild(initialLocation);
            }
            return child_;
        }
    }
    addr_ = destination;
    mb_->move(initialLocation, destination);

// compete with neighbours at the first vacant spot
    competeWithAll();
    if (0 >= getLP()) {
        die();
    }
    if (child_) {
        placeChild(initialLocation);
    }

// return a pointer to the child so gameManager can add it to it's own array
    return child_;
}


void funnimal::compete(Funnimal oponnent)
{
    int myNum = getCompetitionNumber();
    int oponnentNum = oponnent->getCompetitionNumber();
    if (myNum == oponnentNum) {
        if (myNum == 1) {
            LP_ += MUTUAL_1;
            oponnent->LP_ += MUTUAL_1;
        } else {
            LP_ += MUTUAL_0;
            oponnent->LP_ += MUTUAL_0;
        }
    } else {
        if (myNum == 1) {
            LP_ += DIFF_1;
            oponnent->LP_ += DIFF_0;
        } else {
            LP_ += DIFF_0;
            oponnent->LP_ += DIFF_1;
        }
    }
    if (0 >= oponnent->getLP()) {
        oponnent->die();
    }
}

//helper function for competeWithAll
FunnimalList funnimal::getAllNeighbours(Address a) const
{
    FunnimalList l;
    vector<Dir> directions = {Dir::N, Dir::E, Dir::S, Dir::W};
    for (Dir d : directions) {
        Address aNeighbour = a.to(d);
        if (mb_->isValid(aNeighbour)) {
            if (!mb_->empty(aNeighbour)) {
                Funnimal f = mb_->at(aNeighbour);
                l.push_back(f);
            }
        }
    }
    return l;
}

void funnimal::competeWithAll()
{
    FunnimalList neighbours = getAllNeighbours(addr_);

// // This is the optional mechanism to have funnimals die if overcrowded
//
//    if (neighbours.size() > 2) {
//        pay(getLP());
//        die();
//        return;
//    }

    for(Funnimal neighbour: neighbours) {
        if (neighbour == partner_ || neighbour == child_) {
            continue;
        }
        compete(neighbour);
        if (LP_ <= 0) {
            die();
            return;
        }
    }
}

Funnimal funnimal::mate(Funnimal partner)
{
    // TODO: remove after debugging
    assert(hasMated_ == false);

    hasMated_ = true;
    return pick_a_number(0,1)?spawn():partner->spawn();
}

// reports

int funnimal::getLP()
{
    return LP_;
}

ostream& funnimal::print(ostream& os) const
{
    os << "I'm a type-";
    printLetter();
    os << " funnimal at location ";
    getAddress().print();
    os << endl;
    return os;
}

void funnimal::printLetter(ostream& os) const
{
    printType(os);
}

// private

Dir funnimal::selectDirection() const
{
    return intToDir(pick_a_number(1,4));
}

Address funnimal::getNextAddress(const Address a) const
{
    Address candidate = invalidAddress;
    do {
        candidate = a.to(selectDirection());
    } while (!mb_->isValid(candidate));
    return candidate;
};

void funnimal::resetMemory()
{
    child_ = nullptr;
    partner_ = nullptr;
    hasMated_ = false;
}

void funnimal::pay(int price)
{
    LP_ -= price;
}


void funnimal::die()
{
    mb_->remove(addr_);
}

void funnimal::placeChild(Address initialLocation)
{
    mb_->add(child_, initialLocation);
    child_->setAddress(initialLocation);
    child_->setMB(mb_);
}
