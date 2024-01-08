#include <stdio.h>
#include <stdlib.h>
#define TAM_PIL 100
#define TAM_TAB 100

enum 
{
    INT,
    LOG,
    REG
};

typedef struct listaCampos{
	char nome[100];
	int tip;
	int posicao;
	int deslocamento;
	int tamanho;
    struct listaCampos *prox;
}listaCampos;

struct elemTabSimbolos {
    char id[100]; 
    int end;   
    int tip;
    int tam;	
    int posicao; 
    listaCampos* listaDeCampos;	
} tabSimb[TAM_TAB], elemTab;

int posTab = 0; 

char nomeTipo[3][4]={"INT","LOG","REG"};


//incializa lista de campos (de um elemento da tabela)
listaCampos *inicializaListaCampos() { return NULL; }

//atualiza lista de campos
listaCampos *adicionaCampo(listaCampos *lista, char *nome, int tip, int pos, int des, int tam) {
    listaCampos *novoCampo = (listaCampos *)malloc(sizeof(listaCampos));
    strcpy(novoCampo->nome, nome);
    novoCampo->tip = tip;
    novoCampo->posicao = pos;
    novoCampo->deslocamento = des;
    novoCampo->tamanho = tam;
    novoCampo->prox = lista;
    return novoCampo;
}

//busca atomo na lista de campos de um elemento do tipo registro da tabela
listaCampos *buscaCampo(listaCampos *lista, char *nome) {
    while (lista && strcmp(lista->nome, nome) != 0) {
        lista = lista->prox;
    }
    return lista;
}

//busca campo nas listas de campos dos registros na tabela de símbolos
listaCampos *buscaCampoTabela(char *nome) {
    listaCampos *result;
    
    for (int i = 0; tabSimb[i].end; i++) {
        result = tabSimb[i].listaDeCampos;

        while(result) {
            listaCampos *campo = buscaCampo(result, nome);
            if (campo) { return campo; }
            result = result->prox;
        }
    }
    return NULL;
}

//busca símbolo na tabela de elementos
int buscaSimbolo (char *s) {
    int i;
    for(i = posTab - 1; strcmp(tabSimb[i].id, s) && i >= 0; i--);
    return i; 
}

//insere símbolo na tabela de elementos
void insereSimbolo (struct elemTabSimbolos elem) {
    int i;
    if(posTab == TAM_TAB)
        yyerror ("Tabela de Simbolos cheia!");
    for(i = posTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--)
        ;
    if(i != -1){
        char msg[200];
        sprintf(msg, "Identificador [%s] duplicado", elem.id);
        yyerror (msg);
    }
    tabSimb[posTab++] = elem;
}

//imprime campos da lista de um elemento com posisão i na tabela de elementoss
void mostraTabelaCampos(int i) {
    listaCampos *campoAtual = tabSimb[i].listaDeCampos;

    listaCampos *camposTemp[TAM_TAB];
    int numCampos = 0;

    while (campoAtual) {
        camposTemp[numCampos++] = campoAtual;
        campoAtual = campoAtual->prox;
    }

    for (int j = numCampos - 1; j >= 0; j--) {
        listaCampos *campoAtual = camposTemp[j];
        printf(" (%s,%s,%d,%d,%d)", campoAtual->nome, nomeTipo[campoAtual->tip],
               campoAtual->posicao, campoAtual->deslocamento, campoAtual->tamanho);
        if (j > 0) {
            printf(" =>");
        }
    }
}


//imprime tabela de símbolos
void mostraTabela() {
    puts("-----------------------TABELA DE SIMBOLOS------------------------");
    printf("%20s | %4s | %4s | %4s | %4s | %4s \n", "ID", "END", "TIP", "TAM", "POS", "CAMPOS");
    puts("-----------------------------------------------------------------");
    
    for (int i = 0; i < posTab; i++) {
        printf("%20s | %4d | %4s | %4d | %4d |", tabSimb[i].id, tabSimb[i].end,
               nomeTipo[tabSimb[i].tip], tabSimb[i].tam, tabSimb[i].posicao);

        mostraTabelaCampos(i);
        printf("\n");
    }
    puts("-----------------------------------------------------------------");
}

//retorna o tamanho da lista de campos de um elemento da tabela
int tamanhoListaCampos(listaCampos *lista) {
    int tam = 0;
    while(lista) {
        tam += lista->tamanho;
        lista = lista->prox;
    }
    return tam;
}


// Pilha Semantica
int pilha[TAM_PIL];
int topo = -1;

void empilha (int valor) {
    if(topo == TAM_PIL)
        yyerror("Pilha semantica cheia!");
    pilha[++topo] = valor;
}

int desempilha (void) {
    if(topo == -1)
        yyerror("Pilha semantica vazia!");
    return pilha[topo--];
}

// tipo1 e tipo2 são os tipos esperados na expressão
// ret é o tipo que será empilhado com resultado da expressão
void testaTipo (int tipo1, int tipo2, int ret) {
    int t1 = desempilha();
    int t2 = desempilha();
    if (t1 != tipo1 || t2 != tipo2) 
        yyerror("Incompatibilidade de tipo!");
    empilha(ret);
}