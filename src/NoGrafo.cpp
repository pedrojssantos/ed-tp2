#include "NoGrafo.h"

NoGrafo::NoGrafo(int id, int tipo) : _id(id), _pos(0), _tipo(tipo) {}

int NoGrafo::getId() const
{
    return _id;
}

int NoGrafo::getPos() const
{
    return _pos;
}

int NoGrafo::getTipo() const
{
    return _tipo;
}
