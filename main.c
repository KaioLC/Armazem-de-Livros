#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct User{
    int id;
    char nome[255];
    char cpf[15];
    char senha[80];
    char registros[255][100];
    char livros[255][10];
}User;

void limpaBuffer(){
    int c;
    while(c = getchar() != '\n' && c != EOF){ }
}

bool usuario_existente(char* cpf){
    User ler_usuarios;

    FILE* arquivo = fopen("usuarios", "rb");
    if(arquivo == NULL){
        printf("\n\t\x1b[32m Nosso Primeiro Usuário! Olá\x1b[0m\n\n");

        return false;
    }

    while(fread(&ler_usuarios,sizeof(User),1,arquivo)){
        if(strcmp(cpf, ler_usuarios.cpf) == 0){
           
            fclose(arquivo);
            return true;
        }
    }
    fclose(arquivo);
    return false;
}

int gera_id(){
    int id;

    FILE* pegar_id = fopen("usuarios", "rb");
    if(pegar_id == NULL){
        id = 0;
    }
    else{
        fseek(pegar_id,(-sizeof(User)),SEEK_END);
        fread(&id,sizeof(int),1,pegar_id);
        id++;
    }
    fclose(pegar_id);
    
    return id;
}

bool cadastro(){
    User novousuario;

    puts("\tPágina de Cadastro");

    printf("Insira seu CPF: ");
    fgets(novousuario.cpf,sizeof(novousuario.cpf),stdin);
    
    if(usuario_existente(novousuario.cpf) == true){
        puts("Usuario existente.");
        return false;
    }
    
    printf("Insira seu nome: ");
    fgets(novousuario.nome,sizeof(novousuario.nome),stdin);
    printf("Insira sua senha: ");
    fgets(novousuario.senha,sizeof(novousuario.senha),stdin);


    novousuario.id = gera_id();

    FILE* adicionar_usuario = fopen("usuarios", "ab");
    if(adicionar_usuario == NULL){
        puts("Incapaz de adicionar usuario");
        return false;
    }
    fwrite(&novousuario,sizeof(User),1,adicionar_usuario);
    fclose(adicionar_usuario);
    return true;
}


int main(void){
    User usuario;
    
    cadastro();
    
    FILE* arquivo = fopen("usuarios","rb");

    if(arquivo == NULL){
        printf("Não foi possivel abrir o arquivo usuario");
        exit(1);
    }

    // while(fread(&usuario,sizeof(User),1,arquivo)){
    //     printf("ID = %d   %s\n", usuario.id, usuario.nome);
    // }


    return 0;
}