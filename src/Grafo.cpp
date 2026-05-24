#include <string>

#include "Grafo.h"
#include "No.h"

Grafo::Grafo(bool direcionado, std::string& modo) : _direcionado(direcionado), _numVertices(1), _numArestas(0), _idxAtual(0), _modo(modo)
{
    _listaAdj = new No*[_numVertices]();
    _matrizAdj = new int*[_numVertices]();
}

Grafo::~Grafo()
{
    for (int i=0; i<_numVertices; ++i)
    {
        delete _listaAdj[i];
    }

    delete[] _listaAdj;
}

void Grafo::criarAresta(No *no1, No *no2)
{
    if (!no1 || !no2) return;

    No* novoNo = new No();
    novoNo->_id = no2->_id;
    novoNo->_pos = -1;
    novoNo->_tipo = no2->_tipo;
    novoNo->_prox = nullptr;

    No* aux = nullptr;
    No* noAtual = _listaAdj[no1->_pos];

    while (true)
    {
        if (!noAtual) break;

        aux = noAtual;
        noAtual = noAtual->_prox;
    }

    if (aux) aux->_prox = novoNo;
}

void Grafo::mudarModo(std::string& modo)
{
    _modo = modo;
}

No* Grafo::adicionarVertice(int id, int tipo) {
    if (_idxAtual==_numVertices)
    {
        No** temp = new No*[_numVertices*2];

        for (int i=0; i<_numVertices*2; ++i)
        {
            if (i<_numVertices)
            {
                temp[i] = _listaAdj[i];
            }
            else
            {
                temp[i] = nullptr;
            }
        }

        delete[] _listaAdj;

        _listaAdj = temp;

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

void Grafo::adicionarAresta(No* no1, No* no2)
{
    criarAresta(no1, no2);
    criarAresta(no2, no1);
}

void Grafo::removerAresta(No* no1, No* no2)
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
        aux = noAtual->_prox;
        noAtual->_prox = nullptr;

        delete noAtual;
    }
}
