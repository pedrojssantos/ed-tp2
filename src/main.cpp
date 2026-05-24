#include <iostream>
#include <string>
#include <sstream>

#include "Dicionario.h"
#include "Grafo.h"
#include "Ordenador.h"

int main()
{
    std::string modo = "L";

    Dicionario dic;
    Grafo gfSocial(true, modo);
    Grafo gfTemas(false, modo);

    int proxIdUsr = 0;
    int proxIdTm = 0;

    std::string linha;
    std::string comando;

    // Loop principal
    while (std::getline(std::cin, linha))
    {
        if (!linha.empty() && linha.back() == '\r')
        {
            linha.pop_back();
        }

        std::stringstream token(linha);
        if (!(token >> comando)) continue;

        // Comando A: Alterna a representação interna dos grafos
        if (comando == "A")
        {
            token >> modo;

            gfSocial.mudarModo(modo);
            gfTemas.mudarModo(modo);

            std::cout << "A " << modo << std::endl;
        }
        // Comando T: Cadastra um novo Tema
        else if (comando == "T")
        {
            std::string nome, tipo;
            token >> nome >> tipo;

            // Cria o vértice físico no grafo e registra no dicionário
            No* noTm = gfTemas.adicionarVertice(proxIdTm, 0);
            dic.registrarTm(proxIdTm, nome, tipo, noTm);

            std::cout << "T " << proxIdTm << std::endl;
            ++proxIdTm;
        }
        // Comando U: Cadastra um novo Usuário e seus interesses
        else if (comando == "U")
        {
            std::string nome;
            int idade = 0;
            token >> nome >> idade;

            No* noUsrSc = gfSocial.adicionarVertice(proxIdUsr, 1);
            No* noUsrTm = gfTemas.adicionarVertice(proxIdUsr, 1);
            dic.registrarUsr(proxIdUsr, nome, idade, noUsrSc, noUsrTm);

            int idTm = 0;
            // Lê sequencialmente todos os IDs de temas passados na mesma linha
            while (token >> idTm)
            {
                No* noTm = dic.buscarNoTm(idTm);
                if (noTm) gfTemas.relacionar(noUsrTm, noTm);
            }

            std::cout << "U " << proxIdUsr << std::endl;
            ++proxIdUsr;
        }
        // Comando S: Um usuário passa a seguir outro
        else if (comando == "S")
        {
            int idUsr1 = 0, idUsr2 = 0;
            token >> idUsr1 >> idUsr2;

            No* noUsr1 = dic.buscarNoUsrSc(idUsr1);
            No* noUsr2 = dic.buscarNoUsrSc(idUsr2);

            if (noUsr1 && noUsr2) gfSocial.relacionar(noUsr1, noUsr2);

            std::cout << "S " << dic.buscarUsr(idUsr1)->getNome() << " "
                      << dic.buscarUsr(idUsr2)->getNome() << std::endl;
        }
        // Comando R: Um usuário deixa de seguir outro
        else if (comando == "R")
        {
            int idUsr1 = 0, idUsr2 = 0;
            token >> idUsr1 >> idUsr2;

            No* noUsr1 = dic.buscarNoUsrSc(idUsr1);
            No* noUsr2 = dic.buscarNoUsrSc(idUsr2);

            if (noUsr1 && noUsr2) gfSocial.desrelacionar(noUsr1, noUsr2);

            std::cout << "R " << dic.buscarUsr(idUsr1)->getNome() << " "
                      << dic.buscarUsr(idUsr2)->getNome() << std::endl;
        }
        // Comando LT: Lista os temas de interesse de um usuário
        else if (comando == "LT")
        {
            int idUsr = 0;
            token >> idUsr;

            No* noUsr = dic.buscarNoUsrTm(idUsr);
            if (!noUsr) continue;

            int* suc = new int[gfTemas.getNumVertices()];
            int numSuc = gfTemas.buscarSucessores(noUsr, suc);

            Ordenador::ordenar(suc, numSuc);

            std::string temas;
            for (int i=0; i<numSuc; ++i)
            {
                temas += " " + dic.buscarTm(suc[i])->getNome();
            }

            std::cout << "LT " << dic.buscarUsr(idUsr)->getNome() << temas << std::endl;
            delete[] suc;
        }
        // Comando LC: Lista quem segue um usuário
        else if (comando == "LC")
        {
            int idUsr = 0;
            token >> idUsr;

            No* noUsr = dic.buscarNoUsrSc(idUsr);
            if (!noUsr) continue;

            int* ant = new int[gfSocial.getNumVertices()];
            int numAnt = gfSocial.buscarAntecessores(noUsr, ant);

            Ordenador::ordenar(ant, numAnt);

            std::string usrs;
            for (int i=0; i<numAnt; ++i)
            {
                usrs += " " + dic.buscarUsr(ant[i])->getNome();
            }

            if (numAnt == 0) usrs = "";
            std::cout << "LC " << dic.buscarUsr(idUsr)->getNome() << usrs << std::endl;
            delete[] ant;
        }
        // Comando LS: Lista quem o usuário segue
        else if (comando == "LS")
        {
            int idUsr = 0;
            token >> idUsr;

            No* noUsr = dic.buscarNoUsrSc(idUsr);
            if (!noUsr) continue;

            int* suc = new int[gfSocial.getNumVertices()];
            int numSuc = gfSocial.buscarSucessores(noUsr, suc);

            Ordenador::ordenar(suc, numSuc);

            std::string usrs;
            for (int i=0; i<numSuc; ++i)
            {
                usrs += " " + dic.buscarUsr(suc[i])->getNome();
            }

            if (numSuc == 0) usrs = "";
            std::cout << "LS " << dic.buscarUsr(idUsr)->getNome() << usrs << std::endl;
            delete[] suc;
        }
        // Comando LA: Lista os amigos mútuos
        else if (comando == "LA")
        {
            int idUsr = 0;
            token >> idUsr;

            No* noUsr = dic.buscarNoUsrSc(idUsr);
            if (!noUsr) continue;

            int* suc = new int[gfSocial.getNumVertices()];
            int numSuc = gfSocial.buscarSucessores(noUsr, suc);

            int* ant = new int[gfSocial.getNumVertices()];
            int numAnt = gfSocial.buscarAntecessores(noUsr, ant);

            Ordenador::ordenar(suc, numSuc);
            Ordenador::ordenar(ant, numAnt);

            int cont = 0;
            std::string amigos;

            // Busca elementos em comum entre os dois vetores
            for (int i=0; i<numSuc; ++i)
            {
                for (int j=0; j<numAnt; ++j)
                {
                    if (suc[i] == ant[j])
                    {
                        amigos += " " + dic.buscarUsr(suc[i])->getNome();
                        ++cont;
                    }
                }
            }

            if (cont == 0) amigos = "";
            std::cout << "LA " << dic.buscarUsr(idUsr)->getNome() << amigos << std::endl;

            delete[] suc;
            delete[] ant;
        }
        // Comando Q: Mede o relacionamento entre dois usuários
        else if (comando == "Q")
        {
            int idUsr1 = 0, idUsr2 = 0;
            token >> idUsr1 >> idUsr2;

            No* noUsr = dic.buscarNoUsrSc(idUsr1);
            if (!noUsr) continue;

            int* suc = new int[gfSocial.getNumVertices()];
            int numSuc = gfSocial.buscarSucessores(noUsr, suc);

            int* ant = new int[gfSocial.getNumVertices()];
            int numAnt = gfSocial.buscarAntecessores(noUsr, ant);

            int valor = 0;
            int aux = 0;

            // Verifica se noUsr2 é sucessor (Usuário 1 segue Usuário 2)
            for (int i=0; i<numSuc; ++i)
            {
                if (suc[i] == idUsr2)
                {
                    valor = 1;
                    ++aux;
                }
            }

            // Verifica se noUsr2 é antecessor (Usuário 2 segue Usuário 1)
            for (int i=0; i<numAnt; ++i)
            {
                if (ant[i] == idUsr2)
                {
                    valor = 2;
                    ++aux;
                }
            }

            if (aux == 2) valor = 3;

            std::cout << "Q " << dic.buscarUsr(idUsr1)->getNome() << " "
                      << dic.buscarUsr(idUsr2)->getNome() << " " << valor << std::endl;

            delete[] suc;
            delete[] ant;
        }
        // Comando G: Verifica se o usuário possui interesse em um tema específico
        else if (comando == "G")
        {
            int idUsr = 0, idTm = 0;
            token >> idUsr >> idTm;

            No* noUsr = dic.buscarNoUsrTm(idUsr);
            if (!noUsr) continue;

            int* suc = new int[gfTemas.getNumVertices()];
            int numSuc = gfTemas.buscarSucessores(noUsr, suc);

            int valor = 0;
            for (int i=0; i<numSuc; ++i)
            {
                if (idTm == suc[i]) valor = 1;
            }

            std::cout << "G " << dic.buscarUsr(idUsr)->getNome() << " "
                      << dic.buscarTm(idTm)->getNome() << " " << valor << std::endl;

            delete[] suc;
        }
        // Comando F: Consulta a popularidade de um tema
        else if (comando == "F")
        {
            int idTm = 0;
            token >> idTm;

            No* noTm = dic.buscarNoTm(idTm);
            if (!noTm) continue;

            int* suc = new int[gfTemas.getNumVertices()];
            int numSuc = gfTemas.buscarSucessores(noTm, suc);

            std::cout << "F " << dic.buscarTm(idTm)->getNome() << " " << numSuc << std::endl;
            delete[] suc;
        }
    }

    return 0;
}