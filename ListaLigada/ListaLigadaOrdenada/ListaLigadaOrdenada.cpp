#include <iostream>
using namespace std;

// definição de tipo
struct NO {
    int valor;
    NO* prox;
};

NO* primeiro = NULL;
NO* ultimo = NULL; // ponteiro para otimização da inserção

// headers
void menu();
void inicializar();
void exibirQuantidadeElementos();
void exibirElementos();
void inserirElemento();
void excluirElemento();
void buscarElemento();
NO* posicaoElemento(int numero);

//--------------------------

int main() {
    menu();
}

void menu() {
    int op = 0;
    while (op != 7) {
        system("cls");
        cout << "Menu Lista Ligada\n\n";
        cout << "1 - Inicializar Lista\n";
        cout << "2 - Exibir quantidade de elementos\n";
        cout << "3 - Exibir elementos\n";
        cout << "4 - Buscar elemento\n";
        cout << "5 - Inserir elemento\n";
        cout << "6 - Excluir elemento\n";
        cout << "7 - Sair\n\n";
        cout << "Opcao: ";
        cin >> op;

        switch (op) {
        case 1: inicializar(); break;
        case 2: exibirQuantidadeElementos(); break;
        case 3: exibirElementos(); break;
        case 4: buscarElemento(); break;
        case 5: inserirElemento(); break;
        case 6: excluirElemento(); break;
        case 7: return;
        default: cout << "Opcao invalida!\n";
        }

        system("pause"); // somente no windows
    }
}

// Inicializa a lista
void inicializar() {
    NO* aux = primeiro;
    while (aux != NULL) {
        NO* temp = aux;
        aux = aux->prox;
        free(temp);
    }
    primeiro = NULL;
    ultimo = NULL; // reset do ponteiro ultimo
    cout << "Lista inicializada.\n";
}

// Exibe quantidade de elementos
void exibirQuantidadeElementos() {
    int nElementos = 0;
    NO* aux = primeiro;
    while (aux != NULL) {
        nElementos++;
        aux = aux->prox;
    }
    cout << "Quantidade de elementos: " << nElementos << endl;
}

// Exibe elementos da lista
void exibirElementos() {
    if (primeiro == NULL) {
        cout << "Lista vazia\n";
        return;
    }
    cout << "Elementos: ";
    NO* aux = primeiro;
    while (aux != NULL) {
        cout << aux->valor << " ";
        aux = aux->prox;
    }
    cout << endl;
}

// Retorna ponteiro para elemento ou NULL
NO* posicaoElemento(int numero) {
    NO* aux = primeiro;
    while (aux != NULL) {
        if (aux->valor == numero)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

// Inserção ordenada com otimização
void inserirElemento() {
    NO* novo = (NO*)malloc(sizeof(NO));
    if (!novo) {
        cout << "Erro ao alocar memoria!\n";
        return;
    }

    cout << "Digite o elemento: ";
    cin >> novo->valor;
    novo->prox = NULL;

    // Verifica duplicidade
    if (posicaoElemento(novo->valor)) {
        cout << "Valor existente!\n";
        free(novo);
        return;
    }

    NO* atual = primeiro;
    NO* anterior = NULL;

    // Encontra posição correta para manter ordem crescente
    while (atual != NULL && atual->valor < novo->valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) { // inserir no início
        novo->prox = primeiro;
        primeiro = novo;
        if (!ultimo) ultimo = novo; // lista estava vazia
    }
    else { // inserir no meio ou fim
        anterior->prox = novo;
        novo->prox = atual;
    }

    // Atualiza ultimo se inserido no final
    if (atual == NULL) ultimo = novo;

    cout << "Elemento inserido com sucesso!\n";
}

// Busca otimizada
void buscarElemento() {
    if (!primeiro) {
        cout << "Lista vazia.\n";
        return;
    }

    int num;
    cout << "Digite o elemento a buscar: ";
    cin >> num;

    NO* aux = primeiro;
    while (aux != NULL) {
        if (aux->valor == num) {
            cout << "Elemento encontrado!\n";
            return;
        }
        if (aux->valor > num) {
            cout << "Elemento nao encontrado!\n";
            return;
        }
        aux = aux->prox;
    }

    cout << "Elemento nao encontrado!\n";
}

// Exclusão otimizada
void excluirElemento() {
    if (!primeiro) {
        cout << "Lista vazia.\n";
        return;
    }

    int num;
    cout << "Digite o elemento a excluir: ";
    cin >> num;

    NO* atual = primeiro;
    NO* anterior = NULL;

    while (atual != NULL && atual->valor < num) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual || atual->valor > num) {
        cout << "Elemento nao encontrado!\n";
        return;
    }

    // Remove elemento
    if (anterior == NULL) {
        primeiro = atual->prox;
    }
    else {
        anterior->prox = atual->prox;
    }

    // Atualiza ponteiro ultimo se necessário
    if (atual == ultimo) {
        ultimo = anterior;
    }

    free(atual);
    cout << "Elemento excluido com sucesso.\n";
}
