#include <iostream>
#include <string.h>


using namespace std;

typedef struct Node
{
    int data;
    Node *left, *right;
}Node;

int height = 0;

void searchKey(Node* &curr, int key, Node* &parent)
{
    while (curr != NULL && curr->data != key)
    {
        parent = curr;

        if (key < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
}

Node* newNode(int key)
{
    Node* node = new Node;
    node->data = key;
    node->left = node->right = NULL;
 
    return node;
}

Node* insert(Node* root, int key)
{
    if (root == NULL) {
        return newNode(key);
    }
    if (key < root->data) {
        
        root->left = insert(root->left, key);
    }
    else {
        
        root->right = insert(root->right, key);    
    }
    return root;
}

void inorder(Node* root)
{
    if (root == NULL) {
        return;
    }
 
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

bool busca_avl(Node* root, int key){
    if (root == NULL){
        return false;
    }
    if(key == root->data){
        return true;
    }
    else if (key < root->data){
        return busca_avl(root->left, key);
    }
    else{
        return busca_avl(root->right, key);
    }
}

Node* minValueNode(Node* node){
    Node* current = node;
    
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

Node* getMinimumKey(Node* curr)
{
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

void deleteNode(Node* &root, int key)
{
    Node* parent = NULL;
 
    Node* curr = root;
 
    searchKey(curr, key, parent);
 
    if (curr == NULL) {
        return;
    }
 
    if (curr->left == NULL && curr->right == NULL)
    {
        if (curr != root)
        {
            if (parent->left == curr) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
        }
        else {
            root = NULL;
        }
 
        delete(curr);
    }
 
    else if (curr->left && curr->right)
    {
        Node* successor = getMinimumKey(curr->right);
 
        int val = successor->data;
 
        deleteNode(root, successor->data);
 
        curr->data = val;
    }
 
    else {
        Node* child = (curr->left)? curr->left: curr->right;
 
        if (curr != root)
        {
            if (curr == parent->left) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
 
        else {
            root = child;
        }
 
        delete(curr);
    }
}

int getLevelUtil(Node *root, int data, int level){
    if (root == NULL)
        return 0;
    if (root->data == data)
        return level;
    int downlevel = getLevelUtil(root-> left, data, level + 1);
    if (downlevel != 0)
        return downlevel;
    downlevel = getLevelUtil(root->right, data, level + 1);
    return downlevel;
}

int Height(Node* root, int data){
    return getLevelUtil(root, data, 0);
}

void printPreorder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
  
    cout << node->data << endl; 
  
    printPreorder(node->left);  
  
    printPreorder(node->right); 
} 

Node* buscaparentes_avl(Node* root, int key, Node* parent){
    if (root == NULL){
        return NULL;
    }
    if(key == root->data){
        return parent;
    }
    else if (key < root->data){
        parent = root;
        return buscaparentes_avl(root->left, key, parent);
    }
    else{
        parent = root;
        return buscaparentes_avl(root->right, key, parent);
    }
}

Node *rightRotate(Node *y) 
{ 
    Node *x = y->left; 
    Node *T2 = x->right; 
  
    x->right = y; 
    y->left = T2; 

    return x; 
} 

Node *leftRotate(Node *x) 
{ 
    Node *y = x->right; 
    Node *T2 = y->left; 
 
    y->left = x; 
    x->right = T2; 

    return y; 
} 

int main(){
    char test[4];
    bool achei;
    int altura;
    Node* root = NULL;
    cin>>test;
    int key;
    Node* pai = NULL;
    Node* avo = NULL;
    while(strcmp(test, "END")!=0){
        if (strcmp (test, "SLD") == 0){
            cin>>key;
            achei = busca_avl(root, key);
            if (achei == 0){
                root = insert(root, key);
            }
            else{
                pai = buscaparentes_avl(root, key, NULL);
                if (pai != NULL){
                    avo = buscaparentes_avl(root, pai->data, NULL);
                    if(avo == NULL){
                        if (key < pai->data){
                            root = rightRotate(pai);
                        }
                        else{
                            root = leftRotate(pai);
                        }
                    }
                    else{
                        if (pai->data < avo->data){
                            if (key < pai->data){
                                avo->left = rightRotate(pai);
                            }
                            else{
                                avo->left = leftRotate(pai);
                            }                            
                        }
                        else{
                            if (key < pai->data){
                                avo->right = rightRotate(pai);
                            }
                            else{
                                avo->right = leftRotate(pai);
                            } 
                        }
                    }
                }
            }
            altura = Height(root, key);
            cout << altura<< endl;
        }
        if (strcmp (test, "STK") == 0){
            cin>>key;
            achei = busca_avl (root, key);
            if (!achei){ 
                cout<<"NULL"<<endl;
            }
            else {
                altura = Height(root, key);
                cout << altura<< endl;
            }
            deleteNode(root, key);

        }
        if (strcmp (test, "EMG") == 0){
            if (root == NULL){
                cout<<"-1 -1"<<endl;
            }
            else {
                cout<<root->data<< " ";
                deleteNode(root, root->data);
                if (root == NULL){
                    cout<<"-1"<<endl;
                }
                else {
                    cout<<root->data<<endl;
                }
            }    
        }     
        cin>>test;
    }
printPreorder(root);
return 0;
}