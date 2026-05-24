#include <string>

#include "Dicionario.h"
#include "Usuario.h"
#include "Tema.h"
#include "No.h"

// Inicializa os vetores de mapeamento com capacidade inicial 1
Dicionario::Dicionario() : _numUsr(1), _numTm(1)
{
    _usuarios = new Usuario*[_numUsr]();
    _temas = new Tema*[_numTm]();
    _nosUsrSc = new No*[_numUsr]();
    _nosUsrTm = new No*[_numUsr]();
    _nosTm = new No*[_numTm]();
}

// Libera a memória alocada para os objetos e depois os vetores
Dicionario::~Dicionario()
{
    for (int i=0; i<_numUsr; ++i)
    {
        Usuario* usr = _usuarios[i];
        if (usr) delete usr;
    }

    delete[] _usuarios;
    delete[] _nosUsrSc;
    delete[] _nosUsrTm;

    for (int i=0; i<_numTm; ++i)
    {
        Tema* tm = _temas[i];
        if (tm) delete tm;
    }

    delete[] _temas;
    delete[] _nosTm;
}

// Registra um usuário, dobrando o tamanho dos vetores caso atinja o limite
void Dicionario::registrarUsr(int id, std::string& nome, int idade, No* noUsrSc, No* noUsrTm)
{
    // Verifica se precisa redimensionar (capacidade máxima atingida)
    if (id==_numUsr)
    {
        Usuario** temp1 = new Usuario*[_numUsr*2];
        No** temp2 = new No*[_numUsr*2];
        No** temp3 = new No*[_numUsr*2];

        // Copia os dados antigos para os novos vetores maiores
        for (int i=0; i<_numUsr*2; ++i)
        {
            if (i<_numUsr)
            {
                temp1[i] = _usuarios[i];
                temp2[i] = _nosUsrSc[i];
                temp3[i] = _nosUsrTm[i];
            }
            else
            {
                temp1[i] = nullptr;
                temp2[i] = nullptr;
                temp3[i] = nullptr;
            }
        }

        delete[] _usuarios;
        delete[] _nosUsrSc;
        delete[] _nosUsrTm;

        _usuarios = temp1;
        _nosUsrSc = temp2;
        _nosUsrTm = temp3;

        _numUsr*=2;
    }

    _usuarios[id] = new Usuario(id, nome, idade);
    _nosUsrSc[id] = noUsrSc;
    _nosUsrTm[id] = noUsrTm;
}

// Registra um tema, dobrando o tamanho dos vetores caso atinja o limite
void Dicionario::registrarTm(int id, std::string& nome, std::string& tipo, No* no)
{
    // Verifica se precisa redimensionar (capacidade máxima atingida)
    if (id==_numTm)
    {
        Tema** temp1 = new Tema*[_numTm*2];
        No** temp2 = new No*[_numTm*2];

        // Copia os dados antigos para os novos vetores maiores
        for (int i=0; i<_numTm*2; ++i)
        {
            if (i<_numTm)
            {
                temp1[i] = _temas[i];
                temp2[i] = _nosTm[i];
            }
            else
            {
                temp1[i] = nullptr;
                temp2[i] = nullptr;
            }
        }

        delete[] _temas;
        delete[] _nosTm;

        _temas = temp1;
        _nosTm = temp2;
        _numTm*=2;
    }

    _temas[id] = new Tema(id, nome, tipo);
    _nosTm[id] = no;
}

Usuario* Dicionario::buscarUsr(int id) const
{
    if (_usuarios[id]) return _usuarios[id];
    return nullptr;
}

Tema* Dicionario::buscarTm(int id) const
{
    if (_temas[id]) return _temas[id];
    return nullptr;
}

No* Dicionario::buscarNoUsrSc(int id) const
{
    if (_nosUsrSc[id]) return _nosUsrSc[id];
    return nullptr;
}

No* Dicionario::buscarNoUsrTm(int id) const
{
    if (_nosUsrTm[id]) return _nosUsrTm[id];
    return nullptr;
}

No* Dicionario::buscarNoTm(int id) const
{
    if (_nosTm[id]) return _nosTm[id];
    return nullptr;
}