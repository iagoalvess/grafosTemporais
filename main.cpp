#include <iostream>
#include <vector>

using namespace std;

class Vila {
public:
  int _id;
};



class Estrada {
public:
  Vila _inicio;
  Vila _destino;

  int _ano, _tempo, _custo;
};



int main () {
  int N, M;

  vector<Estrada> estradas;

  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    int id1, id2;
    cin >> id1 >> id2;

    Vila inicio;
    Vila destino;

    inicio._id = id1;
    destino._id = id2;

    int ano, tempo, custo;
    cin >> ano >> tempo >> custo;

    Estrada e;
    e._inicio = inicio;
    e._destino = destino;
    e._ano = ano;
    e._tempo = tempo;
    e._custo = custo;

    estradas.push_back(e);
  }

  return 0;
}