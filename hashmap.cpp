#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define tam 50

typedef struct
{
    char nome[30];
    char emprego[30];
    float renda;
} pessoa;

pessoa *tabela[tam];

void limpar_tabela()
{
    for (int i = 0; i < tam; i++)
    {
        tabela[i] = NULL;
    }
}


void exibir_tabela()
{
    for (int i = 0; i < tam; i++)
    {
        if (tabela[i] == NULL)
        {
            printf("\t%i\t _____\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, tabela[i]->nome);
        }
    }
}

int hash(char *nome, int k)
{
    int chave = nome[0];
    for (int i = 1; nome[i] != '\0'; i++)
    {
        chave += nome[i];
    }
    int h0 = chave % 47;
    int h1 = chave % 43;

    chave = (h0 + k * h1) % tam;

    return chave;
}

bool inserir_pessoa(pessoa *pes)
{
    if (pes == NULL)
        return false;

    for (int k = 0; k < tam; k++)
    {
        int index = hash(pes->nome, k);
        if (tabela[index] == NULL)
        {
            tabela[index] = pes;
            return true;
        }
        else
        {
            if (strcmp(tabela[index]->nome, pes->nome) == 0)
            {
                printf("Essa pessoa ja consta no sistema.");
                return false;
            }
        }
    }
    printf("deu erro ai");
    return false;
}

void cad_pessoa()
{
    pessoa *nova_pessoa = new pessoa;

    printf("Insira o nome da pessoa:\n");
    scanf("%s", nova_pessoa->nome);
    getchar();

    printf("Insira a ocupacao da pessoa:\n");
    scanf("%s", nova_pessoa->emprego);
    getchar();

    printf("Insira a renda da pessoa:\n");
    scanf("%f", &nova_pessoa->renda);

    if (inserir_pessoa(nova_pessoa) == true)
        printf("Inserido com sucesso");
}

void buscar_pessoa()
{
    char nome[30];
    printf("Insira o nome da pessoa que procura:\n");
    scanf("%s", nome);
    getchar();
    for (int k = 0; k < tam; k++)
    {
        int chave = hash(nome, k);
        if (tabela[chave] != NULL && strcmp(tabela[chave]->nome, nome) == 0)
        {
            printf("Nome: %s\nOcupacao: %s\nRenda mensal: %.2f", tabela[chave]->nome, tabela[chave]->emprego, tabela[chave]->renda);
            return;
        }
    }
    printf("Pessoa nao consta na tabela");
}

int tamanho(){
    int qnt_no_vetor = 0;
    for(int i=0; i<tam; i++){
        if(tabela[i] != NULL){
            qnt_no_vetor++;
        }
    }
    return qnt_no_vetor;
}

void sortear()
{
    if(tamanho()< 10){
        printf("nao ha elementos o suficiente para sorteio.\n");
        return;
    }
    int i = 0;
    pessoa* sorteados[10];

    for (int i = 0; i < tam; i++)
    {
        sorteados[i] = NULL;
    }

    while(i<10){
        int chave = rand() % tam;
        if (sorteados[chave] == NULL)
        {
            if(tabela[chave] != NULL){
            printf("|Nome: %s\nOcupacao: %s\nRenda mensal: %.2f\n\n", tabela[chave]->nome, tabela[chave]->emprego, tabela[chave]->renda);
            sorteados[chave] = tabela[chave];
            i++;
            }
        }
    }
}

void menu()
{
    printf("\n\n");
    printf("*******\t\tMinha casa minha vida\t********\n");
    printf("*\t1 - Cadastrar\t*\n");
    printf("*\t2 - Buscar\t*\n");
    printf("*\t3 - Sortear\t*\n");
    printf("*\t4 - Exibir\t*\n");
    printf("*\t0 - Sair\t\t*\n");
}

int main(void)
{
    srand(time(NULL));
    int loop = -1;
    limpar_tabela();
    while (loop != 0)
    {
        menu();
        scanf("%i", &loop);
        getchar();
        switch (loop)
        {
        case 1:
            cad_pessoa();
            break;
        case 2:
            buscar_pessoa();
            break;
        case 3:
            sortear();
            break;
        case 4:
            exibir_tabela();
            break;
        case 0:
            printf("Encerrando...");
            break;
        default:
            printf("Insira uma opcao valida.");
            break;
        }
    }
    return 0;
}
