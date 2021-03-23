#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<windows.h>
#define MAX_YR  9999
#define MIN_YR  1900

typedef struct usuario USUARIO;
    struct usuario{
        char us_nome[50];
        char us_email[50];
        char us_senha[10];
    };

typedef struct data DATA;
    struct data{
        int dia;
        int mes;
        int ano;
    };

    typedef struct data_diag DATA_DIAG;
    struct data_diag{
        int dia;
        int mes;
        int ano;
    };

typedef struct endereco ENDERECO;
    struct endereco{
        char rua[80];
        char numero[10];
        char bairro[50];
        char cidade[30];
        char estado[20];
        char cep[9];

    };

typedef struct paciente PACIENTE;
    struct paciente{
        char nome[50];
        char cpf[12];
        char telefone[15];
        char email[50];
        ENDERECO _endereco;
        DATA data_nasc;
        DATA_DIAG dt_diag;
        char comorbidade[200];

    };


void cabecalhoLogin();
void cabecalhoCad();
void cabecalhoPac();
void cad_usuario();
int validaEmail(char email[]);
int validaData();
int verificaSenha(char senha[10]);
int verificaNome(char nome[50]);
int verificaChar(char c[]);
int verificaCPF(char cpf[]);
int verificaCEP(char cep[]);
int verificaNum(char n[]);
int verificaCad(char nome[]);
void menuLogin();
void logar();
int loginEmail(char email[50]);
int loginSenha(char senha [10]);
void cad_paciente();
int verificaPac(char cpf[]);
void listar_usuario();
void cabecalhoListtUs();
int verificaTxt();
void cabecalhoListPac();
void listaPaciente();


 int main(){
    system("color 3f");
    setlocale(LC_ALL, "portuguese_brasil");

    menuLogin();
}

//cabeçalho login
void cabecalhoLogin(){
    system("cls");
    printf(" ___________________________________________________\n");
    printf("|                                                   |\n");
    printf("|                      LOGIN                        |\n");
    printf("|___________________________________________________|\n");
}

//cabeçalho cadastro usuario
void cabecalhoCad(){
     system("cls");
    printf(" ___________________________________________________\n");
    printf("|                                                   |\n");
    printf("|            **CADASTRO DE USUARIOS**               |\n");
    printf("|___________________________________________________|\n");
}


//cabeçalho lista paciente
void cabecalhoListPac(){
     system("cls");
    printf(" ___________________________________________________\n");
    printf("|                                                   |\n");
    printf("|            **PACIENTES CADASTRADOS**              |\n");
    printf("|___________________________________________________|\n");
}

//cabeçalho do menu paciente
void cabecalhoPac(){
     system("cls");
    printf(" ___________________________________________________\n");
    printf("|                                                   |\n");
    printf("|            **CADASTRO DE PACIENTES**              |\n");
    printf("|___________________________________________________|\n");
}

//menu login
void menuLogin(){

    int opt;
     do {
        cabecalhoLogin();
        printf(" ___________________________________________________\n");
        printf("|                                                   |\n");
        printf("|           1-Cadastrar usuario no sistema          |\n");
        printf("|                                                   |\n");
        printf("|           2-Logar no sistema                      |\n");
        printf("|                                                   |\n");
        printf("|___________________________________________________|\n");
        printf(" Selecione:");
        scanf("%d", &opt);


        switch(opt){
              case 1:
                cad_usuario();
            break;

            case 2:
                logar();
            break;

           default:
                printf("Invalido!\n");
                getche();
            break;
        }
    }while(opt != 0);

}

