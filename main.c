//Menu de Admnistradores

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Livro
{
    char titulo[80];
    char genero[80];
    char Autor[80];
    int Paginas;
    char sinopse[300];
    int codigo;
};



void menu(){
    printf("Bem-Vindo administrador! O que deseja fazer? \n \n");
    printf("1- Consultar Livros \n");
    printf("2- Adicionar Livro \n");
    printf("3- Remover Livro\n");
    printf("4- Consultar Usuarios \n");
    printf("5- Remover Usuario \n");
    printf("6- Sair\n");
}
void AddLivro(){
    struct Livro livro;
    FILE *arquivo = fopen("Livros.txt", "a");
    printf("Adicione o Livro: \n");
    printf("Titulo: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    printf("Genero: ");
    fgets(livro.genero, sizeof(livro.genero), stdin);
    printf("Autor: ");
    fgets(livro.Autor, sizeof(livro.Autor), stdin);
    printf("Paginas: ");
    scanf("%d", &livro.Paginas);
    getchar();
    printf("Sinopse: ");
    fgets(livro.sinopse, sizeof(livro.sinopse), stdin);
    int min = 10000;
    int max = 100000; 
    int codigo;
    
    srand(time(NULL));
    
    codigo = (rand() % (max -min + 1)) + min; 
    livro.codigo = codigo; 
    
    //--------------------------------------------------------------------------

    fprintf(arquivo, "Titulo: %s", livro.titulo);
    fprintf(arquivo, "Genero: %s", livro.genero);
    fprintf(arquivo, "Autor: %s", livro.Autor);
    fprintf(arquivo, "Paginas: %d\n", livro.Paginas);
    fprintf(arquivo, "Sinopse: %s", livro.sinopse);
    fprintf(arquivo, "Codigo: %d \n", livro.codigo);
    fprintf(arquivo, "-----------------------------------------------------------\n");
    
    
    fclose(arquivo);

    printf("Livro adicionado com sucesso!");


}

void RemoverLivro(){
    //Não consegui fazer essa função, muito dificil e eu não tenho capacidade
}
void ConsultarLivros(){
    char linha[256];

    
    FILE*arquivo = fopen("Livros.txt", "r");
    printf("\n-----------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo)!= NULL)
    {
        printf("%s", linha);
    }
}
void ConsultarUsuarios(){
    char linha[256];

    
    FILE*arquivo = fopen("Usuarios", "rb");
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
    int opcao; 
    menu();
    scanf("%d", &opcao);
    if(opcao == 1){
        ConsultarLivros();
    }
    else if(opcao == 2){
        getchar();
        AddLivro();
    }
    else if (opcao == 3){
        RemoverLivro();
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
