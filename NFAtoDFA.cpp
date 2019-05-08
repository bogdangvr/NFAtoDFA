#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

ifstream fin ("LNFA.in");
ofstream fout("LNFA.out");

struct tipCoada {
    int pozitieCuvant;
    int stare;
};

vector <int> stari;
vector <char> operatii;
vector <int> stariFinale;
vector <int> a[100][27];
vector <tipCoada> coada;
tipCoada element;

int x,nrStari,nrOperatii,stareInitiala,nrStariFinale,nrTranzitii,sursa,destinatie,lungimeCuvant,raspuns,nrCuvinte;
char caracter,cuvant[1000];


/// functie ce verifica daca un indice reprezinta pozitia unei stari finale
bool esteFinala (int x){
    x=stari[x-1];
    for (int i=0; i<nrStariFinale; i++){
        if (stariFinale[i]==x){
            return 1;
        }
    }
    return 0;
}

int main () {
    /// citim numarul de stari si le salvam in vectorul stari
    fin>>nrStari;
    for (int i=1; i<=nrStari; i++){
        fin>>x;
        stari.push_back(x);
    }

    /// citim numarul de operatii si le salvam in vectorul operatii
    fin>>nrOperatii;
    for (int i=1; i<=nrOperatii; i++){
        fin>>caracter;
        operatii.push_back(caracter);
    }

    /// citim starea initiala
    fin>>stareInitiala;
    stareInitiala=index(stareInitiala)+1;

    /// citim numarul de stari finale si le salvam in vectorul stariFinale
    fin>>nrStariFinale;
    for (int i=1; i<=nrStariFinale; i++){
        fin>>x;
        stariFinale.push_back(x);
    }

    /// citim numarul de tranzitii si le salvam in matrice astfel:
    /// fiecare linie va reprezenta o stare, iar fiecare coloana va fi o operatie;
    /// valorile de pe o anumita linie si coloana vor reprezenta posibilele destinatii
    /// daca se aplica pe starea linie operatia coloana
    fin>>nrTranzitii;
    for (int i=1; i<=nrTranzitii; i++){
        fin>>sursa>>caracter>>destinatie;
        sursa=index(sursa)+1;
        destinatie=index(destinatie)+1;
        if (caracter=='.'){
            a[sursa][0].push_back(destinatie);
        }
        else{
            a[sursa][caracter-'a'+1].push_back(destinatie);
        }
    }
    fin>>nrCuvinte;
    for (int i=1; i<=nrCuvinte; i++){
        coada.clear();
        raspuns=0;
        fin>>cuvant;
        lungimeCuvant=strlen(cuvant);
        element.pozitieCuvant=0;
        element.stare=stareInitiala;
        coada.push_back(element);

        bfs(0,0);

        if (raspuns==0){
            fout<<"Cuvantul introdus nu este corect\n";
        }
    }
    return 0;
}
