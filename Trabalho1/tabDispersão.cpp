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
  void separaPalavras(char linhaTXT[], int contadorLinhas); //Separa a string linhaTXT em palavras
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

  TabelaDispersao tab;

  FILE *texto = fopen(argv[1], "r"); //Abrindo arquivo de texto de entrada
  if(texto == NULL)
    printf("***Erro ao abrir o arquivo.txt***\n");

  while(fgets(linhaTXT, sizeof(linhaTXT), texto) != NULL){ //Salvando na string linhaTXT cada linha do texto
    tab.separaPalavras(linhaTXT, contadorLinhas); //Chamando função pra separar a linha em palavras
    contadorLinhas++;
  }

  tab.escreve();
  
  fclose(texto);
  return 0;
}

// ********** MÉTODOS DA CLASSE OCORRENCIA **********
Ocorrencia::Ocorrencia(int linha){ //Construtor padrão
  this->linha = linha; //Iniciando o atributo linha da classe
}

Ocorrencia::~Ocorrencia(){} //Destrutor padrão

// ********** MÉTODOS DA CLASSE LISTAO **********
ListaO::ListaO(){ //Construtor padrão
  this->inicio = NULL; //Iniciando fazendo com que o ponteiro inicio aponte pra nulo
  this->fim = NULL; //Iniciando fazendo com que o ponteiro fim aponte pra nulo
}

ListaO::~ListaO(){ //Destrutor padrão
  Ocorrencia *olhando;

  olhando = this->inicio;
  while(olhando != NULL){ //Passando de ocorrencia em ocorrencia na lista desalocando espaço utilizado na memória
    olhando = olhando->prox;
    delete(this->inicio);
    this->inicio = olhando;  
  }
}

