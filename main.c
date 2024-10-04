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

    fprintf(arquivo, "Título: %s", livro.titulo);
    fprintf(arquivo, "Gênero: %s", livro.genero);
    fprintf(arquivo, "Autor: %s", livro.Autor);
    fprintf(arquivo, "Páginas: %d\n", livro.Paginas);
    fprintf(arquivo, "Sinopse: %s", livro.sinopse);
    fprintf(arquivo, "Código: %d \n", livro.codigo);
    fprintf(arquivo, "-----------------------------------------------------------\n");
    
    
    fclose(arquivo);

    printf("Livro adicionado com sucesso!");


}

//Função de Remoção de Livro com bugs


// void RemoverLivro(){
//     struct Livro livro;
//     FILE * arquivo = fopen("Livros.txt", "r");
//     FILE * temp = fopen("temp.txt", "a");
//     int codigoRemover;

//     printf("Digite o codigo do livro que será removido: ");
//     scanf("%d", &codigoRemover); 



//     int removido = 0;

//     while (fscanf(arquivo, "Título: %[^\n]\n", livro.titulo) != EOF) {
//         fscanf(arquivo, "Gênero: %[^\n]\n", livro.genero);
//         fscanf(arquivo, "Autor: %[^\n]\n", livro.Autor);
//         fscanf(arquivo, "Páginas: %d\n", &livro.Paginas);
//         fscanf(arquivo, "Sinopse: %[^\n]\n", livro.sinopse);
//         fscanf(arquivo, "Código: %d\n", &livro.codigo);
//         fgetc(arquivo);

//         if (livro.codigo != codigoRemover) {
//             fprintf(temp, "Título: %s\n", livro.titulo);
//             fprintf(temp, "Gênero: %s\n", livro.genero);
//             fprintf(temp, "Autor: %s\n", livro.Autor);
//             fprintf(temp, "Páginas: %d\n", livro.Paginas);
//             fprintf(temp, "Sinopse: %s\n", livro.sinopse);
//             fprintf(temp, "Código: %d\n", livro.codigo);
//         } else {
//             removido = 1;
//         }
//     }
    

//     fclose(arquivo);
//     fclose(temp);

//     if(removido == 1){
//         remove("Livros.txt");
//         rename("temp.txt", "Livros.txt");
//         printf("Livro Removido!");
//     }
//     else{
//         remove("temp.txt");
//         printf("Não foi possivel encontrar o codigo desse livro!");
//     }


// }




int main(void)
{
    int opcao; 
    menu();
    scanf("%d", &opcao);
    if(opcao == 2){
        getchar();
        AddLivro();
    }
    else if (opcao == 3){
        RemoverLivro();
    }


    return 0;
}
