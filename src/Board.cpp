#include "Board.h"
#include <assert.h>

using namespace std;

Board::Board(unsigned int I,unsigned int J):dimensions_({I,J})
{
    for (unsigned int i =0; i < I; ++i) {
        contents_.push_back(vector<Funnimal>(J, nullptr));
    }
}

Board::Board(Dim2 dim):Board(dim.first, dim.second)
{
    ;
}

Board::~Board()
{
    //dtor
}

std::shared_ptr<Board> Board::getPtr(void)
{
    return shared_from_this();
}

void Board::print()
{

}

Address Board::add(Funnimal f, Address a)
{
    assert(isValid(a));
    contents_[a.first][a.second] = f;
    return a;
}

Funnimal Board::remove(Address a)
{
    assert(isValid(a));
    auto f = contents_[a.first][a.second];
    contents_[a.first][a.second] = nullptr;
    return f;
}

Funnimal Board::move(Address from, Address to)
{
    assert(isValid(from));
    assert(isValid(to));

    auto f = remove(from);
    add(f, to);
    return f;
}

bool Board::empty(Address a)
{
    assert(isValid(a));
    return (nullptr == contents_[a.first][a.second]);
}

bool Board::isValid(Address a)
{
    return (a.first >= 0 && a.first < dimensions_.first)
            &&
           (a.second >= 0 && a.second < dimensions_.second);
}

Funnimal Board::at(Address a)
{
    if (isValid(a)){
        return contents_.at(a.first).at(a.second);
    }
    return nullptr;
}