void ListaO::insere(int linha){ //Insere a ocorrência na lista de ocorrências
  Ocorrencia *olhando;
  
  olhando = this->inicio;
  while((olhando != NULL) && (olhando->linha != linha)){ //Laço pra descobrir se já existe uma ocorrência da palavra na mesma linha
    olhando = olhando->prox;
  }

  if(olhando == NULL){ //Se olhando == nulo quer dizer que não foi encontrado uma ocorrência da palavra na mesma linha
    Ocorrencia *novaO = new Ocorrencia(linha); //Instanciando um novo objeto da classe ocorrência
    if(this->inicio == NULL){ //Caso a lista esteja vazia ainda
      this->inicio = novaO;
      this->fim = novaO;
      novaO->prox = NULL;
    }
  
    else{ //Caso a lista não esteja vazia
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
  while(olhando != this->fim){ //Laço pra printar ocorrência por ocorrência
    printf("%d,", olhando->linha);
    olhando = olhando->prox;
  }
  printf("%d)", this->fim->linha);
}

// ********** MÉTODOS DA CLASSE PALAVRA **********
Palavra::Palavra(char p[]){ //Construtor padrão
  strcpy(this->p, p); //Iniciando o atributo p da classe
  this->prox = NULL;
}

Palavra::~Palavra(){} //Destrutor padrão

void Palavra::insere(int linha){ //Insere a ocorrência na lista de ocorrências da palavra
  ocorrencias.insere(linha); 
}

void Palavra::escreve(){ //Printa a palavra e suas ocorrências
  printf("%s", this->p);
  ocorrencias.escreve();
}

// ********** MÉTODOS DA CLASSE LISTAP **********
ListaP::ListaP(){ //Construtor padrão
  this->inicio = NULL; //Iniciando fazendo com que o ponteiro inicio aponte pra nulo
  this->fim = NULL; //Iniciando fazendo com que o ponteiro fim aponte pra nulo
}

ListaP::~ListaP(){ //Destrutor padrão
  Palavra *olhando;

  olhando = this->inicio;
  while(olhando != NULL){ //Passando de palavra em palavra na lista desalocando espaço utilizado na memória
    olhando = olhando->prox;
    delete(this->inicio);
    this->inicio = olhando;  
  }
}

Palavra *ListaP::insere(char p[]){ //Insere a palavra na lista de palavras
  Palavra *novaP = new Palavra(p);

  if(this->inicio == NULL){ //Caso a lista esteja vazia
    this->inicio = novaP;
    this->fim = novaP;
    novaP->prox = NULL;
  }

  else{ //Caso a lista não esteja vazia
    this->fim->prox = novaP;
    this->fim = novaP;
    novaP->prox = NULL;
  }

  return novaP;
}

Palavra *ListaP::busca(char p[]){ //Busca a palavra na lista de palavras, devolve um ponteiro pro objeto caso encontre e devolve nulo caso não encontre
  Palavra *olhando;

  olhando = this->inicio;
  while((olhando != NULL) && (strcmp(p, olhando->p) != 0)){ //Verificando palavra por palavra se é a palavra que está buscando
    olhando = olhando->prox;
  }

  if(olhando != NULL) //Se olhando != nulo quer dizer que a palavra foi encontrada na lista
    return olhando;
  else
    return NULL;
}

void ListaP::escreve(){ //Escreve a lista de palavras com suas respectivas ocorrências
  Palavra *olhando;

  olhando = this->inicio;
  while(olhando != NULL){ //Verificando se a lista não está vazia
    printf(" ");
    olhando->escreve();
    olhando = olhando->prox;
  }
}

// ********** MÉTODOS DA CLASSE TABELADISPERSAO **********
TabelaDispersao::TabelaDispersao(){ //Construtor padrão
  fatorDeCarga = 0; //Iniciando o atributo fatorDeCarga da classe
}

TabelaDispersao::~TabelaDispersao(){} //Destrutor padrão

void TabelaDispersao::escreve(){ //Escreve a tabela com cada lista de palavras e suas ocorrências em cada linha de seu hash 
  for(int i = 0; i < TAMANHO; i++){
    printf("%d:", i);
    tabela[i].escreve();
    printf("\n");
  }
  fatorDeCarga = fatorDeCarga / 47;
  printf("Fator de carga: %g", fatorDeCarga);
}

void TabelaDispersao::novaOcorrencia(char p[], int linha){
  if((tabela[h(p)].busca(p) == NULL) && (strlen(p) >= MIN && strlen(p) <= MAX)){ //Caso a palavra ainda não tenha sido inserida, e ela tenha mais que 3 letras e menos que 20 letras
    tabela[h(p)].insere(p)->insere(linha); //Insere a palavra na sua respectiva lista de palavras e sua linha na qual foi encontrada
    fatorDeCarga++;
  }

  else if(strlen(p) >= MIN && strlen(p) <= MAX){ //Caso a palavra ja tenha sido inserida e garantindo que ela tenha mais que 3 letras e menos que 20 letras
    tabela[h(p)].busca(p)->insere(linha); //Insere mais uma ocorrência na lista de ocorrências daquela palavra
  }
}

void TabelaDispersao::separaPalavras(char linhaTXT[], int contadorLinhas){ //Separa a string linhaTXT em palavras
  char *p;
  int tamanhoP;

  p = strtok (linhaTXT," ,.-!\n"); //Aponta do inicio da linha até o primeiro espaço, vírgula, ponto, hífen ou ponto de exclamação
  while (p != NULL)
  {
    tamanhoP = strlen(p);

    for(int i = 0; i < tamanhoP; i++) //Laço para converter letras maiúsculas em letras minúsculas
      p[i] = tolower(p[i]); 

    novaOcorrencia(p, contadorLinhas); //Passa a palavra encontrada pra função novaOcorrencia e qual linha ela está no texto
    p = strtok (NULL, " ,.-!\n"); //Aponta do próximo caracter depois de onde parou que não seja espaço, vírgula, ponto, hífen ou ponto de exclamação até o próximo espaço, vírgula, ponto, hífen ou ponto de exclamação 
  }
}

int TabelaDispersao::valor(char p[]){ //Função para calcular o valor da palavra p
  int valor = 0;

  for(int i = 0; p[i] != '\n' && p[i] != '\0'; i++){ //Somando valor de cada caractere da palavra
    valor = valor + p[i];
  }

  return valor;
}

int TabelaDispersao::h(char p[]){ //Função para calcular o hash da palavra p
  return valor(p) % 47;
}