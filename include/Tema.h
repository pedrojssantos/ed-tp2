#ifndef TP2_TEMA_H
#define TP2_TEMA_H

#include <string>

class Tema
{
private:
    int _id;
    std::string _nome;
    std::string _tipo;
public:
    Tema(int id, std::string& nome, std::string& tipo);
    int getId() const;
    std::string getNome() const;
    std::string getTipo() const;
};

#endif //TP2_TEMA_H