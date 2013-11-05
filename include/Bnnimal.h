#ifndef BNNIMAL_H
#define BNNIMAL_H

#include <memory>
#include <funnimal.h>

class bnnimal;
typedef std::shared_ptr<bnnimal> Bnnimal;

class bnnimal : public funnimal
{
    public:
        bnnimal();
    private:
        virtual Funnimal spawn();
        virtual void printType(std::ostream& os = std::cout) const;
        virtual int getCompetitionNumber(){return 0;};
};

#endif // BNNIMAL_H
