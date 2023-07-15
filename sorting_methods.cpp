#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura de ticket(ingresso);
typedef struct ticket
{
    char cpf[20];
    char name[30];
    int days;
    int data;
    struct ticket *prox = NULL;
} tic;

// Definição da estrutura de lista;
typedef struct lista
{
    tic *start = NULL;
    tic *end = NULL;
    int tam = 0;
} list;

// Cria um novo ticket e insere ele ao final da lista, impedindo duplicidades;
void new_ticket(tic **head, tic **end)
{
    tic *novo = new tic;
    printf("Informe o nome:\n");
    scanf("%s", novo->name);
    getchar();
    printf("Informe o cpf:\n");
    scanf("%s", novo->cpf);
    getchar();
    printf("Informe o dia, mes, e ano, sem barras e espaco, apenas numeros (Caso o primeiro digito seja um 0, NAO INCLUA):\n");
    scanf("%i", &novo->data);
    getchar();

    novo->days = (novo->data / 1000000) + ((novo->data / 10000) % 100) * 30 + (novo->data % 10000) * 365;

    tic *aux1 = *head;
    while (aux1 != NULL)
    {
        if (strcmp(aux1->cpf, novo->cpf) == 0 && strcmp(aux1->name, novo->name) != 0)
        {
            printf("Este cpf ja pertence a outro comprador!");
            return;
        }
        if (strcmp(aux1->cpf, novo->cpf) == 0 && aux1->data == novo->data)
        {
            printf("Este cpf ja possui um ingresso nessa data!");
            return;
        }
        aux1 = aux1->prox;
    }

    if (*head == NULL)
    {
        *head = novo;
        *end = novo;
        return;
    }
    tic *aux = *head;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = novo;
    *end = novo;
}

// Imprime os ingressos da lista;
void show_tickets(tic *start)
{
    tic *aux = start;
    while (aux != NULL)
    {
        printf("nome: %s \n", aux->name);
        printf("cpf:%s \n", aux->cpf);
        printf("%02d/%02d/%04d", aux->data / 1000000, (aux->data / 10000) % 100, aux->data % 10000);
        printf("\n\n");
        aux = aux->prox;
    }
}

