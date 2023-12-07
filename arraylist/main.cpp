#include "arraylist2.h"

int main() {

    Arraylist lista(10);

    for (int i = 0; i < 20; i++) {
        lista.inserirElementoNoFim(i);
    }
    lista.exibirLista();
    std::cout << "quantidade: " << lista.size() << "\ncapacidade: " << lista.capacity() << std::endl;

    lista.inserirElementoEmPosicao(-1, 5);
    lista.exibirLista();
    std::cout << "quantidade: " << lista.size() << "\ncapacidade: " << lista.capacity() << std::endl;

    lista.removerElementoNoFim();
    lista.exibirLista();

    lista.removerElementoEmPosicao(6);
    lista.exibirLista();
    std::cout << "quantidade: " << lista.size() << "\ncapacidade: " << lista.capacity() << std::endl;

    lista.atualizarElemento(-5, 15);
    lista.exibirLista();

    lista.reverseList();
    lista.exibirLista();

    return 0;
}