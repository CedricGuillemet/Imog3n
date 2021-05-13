#include "Node.h"

using namespace Imog3n;

class Circle : public Node
{
    public:
    Circle();
    
    float m_radius{0.3f};

    static inline Description _description{NewDescription<Circle>("Circle")
        .Input("myInput")
        .Output("myOutput")
        .Parameter("m_radius")
    };
};

Circle::Circle()
    : Node()
{
    
}


