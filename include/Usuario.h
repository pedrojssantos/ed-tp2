#ifndef TP2_USUARIO_H
#define TP2_USUARIO_H

#include <string>

class Usuario
{
private:
    int _id;
    std::string _nome;
    int _idade;
public:
    Usuario(int id, std::string& nome, int idade);
    int getId() const;
    std::string getNome() const;
    int getIdade() const;
};

#endif //TP2_USUARIO_H
