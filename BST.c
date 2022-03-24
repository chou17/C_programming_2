#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct treeNode{
    char str[128];
    int cnt;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode* Insert(treeNode *, char *);
treeNode* Find(treeNode *, char *);
void PrintInorder(treeNode *);
int cmp_count(const void *,const void *);
void PrintCnt(treeNode **,int n);
void free_node(treeNode *);
void AddToArray(treeNode *, treeNode **, int *);


int main(){
    char line[128];
    treeNode *root = NULL;
    treeNode *p[1024];
    int n=0;

    while(fgets(line,128,stdin)){
        size_t len = strlen(line);
        line[len - 1] = '\0';

        treeNode *is_repeat = Find(root,line);
        if(is_repeat==NULL)
            root = Insert(root,line);
        else{
            if(*line == '-')
                is_repeat->cnt--;
            else
                is_repeat->cnt++;
        }
    }
    AddToArray(root,p,&n);
    printf("Inorder traversal:\n");
    PrintInorder(root);
    printf("\n");
    printf("Count sorting:\n");
    qsort(p,n,sizeof(p[0]),cmp_count);
    for(int i=0;i<n;i++)
        printf("%d %s\n",p[i]->cnt,p[i]->str);
    return 0;
}

treeNode* Insert(treeNode *node, char *str){
    if(node == NULL) {
        treeNode *temp;
        temp = (treeNode *)malloc(sizeof(treeNode));
        strcpy(temp->str,str);
        temp->cnt = 1;
        temp -> left = temp -> right = NULL;
        return temp;
    }
    int c = strcmp(str,node->str);
    if(c>0)
        node->right = Insert(node->right,str);
    else if(c<0) 
        node->left = Insert(node->left,str);
    return node;
}

treeNode* Find(treeNode *node, char *line){
    if(node == NULL)
        return NULL;

    char *str = line;
    if(*line == '-')
        str = line+1;
    int c = strcmp(str,node->str);
    if(c>0)
        return Find(node->right,str);
    else if(c<0)
        return Find(node->left,str);
    else 
        return node;
    return node;
}

void PrintInorder(treeNode *node){
    if(node == NULL) {
        return;
    }
    PrintInorder(node->left);
    printf("%d %s\n", node->cnt,node->str);
    PrintInorder(node->right);
}


void AddToArray(treeNode *node, treeNode **arr, int *n){
     if(node == NULL)
          return;
     arr[(*n)++] = node;
     if(node->left != NULL)
          AddToArray(node->left, arr,n);
     if(node->right != NULL)
          AddToArray(node->right, arr,n);
}

int cmp_count(const void *pa,const void *pb){
    treeNode *a = *(treeNode **)pa;
    treeNode *b = *(treeNode **)pb;
    if(b->cnt!=a->cnt) 
        return (b->cnt - a->cnt);
    else
        return strcmp(a->str,b->str);
}


void free_node(treeNode *node){
    treeNode *tmp = node;
    free(tmp);
    if(node->left != NULL)
        free_node(node->left);
    if(node->right != NULL)
        free_node(node->right);
}
