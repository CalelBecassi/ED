#include <cstdio>
#include <climits>
#include <string>
#include <algorithm>

using std::string;

class Heap
{
public:
  int *S;//*****************ISSO TEM QUE SER PRIVADO!!!!!!!!!!!!!!!!!****************
  Heap();
  Heap(const int n, const int dados[]);
  Heap(const Heap& outro);
  ~Heap();
  Heap& operator=(const Heap& outro);
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(int p);
  int consulta_maxima();
  int extrai_maxima();
  void altera_prioridade(int i, int p);

  
private:
  int n;
  int capacidade;
  static const int TAMANHO_INICIAL = 4;
  
  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};


int main(void)
{
  Heap h; // construtor Heap()
  
  for (int i = 1; i <= 10; i++){
    h.insere(i);
  }

  printf("h:\n");
  h.escreve();

  h.extrai_maxima();
  h.altera_prioridade(0, -3);
  printf("h:\n");
  h.escreve();

  int v[] = {1,2,3,4,5};
  
  Heap h2(5, v); // construtor Heap(int n, int dados[])
  h2.insere(15);
  printf("h2:\n");
  h2.escreve();
    
  Heap h3(h2); // construtor de cópia padrão
  h2.insere(30);
  printf("h3:\n");
  h3.escreve();

  Heap h4 = h2; // construtor de cópia padrão
  h2.insere(40);
  printf("h4:\n");
  h4.escreve();
  
  h = h2; // operador de atribuição, sem constructor ou constructor de cópia
  h.insere(100);
  printf("h2:\n");
  h2.escreve();
  printf("h:\n");
  h.escreve();

  h = Heap(5, v); // construtor Heap(int n, int dados[]), seguido de atribuição (de cópia, não transferência (move))
  printf("h:\n");
  h.escreve();

  h.extrai_maxima();
  h.altera_prioridade(0, -2);
  printf("h:\n");
  h.escreve();
    
  return 0;
}

Heap::Heap() {
  S = new int[TAMANHO_INICIAL];
  n = 1;
  capacidade = TAMANHO_INICIAL;
}

Heap::Heap(const int n, const int dados[]){//ALGO ERRADO
  this->n = n;
  capacidade = n;
  S =  new int[n];

  for(int i = 0; i < n; i++)
    S[i] = dados[i];

  for(int i = n/2; i >= 0; i--)
    desce(i);

}

Heap::Heap(Heap const& outro){
  this->capacidade = outro.capacidade;
  this->n = outro.n;

  for(int i = 1; i <= this->n; i++){
    this->S[i] = outro.S[i];
  }
}

Heap::~Heap() {
}

Heap& Heap::operator=(Heap const& outro){
  delete[] S;
  S = new int[outro.capacidade];
  this->capacidade = outro.capacidade;
  this->n = outro.n;

  for(int i = 1; i <= this->n; i++){
    this->S[i] = outro.S[i];
  }

  return *this;
}

void Heap::escreve_niveis() {
  int escritos = 0, fim_nivel = 1;

  for(int i = 0; i < n; i++) {
    printf("%d ", S[i]);
    if (++escritos == fim_nivel) {
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

void Heap::escreve(const string& prefixo, int i) {//ALGO ERRADO
  if (i < n) {
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < n-1;
    
    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" );

    printf("%d\n", S[i]);
      
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

int Heap::pai(int i) {
  return (i - 1) / 2;
}

int Heap::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

int Heap::direito(int i) {
  return 2 * (i + 1);
}

void Heap::troca(int i, int j) {
  int aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

void Heap::desce(int i) {

    while ((S[i] < S[esquerdo(i)]) || (S[i] < S[direito(i)])){

      if (S[i] < S[esquerdo(i)]){
          if (S[esquerdo(i)] > S[direito(i)]){
            troca(i, esquerdo(i));
            i = esquerdo(i);
          }
          else{
            troca(i, direito(i));
            i = direito(i);
          }
      }

     if(S[i] < S[direito(i)]){
         if (S[esquerdo(i)] < S[direito(i)]){
            troca(i, direito(i));
            i = direito(i);
          }
          else{
            troca(i, esquerdo(i));
            i = esquerdo(i);
          }
     }
  }
}

void Heap::sobe(int i) {
  while (S[pai(i)] < S[i]) {
    troca(i, pai(i));
    i = pai(i);
  }
}

void Heap::insere(int p) {
  if(n <= capacidade){
    S[n] = p;
    n++;
  }

  else{
    capacidade = capacidade * 2;
    int *novo = new int[capacidade];

    for(int i = 0; i < n; i++)
      novo[i] = S[i];

    delete[] S;
    S = novo;

    S[n] = p;
    n++;
  }
  printf("%d\n", S[n-1]);
  //sobe(n-1);
}

int Heap::consulta_maxima() {
  return S[0];
}

int Heap::extrai_maxima() {
  int max = S[0];

  altera_prioridade(0, (S[n - 1]));
  n--;

  return max;
}

void Heap::altera_prioridade(int i, int p) {
  if(p > S[i]){
    S[i] = p;
    sobe(i);
  }

  else{
    S[i] = p;
    desce(i);
  }
}