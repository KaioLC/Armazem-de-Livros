#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LOGIN_ADMIN "admin"
#define SENHA_ADMIN "admin"

typedef struct User{
    int id;
    char nome[255];
    char senha[80];
    char registros[255][100];
    char livros[255][10];
}User;

void limpaBuffer(){
    int c;
    while(c = getchar() != '\n' && c != EOF){ }
}

char* clear_newLine(char* string){

    string[strcspn(string, "\n")] = 0;

    return string;
}

bool usuario_existente(char* nome){
    User ler_usuarios;

    FILE* arquivo = fopen("usuarios", "rb");
    if(arquivo == NULL){
        printf("\n\t\x1b[32m Nosso Primeiro Usuário! Olá\x1b[0m\n\n");

        return false;
    }

    while(fread(&ler_usuarios,sizeof(User),1,arquivo)){
        if(strcmp(nome, ler_usuarios.nome) == 0){
           
            fclose(arquivo);
            return true;
        }
    }
    fclose(arquivo);
    return false;
}

long seekUser(User* user_logado, FILE* arquivo){
    User usuarios;
    
    long pos = -1;

    while(fread(&usuarios,sizeof(User),1,arquivo)){
        if(strcmp(user_logado->nome, usuarios.nome) == 0 && strcmp(user_logado->senha, usuarios.senha) == 0){
            
            pos = ftell(arquivo) - sizeof(User);
        }
    }

    return pos;
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

    printf("Insira seu Usuario: ");
    fgets(novousuario.nome,sizeof(novousuario.nome),stdin);
    strcpy(novousuario.nome, clear_newLine(novousuario.nome));

    if(usuario_existente(novousuario.nome) == true || novousuario.nome == LOGIN_ADMIN){
        puts("Usuario existente.");
        return false;
    }
    
    printf("Insira sua senha: ");
    fgets(novousuario.senha,sizeof(novousuario.senha),stdin);
    strcpy(novousuario.senha, clear_newLine(novousuario.senha));



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

bool login(User* user_logado){

    FILE* coletar_user = fopen("usuarios", "rb");
    if(coletar_user == NULL){
        puts("\nSem usuarios cadastrados.\n");
        return false;
    }
    
    puts("\t\tPágina de Login");

    printf("Digite seu Usuario: ");
    fgets(user_logado->nome,sizeof(user_logado->nome),stdin);
    strcpy(user_logado->nome, clear_newLine(user_logado->nome));


    printf("Digite sua senha: ");
    fgets(user_logado->senha,sizeof(user_logado->senha),stdin);
    strcpy(user_logado->senha, clear_newLine(user_logado->senha));


    long pos_user = seekUser(user_logado, coletar_user);

    if( pos_user != -1){

        fseek(coletar_user, pos_user, SEEK_SET);
        fread(user_logado,sizeof(User),1,coletar_user);
        fclose(coletar_user);

        return true;
    }
    else{

        printf("Usuario/Senha Incorretos.");
        fclose(coletar_user);

        return false;
    }
}

bool tela_inicial(){
    puts("\tPágina de Login/Cadastro");

    printf("[1] Login\n[2] Cadastro\n[3] Creditos\n");
    
    printf("\n\tOpcao: ");
    char opcao = getchar();
    limpaBuffer();

    switch(opcao){
        case '1':
            return true;
        case '2':
            if(cadastro()) return true;
        case '3':
            /// Possivel pagina de creditos;
            break;
        default:
            puts("Opcao Inválida");
            break;
    }


}

int main(void){
    User usuario;

    if(tela_inicial()) if(login(&usuario)){
        puts("Logado com sucesso!");
    }
    

    return 0;
}