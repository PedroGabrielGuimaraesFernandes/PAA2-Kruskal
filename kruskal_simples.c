//Grupo
//Pedro Gabriel Guimarães Fernandes RA: 10437465

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar uma aresta
typedef struct {
    int origem;
    int destino;
    int peso;
} Aresta;

// Função para ordenar as arestas pelo peso (usando o método bolha)
void ordenarArestas(Aresta arestas[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (arestas[j].peso > arestas[j + 1].peso) {
                Aresta temp = arestas[j];
                arestas[j] = arestas[j + 1];
                arestas[j + 1] = temp;
            }
        }
    }
}

// Função para encontrar o conjunto de um vértice
// (bem simples, sem otimizações)
int encontrarConjunto(int conjunto[], int v) {
    return conjunto[v];
}

// Função para unir dois conjuntos, muda o número do conjunto
void unirConjuntos(int conjunto[], int v1, int v2, int V) {
    int antigo = conjunto[v2];
    int novo = conjunto[v1];
    for (int i = 0; i < V; i++) {
        if (conjunto[i] == antigo)
            conjunto[i] = novo;
    }
}

// Função principal do algoritmo de Kruskal
void kruskal(int V, int E, Aresta arestas[]) {
    Aresta resultado[V - 1]; // Arestas da árvore geradora mínima
    int contArestas = 0;     // Quantas arestas já foram escolhidas
    int custoTotal = 0;

    // Cada vértice começa no seu próprio conjunto
    int conjunto[V];
    for (int i = 0; i < V; i++)
        conjunto[i] = i;

    // Passo 1: ordenar arestas pelo peso
    ordenarArestas(arestas, E);

    // Passo 2: percorrer as arestas em ordem crescente
    for (int i = 0; i < E && contArestas < V - 1; i++) {
        int v1 = arestas[i].origem;
        int v2 = arestas[i].destino;

        // Se estiverem em conjuntos diferentes
        if (encontrarConjunto(conjunto, v1) != encontrarConjunto(conjunto, v2)) {
            resultado[contArestas++] = arestas[i];
            custoTotal += arestas[i].peso;
            unirConjuntos(conjunto, v1, v2, V);
        }
    }

    // Exibir resultado final
    printf("Arestas na Arvore Geradora Minima:\n");
    for (int i = 0; i < contArestas; i++) {
        printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
    }
    printf("Custo total da MST: %d\n", custoTotal);
}

int main() {
    FILE* arquivo = fopen("in.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'in.txt'\n");
        return 1;
    }

    int V, E;
    fscanf(arquivo, "%d %d", &V, &E);

    Aresta arestas[E];
    for (int i = 0; i < E; i++) {
        fscanf(arquivo, "%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].peso);
    }
    fclose(arquivo);

    kruskal(V, E, arestas);
    return 0;
}
