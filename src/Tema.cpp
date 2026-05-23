#include <string>

#include "Tema.h"

Tema::Tema(int id, std::string& nome, std::string& tipo) : _id(id), _nome(nome), _tipo(tipo) {}

int Tema::getId() const
{
    return _id;
}

std::string Tema::getNome() const
{
    return _nome;
}

std::string Tema::getTipo() const
{
    return _tipo;
}
