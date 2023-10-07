#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Vila {
public:
  int _id;
};



class Estrada {
public:
  Vila _origem;
  Vila _destino;

  bool _usada;

  int _ano, _tempo, _custo;
};



class Balconia {
public:
  int _numero_vilas;
  int _numero_estradas;

  vector<Vila> vilas;
  vector<Estrada> estradas;

  void preencherVilas() {
    for (int i = 1; i <= _numero_vilas; i++) {
      Vila vila;
      vila._id = i;
      vilas.push_back(vila);
    }
  }
};



class UnionFind {
private:
  vector<int> pai;
  vector<int> rank;

public:
  UnionFind(int n) {
    pai.resize(n, -1);
    rank.resize(n, 1);
  }

  int find(int i) {
    if (pai[i] == -1)
      return i;

    return pai[i] = find(pai[i]);
  }

  void unite(int x, int y) {
    int s1 = find(x);
    int s2 = find(y);

    if (s1 != s2) {
      if (rank[s1] < rank[s2]) {
        pai[s1] = s2;
      }
      else if (rank[s1] > rank[s2]) {
        pai[s2] = s1;
      }
      else {
        pai[s2] = s1;
        rank[s1] += 1;
      }
    }
  }
};



void Kruskal(Balconia balconia, function<bool(const Estrada&, const Estrada&)> comparacao, bool tipo) {
  sort(balconia.estradas.begin(), balconia.estradas.end(), comparacao);

  UnionFind U(balconia._numero_vilas);

  int ans = 0;
  int ano_maximo = INT_MIN;

  for (auto e : balconia.estradas) {
    int w = e._custo;
    int x = e._origem._id - 1;
    int y = e._destino._id - 1;

    if (U.find(x) != U.find(y)) {
      U.unite(x, y);

      if (tipo) {
        ans += e._custo;
      } else if (e._ano > ano_maximo) {
        ano_maximo = e._ano;
      }
    }
    else if (U.find(y) != U.find(x)) {
      U.unite(y, x);

      if (tipo) {
        ans += e._custo;
      } else if (e._ano > ano_maximo) {
        ano_maximo = e._ano;
      }
    }
  }

  if (tipo) {
    cout << "N+3: " << ans << endl; 
  } else {
    cout << "N+2: " << ano_maximo << endl; 
  }
} 



void BelmannFord(Balconia balconia) {
  int num_vilas = balconia._numero_vilas;
  int num_estradas = balconia._numero_estradas;

  int distancias[num_vilas];
  Estrada* estrada_max_ano = nullptr;  // Para armazenar a estrada com o ano máximo.

  for (int i = 0; i < num_vilas; i++) {
    distancias[i] = INT_MAX;
  }
  distancias[0] = 0;

  for (int i = 1; i <= num_vilas - 1; i++) {
    for (int j = 0; j < num_estradas; j++) {
      int u = balconia.estradas[j]._origem._id - 1;
      int v = balconia.estradas[j]._destino._id - 1;

      int tempo = balconia.estradas[j]._tempo;
      if (distancias[u] != INT_MAX && distancias[u] + tempo < distancias[v]) {
        distancias[v] = distancias[u] + tempo;

        // Marcar a estrada como usada no caminho mínimo.
        balconia.estradas[j]._usada = true;

        // Verificar se essa é a estrada com o ano máximo até agora.
        if (!estrada_max_ano || balconia.estradas[j]._ano > estrada_max_ano->_ano) {
          estrada_max_ano = &balconia.estradas[j];
        }
      }

      if (distancias[v] != INT_MAX && distancias[v] + tempo < distancias[u]) {
        distancias[u] = distancias[v] + tempo;

        // Marcar a estrada como usada no caminho mínimo.
        balconia.estradas[j]._usada = true;

        // Verificar se essa é a estrada com o ano máximo até agora.
        if (!estrada_max_ano || balconia.estradas[j]._ano > estrada_max_ano->_ano) {
          estrada_max_ano = &balconia.estradas[j];
        }
      }
    }
  }

  for (int i = 0; i < num_vilas; ++i) {
    cout << distancias[i] << endl;
  }
  cout << "N+1: " << estrada_max_ano->_ano << endl;

  return;
}




int main() {
  int N, M;
  cin >> N >> M;

  Balconia balconia;
  balconia._numero_vilas = N;
  balconia._numero_estradas = M;
  balconia.preencherVilas();

  for (int i = 0; i < M; i++) {
    int id1, id2;
    cin >> id1 >> id2;

    Vila origem;
    Vila destino;

    origem._id = id1;
    destino._id = id2;

    int ano, tempo, custo;
    cin >> ano >> tempo >> custo;

    Estrada e;
    e._origem = origem;
    e._destino = destino;
    e._ano = ano;
    e._tempo = tempo;
    e._custo = custo;

    balconia.estradas.push_back(e);
  }

  BelmannFord(balconia);

  Kruskal(balconia, [](const Estrada& a, const Estrada& b) { return a._ano < b._ano; }, false);
  Kruskal(balconia, [](const Estrada& a, const Estrada& b) { return a._custo < b._custo; }, true);

  return 0;
}