// Recebe uma lista, um nó referência e retorna o anterior deste nó, caso exista;
tic *prev(list *lst, tic *referencia)
{
    if ((referencia == NULL) || (referencia == lst->start) || (lst == NULL))
        return NULL;
    tic *aux = lst->start;
    while (aux != NULL)
    {
        if (aux->prox == referencia)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}
// Realiza as atualizações de ponteiros do loop interno do insertion sort
void troca_insertion(list *lst, tic *aux, tic *troca, tic *proximo, tic *anterior)
{
    if (troca == lst->end)
    {
        lst->end = prev(lst, troca);
    }
    if (aux == lst->start)
    {
        troca->prox = lst->start;
        lst->start = troca;
        anterior->prox = proximo;
    }
    else
    {
        troca->prox = aux;
        anterior->prox = proximo;
        anterior = prev(lst, aux);
        if (anterior != NULL)
        {
            anterior->prox = troca;
        }
    }
}

// Organiza a lista em ordem alfabética com o insertion sort e pesquisa os ingressos com o cpf informado;
void sort_and_search(list *lista)
{
    if (lista->tam == 0)
    {
        printf("A lista esta vazia");
        return;
    }

    tic *aux_cpf = lista->start;
    char busca[20];
    printf("Informe o cpf que deseja buscar:\n");
    scanf("%s", busca);
    getchar();
    bool achou = false;

    if (lista->tam == 1)
    {
        if (strcmp(aux_cpf->cpf, busca) == 0)
        {
            printf("nome: %s \n", aux_cpf->name);
            printf("cpf:%s \n", aux_cpf->cpf);
            printf("%02d/%02d/%04d", aux_cpf->data / 1000000, (aux_cpf->data / 10000) % 100, aux_cpf->data % 10000);
            printf("\n\n");
            return;
        }
        else
        {
            printf("O cpf nao foi encontrado.");
            return;
        }
    }

    if (lista->tam == 2)
    {

        while (aux_cpf != NULL)
        {
            if (strcmp(aux_cpf->cpf, busca) == 0)
            {
                achou = true;
                printf("nome: %s \n", aux_cpf->name);
                printf("cpf:%s \n", aux_cpf->cpf);
                printf("%02d/%02d/%04d", aux_cpf->data / 1000000, (aux_cpf->data / 10000) % 100, aux_cpf->data % 10000);
                printf("\n\n");
            }
            aux_cpf = aux_cpf->prox;
        }
        if (achou == false)
        {
            printf("O cpf requisitado nao foi encontrado na lista.");
        }

        tic *aux_swap = lista->start->prox;
        if (strcmp(aux_swap->name, lista->start->name) < 0)
        {
            lista->start->prox = aux_swap->prox;
            aux_swap->prox = lista->start;
            lista->start = aux_swap;
            return;
        }
        else
        {
            return;
        }
    }

    tic *troca = lista->start->prox;
    tic *anterior = prev(lista, troca);
    tic *aux = lista->start;
    tic *proximo = troca->prox;

    while (troca != NULL)
    {
        while (aux != troca)
        {
            if (strcmp(aux->name, troca->name) > 0)
            {
                troca_insertion(lista, aux, troca, proximo, anterior);
                break;
            }
            aux = aux->prox;
        }
        troca = proximo;
        aux = lista->start;
        anterior = prev(lista, troca);
        if (troca != NULL)
        {
            proximo = troca->prox;
        }
    }

    aux_cpf = lista->start;
    while (aux_cpf != NULL)
    {
        if (strcmp(aux_cpf->cpf, busca) == 0)
        {
            printf("nome: %s \n", aux_cpf->name);
            printf("cpf:%s \n", aux_cpf->cpf);
            printf("%02d/%02d/%04d", aux_cpf->data / 1000000, (aux_cpf->data / 10000) % 100, aux_cpf->data % 10000);
            printf("\n\n");
            achou = true;
        }
        aux_cpf = aux_cpf->prox;
    }
    if (achou == false)
    {
        printf("Nao foram achados ingressos com esse cpf!");
    }
}

void remover(list *lst, tic *elemento)
{
    if ((lst == NULL) || (elemento == NULL) || (lst->tam == 0))
    {
        return;
    }

    if ((lst->start == elemento) && (lst->end == elemento))
    {
        lst->tam = 0;
        lst->start = NULL;
        lst->end = NULL;
        return;
    }

    lst->tam--;

    if (lst->start == elemento)
    {
        lst->start = lst->start->prox;
        elemento->prox = NULL;
        return;
    }

    if (lst->end == elemento)
    {
        lst->end = prev(lst, lst->end);
        lst->end->prox = NULL;
        return;
    }

    tic *antElem = prev(lst, elemento);
    tic *proxElem = elemento->prox;
    if (antElem != NULL)
    {
        antElem->prox = proxElem;
    }
    elemento->prox = NULL;
}

void inserir_inicio(list *lst, tic *Novo)
{
    if ((lst == NULL) || (Novo == NULL))
        return;
    if (lst->tam == 0)
    {
        lst->start = Novo;
        lst->end = Novo;
        lst->tam = 1;
        Novo->prox = NULL;
        return;
    }
    Novo->prox = lst->start;
    lst->start = Novo;
    lst->tam++;
}

void anexar_inicio(list *lst, list *nova)
{
    if ((nova == NULL) || (nova->tam == 0) || (lst == NULL))
    {
        return;
    }
    lst->tam += nova->tam;
    nova->end->prox = lst->start;
    lst->start = nova->start;
}

void anexar_fim(list *lst, list *nova)
{
    if ((lst == NULL) || (nova == NULL) || (nova->tam == 0))
    {
        return;
    }
    lst->tam += nova->tam;
    lst->end->prox = nova->start;
    lst->end = nova->end;
}
// Ordena a lista de acordo com a quantidade de dias, colocando do menor para o maior;
void quick_sort(list *lst)
{
    if (lst->tam == 0)
    {
        return;
    }

    if (lst->tam == 1)
    {
        return;
    }

    int metade = lst->tam / 2;
    tic *pivo = lst->start;
    for (int i = 0; i < metade; i++)
    {
        pivo = pivo->prox;
    }

    lista menores;
    lista maiores;

    tic *aux = lst->start;
    tic *elemento = NULL;

    while (aux != NULL)
    {
        elemento = aux;
        aux = aux->prox;
        if (elemento == pivo)
        {
            continue;
        }
        remover(lst, elemento);
        if (pivo->days > elemento->days)
        {
            inserir_inicio(&menores, elemento);
        }
        else
        {
            inserir_inicio(&maiores, elemento);
        }
    }
    quick_sort(&menores);
    anexar_inicio(lst, &menores);
    quick_sort(&maiores);
    anexar_fim(lst, &maiores);
}
// Faz a contagem das ocorrências em cada data;
void tickets_per_date(list *lst)
{

    if (lst->tam == 0)
    {
        printf("a lista esta vazia!");
        return;
    }
    if (lst->tam == 1)
    {
        printf("ha somente um ingresso, na data:%02d/%02d/%04d", lst->start->data / 1000000, (lst->start->data / 10000) % 100, lst->start->data % 10000);
        return;
    }
    if (lst->tam == 2)
    {
        tic *aux_isolated = lst->start;
        int atual = aux_isolated->data;
        int seguinte = aux_isolated->prox->data;
        if (atual != seguinte)
        {
            printf("Ha um ingresso em:%02d/%02d/%04d\n\n", atual / 1000000, (atual / 10000) % 100, atual % 10000);
            printf("E outro em:%02d/%02d/%04d\n\n", seguinte / 1000000, (seguinte / 10000) % 100, seguinte % 10000);
            return;
        }
        if (atual == seguinte)
        {
            printf("Os dois ingressos sao de:%02d/%02d/%04d\n\n", atual / 1000000, (atual / 10000) % 100, atual % 10000);
            return;
        }
    }
    else
    {
        tic *aux = lst->start;
        int cont = 0;
        int atual = aux->data;
        while (aux != NULL)
        {
            if (aux->data == atual)
            {
                cont++;
            }
            if (aux->data != atual || aux->prox == NULL)
            {
                printf("%i ingressos foram vendidos em: %02d/%02d/%04d\n\n", cont, atual / 1000000, (atual / 10000) % 100, atual % 10000);
                cont = 1;
                atual = aux->data;
            }
            if (aux->prox == NULL && aux->data == atual)
            {
                printf("%i ingressos foram vendidos em: %02d/%02d/%04d\n\n", cont, atual / 1000000, (atual / 10000) % 100, atual % 10000);
            }
            aux = aux->prox;
        }
    }
}

void menu()
{
    printf("\n\n");
    printf("*******\t\tEven33\t********\n");
    printf("*\t1 - Registrar compra\t*\n");
    printf("*\t2 - Exibir registros\t*\n");
    printf("*\t3 - Buscar compras por cpf\t*\n");
    printf("*\t4 - Encerrar processo de vendas\t*\n");
    printf("*\t0 - Sair\t\t*\n");
}

int main(void)
{
    srand(time(NULL));
    list *registros = new list;
    int loop = -1;
    while (loop != 0)
    {
        menu();
        scanf("%i", &loop);
        getchar();
        switch (loop)
        {
        case 1:
            new_ticket(&registros->start, &registros->end);
            registros->tam++;
            break;
        case 2:
            show_tickets(registros->start);
            break;
        case 3:
            sort_and_search(registros);
            break;
        case 4:
            quick_sort(registros);
            tickets_per_date(registros);
            registros->start = NULL;
            registros->tam = 0;
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