//menu do paciente
void menuCadPaciente(){
    int opt;
     do{
        printf(" ___________________________________________________\n");
        printf("|                                                   |\n");
        printf("|              SISTEMA HOSPITALAR                   |\n");
        printf("|___________________________________________________|\n");
        printf("|                                                   |\n");
        printf("|           1-Cadastrar Paciente                    |\n");
        printf("|                                                   |\n");
        printf("|           2-Listar Pacientes                      |\n");
        printf("|                                                   |\n");
        printf("|           0-Sair                                  |\n");
        printf("|                                                   |\n");
        printf("|___________________________________________________|\n");
        printf(" Selecione:\n");
        scanf(" %d", &opt);

        switch(opt){

            case 1:
                //cadastrar pacientes
                cad_paciente();
                break;
            case 2:
                //listar pacientes
                listaPaciente();
                break;
            case 0:
                //sair
                printf(" Saindo......");
                Sleep(1);
                system("cls");
                menuLogin();

            default:
                printf("\nInvalido!\n");
                getch();
                system("cls");
                menuCadPaciente();
                break;
        }

     }while(opt != 0 );

}


//cadastro de pacientes
void cad_paciente(){
    PACIENTE p;

    FILE* file;
    file = fopen("pacientes.txt","a");
    if(!file){
        printf("ERRO: file(pacientes)");
    }else{

        cabecalhoPac();

        do{
            do{
                fflush(stdin);
                printf(" Data diagnostico formato dia/mes/ano:");
                scanf("%d/%d%/%d",&p.dt_diag.dia, &p.dt_diag.mes, &p.dt_diag.ano);
                if(validaData(p.dt_diag.dia, p.dt_diag.mes, p.dt_diag.ano)!=1)
                    printf("Data invalida!\n");
            }while(validaData(p.dt_diag.dia, p.dt_diag.mes, p.dt_diag.ano)!=1);

            do{
                fflush(stdin);
                printf(" Cpf do paciente: ");
                scanf("%s%*c",&p.cpf);
                if(verificaCPF(p.cpf)==1){
                    printf("Cpf invalido! Verifique se digitou 11 números sem letras ou caracteres especiais.\n");
                }
                 if(verificaPac(p.cpf)==0){
                    printf("****Paciente cadastrado!****");
                    getch();
                    system("cls");
                    cad_paciente();
                }
            }while(verificaCPF(p.cpf)==1);

            do{
                fflush(stdin);
                printf(" Nome do paciente:");
                scanf("%[^\n]s%*c",&p.nome);
                if(verificaChar(p.nome)==1){
                    printf("Caracteres especiais e números não permitidos!\n");
                }
            }while(verificaChar(p.nome)==1);

            do{
                fflush(stdin);
                printf(" Data nascimento formato dia/mes/ano:");
                scanf("%d/%d%/%d",&p.data_nasc.dia,&p.data_nasc.mes,&p.data_nasc.ano);
                if(validaData(p.data_nasc.dia,p.data_nasc.mes,p.data_nasc.ano)!=1)
                    printf("Data invalida!\n");
            }while(validaData(p.data_nasc.dia,p.data_nasc.mes,p.data_nasc.ano)!=1);




            do{
                fflush(stdin);
                printf(" Telefone do paciente: ");
                scanf("%s%*c",&p.telefone);
                if(verificaNum(p.telefone)==1){
                     printf("Digite numeros sem letras ou caracteres especiais.\n");
                }
            }while(verificaNum(p.telefone)==1);

            do{
                fflush(stdin);
                printf(" Email do paciente: ");
                scanf("%[^\n]s%*c",&p.email);
                if(validaEmail(p.email)==1){
                    printf("Email invalido\n");
                }
            }while(validaEmail(p.email)==1);


            do{
                fflush(stdin);
                printf(" Rua: ");
                scanf("%[^\n]s%*c",&p._endereco.rua);
                if(verificaChar(p._endereco.rua)==1)
                    printf("Digite apenas letras!\n");
            }while(verificaChar(p._endereco.rua)==1);

            do{
                fflush(stdin);
                printf(" Numero: ");
                scanf("%[^\n]s%*c",&p._endereco.numero);
                if(verificaNum(p._endereco.numero)==1)
                    printf("Digite apenas numeros!\n");
            }while(verificaNum(p._endereco.numero)==1);

            do{
                fflush(stdin);
                printf(" Bairro: ");
                scanf("%[^\n]s%*c",&p._endereco.bairro);
                if(verificaChar(p._endereco.bairro)==1)
                    printf("Digite apenas letras!\n");
            }while(verificaChar(p._endereco.bairro)==1);

            do{
               fflush(stdin);
                printf(" Cidade: ");
                scanf("%[^\n]s%*c",&p._endereco.cidade);
                if(verificaChar(p._endereco.cidade)==1)
                    printf("Digite apenas letras!\n");
            }while(verificaChar(p._endereco.cidade)==1);

            do{
                fflush(stdin);
                printf(" Estado: ");
                scanf("%[^\n]s%*c",&p._endereco.estado);
                if(verificaChar(p._endereco.estado)==1)
                    printf("Digite apenas letras!\n");
            }while(verificaChar(p._endereco.estado)==1);

            do{
                fflush(stdin);
                printf(" Cep: ");
                scanf("%s%*c",&p._endereco.cep);
                if(verificaNum(p._endereco.numero)==1)
                    printf("Digite apenas 8 digitos, sem letras ou caracteres!\n");
            }while(verificaNum(p._endereco.numero)==1);


                fflush(stdin);
                printf(" Possui comorbidades?(s/n)");
                if(getche() == 's' || getche()== 'S'){
                        do{
                            printf("\nDescreva comorbidades:");
                            fflush(stdin);
                            scanf("%[^\n]s%*c",&p.comorbidade);
                            if(verificaChar(p.comorbidade)==1){
                                printf("Digite apenas letras!\n");
                            }
                        }while(verificaChar(p.comorbidade)==1);
                }

            }while(getche() == 's' || getche()== 'S');

            fwrite(&p,sizeof(PACIENTE),1,file);

            printf("\n\nDados salvos com sucesso...\n");
            fclose(file);
///////////////////////salva no grupo de risco///////////////////////////////////////////////
            int idade = p.dt_diag.ano - p.data_nasc.ano;

            if(idade >= 65){

                FILE* file;
                file = fopen("pacientes_risco.txt", "a");
                if(!file){
                    printf("ERRO: file(pacientes_risco.");
                }else{
                    fprintf(file,"%i %s\n",idade, p._endereco.cep);
                }
                fclose(file);

            }

             printf(" Deseja cadastrar mais pacientes?(s/n)");
            if(getche() == 's' || getche()== 'S'){
                system("cls");
                cad_paciente();
            }else{

                system("cls");
                menuCadPaciente();
            }

        }
            system("cls");
            menuLogin();
}



