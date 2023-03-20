/**
    Atividade Avaliativa 3 - Módulo 2
    Disciplina de Estruturas de Dados

    Aluno1: Matheus Muniz Gomes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 100
#define MAX_NOME 30

typedef struct _mov *ptrMovimentacao;
typedef struct _mov {
    int tipo;
    int idClienteDest;
    int idClienteOrig;
    float valor;
    ptrMovimentacao proximo;
} Movimentacao;

typedef struct _conta {
    int numero;
    float saldo;
    float saldoInicial;
    Movimentacao *movimentacoes;
} Conta;

typedef struct _cliente *ptrCliente;
typedef struct _cliente {
    int id;
    Conta contaCliente;
    ptrCliente proximo;
} Cliente;

typedef struct _banco {
    char nome[MAX_NOME];
    Cliente *clientes;
} Banco;

/**
    Função para criacao de uma nova movimentacao
*/
ptrMovimentacao criarNovaMovimentacao(short int tipo, float valor, int idClienteOrig, int idClienteDest) {
    // Aloca espaço para a estrutura Movimentacao
    Movimentacao *novaMovimentacao = (Movimentacao *)malloc(sizeof(Movimentacao));

    if (novaMovimentacao == NULL)
        return NULL; // Verifica se houve erro na alocação de memória

    // Preenche os campos da estrutura Movimentacao
    novaMovimentacao->tipo = tipo;
    novaMovimentacao->valor = valor;
    novaMovimentacao->idClienteOrig = idClienteOrig;
    novaMovimentacao->idClienteDest = idClienteDest;

    novaMovimentacao->proximo = NULL;

    return novaMovimentacao;
}

/**
    Função que realiza a busca de um determinado cliente.
    Esta função deverá retornar NULL caso cliente não esteja na lista.
*/
Cliente *buscarCliente(Banco *b, int idCliente) {
    Cliente *atual = b->clientes;

    while (atual != NULL) {
        if (atual->id == idCliente)
            return atual;
        atual = atual->proximo;
    }

    return NULL;
}

/**
    Função que tem por objetivo realizar uma movimentação de saque: Adição de uma movimentação no cliente c
*/
void realizarSaque(Cliente *c, Movimentacao *saque) {
    // Adiciona a nova movimentação no final da lista de movimentações da conta do cliente
    if (c->contaCliente.movimentacoes == NULL)
        c->contaCliente.movimentacoes = saque;
    else {
        Movimentacao *atual = c->contaCliente.movimentacoes;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = saque;
    }

    // Atualiza o saldo do cliente
    c->contaCliente.saldo -= saque->valor;
}

/**
    Função que tem por objetivo realizar uma movimentação de depósito: Adição de uma movimentação no cliente c
*/
void realizarDeposito(Cliente *c, Movimentacao *dep) {
    // Adiciona a nova movimentação no final da lista de movimentações da conta do cliente
    if (c->contaCliente.movimentacoes == NULL)
        c->contaCliente.movimentacoes = dep;
    else {
        Movimentacao *atual = c->contaCliente.movimentacoes;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = dep;
    }

    // Atualiza o saldo do cliente
    c->contaCliente.saldo += dep->valor;
}

/**
    Função que tem por objetivo a realização de transferencia: orig -> dest
*/
void realizarTransferencia(Cliente *clienteOrig, Cliente *clienteDest, float valor) {
    Movimentacao *saque = criarNovaMovimentacao(1, valor, clienteOrig->id, clienteDest->id);
    Movimentacao *deposito = criarNovaMovimentacao(0, valor, clienteDest->id, clienteOrig->id);

    realizarSaque(clienteOrig, saque);
    realizarDeposito(clienteDest, deposito);
}

/**
    Função que tem por objetivo a adição de um cliente no banco de forma ordenada
*/
void adicionarCliente(Banco *b, Cliente *c) {
    if (b->clientes == NULL) {
        // Se a lista de clientes estiver vazia, adiciona o novo cliente no início
        b->clientes = c;
        return;
    }

    Cliente *atual = b->clientes;
    Cliente *anterior = NULL;

    while (atual != NULL && atual->id < c->id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) {
        // Adiciona o novo cliente no início da lista
        c->proximo = b->clientes;
        b->clientes = c;
    }
    else {
        // Adiciona o novo cliente após o cliente anterior
        anterior->proximo = c;
        c->proximo = atual;
    }
}

