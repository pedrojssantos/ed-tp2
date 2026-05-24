#include <string>

#include "Grafo.h"
#include "No.h"

Grafo::Grafo(bool direcionado, std::string& modo) :
    _direcionado(direcionado), _numVertices(1), _numArestas(0), _idxAtual(0), _modo(modo)
{
    _listaAdj = new No*[_numVertices]();

    if (_modo == "M")
    {
        _matrizAdj = new int*[_numVertices]();
        for (int i=0; i<_numVertices; ++i)
        {
            _matrizAdj[i] = new int[_numVertices]();
        }
    }
    else
    {
        _matrizAdj = nullptr;
    }
}

Grafo::~Grafo()
{
    if (_modo=="L")
    {
        for (int i=0; i<_numVertices; ++i)
        {
            No* aux = nullptr;
            No* noAtual = _listaAdj[i];

            while (noAtual)
            {
                aux = noAtual->_prox;
                delete noAtual;
                noAtual = aux;
            }
        }
    }
    else
    {
        for (int i=0; i<_numVertices; ++i)
        {
            delete[] _matrizAdj[i];
        }

        for (int i=0; i<_numVertices; ++i)
        {
            delete _listaAdj[i];
        }
    }

    delete[] _listaAdj;
    delete[] _matrizAdj;
    _listaAdj = nullptr;
    _matrizAdj = nullptr;
}

void Grafo::criarAresta(No *no1, No *no2)
{
    if (!no1 || !no2) return;

    if (_modo=="L")
    {
        No* novoNo = new No();
        novoNo->_id = no2->_id;
        novoNo->_pos = no2->_pos;
        novoNo->_tipo = no2->_tipo;
        novoNo->_prox = nullptr;

        No* noAtual = _listaAdj[no1->_pos];

        while (noAtual->_prox)
        {
            noAtual = noAtual->_prox;
        }

        noAtual->_prox = novoNo;
    }
    else
    {
        int pos1 = no1->_pos;
        int pos2 = no2->_pos;

        _matrizAdj[pos1][pos2] = 1;
    }
}

void Grafo::removerAresta(No* no1, No* no2)
{
    if (!no1 || !no2) return;

    if (_modo=="L")
    {
        No* aux = _listaAdj[no1->_pos];
        No* noAtual = aux->_prox;

        while (noAtual)
        {
            if (noAtual->_id==no2->_id) break;

            aux = noAtual;
            noAtual = noAtual->_prox;
        }

        if (noAtual)
        {
            aux->_prox = noAtual->_prox;

            delete noAtual;
        }
    }
    else
    {
        int pos1 = no1->_pos;
        int pos2 = no2->_pos;

        _matrizAdj[pos1][pos2] = 0;
    }
}

void Grafo::mudarModo(std::string& modo)
{
    if (_modo==modo) return;

    _modo = modo;

    if (_modo=="M")
    {
        _matrizAdj = new int*[_numVertices]();

        for (int i=0; i<_numVertices; ++i)
        {
            _matrizAdj[i] = new int[_numVertices]();
        }

        for (int i=0; i<_numVertices; ++i)
        {
            if (!_listaAdj[i]) continue;

            No* aux = nullptr;
            No* noAtual = _listaAdj[i]->_prox;

            while (noAtual)
            {
                int pos = noAtual->_pos;
                _matrizAdj[i][pos] = 1;

                aux = noAtual->_prox;
                delete noAtual;
                noAtual = aux;
            }

            _listaAdj[i]->_prox = nullptr;
        }
    }
    else
    {
        for (int i=0; i<_numVertices; ++i)
        {
            for (int j=0; j<_numVertices; ++j)
            {
                if (_matrizAdj[i][j])
                {
                    criarAresta(_listaAdj[i], _listaAdj[j]);
                }
            }
        }

        for (int i=0; i<_numVertices; ++i)
        {
            delete[] _matrizAdj[i];
        }

        delete[] _matrizAdj;
        _matrizAdj = nullptr;
    }
}

int Grafo::getNumVertices() const
{
    return _numVertices;
}

No* Grafo::adicionarVertice(int id, int tipo) {
    if (_idxAtual==_numVertices)
    {
        if (_matrizAdj)
        {
            int** temp1 = new int*[_numVertices*2]();

            for (int i=0; i<_numVertices*2; ++i)
            {
                temp1[i] = new int[_numVertices*2]();
            }

            for (int i=0; i<_numVertices; ++i)
            {
                for (int j=0; j<_numVertices; ++j)
                {
                    temp1[i][j] = _matrizAdj[i][j];
                }

                delete[] _matrizAdj[i];
            }

            delete[] _matrizAdj;
            _matrizAdj = temp1;
        }

        No** temp2 = new No*[_numVertices*2];

        for (int i=0; i<_numVertices*2; ++i)
        {
            if (i<_numVertices)
            {
                temp2[i] = _listaAdj[i];
            }
            else
            {
                temp2[i] = nullptr;
            }
        }

        delete[] _listaAdj;

        _listaAdj = temp2;

        _numVertices*=2;
    }

    No* novoNo = new No();
    novoNo->_id = id;
    novoNo->_pos = _idxAtual;
    novoNo->_tipo = tipo;
    novoNo->_prox = nullptr;

    _listaAdj[_idxAtual] = novoNo;
    ++_idxAtual;

    return novoNo;
}

void Grafo::relacionar(No* no1, No* no2)
{
    criarAresta(no1, no2);
    if (!_direcionado) criarAresta(no2, no1);
}

void Grafo::desrelacionar(No* no1, No* no2)
{
    removerAresta(no1, no2);
    if (!_direcionado) removerAresta(no2, no1);
}

int Grafo::buscarSucessores(No* no, int* suc)
{
    int cont=0;

    if (_modo=="L")
    {
        No* noAtual = _listaAdj[no->_pos]->_prox;

        while (noAtual)
        {
            suc[cont] = noAtual->_id;

            ++cont;
            noAtual = noAtual->_prox;
        }
    }
    else
    {
        for (int j=0; j<_numVertices; ++j)
        {
            if (_matrizAdj[no->_pos][j])
            {
                suc[cont] = _listaAdj[j]->_id;
                ++cont;
            }
        }
    }

    return cont;
}

int Grafo::buscarAntecessores(No* no, int* suc)
{
    int cont=0;

    if (_modo=="L")
    {
        for (int i=0; i<_numVertices; ++i)
        {
            No* aux = _listaAdj[i];

            if (!aux) continue;

            No* noAtual = aux->_prox;

            while (noAtual)
            {
                if (no->_id==noAtual->_id)
                {
                    suc[cont] = aux->_id;
                    ++cont;
                    break;
                }

                noAtual = noAtual->_prox;
            }
        }
    }
    else
    {
        for (int i=0; i<_numVertices; ++i)
        {
            if (_matrizAdj[i][no->_pos])
            {
                suc[cont] = _listaAdj[i]->_id;
                ++cont;
            }
        }
    }

    return cont;
}