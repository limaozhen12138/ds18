#include <cstdlib>
#include <cstdio>
using namespace std;
typedef struct Node{
    int key;
    struct Node *lchild,*rchild;
}Node;

Node *getNewNode(int key){
    Node *p = (Node *) malloc(sizeof (Node));
    p -> key = key;
    p -> lchild = p -> rchild = NULL;
    return p;
    }
void clear(Node *node){
    if(node == NULL ) return;
    clear(node -> lchild);
    clear(node -> rchild);
    free(node);
    return;
}
Node *insert(Node *root, int key){
    if(root == NULL) return getNewNode(key);
    if(root -> key == key)return root;
    if(root -> key > key) root -> lchild = insert(root -> rchild, key);
    else root -> rchild = insert(root -> rchild, key);
    return root;   
    
}

Node *predecessor(Node *root){
    Node  *temp = root -> lchild;
    while (temp -> rchild) temp = temp -> rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL)return root;
    if (root->key > key) root->lchild = erase(root->lchild, key);
    else if (root->key < key) root->rchild = erase(root->rchild, key);
    else{

        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    return root;
}


void  __in_order(Node *root){
    if(root == NULL) return;
    __in_order(root -> lchild);
    printf("%d ", root -> key);
    __in_order(root -> rchild);
    return;
}

void in_order(Node *root){
    printf("in order output : \n");
    __in_order(root);
    printf("\n");
    return;
}

int main(){
    int opt, value;
    Node *root = NULL;
    while (~scanf("%d,%d",&opt, &value)){//注意scanf，会读取/n，然而scanf原函数就带有换行符，容易滞留在缓冲区
        switch (opt) {
            case 1: root = insert(root, value);break;
            case 2: root = erase(root, value);break;
        }
        in_order(root);
    }
    return 0;
    
    
}