//função para cadastrar usuarios do sistema **************************
void cad_usuario(){
    FILE* arquivo;
    USUARIO usr;
    arquivo = fopen("usuarios.txt", "a");


    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo.\n");
    }
    else{
        do{
            cabecalhoCad();
            do{

                fflush(stdin);
                printf(" Digite o nome: ");
                scanf("%[^\n]s%*c",&usr.us_nome);

                if(verificaCad(usr.us_nome)==0){
                    printf("****Usuario ja cadastrado!****");
                    getch();
                    system("cls");
                    cad_usuario();
                }

            }while(verificaCad(usr.us_nome)==0);


             do{
                fflush(stdin);
                printf(" Digite um e-mail: ");
                scanf("%[^\n]s%*c",&usr.us_email);

                 if(validaEmail(usr.us_email)==1){
                    printf("****ERRO: DIGITE UM EMAIL VALIDO!****\n");
                }
            }while(validaEmail(usr.us_email)==1);

            do{
                fflush(stdin);
                printf(" Crie uma senha de 5 digitos:");
                scanf("%s%*c",&usr.us_senha);
                if (verificaSenha(usr.us_senha)== 1) {
                    printf("**Erro, informe uma senha numerica de 5 digitos!**\n");
                }
            }while(verificaSenha(usr.us_senha)==1);


            fprintf(arquivo,"%s %s %s\n",usr.us_nome,usr.us_email,usr.us_senha);

            fclose(arquivo);
            printf(" Dados salvos com sucesso!\n\n");
            printf(" Deseja cadastrar mais usuarios?(s/n)");
            if(getche() == 's' || getche()== 'S'){
                system("cls");
                cad_usuario();
            }

        }while(getche() == 's' ||  getche() == 'S');

            getche();
            system("cls");
            menuLogin();
    }

}

