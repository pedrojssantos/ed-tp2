#include <string>

#include "Usuario.h"

Usuario::Usuario(int id, std::string& nome, int idade) : _id(id), _nome(nome), _idade(idade) {}

int Usuario::getId() const
{
    return _id;
}

std::string Usuario::getNome() const
{
    return _nome;
}

int Usuario::getIdade() const
{
    return _idade;
}
