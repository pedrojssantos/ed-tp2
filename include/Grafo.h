#ifndef TP2_GRAFO_H
#define TP2_GRAFO_H

#include <string>

#include "No.h"

class Grafo
{
private:
    bool _direcionado;
    int _numVertices;
    int _numArestas;
    int _idxAtual;
    No** _listaAdj;
    int** _matrizAdj;
    std::string _modo;
    void criarAresta(No* no1, No* no2);
public:
    Grafo(bool direcionado, std::string& modo);
    ~Grafo();
    void mudarModo(std::string& modo);
    int getNumVertices() const;
    No* adicionarVertice(int id, int tipo);
    void adicionarAresta(No* no1, No* no2);
    void removerAresta(No* no1, No* no2);
    int buscarSucessores(No* no, int* suc);
    int buscarAntecessores(No* no, int* suc);
};

#endif //TP2_GRAFO_H