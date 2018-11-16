#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>

class Figure {
public:
    Figure();
    virtual double Square() = 0;
    virtual void Print() = 0;
    virtual ~Figure() = 0;
    virtual bool empty();
    friend  std::ostream& operator<<(std::ostream& os, const Figure& obj);

    virtual std::ostream* Show(std::ostream& os);
};

#endif /* FIGURE_H */
