//Menu de Admnistradores

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Livro
{
    char titulo[80];
    char genero[80];
    char autor[80];
    int paginas;
    char sinopse[300];
    int codigo;
}Livro;



void menu(){
    printf("Bem-Vindo administrador! O que deseja fazer? \n \n");
    printf("1- Consultar Livros \n");
    printf("2- Adicionar Livro \n");
    printf("3- Remover Livro\n");
    printf("4- Consultar Usuarios \n");
    printf("5- Remover Usuario \n");
    printf("6- Sair\n");
}
void AddLivro(Livro* livros){
    
    FILE *arquivo = fopen("Livros.bin", "ab");
    printf("Adicione o Livro: \n");
    printf("Titulo: ");
    fgets(livros->titulo, sizeof(livros->titulo), stdin);
    printf("Genero: ");
    fgets(livros->genero, sizeof(livros->genero), stdin);
    printf("Autor: ");
    fgets(livros->autor, sizeof(livros->autor), stdin);
    printf("Paginas: ");
    scanf("%d", &livros->paginas);
    getchar();
    printf("Sinopse: ");
    fgets(livros->sinopse, sizeof(livros->sinopse), stdin);
    int min = 10000;
    int max = 100000; 
    int codigo;
    
    srand(time(NULL));
    
    codigo = (rand() % (max -min + 1)) + min; 
    livros->codigo = codigo; 
    
    //--------------------------------------------------------------------------

    fwrite(livros, sizeof(Livro), 1, arquivo);   // Grava o título
    fclose(arquivo);
    printf("Livro adicionado com sucesso!");


}
int ListarLivros(Livro* livros){
    

    FILE *arquivo = fopen("Livros.bin", "rb"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
    while (fread(livros, sizeof(Livro), 1, arquivo)) {
            printf("Titulo: %s\n", livros->titulo);
            printf("Genero: %s\n", livros->genero);
            printf("Autor: %s\n", livros->autor);
            printf("Paginas: %d\n", livros->paginas);
            printf("Sinopse: %s\n", livros->sinopse);
            printf("Codigo: %d\n", livros->codigo);
            printf("-----------------------------------------------------------\n");
        }
        
    if (feof(arquivo)) {
        printf("Esses sao os livros disponiveis.\n");
    } else {
        printf("Ocorreu um erro na leitura do arquivo.\n");
    }
    fclose(arquivo);

    return 0;
}

void RemoverLivro(Livro* livros){
    int codigo;
    ListarLivros(livros);

    puts("\t\tPagina de remover livros");
    printf("Insira o codigo do livro que deseja remover: ");
    scanf("%d",&codigo);

    FILE* coletarbooks = fopen("Livros.bin", "rb+");
    if(coletarbooks == NULL){
        puts("Nenhum livro cadastrado");
        return;
    }

    // Obtendo numero total de livros
    fseek(coletarbooks,0, SEEK_END);
    size_t pos = ftell(coletarbooks);
    size_t qtd_livros = pos/sizeof(Livro);


    // Coletando todos os livros
    Livro* all_livros = malloc(qtd_livros * sizeof(Livro));
    fseek(coletarbooks,0,SEEK_SET);
    fread(all_livros, sizeof(Livro), qtd_livros, coletarbooks);
    fclose(coletarbooks);
    puts("TODOS OS LIVROS FORAM COLETADOS");

    Livro* filteredBooks = malloc((qtd_livros - 1)*sizeof(Livro));
    int cont = 0;

    // Pegando os livros que nao foram removidos
    for(unsigned int i = 0; i < qtd_livros; i++){
        if(all_livros[i].codigo != codigo){
            filteredBooks[cont] = all_livros[i];
            cont++;
        }
    }
    free(all_livros);

    // Escrevendo os livros que nao foram removidos no arquivo
    FILE* rewriteBooks = fopen("Livros.bin", "wb");
    if(rewriteBooks == NULL){
        puts("Impossivel reescrever livros");
        return;
    }
    fwrite(filteredBooks,sizeof(Livro),cont,rewriteBooks);
    fclose(rewriteBooks);
    free(filteredBooks);

}


void ConsultarUsuarios(){
    char linha[256];

    
    FILE*arquivo = fopen("Usuarios.bin", "rb");
    printf("\n-----------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo)!= NULL)
    {
        printf("%s", linha);
    }
}
void RemoverUsuarios(){
    //Não tenho capacidade de Fazer isso
}


int main(void)
{
    Livro livros;
    int opcao; 
    menu();
    scanf("%d", &opcao);
    if(opcao == 1){
        ListarLivros(&livros);
    }
    else if(opcao == 2){
        getchar();
        AddLivro(&livros);
    }
    else if (opcao == 3){
        RemoverLivro(&livros);
    }
    else if (opcao == 4){
        ConsultarUsuarios();
    }
    else if(opcao == 5){
        RemoverUsuarios();
    }
    else if (opcao == 6)
    {
        printf("Saindo...");
        exit(1);
    }
    

    return 0;
}
