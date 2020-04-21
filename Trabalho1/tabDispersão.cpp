/***************************************************************************
*
*   Calel Becassi Benis
*   Trabalho 1
*   Professor: Diego Padilha Rubert
*
*/

#include <cstdio>
#include <cctype>
#include <cstring>

#define MIN 3
#define MAX 20


/* Célula de uma lista encadeada de ocorrências, armazena um inteiro */
class Ocorrencia {
  friend class ListaO;

public:
  Ocorrencia(int linha); // Construtor padrão
  ~Ocorrencia();         // Destrutor padrão

private:
  int linha;
  Ocorrencia *prox;
};


/* Lista encadeada de ocorrências, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaO {
public:
  ListaO();               // Construtor padrão
  ~ListaO();              // Destrutor padrão
  void insere(int linha); // Recebe um inteiro e insere na lista
  void escreve();         // Escreve os elementos da lista

private:
  Ocorrencia *inicio; // Início da lista
  Ocorrencia *fim;    // Fim da lista
};


/* Célula de uma lista encadeada de palavras, armazena uma cadeia de caracteres */
class Palavra {
  friend class ListaP;

public:
  Palavra(char p[]);      // Construtor padrão
  ~Palavra();             // Destrutor padrão
  void insere(int linha); // Insere uma ocorrência na lista de ocorrências
  void escreve();         // Escreve a palavra e suas ocorrências

private:
  char p[MAX];        // A palavra em si
  ListaO ocorrencias; // Lista de ocorrências
  Palavra *prox;      // Próxima Palavra na lista
};


/* Lista encadeada de palavras, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaP {
public:
  ListaP();                  // Construtor padrão
  ~ListaP();                 // Destrutor padrão
  Palavra *insere(char p[]); // Recebe uma palavra e insere na lista, devolvendo um ponteiro para o objeto inserido
  Palavra *busca(char p[]);  // Busca e devolve o objeto de uma palavra na lista
  void escreve();            // Escreve os elementos da lista

private:
  Palavra *inicio; // Início da lista
  Palavra *fim;    // Fim da lista
};


/* Tabela de dispersão que guarda um índice de palavras */
class TabelaDispersao {
public:
  TabelaDispersao();  // Construtor padrão
  ~TabelaDispersao(); // Destrutor padrão
  void escreve();     // Escreve a tabela (incluindo fator de carga)
  void novaOcorrencia(char p[], int linha); // Registra uma nova ocorrência de uma palavra
  void separaPalavras(char linhaTXT[], int contadorLinhas); // Recebe a linha e devolve a palavra em objeto
  float fatorDeCarga;

private:
  static const int TAMANHO = 47; // Tamanho da tabela
  ListaP tabela[TAMANHO];        // Listas da tabela

  int valor(char p[]); // Valor da palavra p
  int h(char p[]);     // Função de hash
};

int main(int argc, char *argv[]){
  int contadorLinhas = 1;
  char linhaTXT[999999];

  TabelaDispersao *tab = new TabelaDispersao();

  FILE *texto = fopen(argv[1], "r");
  if(texto == NULL)
    printf("***Erro ao abrir o arquivo.txt***\n");

  while(fgets(linhaTXT, sizeof(linhaTXT), texto) != NULL){ //Passando linha por linha do texto.
    tab->separaPalavras(linhaTXT, contadorLinhas);
    contadorLinhas++;
  }

  tab->escreve();

  fclose(texto);
  return 0;
}

Ocorrencia::Ocorrencia(int linha){
  this->linha = linha;
}

ListaO::ListaO(){
  this->inicio = NULL;
  this->fim = NULL;
}

void ListaO::insere(int linha){
  Ocorrencia *olhando;
  
  olhando = this->inicio;
  while((olhando != NULL) && (olhando->linha != linha)){
    olhando = olhando->prox;
  }

  if(olhando == NULL){
    Ocorrencia *novaO = new Ocorrencia(linha);
    if(this->inicio == NULL){
      this->inicio = novaO;
      this->fim = novaO;
      novaO->prox = NULL;
    }
  
    else{
      this->fim->prox = novaO;
      this->fim = novaO;
      novaO->prox = NULL;
    }
  }
}

void ListaO::escreve(){
  Ocorrencia *olhando;

  olhando = this->inicio;
  printf("(");
  while(olhando != this->fim){
    printf("%d,", olhando->linha);
    olhando = olhando->prox;
  }
  printf("%d)", this->fim->linha);
}

Palavra::Palavra(char p[]){
  strcpy(this->p, p);
  this->prox = NULL;
}

void Palavra::insere(int linha){
  ocorrencias.insere(linha);
}

void Palavra::escreve(){
  printf("%s", this->p);
  ocorrencias.escreve();
}

ListaP::ListaP(){
  this->inicio = NULL;
  this->fim = NULL;
}
ListaP::~ListaP(){}

Palavra *ListaP::insere(char p[]){
  Palavra *novaP = new Palavra(p);

  if(this->inicio == NULL){
    this->inicio = novaP;
    this->fim = novaP;
    novaP->prox = NULL;
  }

  else{
    this->fim->prox = novaP;
    this->fim = novaP;
    novaP->prox = NULL;
  }
  return novaP;
}

Palavra *ListaP::busca(char p[]){
  Palavra *olhando;

  olhando = this->inicio;
  while((olhando != NULL) && (strcmp(p, olhando->p) != 0)){
    olhando = olhando->prox;
  }

  if(olhando != NULL)
    return olhando;
  else
    return NULL;
}

void ListaP::escreve(){
  Palavra *olhando;

  olhando = this->inicio;
  while(olhando != NULL){
    printf(" ");
    olhando->escreve();
    olhando = olhando->prox;
  }
}

TabelaDispersao::TabelaDispersao(){
  fatorDeCarga = 0;
}
TabelaDispersao::~TabelaDispersao(){}

void TabelaDispersao::escreve(){
  for(int i = 0; i < TAMANHO; i++){
    printf("%d:", i);
    tabela[i].escreve();
    printf("\n");
  }
  fatorDeCarga = fatorDeCarga / 47;
  printf("Fator de carga: %g", fatorDeCarga);
}

void TabelaDispersao::novaOcorrencia(char p[], int linha){
  if((tabela[h(p)].busca(p) == NULL) && (strlen(p) >= MIN)){
    tabela[h(p)].insere(p)->insere(linha);
    fatorDeCarga++;
  }

  else if(strlen(p) >= MIN){
    tabela[h(p)].busca(p)->insere(linha);
  }
}

void TabelaDispersao::separaPalavras(char linhaTXT[], int contadorLinhas){
  char *p;
  int tamanhoP;

  p = strtok (linhaTXT," ,.-");
  while (p != NULL)
  {
    tamanhoP = strlen(p);

    for(int i = 0; i < tamanhoP; i++) //Laço para converter letras maiúsculas para letras minúsculas
      p[i] = tolower(p[i]); 

    novaOcorrencia(p, contadorLinhas);
    p = strtok (NULL, " ,.-\n");
  }
}

int TabelaDispersao::valor(char p[]){
  int valor = 0;

  for(int i = 0; p[i] != '\n' && p[i] != '\0'; i++){
    valor = valor + p[i];
  }

  return valor;
}

int TabelaDispersao::h(char p[]){
  return valor(p) % 47;
}