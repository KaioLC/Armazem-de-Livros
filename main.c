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
void AddLivro(){
    Livro livro;
    FILE *arquivo = fopen("Livros.txt", "a");

    if(arquivo == NULL){
        printf("Primeiro Livro Cadastrado");
    }

    printf("Adicione o Livro: \n");
    printf("Titulo: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    printf("Genero: ");
    fgets(livro.genero, sizeof(livro.genero), stdin);
    printf("Autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    printf("Paginas: ");
    scanf("%d", &livro.paginas);
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

    fprintf(arquivo, "%d\n", livro.codigo);
    fprintf(arquivo, "%s", livro.titulo);
    fprintf(arquivo, "%s", livro.genero);
    fprintf(arquivo, "%s", livro.autor);
    fprintf(arquivo, "%d\n", livro.paginas);
    fprintf(arquivo, "%s", livro.sinopse);
    
    fclose(arquivo);

    printf("Livro adicionado com sucesso!");


}

void RemoverLivro(){
    //Não consegui fazer essa função, muito dificil e eu não tenho capacidade
}
void ConsultarLivros(){
    Livro livro;
    FILE*arquivo = fopen("Livros.txt", "r");

    if(arquivo == NULL){
        printf("Nenhum Livro cadastrado.");
        return;
    }
    printf("\n-----------------------------------------------------------\n");

    while (fscanf(arquivo, "Codigo: %d\nTitulo: %[^\n]\nGenero: %[^\n]\nAutor: %[^\n]\nPaginas: %d\nSinospe: %[^\n]\n",&livro.codigo, livro.titulo, livro.genero, livro.autor, &livro.paginas, livro.sinopse) != EOF)
    {   
        printf("Título: %s\n", livro.titulo);
        printf("Gênero: %s\n", livro.genero);
        printf("Autor: %s\n", livro.autor);
        printf("Páginas: %d\n", livro.paginas);
        printf("Sinopse: %s\n", livro.sinopse);
        printf("Código: %d\n", livro.codigo);
        printf("-----------------------------------------------------------\n");
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