//verifica se ano bisexto
int  anoBi(int ano){
    return (((ano % 4 == 0) &&
             (ano % 100 != 0)) ||
            (ano % 400 == 0));
}

//verifica data
int validaData(int dia, int mes, int ano){
       if (ano > MAX_YR ||
            ano < MIN_YR)
        return 0;
    if (mes < 1 ||mes > 12)
        return 0;
    if (dia < 1 || dia > 31)
        return 0;

    if (mes == 2)
    {
        if (anoBi(ano))
            return (dia <= 29);
        else
            return (dia <= 28);
    }
    if (mes == 4 || mes == 6 ||
            mes == 9 || mes == 11)
        return (dia <= 30);
    return 1;

}

//função para checar o email que o susuario digitar
int validaEmail(char e[]){

  int tam=strlen(e);
  int arroba = 0, ponto = 0, antesPonto = 0, depoisPonto = 0, i;

  for (i = 0; i < tam; i++) {
    char c = e[i];
    if(c == '@') {
      if (arroba)
        break;
      arroba = 1;
      if (i < 3)
        break;
    }
    else if (arroba) {
      if (ponto) {
        depoisPonto++;
      }
      else if(c == '.') {
        ponto = 1;
        if (antesPonto < 3) {
          break;
        }
      }
      else {
        antesPonto++;
      }
    }
  } // for

  if (i == tam && depoisPonto > 1)
    return 0;

  else
    return 1;

}

//verifica se o usuario digita letra
int verificaChar(char c[]){
     int i;
    for (i = 0; i < strlen(c); i++) {
        if (!isalpha(c[i])) {
           return 1;
        }else{
            return 0;
        }
    }
}

//verifica se o cpf contem 11 numeros, e não posssui letras
int verificaCPF(char cpf[]){
     int i;
    for (i = 0; i < strlen(cpf); i++) {
        if (!isdigit(cpf[i])|| strlen(cpf) < 11 || strlen(cpf)> 11) {
           return 1;
        }else{
            return 0;
        }
    }
}

//verifica se o cep contem 8 numeros e não possiui letras
int verificaCEP(char cep[]){
     int i;
    for (i = 0; i < strlen(cep); i++) {
        if (!isdigit(cep[i])|| strlen(cep) < 8 || strlen(cep)> 8) {
           return 1;
        }else{
            return 0;
        }
    }
}

//verifica se é nunmero
int verificaNum(char n[]){
     int i;
    for (i = 0; i < strlen(n); i++) {
        if (!isdigit(n[i])) {
           return 1;
        }else{
            return 0;
        }
    }
}

//função para não deixar o usuário digitar letras e senhas grandes
int verificaSenha(char senha[]){
     int i;
    for (i = 0; i < strlen(senha); i++) {
        if (!isdigit(senha[i])|| strlen(senha) <5 || strlen(senha)> 5) {
           return 1;
        }else{
            return 0;
        }
    }
}

//verifica se ja existe usuario ja cadastrado
int verificaCad(char nome[]){

    char linha[50];

    FILE *arquivo;
    //USUARIO usr;
    arquivo = fopen("usuarios.txt","r");
    if(!arquivo){
        printf("ERRO!");
    }else{
        while (fgets(linha,sizeof(linha),arquivo)!=NULL)
            if(strstr(linha,nome)!=NULL){
                fclose(arquivo);
                return 0;
            }
            return 1;

    }
}

//verifica se ja existe paciente ja cadastrado
int verificaPac(char cpf[]){

    PACIENTE p;
    FILE *arquivo;

    arquivo = fopen("pacientes.txt","r");
    if(!arquivo){
        printf("ERRO!");
    }else{
        while(fread(&p, sizeof(p),1, arquivo)==1)

            if(strstr(p.cpf,cpf)!=NULL){
                fclose(arquivo);
                return 0;
            }
            return 1;

    }
}

