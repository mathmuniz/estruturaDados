#include <stdio.h>
#include <stdlib.h>

#define DELIMITADOR_VAZIO '#'
#define TAM_MAX_EXPRESSAO 10000

typedef struct _tipoNo {
    char elem;
    struct _tipoNo* prox;
} No;

typedef struct _tipoPilha {
    No* topo;
} Pilha;

No* criaNovoNo(int elem) {
    No* novoNo = NULL;
    novoNo = (No*) malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->elem = elem;
        novoNo->prox = NULL;
    }
    return novoNo;
}

void empilhar(Pilha *p, char e) {
    No* novoNo = criaNovoNo(e);
    if (novoNo != NULL) {
       novoNo->prox = p->topo;
       p->topo = novoNo;
    }
}

short int pilhaEstaVazia(Pilha *p) {
    return p->topo == NULL;
}

char desempilhar(Pilha *p) {
    char ret = DELIMITADOR_VAZIO;
    No* temp = NULL;
    if (!pilhaEstaVazia(p)) {
        ret = p->topo->elem;
        temp = p->topo->prox;
        free(p->topo);
        p->topo = temp;
    }
    return ret;
}

Pilha *criaPilha() {
    Pilha *novaPilha = NULL;
    novaPilha = (Pilha*) malloc(sizeof(Pilha));
    if (novaPilha != NULL) {
        novaPilha->topo = NULL;
    }
    return novaPilha;
}

void imprimirPilha(Pilha *p) {
    No* aux = NULL;
    if (pilhaEstaVazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }
    
    printf("Elementos na pilha:\n");
    aux = p->topo;
    while(aux != NULL) {
        printf("|%3d| -> 0x%p\n", aux->elem, aux);
        aux = aux->prox;
    }
}

void esvaziarPilha(Pilha *p) {
    while(desempilhar(p) != DELIMITADOR_VAZIO);
}

void liberarPilha(Pilha *p) {
    free(p);
}

short int correspondente(char c1, char c2) {
    return (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}');
}

short int expression_analyze(Pilha *p, char *expr) {
    int i = 0;
    short int valido = 1;
    char elem = expr[0];
    char elemDesem = '\0';
    while (elem != '\0') {
        if (elem == '(' || elem == '[' || elem == '{') {
            empilhar(p, elem);
        }
        if (elem == ')' || elem == ']' || elem == '}') {
            if (pilhaEstaVazia(p)) {
                valido = 0;
            } else {
                elemDesem = desempilhar(p);
                if (!correspondente(elemDesem, elem)) {
                    valido = 0;
                }
            }

        }
        i = i + 1;
        elem = expr[i];
    }
    if (!pilhaEstaVazia(p)) {
        valido = 0;
    }
    return valido;
}

int main(void) {

    // Alocação da expressão e da pilha:
    char *expr = (char*) malloc(TAM_MAX_EXPRESSAO * sizeof(char));
    Pilha *p = criaPilha();

    // Verificação se a alocação foi bem sucedida:
    if (p != NULL && expr != NULL) {
        // Leitura da expressão:
        scanf("%[^\n]", expr);
        // Analise e saida com o resultado:
        if (expression_analyze(p, expr)) {
            printf("Valida\n");
        } else {
            printf("Invalida\n");
        }
        // Liberação de memoria:
        esvaziarPilha(p);
        liberarPilha(p);
        free(expr);
    } else {
        printf("Erro na alocacao de memoria!\n");
    }

    return 0;
}
