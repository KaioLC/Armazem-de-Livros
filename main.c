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
    char autor[80];
    int paginas;
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
    FILE *arquivo = fopen("Livros.bin", "ab");
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

    fwrite(livro.titulo, sizeof(livro.titulo), 1, arquivo);   // Grava o título
    fwrite(livro.genero, sizeof(livro.genero), 1, arquivo);   // Grava o gênero
    fwrite(livro.autor, sizeof(livro.autor), 1, arquivo);     // Grava o autor
    fwrite(&livro.paginas, sizeof(livro.paginas), 1, arquivo); // Grava o número de páginas
    fwrite(livro.sinopse, sizeof(livro.sinopse), 1, arquivo); // Grava a sinopse
    fwrite(&livro.codigo, sizeof(livro.codigo), 1, arquivo);   // Grava o código
    fclose(arquivo);  // Fecha o arquivo

    printf("Livro adicionado com sucesso!");


}

void RemoverLivro(){
    //Não consegui fazer essa função, muito dificil e eu não tenho capacidade
}
int ConsultarLivros(){
    
    struct Livro livro;

    FILE *arquivo = fopen("livros.bin", "rb"); 
    if (arquivo != NULL) {
        while (fread(&livro, sizeof(livro), 1, arquivo) == 1) {
            printf("Titulo: %s\n", livro.titulo);
            printf("Genero: %s\n", livro.genero);
            printf("Autor: %s\n", livro.autor);
            printf("Paginas: %d\n", livro.paginas);
            printf("Sinopse: %s\n", livro.sinopse);
            printf("Codigo: %d\n", livro.codigo);
            printf("-----------------------------------------------------------\n");
        }
        
        if (feof(arquivo)) {
            printf("Esses sao os livros disponiveis.\n");
        } else {
            printf("Ocorreu um erro na leitura do arquivo.\n");
        }

        fclose(arquivo); 
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }

    return 0;
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
