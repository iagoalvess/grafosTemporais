#include <iostream>
#include <vector>

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
};



void BelmannFord(vector<Estrada> caminho, int origem) {

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

  return 0;
}