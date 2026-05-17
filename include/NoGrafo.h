#ifndef TP2_NOGRAFO_H
#define TP2_NOGRAFO_H

class NoGrafo
{
private:
    int _id;
    int _pos;
    int _tipo;
public:
    NoGrafo(int id, int tipo);
    int getId() const;
    int getPos() const;
    int getTipo() const;
};

#endif //TP2_NOGRAFO_H
