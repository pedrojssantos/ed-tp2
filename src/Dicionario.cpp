#include <string>

#include "Dicionario.h"
#include "Usuario.h"
#include "Tema.h"
#include "NoGrafo.h"

Dicionario::Dicionario() : _numUsr(1), _numTm(1)
{
    _usuarios = new Usuario*[_numUsr];
    _temas = new Tema*[_numTm];
    _nosUsr = new NoGrafo*[_numUsr];
    _nosTm = new NoGrafo*[_numTm];
}

Dicionario::~Dicionario()
{
    for (int i=0; i<_numUsr; ++i)
    {
        Usuario* usr = _usuarios[i];
        NoGrafo* noUsr = _nosUsr[i];

        if (usr) delete usr;
        if (noUsr) delete noUsr;
    }

    delete[] _usuarios;
    delete[] _nosUsr;

    for (int i=0; i<_numTm; ++i)
    {
        Tema* tm = _temas[i];
        NoGrafo* noTm = _nosTm[i];

        if (tm) delete tm;
        if (noTm) delete noTm;
    }

    delete[] _temas;
    delete[] _nosTm;
}

void Dicionario::registrarUsr(int id, std::string& nome, int idade, NoGrafo* no)
{
    if (id==_numUsr)
    {
        Usuario** temp1 = new Usuario*[_numUsr*2];
        NoGrafo** temp2 = new NoGrafo*[_numUsr*2];

        for (int i=0; i<_numUsr*2; ++i)
        {
            if (i<_numUsr)
            {
                temp1[i] = _usuarios[i];
                temp2[i] = _nosUsr[i];
            }
            else
            {
                temp1[i] = nullptr;
                temp2[i] = nullptr;
            }
        }

        delete[] _usuarios;
        delete[] _nosUsr;

        _usuarios = temp1;
        _nosUsr = temp2;
        _numUsr*=2;
    }

    _usuarios[id] = new Usuario(id, nome, idade);
    _nosUsr[id] = no;
}

void Dicionario::registrarTm(int id, std::string& nome, std::string& tipo, NoGrafo* no)
{
    if (id==_numTm)
    {
        Tema** temp1 = new Tema*[_numUsr*2];
        NoGrafo** temp2 = new NoGrafo*[_numTm*2];

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

const Usuario* Dicionario::buscarUsr(int id) const
{
    if (_usuarios[id]) return _usuarios[id];

    return nullptr;
}

const Tema* Dicionario::buscarTm(int id) const
{
    if (_temas[id]) return _temas[id];

    return nullptr;
}

const NoGrafo* Dicionario::buscarNoUsr(int id) const
{
    if (_nosUsr[id]) return _nosUsr[id];

    return nullptr;
}

const NoGrafo* Dicionario::buscarNoTm(int id) const
{
    if (_nosTm[id]) return _nosTm[id];

    return nullptr;
}
