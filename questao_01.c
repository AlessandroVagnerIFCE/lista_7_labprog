#include <stdio.h>
#include <stdlib.h>

typedef struct user {
    char *nome;
    unsigned char idade;
    char *ocupacao;
} Usuario;

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Síntaxe para uso: \n %s [nome de usuário] [idade] [ocupação]\n", *argv);
        exit(1);
    }

    FILE *fp;

    fp = fopen("dados_usuarios.csv", "a+");
    if (!fp) {
        puts("Não foi possível abrir o arquivo");
        exit(2);
    }

    //Ir para o início do arquivo
    //Detectar se o arquivo foi criado recentemente e adicionar a legenda
    rewind(fp);
    if (getc(fp) != 'N') {
        fprintf(fp, "Nome, Idade, Ocupação\n");
    }
    fseek(fp, 0, SEEK_END); //Voltar para o final do arquivo

    //Obter dados
    Usuario x;
    x.nome = *(argv + 1);
    x.idade = abs(atoi(*(argv + 2)));
    x.ocupacao = *(argv + 3);

    fprintf(fp, "%s, %hhu, %s\n", x.nome, x.idade, x.ocupacao); //Escrever no arquivo

    fclose(fp);

    return 0;
}