/**
    Função que tem por objetivo a adição de um novo cliente com seus dados iniciais.
    Lembre-se que um cliente deverá possuir uma conta e esta conta possui uma lista de movimentações.
*/
ptrCliente criarNovoCliente(int idCliente, int numConta, float saldo) {
    // Aloca espaço para a estrutura Cliente
    ptrCliente novoCliente = (ptrCliente)malloc(sizeof(Cliente));

    if (novoCliente == NULL)
        return NULL; // Verifica se houve erro na alocação de memória

    // Preenche os campos da estrutura Cliente
    novoCliente->id = idCliente;
    novoCliente->proximo = NULL;

    // Cria uma nova conta
    Conta *novaConta = (Conta *)malloc(sizeof(Conta));
    if (novaConta == NULL) {
        free(novoCliente); // Libera a memória alocada para a estrutura Cliente em caso de erro
        return NULL;
    }

    // Preenche os campos da estrutura Conta
    novaConta->numero = numConta;
    novaConta->saldo = saldo;
    novaConta->saldoInicial = saldo;
    novaConta->movimentacoes = NULL;

    novoCliente->contaCliente = *novaConta;

    return novoCliente;
}

/**
    Função que tem por objetivo a criação de um novo banco.
    Lembre-se, o banco possui uma lista de clientes.
*/
Banco *criarBanco(char *nome) {
    Banco *banco = (Banco *)malloc(sizeof(Banco)); // Aloca espaço na memória para o banco
    if (banco == NULL)
        return NULL; // Verifica se houve erro na alocação de memória

    strcpy(banco->nome, nome); // Copia o nome para o campo nome do banco
    banco->clientes = NULL;    // Inicializa o ponteiro para a lista de clientes como NULL

    return banco;
}

/**
    Função que tem por objetivo liberar toda e qualquer memória alocada dinamicamente para o banco, na seguinte ordem:
    1 - Lista de movimentações de cada cliente
    2 - Lista de clientes
    3 - banco
*/
void liberarBanco(Banco *b) {
    ptrCliente auxClie = b->clientes;
    while (auxClie != NULL) {
        ptrCliente proximoClie = auxClie->proximo;
        ptrMovimentacao auxMov = auxClie->contaCliente.movimentacoes;
        while (auxMov != NULL) {
            ptrMovimentacao proximoMov = auxMov->proximo;
            free(auxMov);
            auxMov = proximoMov;
        }
        free(auxClie);
        auxClie = proximoClie;
    }
    free(b);
}

// Função que realiza a abertura do arquivo. NÃO altere esta função
FILE *openFile(char *path, char *mode) {
    return fopen(path, mode);
}

/**
 * Função que realiza a leitura dos dados no arquivo.
 * Para uma melhor compreensão desta função, leia o arquivo LEIA-ME.txt

    -----------------------------------
    | ATENCAO: NÃO altere esta função |
    -----------------------------------

 * Colunas presentes no arquivo:
 * cn = Coluna n, onde n = (1..4)
 * c1 = mov
 * c2 = (idCliente ou TipoMov)
 * c3 = (numConta, idCliente ou idClienteOrig-idClienteDest)
 * c4 = valor
 * */
