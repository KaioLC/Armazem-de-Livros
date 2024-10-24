#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LOGIN_ADMIN "admin"
#define SENHA_ADMIN "admin"

typedef struct User{
    int id;
    char nome[255];
    char senha[80];
    char registros[255][100];
    char livros[255][10];
}User;

typedef struct Livro
{
    int codigo;
    char titulo[80];
    char genero[80];
    char autor[80];
    int paginas;
    char sinopse[300];
}Livro;


enum progam_status {INIT, LOGGED, EXIT, ADD_BK, RMV_BK, RMV_USER};

void limpaBuffer(){
    int c;
    while((c = getchar() != '\n') && (c != EOF)){ };
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
        if(strcmp(nome, ler_usuarios.nome) == 0 || strcmp(nome,LOGIN_ADMIN) == 0){
           
            fclose(arquivo);
            return true;
        }
    }
    fclose(arquivo);
    return false;
}

bool is_admin(char* login, char* senha){

    if(strcmp(login, LOGIN_ADMIN) == 0 && strcmp(senha, SENHA_ADMIN) == 0){

        return true; // admin fez login
    }

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

void back_to_menu(){
    // int opcao;
    limpaBuffer();
    while(1){
        // puts("[1] Voltar");
        printf("Aperta a tecla ENTER para voltar: ");
        // scanf("%d", &opcao);
        if(getchar()){
            return;
        }
        puts("Nenhuma tecla foi pressionada");
    }
}
int gera_id_user(){
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
int gera_id_books(){
    int id;
    
    FILE* pegar_id = fopen("Livros.bin", "rb");
    if(pegar_id == NULL){
        id = 0;
    }
    else{
        fseek(pegar_id,(-sizeof(Livro)),SEEK_END);
        fread(&id,sizeof(int),1,pegar_id);
        id++;
    }
    fclose(pegar_id);
    
    return id;
}

bool cadastro(){
    User novousuario;

    puts("\tPagina de Cadastro");

    printf("Insira seu Usuario: ");
    fgets(novousuario.nome,sizeof(novousuario.nome),stdin);
    strcpy(novousuario.nome, clear_newLine(novousuario.nome));

    if(usuario_existente(novousuario.nome)){
        puts("Usuario existente.");
        return false;
    }
    
    printf("Insira sua senha: ");
    fgets(novousuario.senha,sizeof(novousuario.senha),stdin);
    strcpy(novousuario.senha, clear_newLine(novousuario.senha));



    novousuario.id = gera_id_user();

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
    
    puts("\t\tPagina de Login");

    printf("Digite seu Usuario: ");
    fgets(user_logado->nome,sizeof(user_logado->nome),stdin);
    strcpy(user_logado->nome, clear_newLine(user_logado->nome));


    printf("Digite sua senha: ");
    fgets(user_logado->senha,sizeof(user_logado->senha),stdin);
    strcpy(user_logado->senha, clear_newLine(user_logado->senha));

    if(is_admin(user_logado->nome, user_logado->senha)) return true;

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
    puts("\tPagina de Login/Cadastro");

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
    return false;
}

// funcao que armazena os registros do programa no arquivo log.txt
void registros(int status, User* user_logado, int id){
    FILE* registros = fopen("log.txt", "a");
    if(registros == NULL){
        printf("Erro ao abrir o arquivo de registros");
        return;
    }
    time_t seconds; // long long seconds

    time(&seconds);
    char* data_hora = ctime(&seconds);
    data_hora[strcspn(data_hora, "\n")] = 0;

    switch(status){
        case INIT:
            fprintf(registros,">>> %s Programa Iniciado <<<\n",data_hora);
            break;
        case LOGGED:
            if(strcmp(user_logado->nome,"admin") == 0 && strcmp(user_logado->senha,"admin") == 0){
                fprintf(registros,"--- %s O Administrador entrou ---\n",data_hora);
            }
            else{
                fprintf(registros,"--- %s O usuario [%d]  %s conectou ---\n",data_hora,user_logado->id,user_logado->nome);
            }
            break;
        case EXIT:
            fprintf(registros,"<<< %s Sessão Encerrada >>>\n",data_hora);
            break;
        case ADD_BK:
            fprintf(registros,"%s O Administrador adicionou um Livro -> ID [%d] \n",data_hora, id);
            break;
        case RMV_BK:
            fprintf(registros,"%s O Administrador removeu um Livro -> ID [%d] \n",data_hora, id);
            break;
        case RMV_USER:
            fprintf(registros,"%s O Administrador removeu um Usuario -> ID [%d] \n",data_hora, id);
            break;
        default:
            printf("Impossível armazenar o registro");
    }
    fclose(registros);
}


void menu_adm(){
    printf("\n\nMenu do administrador! O que deseja fazer? \n \n");
    printf("1- Consultar Livros \n");
    printf("2- Adicionar Livro \n");
    printf("3- Remover Livro\n");
    printf("4- Consultar Usuarios \n");
    printf("5- Remover Usuario \n");
    printf("6- Sair\n");
}
void menu_user(){
    puts("\n\n\tMenu Principal \n\n");
    puts("[1] Consultar Livros Disponíveis");
    puts("[2] Consultar seus Livros");
    puts("[3] Alugar Livro");
    puts("[4] Devolver Livro");
    puts("[5] Sair");
}
void AddLivro(Livro* livros){
    puts("\n\t\tTodos os Livros Disponíveis \n");
    FILE *arquivo = fopen("Livros.bin", "ab");
    printf("Adicione o Livro: \n");
    printf("Titulo: ");
    fgets(livros->titulo, sizeof(livros->titulo), stdin);
    strcpy(livros->titulo, clear_newLine(livros->titulo));
    printf("Genero: ");
    fgets(livros->genero, sizeof(livros->genero), stdin);
    strcpy(livros->genero, clear_newLine(livros->genero));
    printf("Autor: ");
    fgets(livros->autor, sizeof(livros->autor), stdin);
    strcpy(livros->autor, clear_newLine(livros->autor));
    printf("Paginas: ");
    scanf("%d", &livros->paginas);
    limpaBuffer();
    printf("Sinopse: ");
    fgets(livros->sinopse, sizeof(livros->sinopse), stdin);
    strcpy(livros->sinopse, clear_newLine(livros->sinopse));

    int codigo = gera_id_books();
    livros->codigo = codigo; 
    
    //--------------------------------------------------------------------------

    fwrite(livros, sizeof(Livro), 1, arquivo); 
    fclose(arquivo);

    registros(ADD_BK,NULL,codigo);
    printf("Livro adicionado com sucesso!");


}
int ListarLivros(Livro* livros){
    

    FILE *arquivo = fopen("Livros.bin", "rb"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }

    while (fread(livros, sizeof(Livro), 1, arquivo)) {
            printf("-----------------------------------------------------------\n");
            printf("\x1b[32mTitulo: %s\x1b[0m\n", livros->titulo);
            printf("Genero: %s\n", livros->genero);
            printf("Autor: %s\n", livros->autor);
            printf("Paginas: %d\n", livros->paginas);
            printf("Sinopse: %s\n", livros->sinopse);
            printf("\x1b[32mCodigo: %d\n\x1b[0m", livros->codigo);
            printf("-----------------------------------------------------------\n");
        }
        
    if (feof(arquivo)) {
        printf("Esses sao os livros disponiveis.\n");
    } else {
        printf("Ocorreu um erro na leitura do arquivo.\n");
    }
    fclose(arquivo);
    back_to_menu();
    return 0;
}

void RemoverLivro(){
    int codigo;

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

    Livro* filteredBooks = malloc((qtd_livros)*sizeof(Livro));
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
    registros(RMV_BK,NULL,codigo);
    printf("Livro com ID [%d] foi removido.",codigo);
    fclose(rewriteBooks);
    free(filteredBooks);

}


void ConsultarUsuarios(User* usuarios){
    puts("\t\tLista de todos os usuarios!");
    FILE*arquivo = fopen("usuarios", "rb");
    printf("\n-----------------------------------------------------------\n");

    while (fread(usuarios, sizeof(User),1,arquivo))
    {
        printf("ID: %d User: %s\n", usuarios->id, usuarios->nome);
    }

    return back_to_menu();
}
void RemoverUsuarios(){
    int id;

    puts("\t\tPagina de remover usuarios");
    printf("Insira o ID do Usuario que deseja remover: ");
    scanf("%d",&id);

    FILE* coletarusers = fopen("usuarios", "rb+");
    if(coletarusers == NULL){
        puts("Nenhum usuario cadastrado");
        return;
    }

    // Obtendo numero total de usuarios
    fseek(coletarusers,0, SEEK_END);
    size_t pos = ftell(coletarusers);
    size_t qtd_usuarios = pos/sizeof(User);


    // Coletando todos os usuarios
    User* all_users = malloc(qtd_usuarios * sizeof(User));
    fseek(coletarusers,0,SEEK_SET);
    fread(all_users, sizeof(User), qtd_usuarios, coletarusers);
    if(all_users == NULL){
        puts("Erro na alocacao de memoria para all_users");
        return;
    }
    fclose(coletarusers);

    User* filteredUsers = malloc((qtd_usuarios)*sizeof(User));
    if(filteredUsers == NULL){
        puts("Erro na alocacao de memoria para filteredUsers");
        free(all_users);
        return;
    }
    int cont = 0;

    // Pegando os usuarios que nao foram removidos
    for(unsigned int i = 0; i < qtd_usuarios; i++){
        if(all_users[i].id != id){
            filteredUsers[cont] = all_users[i];
            cont++;
        }
    }
    free(all_users);

    // Escrevendo os usuarios que nao foram removidos no arquivo
    FILE* rewriteUsers = fopen("usuarios", "wb");
    if(rewriteUsers == NULL){
        puts("Impossivel reescrever usuarios");
        free(filteredUsers);
        return;
    }
    
    fwrite(filteredUsers,sizeof(User),cont,rewriteUsers);
   
    free(filteredUsers);
   
    fclose(rewriteUsers);
 
    registros(RMV_USER,NULL,id);
    printf("Usuario com ID [%d] foi removido.",id);
}


int main(void)
{
    User usuario;
    Livro livros;
    registros(INIT,&usuario,0);
    int opcao; 
    if(tela_inicial()) if(login(&usuario)){
        if(is_admin(usuario.nome, usuario.senha)){

            registros(LOGGED,&usuario,0);

            
            while(true){
                menu_adm();
                scanf("%d", &opcao);
                limpaBuffer();
                switch(opcao){
                    case 1:
                        ListarLivros(&livros);
                        break;
                    case 2:
                        getchar();
                        AddLivro(&livros);
                        break;
                    case 3:
                        RemoverLivro();
                        break;
                    case 4:
                        ConsultarUsuarios(&usuario);
                        break;
                    case 5:
                        RemoverUsuarios();
                        break;
                    case 6:
                        puts("Saindo...");
                        registros(EXIT,&usuario,0);
                        exit(1);
                    default:
                        puts("Opcao Invalida...");
                        break;
                }

            }
        }
        else{
            registros(LOGGED,&usuario,0);
            
            while(true){
                menu_user();
                scanf("%d", &opcao);
                switch(opcao){
                    case 1:
                        ListarLivros(&livros);
                        break;
                    case 2:
                        puts("Consultar seus Livros");
                        break;
                    case 3:
                        puts("Alugar um Livro");
                        break;
                    case 4:
                        puts("Devolver um Livro");
                        break;
                    case 5:
                        puts("Sair");
                        registros(EXIT,&usuario,0);
                        exit(1);
                        break;
                    default:
                        puts("Opcao Invalida");
                        break;
                }
            
            }
        }
    }
    return 0;
}
