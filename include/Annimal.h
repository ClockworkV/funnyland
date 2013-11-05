#ifndef ANNIMAL_H
#define ANNIMAL_H

#include <memory>
#include "Funnimal.h"

class annimal;
typedef std::shared_ptr<annimal> Annimal;

class annimal : public funnimal
{
    public:
        annimal();
    private:
        virtual Funnimal spawn();
        virtual void printType(std::ostream& os = std::cout) const;
        virtual int getCompetitionNumber(){return pick_a_number(0,1);};
};



#endif // ANNIMAL_H
