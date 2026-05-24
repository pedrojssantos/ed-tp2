#ifndef TP2_ORDENADOR_H
#define TP2_ORDENADOR_H

#include "No.h"

class Ordenador
{
private:
    static int* ordernarRecursivamente(int* res, int N);

public:
    static void ordenar(int* res, int N);
};

#endif //TP2_ORDENADOR_H
