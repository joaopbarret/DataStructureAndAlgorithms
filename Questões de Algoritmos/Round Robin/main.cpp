#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

typedef struct Node
{
    int ID;
    int cont;
    Node* next;
}Node;

typedef struct NodeCPU
{
    int ID;
    int cont;
}NodeCPU;

int contciclo = 0;

Node* head = NULL;
Node* tail = NULL;
Node* temp = NULL;

Node* front = NULL;
Node* rear = NULL;
Node* moment = NULL;



void Admission(int id) {
   if (tail == NULL) {
      tail = new Node ();
      tail->next = NULL;
      tail->ID = id;
      tail->cont = 0; 
      head = tail;
   } else {
      temp= new Node (); 
      tail->next = temp;
      temp->ID = id;
      temp->cont= 0;
      temp->next = NULL;
      tail = temp;
   }
}

void Swap (int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void DeleteEnd() {
   moment = front;
   if (front == NULL) {
   }
   else
   if (moment->next != NULL) {
      moment = moment->next;
      delete(front);
      front = moment;
   } else {
      delete(front);
      front = NULL;
      rear = NULL;
   }
}

void Admission2(int id, int cont) {
   if (tail == NULL) {
      tail = new Node ();
      tail->next = NULL;
      tail->ID = id;
      tail->cont = cont; 
      head = tail;
   } else {
      temp= new Node (); 
      tail->next = temp;
      temp->ID = id;
      temp->cont= cont;
      temp->next = NULL;
      tail = temp;
   }
}
void Display() {
   temp = head;
   if ((head == NULL) && (tail == NULL)) {
      cout<<"Queue is empty"<<endl;
      return;
   }
   cout<<"Queue elements are: ";
   while (temp != NULL) {
      cout<<temp->cont<<" ";
      cout << temp->ID<<" ";
      temp = temp->next;
   }
   cout<<endl;
}

Node* Delete() {
    Node* aux = NULL;
   temp = head;
   if (head == NULL) {

   }
   else
   if (temp->next != NULL) {
      temp = temp->next;

      aux = head;
      head = temp;
   } else {

      aux = head;
      head = NULL;
      tail = NULL;
   }
    return aux;
}

void DisplayEnd() {
   moment = front;
   if ((front == NULL) && (rear == NULL)) {
      return;
   }
   while (moment != NULL) {
      cout<<moment->ID<<" ";
      cout<<moment->cont<<endl;
      moment = moment->next;
   }
}

void Insert(int val, int cont) {
   if (rear == NULL) {
      rear = new Node ();
      rear->next = NULL;
      rear->ID = val;
      rear->cont = cont;
      front = rear;
   } else {
      moment =new Node ();
      rear->next = moment ;
      moment->ID = val;
      moment->cont = cont; 
      moment->next = NULL;
      rear = moment ;
   }
}

int main(){
    char test[4];
    int contnew = 0;
    int P, S;
    int contCPU = 0;
    cin>>P;
    cin>>S;
    cin>>test;
    int i;
    int contEnd = 0;
    int vetor[10000] = {0};
    Node* aux;
    aux = new Node ();
    aux->ID = 0;
    aux->cont = 0;
    aux->next = NULL;
    int contvoltou = 0;

    NodeCPU CPU[P];
    for (i=0;i<P;i++){
        CPU[i].cont = 0;
        CPU[i].ID = 0; 
    }
    while(strcmp(test, "END")!=0){
        
        /* fazer um for checkando se tem nulo no vetor, se sim recebe um return de um dequeue do primeiro da fila*/

        if (strcmp (test, "NEW") == 0){
            cin>>vetor[contnew];
            contnew++;
        }
        if (strcmp (test, "TER") == 0){
            //tirar da cpu, colocar na fila, printar e tirar da fila
            int index;
            NodeCPU agora;
            cin>>agora.ID;
            for (i=0;i<P;i++){
                if(CPU[i].ID==agora.ID){
                    index = i;
                    CPU[i].cont ++;
                    Insert(CPU[i].ID, CPU[i].cont);
                    CPU[i].ID = 0;
                    CPU[i].cont = 0;
                    contEnd ++;

                }
            }
            for (i=index;i<(P-1);i++){
                Swap (&(CPU[i].cont), &(CPU[i+1].cont));
                Swap (&(CPU[i].ID), &(CPU[i+1].ID));
            }
        } 
        if (strcmp (test, "SCH") == 0){
        //coloca do vetor pra fila de volta e exclui do vetor
            for(i=0;i<P;i++){
                if(CPU[i].ID !=0){
                    CPU[i].cont++;
                }
            }

            for (i=0;i<P;i++){
                if(CPU[i].cont!= 0){
                    if(CPU[i].ID != 0 && CPU[i].cont%S == 0){
                    Admission2(CPU[i].ID, CPU[i].cont);
                    CPU[i].ID = 0;
                    CPU[i].cont = 0;
                    contvoltou++;
                    }
                }
            }             
            
            //admite os news na fila

            for(i=0;i<contnew;i++){
                Admission(vetor[i]);
            }
            
            //coloca da fila pro vetor e exclui da fila
            for (i=0;i<P;i++){

                if(CPU[i].ID == 0){
                    if (head == NULL){

                    }
                    else{
                        aux = Delete ();
                        CPU[i].ID = aux->ID;
                        CPU[i].cont = aux->cont;
                        contCPU ++;
                    }
                }
                else {
                    
                }
            }
            cout<< "ciclo " << contciclo << endl;
            DisplayEnd();
            cout << contvoltou << endl;
            cout << contnew << endl;
            cout<< contCPU << endl;
            contnew = 0;
            contCPU = 0;
            contvoltou = 0;
            contciclo ++;
            for (i=0;i<contEnd;i++){
                DeleteEnd();
            }
        }

        cin>>test;
    }
    
    return 0;
}