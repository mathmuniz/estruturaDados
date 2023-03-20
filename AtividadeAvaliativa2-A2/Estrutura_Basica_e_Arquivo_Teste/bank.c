/**
	Atividade Avaliativa 3 - Módulo 2
	Disciplina de Estruturas de Dados
	
	Aluno1: Nome do aluno 1
	Aluno2: Nome do aluno 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 100
#define MAX_NOME 30

/**
 * Você deverá completar a definição dos TADS (Movimentacao, Conta, Cliente e Banco)
*/

typedef struct _mov *ptrMovimentacao;
typedef struct _mov {
	// complete a definição deste TAD
} Movimentacao;

typedef struct _conta {
	// complete a definição deste TAD
} Conta;

typedef struct _cliente *ptrCliente;
typedef struct _cliente {
	// complete a definição deste TAD
	int id;
} Cliente;

typedef struct _banco {
	// complete a definição deste TAD
    char nome[MAX_NOME];
} Banco;


/** 
	Função para criacao de uma nova movimentacao
	Você deverá implementar as funcionalidades desta função
*/
ptrMovimentacao criarNovaMovimentacao(short int tipo, float valor, int idClienteOrig, int idClienteDest) {
	// o retorno é apenas ilustrativo. Você deverá modificá-lo posteriormente para atender aos requisitos da aplicação.
    return (ptrMovimentacao) malloc(sizeof(Movimentacao));
}

/**
	Função que realiza a busca de um determinado cliente. 
	Esta função deverá retornar NULL caso cliente não esteja na lista.
	Você deverá implementar as funcionalidades desta função
*/
Cliente* buscarCliente(Banco *b, int idCliente) {    
	// o retorno é apenas ilustrativo. Você deverá modificá-lo posteriormente para atender aos requisitos da aplicação.
    return (ptrCliente) malloc(sizeof(Cliente));
}

/** 
	Função que tem por objetivo realizar uma movimentação de saque: Adição de uma movimentação no cliente c
	Você deverá implementar as funcionalidades desta função
*/
void realizarSaque(Cliente *c, Movimentacao* saque) {
    // A linha abaixo é apenas ilustrativa, remova-a posteriormente.
    printf("Realizar saque\n");	
}

/** 
	Função que tem por objetivo realizar uma movimentação de depósito: Adição de uma movimentação no cliente c
	Você deverá implementar as funcionalidades desta função
*/
void realizarDeposito(Cliente *c, Movimentacao* dep) {
    // A linha abaixo é apenas ilustrativa, remova-a posteriormente.
    printf("Realizar deposito\n");	
}


/** 
	Função que tem por objetivo a realização de transferencia: orig -> dest
	Você deverá implementar as funcionalidades desta função
*/
void realizarTransferencia(Cliente *orig, Cliente *dest, float valor) {
    // A linha abaixo é apenas ilustrativa, remova-a posteriormente.
    printf("Realizar transferencia\n");	
}


/** 
	Função que tem por objetivo a adição de um cliente no banco de forma ordenada
	Você deverá implementar as funcionalidades desta função
*/
void adicionarCliente(Banco *b, Cliente *c) {  
    // A linha abaixo é apenas ilustrativa, remova-a posteriormente.
    printf("Adicionar cliente %d\n", c->id);

}


/** 
	Função que tem por objetivo a adição de um novo cliente com seus dados iniciais.
	Lembre-se que um cliente deverá possuir uma conta e esta conta possui uma lista de movimentações.
	Você deverá completar as funcionalidades desta função
*/
ptrCliente criarNovoCliente(int idCliente, int numConta, float saldo) {
	ptrCliente novoCliente = (ptrCliente) malloc(sizeof(Cliente));
	novoCliente->id = idCliente;
	
    return novoCliente;
}

/** 
	Função que tem por objetivo a criação de um novo banco.
	Lembre-se, o banco possui uma lista de clientes.
	Você deverá implementar as funcionalidades desta função
*/
Banco* criarBanco(char *nome) {
	// o retorno é apenas ilustrativo. Você deverá modificá-lo posteriormente para atender aos requisitos da aplicação.
    return (Banco*) malloc(sizeof(Banco));
    
}

/** 
	Função que tem por objetivo liberar toda e qualquer memória alocada dinamicamente para o banco, na seguinte ordem:
	1 - Lista de movimentações de cada cliente
	2 - Lista de clientes
	3 - banco
	
	Você deverá implementar as funcionalidades desta função
*/
void liberarBanco(Banco *b) {
}


// Função que realiza a abertura do arquivo. NÃO altere esta função
FILE* openFile(char *path, char *mode) {
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
void readFile(FILE *ptr, Banco *banco)
{
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
            } else {
                printf("ERRO - Ocorreu um erro ao tentar adicionar o cliente %d\n", idCliente);
                liberarBanco(banco);
                fclose(ptr);
                exit(1);
            }
        } else if (strcmp("mov", c1) == 0) { // realizar movimentacoes
            ptrMovimentacao novaMovimentacao = NULL;
            
            switch(c2) {
                case 0: // deposito
                    idCliente = atoi(c3);
                    clienteOrig = buscarCliente(banco, idCliente);

                    if (clienteOrig) {
                        novaMovimentacao = criarNovaMovimentacao(0, valor, clienteOrig->id, 0);

                        if (novaMovimentacao) {
                            realizarDeposito(clienteOrig, novaMovimentacao);
                            clienteOrig = NULL;
                        } else {
                            printf("ERRO - Ocorreu um erro ao tentar depositar %.2f para o cliente %d.\n", valor, idCliente);
                            liberarBanco(banco);
                            fclose(ptr);                                                     
                            exit(1);
                        }

                    } else {
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
                        } else {
                            printf("ERRO - Ocorreu um erro ao tentar realizar o saque de %.2f para o cliente %d.\n", valor, idCliente);
                            liberarBanco(banco);
                            fclose(ptr);                            
                            exit(1);
                        }

                    } else {
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
                    } else {
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
	Você deverá implementar as funcionalidades desta função
*/
void imprimirDados(Banco *b) {
    // A linha abaixo é apenas ilustrativa, remova-a posteriormente.
	printf("Realizar a impressão dos dados seguindo os requisitos da especificao\n");
}


int main(int argc, char *argv[])
{
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
    } else {
        printf("Falha ao tentar abrir o arquivo\n");
        exit(1);
    }
    return 0;
}
