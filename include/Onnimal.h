#ifndef ONNIMAL_H
#define ONNIMAL_H

#include <memory>
#include <Funnimal.h>

class onnimal;
typedef std::shared_ptr<onnimal> Onnimal;

class onnimal : public funnimal
{
    public:
        onnimal();
    private:
        virtual Funnimal spawn();
        virtual void printType(std::ostream& os = std::cout) const;
        virtual int getCompetitionNumber(){return 1;};
};

#endif // ONNIMAL_H
