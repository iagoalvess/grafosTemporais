#include <iostream>
#include <tuple>
#include <list>
#include <queue>
#include <algorithm>

#define INFINITO 0x3f3f3f3f3f3f3f3f

using namespace std;

// Definição de Estrada <Destino, Ano, Tempo, Custo>
typedef tuple<int, int, int64_t, int64_t> estrada;

class Balconia {
	int num_vilas; // Número de vértices

	list<estrada>* estradas; // Lista de arestas

public:
	Balconia(int N);
  ~Balconia();

	void adicionaEstrada(int o, int d, int64_t a, int64_t t, int64_t c);

	void caminhoMinimo();

  void arvoreCusto();
  void arvoreAno();
};



// Construtor do grafo
Balconia::Balconia(int N) {
	this->num_vilas = N;
	estradas = new list<estrada>[N];
}



Balconia::~Balconia() {
  delete[] estradas;
}



// Adiciona uma aresta (dado que é bidirecional)
void Balconia::adicionaEstrada(int o, int d, int64_t a, int64_t t, int64_t c) {
	estradas[o].push_back(make_tuple(d, a, t, c));
	estradas[d].push_back(make_tuple(o, a, t, c));
}



void Balconia::caminhoMinimo() {
	priority_queue<estrada, vector<estrada>, greater<estrada>> fila;

  // Inicializa as distâncias com infinito
	vector<int64_t> distancias(num_vilas, INFINITO);

  // Vetor para encontrar o o primeiro ano em que todas 
  // distâncias podem ser realizadas ao mesmo tempo
  vector<int64_t> anoMaxPorCaminho(num_vilas, -1);

	fila.push(make_tuple(0, 0, 0, 0));
	distancias[0] = 0;

	while (!fila.empty()) {
    // Pega a vila de maior prioridade na fila
		int u = get<1>(fila.top());
		fila.pop();

		for (auto& e : estradas[u]) {
			int v = get<0>(e); // Próxima vila alcançável
			int64_t ano = get<1>(e);
			int64_t tempo = get<2>(e);

			if (distancias[v] > distancias[u] + tempo) {
				distancias[v] = distancias[u] + tempo;
				anoMaxPorCaminho[v] = max(anoMaxPorCaminho[u], ano);
				fila.push(make_tuple(distancias[v], v, 0, 0));
			}
		}
	}

  // Imprime as distâncias mínimas para todas as vilas
	for (int i = 0; i < num_vilas; i++) {
		printf("%ld\n", distancias[i]);
	}

  // Encontra e imprime o ano máximo entre todas as estradas percorridas
  int64_t anoMax = *max_element(anoMaxPorCaminho.begin(), anoMaxPorCaminho.end());
  printf("%ld\n", anoMax);
}



void Balconia::arvoreAno() {
  priority_queue<estrada, vector<estrada>, greater<estrada>> fila;
  
  // Um vetor para marcar vilas como visitadas
  vector<bool> visitados(num_vilas, false);

  // Variavel para armazenar o ano máximo da árvore
  int64_t anoMaximo = -1;

  fila.push({0, 0, 0, 0});

  while (!fila.empty()) {
    // Pega a vila de maior prioridade na fila
    auto aux = fila.top();
    fila.pop();

    int64_t ano = get<0>(aux);
    int u = get<1>(aux);

    if (visitados[u] == true) {
      continue; // Se a vila já foi visitada, continua para a próxima iteração
    }

    // Atualiza o ano máximo se necessário
    if (ano > anoMaximo) anoMaximo = ano;
    visitados[u] = true; // Marca a vila como visitada


    for (auto v : estradas[u]) {
      if (visitados[get<0>(v)] == false) {
        // Adiciona vilas vizinhas à fila
        fila.push({get<1>(v), get<0>(v), get<2>(v), get<3>(v)});
      }
    }
  }

  printf("%ld\n", anoMaximo);
}



void Balconia::arvoreCusto() {
  priority_queue<estrada, vector<estrada>, greater<estrada>> fila;
  
  // Um vetor para marcar vilas como visitadas
  vector<bool> visitados(num_vilas, false);

  // Variavel para armazenar o a o menor custo possível
  // para  chegar de qualquer vila a qualquer outra
  int64_t custoTotal = 0;

  fila.push({0, 0, 0, 0});

  while (!fila.empty()) {
    auto aux = fila.top();
    fila.pop();

    int64_t custo = get<0>(aux);
    int u = get<3>(aux);

    if (visitados[u] == true) {
      continue; // Se a vila já foi visitada, continue para a próxima iteração
    }

    custoTotal += custo;
    visitados[u] = true; // Marca a vila como visitada

    for (auto v : estradas[u]) {
      if (visitados[get<0>(v)] == false) {
        // Adiciona vilas vizinhas à fila
        fila.push({get<3>(v), get<1>(v), get<2>(v), get<0>(v)});
      }
    }
  }

  printf("%ld\n", custoTotal);
}

int main() {
  int N, M;
  if (scanf("%d %d", &N, &M) != 2) {
    printf("Erro ao ler N e M\n");
    return 1;
  }

  Balconia g(N);

  for (int i = 0; i < M; i++) {
    int o, u;
    int64_t a, t, c;
    if (scanf("%d %d %ld %ld %ld", &o, &u, &a, &t, &c) != 5) {
      printf("Erro ao ler os parâmetros da estrada %d\n", i + 1);
      return 1;
    }

    o = o - 1;
    u = u - 1;

    g.adicionaEstrada(o, u, a, t, c);
  }

  g.caminhoMinimo();
  g.arvoreAno();
  g.arvoreCusto();

  return 0;
}
