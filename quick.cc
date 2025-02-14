#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<int> quicksort(vector<int> organizar){
    int pivote = organizar.at(organizar.size() / 2);

    vector<int> menores;
    vector<int> mayores;

    for(int i = 0; i < organizar.size(); i++){
        if(i == organizar.size() / 2){
            //nada
        }
        else{
            if(organizar.at(i) < pivote){
                menores.push_back(organizar.at(i));
            }
            else if(organizar.at(i) >= pivote){
                mayores.push_back(organizar.at(i));
            }
        }
    }
    vector<int> organizado;
    if(menores.size() != 0){
        menores = quicksort(menores);
    }
    if(mayores.size() != 0){
        mayores= quicksort(mayores);
    }

    for(int i = 0; i < menores.size(); i++){
        organizado.push_back(menores.at(i));
    }
    organizado.push_back(pivote);
    for(int i = 0; i < mayores.size(); i++){
        organizado.push_back(mayores.at(i));
    }
   
  return organizado;

}

int main(){
    vector<int> prueba;

    for(int i = 0; i < 10; i++){
        int var = 0;
        cin >> var;
        prueba.push_back(var);
    }

    cout << "sin" << endl;
    for(int i = 0; i < 10; i++){
       
        cout << " " << prueba.at(i);
    }

    vector<int> prueba2;

    prueba2 = quicksort(prueba);

    cout << "\ncon" << endl;
    for(int i = 0; i < 10; i++){
       
        cout << " " << prueba2.at(i);
    }
 return 0;
}