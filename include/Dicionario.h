#ifndef TP2_DICIONARIO_H
#define TP2_DICIONARIO_H

#include <string>

#include "No.h"
#include "Usuario.h"
#include "Tema.h"

class Dicionario
{
private:
    Usuario** _usuarios;
    Tema** _temas;
    No** _nosUsrSc;
    No** _nosUsrTm;
    No** _nosTm;
    int _numUsr;
    int _numTm;
public:
    Dicionario();
    ~Dicionario();
    void registrarUsr(int id, std::string& nome, int idade, No* noUsrSc, No* noUsrTm);
    void registrarTm(int id, std::string& nome, std::string& tipo, No* no);
    const Usuario* buscarUsr(int id) const;
    const Tema* buscarTm(int id) const;
    const No* buscarNoUsrSc(int id) const;
    const No* buscarNoUsrTm(int id) const;
    const No* buscarNoTm(int id) const;
};

#endif //TP2_DICIONARIO_H
