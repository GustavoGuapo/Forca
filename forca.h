#ifndef FORCA_H_INCLUDED
#define FORCA_H_INCLUDED

#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif

struct noSecreto{
    int status;
    char palavra[31];
    char assunto[101];
    struct noSecreto * prox;
    struct noSecreto * ant;

};

struct noLetra
{
    char letra;
    int status;
    struct noLetra * prox;
    struct noLetra * ant;
};

typedef struct noSecreto NoSecreto;
typedef struct noSorteada NoSorteada;
typedef struct noLetra noLetra;

int geraAleatorio(int maximo);
NoSecreto * inicializaListaSecreta();
noLetra * inicializaListaLetra();
NoSecreto * carregaListaArquivo(NoSecreto *l, char nomeArq[255]);
void imprimeListaSecreta(NoSecreto *l);
NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100]);
NoSecreto * sorteiaPalavra(NoSecreto *l,NoSecreto * lstRetira);
int temPalavraNaoUsada(NoSecreto *l);
int tamanhoPalavra(NoSecreto * palavra);

int tamanhoListaSecreta(NoSecreto *l);

NoSecreto * retornaPalavraPos(NoSecreto *l, int pos);
NoSecreto * retiraLista(NoSecreto *l, NoSecreto *p,char palavra[31]);
noLetra * insereLetra(noLetra * lstLetra,char palavraSorteada[31],int tamanho);
noLetra * jogoDaForca(noLetra * lstLetra,int * tentativas,char alfabeto[27],int tamanho,char letrasJogo[12],char assunto[50]);
char aoba(int tamanho);
int verificaStatusLetra(noLetra * lstLetra);


#endif // FORCA_H_INCLUDEDss
