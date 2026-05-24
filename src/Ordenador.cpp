#include "Ordenador.h"

void Ordenador::ordenar(int* res, int N)
{
    // Se nao existisse essa funcao extra a unica funcao ordenar retornaria
    // um vetor para quem chamou, mas quem chamou teria que liberar esse vetor da memoria
    // Visando a boa pratica, cria-se essa funcao extra, assim todo vetor criado aqui dentro e 
    // liberado da memoria
    if (N<=0) return;

    int* vetorOrdenado = ordernarRecursivamente(res, N);

    // Copia os dados ordenados de volta para o vetor original 
    for (int i = 0; i < N; ++i)
    {
        res[i] = vetorOrdenado[i];
    }

    delete[] vetorOrdenado;
}

int* Ordenador::ordernarRecursivamente(int* res, int N)
{
    // Base: um vetor de 1 elemento ja esta ordenado
    if (N <= 1)
    {
        int* temp = new int[1];
        temp[0] = res[0];

        return temp;
    }

    // Divisao: quebra o vetor no meio
    int n1 = N/2;
    int n2 = N - n1;

    // Conquista: resolve os dois subproblemas independentemente
    int* temp1 = ordernarRecursivamente(res, n1);
    int* temp2 = ordernarRecursivamente(res + n1, n2);
    int* temp3 = new int[n1 + n2];

    int v = 0, u = 0;

    // Junta as duas metades ordenadas em uma so
    for (int j = 0; j < n1 + n2; ++j)
    {
        if (v >= n1) 
        {
            temp3[j] = temp2[u];
            ++u;
        }
        else if (u >= n2) 
        {
            temp3[j] = temp1[v];
            ++v;
        }
        else if (temp1[v] <= temp2[u])
        {
            temp3[j] = temp1[v];
            ++v;
        }
        else 
        {
            temp3[j] = temp2[u];
            ++u;
        }
    }

    // Desaloca a memoria alocada nas chamadas anteriores
    delete[] temp1;
    delete[] temp2;

    return temp3;
}