

// LEMBRAR DE COLOCAR O CABEÇALHO




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
  
private:
  static const int TAMANHO = 47; // Tamanho da tabela
  ListaP tabela[TAMANHO];        // Listas da tabela

  int valor(char p[]); // Valor da palavra p
  int h(char p[]);     // Função de hash
};
