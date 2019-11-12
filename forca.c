#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"
#include<time.h>


int geraAleatorio(int maximo)
{
    time_t t;
    int n=0;
    srand((unsigned) time(&t));
    n = (rand() % maximo)+1;
    return n;
}

NoSecreto * inicializaListaSecreta()
{
    return NULL;
}

noLetra * inicializaListaLetra()
{
       return NULL;
}

NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100])
{
    NoSecreto * novo;
    novo = (NoSecreto *) malloc(sizeof(NoSecreto));

    novo->status=0;
    strcpy(novo->assunto,subject);
    strcpy(novo->palavra,word);

    novo->ant = NULL;
    novo->prox = l;

    if (l != NULL)
    {
    l->ant = novo;
    }

    l=novo;

    return l;
}

void imprimeListaSecreta(NoSecreto *l)
{
    for(NoSecreto *p=l; p!=NULL; p=p->prox)
    {
        printf("%d) %-30s\t%s\n", p->status,p->palavra,p->assunto);
    }
}

NoSecreto * carregaListaArquivo(NoSecreto * l, char nomeArq[255])
{
    const char ch[2]=";";
    char * token;
    char palavra[31];
    char assunto[101];
    char * linha[1024];
    FILE * fWords;

    fWords = fopen(nomeArq,"r");
    if(fWords==NULL){
        printf("Falha ao acessar base de dados!\n");
        exit(0);
    }
    while(fgets(linha,1024,fWords))
    {
        token = strtok(linha,ch);
        if(token!=NULL)
        {
             strcpy(palavra,token);
        }
        token=strtok(NULL,ch);
        if(token!=NULL)
        {
            strcpy(assunto,token);
        }
        l = inserePalavraSecreta(l,palavra, assunto);
    }

    fclose(fWords);
    return l;
}

int tamanhoListaSecreta(NoSecreto *l)
{
    int n=0;
    for(NoSecreto *p=l;p!=NULL;p=p->prox,n++);
    return n;
}

int temPalavraNaoUsada(NoSecreto *l)
{
    NoSecreto *p;
    for(p=l;p!=NULL;p=p->prox){
        if(p->status==0) return 1;
    }
    return 0;
}

NoSecreto * sorteiaPalavra(NoSecreto *l,NoSecreto * lstRetira)
{

    int tam=0;
    int aleatorio=0;

    NoSecreto * p;

    while(temPalavraNaoUsada(l))
    {

         tam = tamanhoListaSecreta(l);
         aleatorio = geraAleatorio(tam);
         p = retornaPalavraPos(l,aleatorio);
         p->status = 1;
         return p;

    }
    return NULL;
}


NoSecreto * retiraLista(NoSecreto * l,NoSecreto * lstRetira,char palavra[31]) {

    NoSecreto * novo = (NoSecreto*) malloc(sizeof(NoSecreto));

    strcpy(novo->palavra,palavra);

    novo->prox = lstRetira;
    lstRetira = novo;

    NoSecreto * aux = (NoSecreto*)malloc(sizeof(NoSecreto));
    NoSecreto * ant = (NoSecreto*)malloc(sizeof(NoSecreto));

    for (aux = l; aux != NULL; aux = aux->prox)
    {

        if ((aux == l) && (palavra == l->palavra))
        {

            l = aux->prox;
            return l;

        } else if (palavra == aux->palavra)

        {

            ant->prox = aux->prox;
            free (aux);
            return l;
        }
        ant = aux;
    }
    return l;
}


NoSecreto * retornaPalavraPos(NoSecreto *l, int pos)
{
    int n=1;
    NoSecreto *p;
    for(p=l; p!=NULL; p=p->prox)
    {
        if(n==pos) break;
        n++;
    }
    return p;
}

int tamanhoPalavra(NoSecreto * palavra)
{
int n;
for(n=0; palavra->palavra[n]!='\0';n++ ){}
return n;


}

noLetra * insereLetra(noLetra * lstLetra ,char palavraSorteada[31],int tamanho)
{
noLetra * novo;
int k = 0;
int x=0;


    while(x<tamanho)
    {
     novo = (noLetra*) malloc(sizeof(noLetra));
     novo->status = 0;
     novo->prox = lstLetra;
     lstLetra = novo;
     x++;
    }
    noLetra * aux;
    aux = lstLetra;
    while(k!=tamanho)
    {
     aux->letra = palavraSorteada[k];
     aux = aux->prox;
     k++;
    }

return lstLetra;

}

noLetra * jogoDaForca(noLetra * lstLetra,int * tentativas,char alfabeto[27],int tamanho, char letrasJogo[12],char assunto[50])
{
int verificacao=0;
int verificacao2=1;
int verificacao3=0;
int z;
char letra;
int n=0;
noLetra * aux = lstLetra;
z=0;

fflush(stdin);

letra = getch();



if (letra != 13)
{
    for(n=0;alfabeto[n]!='\0';n++)
    {
        if(alfabeto[n]==letra)
        {
            verificacao2 = 0;
            printf("\nEsta letra já foi utilizada!\n\n");

            letra  = "";
            fflush(stdin);

            *tentativas = *tentativas + 1;
            system("pause");

            break;
            n=0;
        }
    }

    if(verificacao2!=0)
    {
        alfabeto[strlen(alfabeto)] = letra;
    }

if(letra!=NULL)
 {
    for(aux=lstLetra; aux!=NULL; aux = aux->prox)
    {
        if(letra==aux->letra)
        {
            verificacao=1;
            aux->status=1;

            system("cls");
            letrasJogo[z]=letra;
            printf("%s\n\n",assunto);

            if(verificacao3!=1)
            *tentativas = *tentativas - 1;
             verificacao3=1;

            for(int k=0; k<tamanho;k++)
            {
             printf("%c ",letrasJogo[k]);
            }
            printf("\n\nTentativas restantes: %d",*tentativas);
        }
        z++;
    }
}

    if(verificacao!=1 && letra!=NULL)
    {
        system("cls");
        *tentativas = *tentativas - 1;
        printf("%s\n\n",assunto);
        for(int k=0; k<tamanho;k++)
        {
        printf("%c ",letrasJogo[k]);
        }
        printf("\n\nTentativas restantes: %d", *tentativas);
    }
    printf("\n\nPalavras Usadas:\n\n");

    n=0;
    while(alfabeto[n]!='\0')
    {
    printf("%c \n",alfabeto[n]);
    n++;
    }

}
return lstLetra;
}
char aoba(int tamanho)
{
char palavra[1];
int z=0;
palavra[z]=' ';
return palavra[0];
}

int verificaStatusLetra(noLetra * lstLetra)
{
noLetra * aux;
    for(aux=lstLetra;aux!=NULL;aux=aux->prox){
        if(aux->status==0) return 1;
    }
    return 0;
}
