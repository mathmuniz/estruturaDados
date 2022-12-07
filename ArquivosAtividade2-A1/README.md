### Especificao
### Gerenciando contatos
Escreva um programa em linguagem C que realize a leitura dos dados de contatos de usuarios
fictıcios. Estes dados estao armazenados no arquivo “contacts dataset.dat” fornecido juntamente com esta especificaao. Neste arquivo, os dados estao dispostos linha a linha. Cada
linha contem as seguintes informacoes:
- Id
- Nome
- Telefone
- E-mail

Ao ser iniciado, seu programa devera ler o caminho para o arquivo com um simples scanf e
posteriormente solicitar o numero de contatos (numCont) a serem lidos, tambem atraves de um
simples scanf.
Existem exatamente 100 registros no arquivo, portanto o valor lido devera estar entre:
1 ≤ numCont ≤ 100.
Nesta atividade voce utilizara um vetor de estruturas (structs) que devera ser alocado dinamicamente de acordo com a quantidade fornecida pelo usuario relacionada ao numero de contatos
a serem lidos. O vetor devera ser do tipo (TContato) e servira para armazenar os dados dos
respectivos contatos.
Devera existir uma funcao para cada uma das seguintes tarefas:
- Alocar o vetor e retornar um ponteiro valido para o mesmo.
- Realizar a leitura dos dados no arquivo e adicionar os contatos no vetor.
- Remover um contato do vetor. Neste caso a funcao devera receber por parametro o id do
contato a ser excluıdo.
- Mostrar os dados dos contatos ordenados por id (identificador).
Para a realizar a ordenacao dos contatos no vetor, o algoritmo quicksort (tambem fornecido
juntamente com esta especificacao) devera ser utilizado.

Observa¸coes importantes:
- Seu programa devera liberar toda e qualquer memoria previamente alocada de forma
dinamica.
- O usuario devera ser informado com uma mensagem de “Arquivo nao encontrado” se
fornecer um nome/caminho de arquivo inexistente. Neste caso o programa devera ser
imediatamente finalizado.
Abaixo seguem alguns exemplos de como seu programa devera se comportar:

./contatos

/home/usuario/Desktop/arquivo.dat

10


Arquivo nao encontrado.

./contatos

/home/usuario/Desktop/arquivo.dat

0

O valor informado deve estar dentro do 

intervalo: 1 <= x <= 100.

./contatos

/home/usuario/Desktop/arquivo.dat

-1

O valor informado deve estar dentro do 

intervalo: 1 <= x <= 100.

./contatos

/home/usuario/Desktop/arquivo.dat

101

O valor informado deve estar dentro do 
intervalo: 1 <= x <= 100.

./contatos

/home/usuario/Desktop/contacts dataset.dat

5