void readFile(FILE *ptr, Banco *banco) {
    char c1[4], c3[8];
    int c2;
    int idCliente, idClienteOrig, idClienteDest, numConta;
    float c4, valor;
    // clientes usados para busca
    ptrCliente clienteOrig = NULL, clienteDest = NULL;

    // Iterando nas linhas do arquivo
    while (fscanf(ptr, "%s\t%d\t%s\t%f\n", c1, &c2, c3, &c4) != EOF) {
        valor = c4;

        if (strcmp("add", c1) == 0) { // adicionar cliente
            idCliente = c2;
            numConta = atoi(c3);

            ptrCliente novoCliente = criarNovoCliente(idCliente, numConta, valor);
            if (novoCliente) {
                adicionarCliente(banco, novoCliente);
            }
            else {
                printf("ERRO - Ocorreu um erro ao tentar adicionar o cliente %d\n", idCliente);
                liberarBanco(banco);
                fclose(ptr);
                exit(1);
            }
        }
        else if (strcmp("mov", c1) == 0) { // realizar movimentacoes
            ptrMovimentacao novaMovimentacao = NULL;

            switch (c2) {
            case 0: // deposito
                idCliente = atoi(c3);
                clienteOrig = buscarCliente(banco, idCliente);

                if (clienteOrig) {
                    novaMovimentacao = criarNovaMovimentacao(0, valor, clienteOrig->id, 0);

                    if (novaMovimentacao) {
                        realizarDeposito(clienteOrig, novaMovimentacao);
                        clienteOrig = NULL;
                    }
                    else {
                        printf("ERRO - Ocorreu um erro ao tentar depositar %.2f para o cliente %d.\n", valor, idCliente);
                        liberarBanco(banco);
                        fclose(ptr);
                        exit(1);
                    }
                }
                else {
                    printf("ERRO - Cliente %d nao encontrado para realizacao de deposito no valor de %.2f.\n", idCliente, valor);
                    liberarBanco(banco);
                    fclose(ptr);
                    exit(1);
                }
                break;

            case 1: // saque
                idCliente = atoi(c3);
                clienteOrig = buscarCliente(banco, idCliente);

                if (clienteOrig) {
                    novaMovimentacao = criarNovaMovimentacao(1, valor, clienteOrig->id, 0);

                    if (novaMovimentacao) {
                        realizarSaque(clienteOrig, novaMovimentacao);
                        clienteOrig = NULL;
                    }
                    else {
                        printf("ERRO - Ocorreu um erro ao tentar realizar o saque de %.2f para o cliente %d.\n", valor, idCliente);
                        liberarBanco(banco);
                        fclose(ptr);
                        exit(1);
                    }
                }
                else {
                    printf("ERRO - Ocorreu um erro ao tentar buscar o cliente %d para realizar o saque de %.2f.\n", idCliente, valor);
                    liberarBanco(banco);
                    fclose(ptr);
                    exit(1);
                }
                break;

            case 2: // transferencia
                idClienteOrig = atoi(strtok(c3, "-"));
                idClienteDest = atoi(strtok(NULL, "-"));

                clienteOrig = buscarCliente(banco, idClienteOrig);
                clienteDest = buscarCliente(banco, idClienteDest);

                if (clienteOrig && clienteDest) {
                    realizarTransferencia(clienteOrig, clienteDest, valor);
                    clienteOrig = NULL;
                    clienteDest = NULL;
                }
                else {
                    printf("ERRO - Ocorreu um erro ao tentar buscar clientes orig %d e dest %d para transferencia do valor %.2f\n", idClienteOrig, idClienteDest, valor);
                    liberarBanco(banco);
                    fclose(ptr);
                    exit(1);
                }
                break;

            default:
                printf("ERRO - movimentacao desconhecida.\n");
                liberarBanco(banco);
                fclose(ptr);
                exit(1);
                break;
            }
        }
    }
}

/**
    Função que tem por objetivo imprimir todos os dados do banco no padrão requerido da especificação
*/
void imprimirDados(Banco *b) {
    Cliente *aux = b->clientes;
    while (aux != NULL) {
        Conta auxConta = aux->contaCliente;
        printf("=====================================================\n");
        printf("Id. Cliente  :    %d\n", aux->id);
        printf("Numero Conta :    %d\n", auxConta.numero);
        printf("Saldo inicial:    %.2f\n", auxConta.saldoInicial);
        printf("------------------- Movimentacoes -------------------\n");
        Movimentacao *m = auxConta.movimentacoes;
        while (m != NULL) {
            if (m->idClienteDest != 0) {
                printf("Tipo: %s| Valor: %.2f", "Transf.  ", m->tipo == 1 ? m->valor * -1 : m->valor);
                printf(" ===> %s: %d", m->tipo == 1 ? "Destinatario" : "Origem", m->idClienteDest);
            }
            else
                printf("Tipo: %s| Valor: %.2f", m->tipo == 0 ? "Deposito " : "Saque    ", m->tipo == 1 ? m->valor * -1 : m->valor);
            printf("\n");

            m = m->proximo;
            
        }
        if (auxConta.movimentacoes == NULL)
            printf("Sem movimentacoes\n");

        printf("\nSaldo Final: %.2f\n", aux->contaCliente.saldo);
        aux = aux->proximo;
    }
    printf("=====================================================");
}


int main(int argc, char *argv[]) {
    char path[MAX_PATH];
    FILE *filePtr = NULL;
    Banco *bomBanco = NULL;

    scanf("%s", path);
    filePtr = openFile(path, "r");

    if (filePtr) {
        bomBanco = criarBanco("BomBanco");
        if (bomBanco) {
            readFile(filePtr, bomBanco);
            imprimirDados(bomBanco);
            liberarBanco(bomBanco);
        }
        fclose(filePtr);
    }
    else {
        printf("Falha ao tentar abrir o arquivo\n");
        exit(1);
    }
    return 0;
}