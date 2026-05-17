#ifndef TP2_DICIONARIO_H
#define TP2_DICIONARIO_H

#include <string>

#include "NoGrafo.h"
#include "Usuario.h"
#include "Tema.h"

class Dicionario
{
private:
    Usuario** _usuarios;
    Tema** _temas;
    NoGrafo** _nosUsr;
    NoGrafo** _nosTm;
    int _numUsr;
    int _numTm;
public:
    Dicionario();
    ~Dicionario();
    void registrarUsr(int id, std::string& nome, int idade, NoGrafo* no);
    void registrarTm(int id, std::string& nome, std::string& tipo, NoGrafo* no);
    const Usuario* buscarUsr(int id) const;
    const Tema* buscarTm(int id) const;
    const NoGrafo* buscarNoUsr(int id) const;
    const NoGrafo* buscarNoTm(int id) const;
};

#endif //TP2_DICIONARIO_H
