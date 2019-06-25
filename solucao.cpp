#include <iostream>
#include "solucao.hpp"

Solucao::Solucao(Grafo *grafo) {
    qtdElementos = grafo->getQtdElementos();
    for (int i = 0; i < qtdElementos; ++i) {
        elementosForaDaRota.push_back(i);
    }
    matrizAdjacencia = grafo->getMatrizAdjacencia();
    somatorioTotal = 0;
    solucaoInicial(grafo);
}

Solucao::~Solucao() {
    elementosForaDaRota.clear();
    solucao.clear();
    arestas.clear();
}

void Solucao::solucaoInicial(Grafo *grafo) {
    srand(time(NULL));

    int pos = rand() % qtdElementos;

    solucao.push_back(elementosForaDaRota[pos]);
    elementosForaDaRota.erase(elementosForaDaRota.begin() + pos);

    int posDisponiveis = qtdElementos - 1, posAresta = 0;
    while (posDisponiveis > 0) {
        int pos = rand() % posDisponiveis;

        solucao.push_back(elementosForaDaRota[pos]);
        elementosForaDaRota.erase(elementosForaDaRota.begin() + pos);

        --posDisponiveis;

        arestas.push_back(matrizAdjacencia[solucao[posAresta]][solucao[posAresta + 1]]);
        somatorioTotal += arestas[posAresta];
        ++posAresta;
    }
    arestas.push_back(matrizAdjacencia[solucao[posAresta]][solucao[0]]);
    somatorioTotal += arestas[posAresta];

    std::cout << "\n\n----- Solucao inicial: -----\n";
    imprimeSolucao();
}

void Solucao::buscaTabu() {
    BuscaTabu *buscaTabu = new BuscaTabu(solucao, arestas, matrizAdjacencia);
    buscaTabu->realizaBuscaTabu(solucao, arestas);

    std::cout << "\n\n----- Solucao apos busca tabu: -----\n";
    imprimeSolucao();
}

void Solucao::imprimeSolucao() {
    std::cout << "\n\nRota: ";
    for (unsigned int i = 0; i < solucao.size(); ++i) {
        std::cout << solucao[i] << " ";
    }
    somatorioTotal = 0;
    std::cout << "\n\nArestas: ";
    for (unsigned int i = 0; i < arestas.size(); ++i) {
        std::cout << arestas[i] << " ";
        somatorioTotal += arestas[i];
    }
    std::cout << "\n\nSomatorio total: " << somatorioTotal << "\n\n";
}