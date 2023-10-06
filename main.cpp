#include <iostream>
#include <vector>
#include <climits> 

using namespace std;

class Vila {
public:
  int _id;
};



class Estrada {
public:
  Vila _origem;
  Vila _destino;

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

  void atualizarNumeroEstradas() {
    _numero_estradas = _numero_estradas * 2;
  }
};



void Verifica(int dist[], int n) {
  cout << "Vila   Distancia do Palacio" << endl;
  for (int i = 0; i < n; ++i)
    cout << i + 1 << "\t\t" << dist[i] << endl;
}



void BelmannFord(Balconia balconia) {
  int num_vilas = balconia._numero_vilas;
  int num_estradas = balconia._numero_estradas;

  int distancias[num_vilas];

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
      }
    }
  }

  Verifica(distancias, num_vilas);
 
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

    Estrada ida;
    ida._origem = origem;
    ida._destino = destino;
    ida._ano = ano;
    ida._tempo = tempo;
    ida._custo = custo;

    balconia.estradas.push_back(ida);

    Estrada volta;
    volta._origem = destino;
    volta._destino = origem;
    volta._ano = ano;
    volta._tempo = tempo;
    volta._custo = custo;

    balconia.estradas.push_back(volta);
  }

  balconia.atualizarNumeroEstradas();

  BelmannFord(balconia);

  return 0;
}