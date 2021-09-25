#include <iostream>
#include <string.h>

using namespace std;

int cont = 0;
int Q;
int M;
int sacola =0;
void combinationUtil(int arr[], int l, int index, int soma);


void printCombination(int arr[], int l)
{

    combinationUtil(arr, l, 0, 0);
}
 
void combinationUtil(int arr[], int l, int index, int soma)
{
    if (index == l)
        return;
    if (arr[index] + soma <= Q){
        if (++sacola >= M){
            cont ++;
        }
        
        combinationUtil (arr, l, index+1, soma + arr[index]);
        sacola --;
    }
    combinationUtil (arr, l, index+1, soma);
}


int main (){
    int vezes;
    cin >> vezes;
    int i;
    for ( i = 0; i<vezes ; i++){
        int l;
        cin >> l;
        int P[l];
        for (int v = 0; v<l; v++){
            cin >> P[v];
        }
        cin >> M;
        cin >> Q;
        int n = sizeof(P)/sizeof(P[0]); 
        printCombination(P,l);  
        if (M == 0)
            cont++;
        cout << "caso " << i <<":" << " " <<cont<< endl;
        cont = 0;
        sacola = 0;
    }
    return 0;
}