//logando no sistema
void logar(){

    USUARIO usr;


        cabecalhoLogin();
        do{
            printf("       \n\n");
            printf(" Informe seu email: ");
            scanf("%s",&usr.us_email);

            if(validaEmail(usr.us_email)==1){
             printf(" \n****ERRO: DIGITE UM EMAIL VALIDO!****");
            }
        }while(validaEmail(usr.us_email)==1);

        printf("       \n");
        do{
            printf(" Informe sua senha numerica: ");
            scanf("%s",&usr.us_senha);

                if(verificaSenha(usr.us_senha)==1){
                    printf("\n**Erro, informe uma senha numerica de 5 digitos!**\n");
                }
        }while(verificaSenha(usr.us_senha)==1);

      if(loginEmail(usr.us_email)== 0 && loginSenha(usr.us_senha)== 0){
            printf(" LOGADO COM SUCESSO...");
            system("cls");
            menuCadPaciente();

         }else{
            printf(" \n****ERRO: Informe um email e senha validos!****");
            getch();
            system("cls");
            logar();
         }
}

//função para validar o email no login
int loginEmail(char email[]){
    char u_email[50];
    FILE *log;

    log = fopen("usuarios.txt", "r");
    if(!log){
        printf("ERRO: log");
    }else{

        while(fgets(u_email,sizeof(u_email), log)!=NULL)

            if(strstr(u_email,email)!=NULL){

                return 0;
            }
                return 1;
            fclose(log);
         }
}

//função para validar a senha no login
int loginSenha(char senha[]){
    char u_senha[10];
    FILE *log;

    log = fopen("usuarios.txt", "r");
    if(!log){
        printf("ERRO: log");
    }else{

        while(fgets(u_senha,sizeof(u_senha), log)!=NULL)

            if(strstr(u_senha,senha)!=NULL){

                return 0;
            }
                return 1;
            fclose(log);
         }

}


//verifica se o arquivo txt está vazio
int verificaTxt(const char* txt){
    FILE *file = fopen(txt, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

//lista todos os pacientes
void listaPaciente(){

    FILE *file;
    file = fopen("pacientes.txt", "r");
    PACIENTE p = {0};


    if(verificaTxt("pacientes.txt")==0){
        printf("\n");
        printf("SEM PACIENTES CADASTRADOS!\n");
        getch();
        system("cls");
        menuCadPaciente();
    }
    if(!file){
        printf("ERRO: ler pacientes.txt");
    }else{
        cabecalhoListPac();

        printf("\n");

        while(fread(&p, sizeof(p),1, file)==1){
            printf("Data diagnostico: %d/%d/%d\n", p.dt_diag.dia, p.dt_diag.mes, p.dt_diag.ano);
            printf("CPF: %s\n",p.cpf);
            printf("Nome paciente: %s\n",p.nome);
            printf("Data Nasc:%d/%d/%d\n", p.data_nasc.dia, p.data_nasc.mes, p.data_nasc.ano);
            printf("Telefone: %s\n",p.telefone);
            printf("Email: %s\n",p.email);
            printf("Rua: %s\n",p._endereco.rua);
            printf("Bairro: %s\n",p._endereco.bairro);
            printf("Municipio: %s\n",p._endereco.cidade);
            printf("Estado: %s\n",p._endereco.estado);
            printf("CEP: %s\n",p._endereco.cep);
            if(p.comorbidade != NULL){
                printf("Comorbidade: %s\n",p.comorbidade);
            }else{
                printf("Comorbidade: %s\n"," ");
            }


            printf("\n_______________________________________________________\n");


        }

    }

    fclose(file);

    printf("Pressione qualquer tecla para voltar ao menu...");
        getch();
        system("cls");
        menuCadPaciente();


    getch();


}
