#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG_MAX 100

//INSTRUÇÕES DE USO:
//Use ./(nome do arquivo) (registro) (nome da ferramenta) (quantidade) (custo) para atualizar a lista
//Use ./(nome do arquivo) para visualizar a lista de ferramentas

typedef struct ferramenta {
    unsigned int reg;
    char *nome;
    unsigned int qtd;
    float custo;
} Ferramenta;

//Cria um arquivo caso inexistente
//Zera os valores presentes
void update_nomes();

//Recebe o nome, o nº do registro, a quantidade e o custo de uma ferramenta
//Salva os dados em um arquivo
void salvar_nomes(char *, unsigned int, unsigned int, float);

//Recebe um vetor de ferramentas
//Obtem dados de um arquivo e coloca no vetor
void ler_nomes(Ferramenta *);

int main(int argc, char *argv[])
{
    if (argc > 5) {
        printf("Síntaxe para uso: \n %s [num registro] [nome da ferramenta] [quantidade] [preço]\n", *argv);
        printf("Caso queira apenas visualizar, use: %s\n", *argv);
        exit(1);
    }

    FILE *fp;

    //fp = fopen("hardware.dat", "r+b");
    //if (!fp) {
        //puts("Não foi possível abrir o arquivo");
        //exit(2);
    //}
    //rewind(fp);

    Ferramenta *v = NULL;
    v = malloc(REG_MAX*sizeof(Ferramenta));

    if (!v) {
        puts("Não há memória disponível");
        exit(3);
    }

    //fclose(fp);
    //ler_nomes(v);

    for (unsigned int j = 0; j < REG_MAX; j++) { //Enumerar os registros
        (v + j)->reg = j;
        (v + j)->nome = malloc(20*sizeof(char));

        if (!(v + j)->nome) {
            puts("Não há memória disponível");
        }
        if ((v + j)->qtd == 0) {
            //strcpy((v + j)->nome, "LIVRE");
            strcpy((v + j)->nome, "LIVRE");
            (v + j)->custo = 0.00;
        } 
        //salvar_nomes((v + j)->nome, (v + j)->reg, (v + j)->qtd, (v + j)->custo);
        //strcpy((v + j)->nome, *(auxiliar + j));
    }
    //ler_nomes(v);
    
    //Atualizar os dados
    if (argc == 5) {
        /*fp = fopen("hardware.dat", "wb");
        if (!fp) {
            puts("Não foi possível abrir o arquivo");
            exit(2);
        }
        rewind(fp);*/

        unsigned int n = abs(atoi(*(argv + 1)));
        //(v + n)->nome = malloc(strlen(*(argv + 2)) + 1);
        strcpy((v + n)->nome, *(argv + 2));
        (v + n)->qtd = abs(atoi(*(argv + 3)));
        (v + n)->custo = atof(*(argv + 4));
        //(v + n)->nome = strcat((v + n)->nome, "\0");
        //fseek(fp, n*sizeof(Ferramenta), SEEK_SET);
        //fwrite((v + n), sizeof(Ferramenta), 1, fp);
        //update_nomes();
        salvar_nomes(*(argv + 2), n, (v + n)->qtd, (v + n)->custo); //Adicionar a nova informação à lista

        //fwrite(v, sizeof(Ferramenta), REG_MAX, fp); //Escrever no arquivo
        //fclose(fp);
    }
    //fclose(fp);

    ler_nomes(v); //Obter dados de ferramentas existentes no arquivo
    update_nomes(); //Isso evita registros duplicados

    puts("# reg - nome - qtd - custo"); //Imprimir a lista
    for (unsigned int i = 0; i < REG_MAX; i++) {
        if ((v+i)->nome == NULL) {
            puts("Nome da ferramenta não encontrado");
            continue;
        }
        if ((v + i)->qtd == 0) { //Remove ferramentas que não estão mais no estoque
            (v + i)->custo = 0;
            strcpy((v + i)->nome, "LIVRE");
        }
        printf("# %u - %s - %u - %.2f\n", (v+i)->reg, (v+i)->nome, (v+i)->qtd, (v+i)->custo);
        salvar_nomes((v + i)->nome, (v + i)->reg, (v + i)->qtd, (v + i)->custo); //Atualizar toda a lista
    }

    free(v);

    return 0;
}

void update_nomes()
{
    FILE *fp;

    fp = fopen("hardware.dat", "w+");
    if (!fp) {
        puts("Erro ao abrir o arquivo de nomes de ferramentas");
        exit(1);
    }
    fclose(fp);
}

void salvar_nomes(char *name, unsigned int n, unsigned int qtd, float custo)
{
    FILE *fp;

    fp = fopen("hardware.dat", "a+");
    if (!fp) {
        puts("Erro ao abrir o arquivo de dados das ferramentas");
        exit(1);
    }
    //printf("%u %s\n", n, name);

    fprintf(fp, "%u %s %u %.2f\n", n, name, qtd, custo);
    fclose(fp);
}

void ler_nomes(Ferramenta *v)
{
    FILE *fp;

    fp = fopen("hardware.dat", "r");
    if (!fp) {
        puts("Erro ao abrir o arquivo de dados das ferramentas");
        puts("Caso seja o primeiro uso, tente inserir uma ferramenta nova para incializar a lista");
        exit(1);
    }

    //Registro
    unsigned int n;

    //Nome
    char *name = malloc(20*sizeof(char));

    if (!name) {
        puts("Não há memória disponível");
        exit(1);
    }

    //Quantidade
    unsigned int qtd;

    //Custo
    float custo;

    //Auxiliar
    char ch;

    rewind(fp);

    /*if (!(ch = getc(fp))) {
        puts("Arquivo inexistente (tente inserir uma ferramenta na lista)");
        exit(2);
    }*/

    while (!feof(fp)) {
        //Obter registro
        fscanf(fp, "%u", &n);
        fseek(fp, 1, SEEK_CUR);

        //Obter nome
        //fgets(name, 20, fp);
        fscanf(fp, "%s", name);
        //printf("%s\n", name);
        //fseek(fp, strlen(name), SEEK_CUR);

        //Obter quantidade
        fscanf(fp, "%u", &qtd);
        //printf("%u\n", qtd);
        fseek(fp, 1, SEEK_CUR);

        //Obter custo
        fscanf(fp, "%f", &custo);
        //printf("%.2f\n", custo);

        //Enviar dados
        (v + n)->reg = n;
        strcpy((v + n)->nome, name);
        //strtok((v + n)->nome, "\n");
        (v + n)->qtd = qtd;
        (v + n)->custo = custo;

        /*if (!(ch = getc(fp))) {
            break;
        } else {
            printf("%c\n", ch);
        }*/

        //Próxima linha
        //while((ch = getc(fp)) != '\n');
    }

    fclose(fp);
}