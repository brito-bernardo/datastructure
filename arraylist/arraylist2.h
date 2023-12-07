#ifndef ARRAYLIST2_H
#define ARRAYLIST2_H

#include <iostream>
#include <vector>

class Arraylist {
private:
    int* vetor;
    int qtdade;
    int capacidade;
public:
    Arraylist(int _capacidade);
    int obterElementoEmPosicao(int posicao); // O(1)
    void duplicarCapacidade(); // O(n)
    void inserirElementoNoFim(int valor); // O(n); teta(1); omega(1)
    void inserirElementoEmPosicao(int valor, int posicao); // O(n)
    void atualizarElemento(int valor, int posicao); // O(1)
    void removerElementoNoFim(); // O(1)
    void removerElementoEmPosicao(int posicao); // O(n)
    void reverseList();
    void exibirLista(); // O(n)
    int size();
    int capacity();
    ~Arraylist();
};

int Arraylist::size() {
    return qtdade;
}

int Arraylist::capacity() {
    return capacidade;
}

Arraylist::Arraylist(int _capacidade) {
    vetor = new int[_capacidade];
    qtdade = 0;
    capacidade = _capacidade;
}

int Arraylist::obterElementoEmPosicao(int posicao) {
    if (posicao >= 0 && posicao < qtdade) {
        return vetor[posicao];
    } else {
        std::cout << "indice invalido\n";
        exit(-1);
    }
    return 0;
}

void Arraylist::duplicarCapacidade() {
    int* aux = new int[2*capacidade];
    for (int i = 0; i < capacidade; i++) {
        aux[i] = vetor[i];
    }
    delete[] vetor;
    vetor = aux;
    capacidade *= 2;
}

void Arraylist::reverseList()
{
    int* aux = new int[qtdade];
    int j = 0;
    for (int i = qtdade - 1; i >= 0; i--)
    {
        aux[j] = vetor[i];
        j++;
    }
    delete[] vetor;
    vetor = aux;
}

void Arraylist::inserirElementoNoFim(int valor) {
    if (qtdade == capacidade) {
        this->duplicarCapacidade();
    }
    vetor[qtdade] = valor;
    qtdade++;
}

void Arraylist::inserirElementoEmPosicao(int valor, int posicao) {
    if (posicao < 0 || posicao > qtdade) {
        std::cout << "indice invalido.\n";
        exit(-1);
    } else if (qtdade == capacidade) {
        this->duplicarCapacidade();
    }

    for (int i = qtdade; i > posicao; i--) {
        vetor[i] = vetor[i - 1];
    }
    vetor[posicao] = valor;
    qtdade++;
}

void Arraylist::atualizarElemento(int valor, int posicao) {
    if(posicao < 0 || posicao > qtdade) {
        std::cout << "indice invalido.\n";
        exit(-1);
    } else {
        vetor[posicao] = valor;
    }
}

void Arraylist::removerElementoNoFim() {
    qtdade--;
}

void Arraylist::removerElementoEmPosicao(int posicao) {
    if (posicao < 0 || posicao > qtdade) {
        std::cout << "indice invalido.\n";
        exit(-1);
    } else {
        for (int i = posicao; i < qtdade - 1; i++) {
            vetor[i] = vetor[i + 1];
        }
        qtdade--;
    }
}

void Arraylist::exibirLista() {
    std::cout << "[";
    for (int i = 0; i < qtdade; i++) {
        std::cout << vetor[i];
        if (i < qtdade - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

Arraylist::~Arraylist() {
    delete[] vetor;
}

#endif //ARRAYLIST2_HPP