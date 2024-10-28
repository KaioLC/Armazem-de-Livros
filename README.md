# Biblioteca Imaginária
## Sobre
O programa foi feito para simular uma biblioteca virtual onde o usuário pode alugar e devolver livros cadastrados pelo administrador, os livros são apenas para ilustração, portanto não existem realmente e não podem ser lidos pelo usuário. Todas as ações como, iniciar programa, realizar login, cadastrar livro, remover livro, alugar livro, devolver livro, remover usuário e finalizar o programa são salvas com data e horário da ação em um arquivo ```log.txt```
## Compilação e Execução
### Compilando
O programa é feito em um arquivo C denominado "main.c", utilizando o compilador gcc onde é realizado a traducao do codigo fonte para a linguagem da máquina, deve-se usar o comando: ```gcc -o nomedoexecutavel main.c```
  - Esse comando vai gerar um arquivo .exe (executavel) onde ao abri-lo vai começar a rodar o programa.
### Etapas de execução
  - Primeiro ocorre um pré-processamento onde é feito a leitura das diretivas (#include e #define) do código:
    - ```#include <stdio.h>``` essa diretiva permite o uso da biblioteca stdio.h que foi usada para possibilitar o uso das funções:
      - ```printf()```,```scanf()```,```fgets()```, ```sprintf()```,```getchar()``` para I/O
      - ```fopen()```,```fclose```,```fread()```,```fwrite()```,```fseek()```,```ftell()``` para manipulacao dos arquivos.
    - ```#include <stdlib.h>``` é responsavel pelas funções:
      - ```malloc()```, ```free()``` para alocamento de memória
      - ```exit()``` para gerenciamento de erros.
    - ```#include <string.h``` dessa biblioteca foram utilizadas as funções:
      - ```strcmp()``` para verificar igualdade entre strings
      - ```strcpy()``` para copiar uma string
      - ```strcspn()``` para retira valores indesejados na string.
    - ```#include <stdbool.h>``` foi usado para declarar valores booleanos (true, false) e facilitar a leitura do código
    - ```#include <time.h>``` biblioteca utilizada para obtenção de datas:
      - ```time()``` coleta a data atual do sistema utilizada em uma variavel tipo time_t
      - ```ctime()``` transforma o resultado obtido em time() para uma string.
    - ```#define LOGIN_ADMIN "admin"``` é criado um macro onde LOGIN_ADMIN é lido como a string "admin"
    - ```#define SENHA_ADMIN "admin"``` é criado um macro de SENHA_ADMIN que é uma string "admin".
   
### Execução
  - Após a obtenção das bibliotecas e macros obtida pelas diretivas, o código é traduzido para linguagem máquina, onde é gerado o arquivo executável para utilização do programa. Utilizando Windows, digite o comando ```nomeexecutavel.exe``` para rodar o código traduzido.
  - Ao ser executado o código é jogado na memória e processado pela CPU, exibindo assim as saídas e também criando arquivos binários para armazenamento conforme definido na estrutura do código.

## Funcionalidades
### Cadastro
Para realizar o cadastro é pedido ao usuário um nome e uma senha, cada usuário possui um nome único e um ID (gerado automaticamente pelo programa após o cadastro).
### Login
Existem 2 formas de realizar o login, sendo uma delas pelo usuário, onde será exibido um menu com ações que um usuário comum pode realizar no programa. Também existe o login de administrador onde é inserido um usuário: **admin** e senha: **admin** definidos pelo programador.
### Tela Usuario
Na tela pós login do usuário existem 5 opções:
  - ### Consultar livros disponíveis
       - Nessa tela o usuário pode consultar todos os livros adicionados pelo administrador no armazem, livros esses que ele pode alugar.
  - ### Aluga livro por ID
       - Essa opção permite o usuário alugar um livro disponível na biblioteca pelo seu ID, só é possível alugar 1 unidade de cada livro e, após alugar um determinado livro o programa armazena a data que foi realizado o pedido. 
  - ### Consulta inventario de livros
       - Utilizando essa função é possível ver todos os **livros alugados** pelo usuário juntamente das respectivas datas. 
  - ### Devolver um livro
       - Aqui é possível realizar a devolução de um livro, ao inserir o ID do livro que deseja devolver ele é removido do inventário do usuário. 
  - ### Sai
       - Finaliza o programa 
### Tela Admin
Na tela de administrador existem 5 opções:
  - ### Consultar livros disponiveis
       - Nessa tela é possível consultar todos os livros adicionados pelo administrador no armazem.
  - ### Adicionar Livro
       - Como o nome sugere, o administrador utiliza esta opção para cadastrar um livro, especificando título, genêro, autor, número de páginas e sinopse do livro, também é gerado um código único do livro, automaticamente. 
  - ### Remover Livro
       - Aqui o administrador insere o código do livro que ele deseja excluir da biblioteca. 
  - ### Consultar usuarios
       - Nessa janela o administrador visualiza todos os usuários juntamente de seus ID's  
  - ### Remover usuario
       - Tendo o ID do usuário o administrador pode utilizar esta opção para apagar sua conta do sistema.
  - ### Sai
       - Finaliza a sessão.
## Creditos
  -  Kaio Custodio (22.224.028-5)
  -  Henrique Nicolini (22.124.049-2)
