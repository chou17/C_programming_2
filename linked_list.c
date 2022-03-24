#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node Node;
struct node{
    char str[1024];
    int count;
    struct node *next;
};

int main(){
    Node *head = NULL;
    Node *curr = NULL;
    
    int n=0;
    char line[1024];

    while(fgets(line,1024,stdin)){
        size_t len = strlen(line);
        int new_s=1;

        if (line[len - 1] == '\n')
            line[len - 1] = '\0';

        if(line[0]!='-'){
            if(n==0){
	            curr=(Node *) malloc(sizeof(Node));
	            strcpy(curr->str,line);
	            head = curr;
	            curr->count = 1;
	            curr->next=NULL;
                n++;
            }
            else{
                Node *ptr = head;
                while(ptr){
                    if(strcmp(line,ptr->str)==0){
                        new_s = 0;
                        ptr->count++;
                        break;
                    }
                    ptr = ptr->next;
                }
                if(new_s == 1){
                    Node *tmp_node;
                    tmp_node=(Node *) malloc(sizeof(Node));
                    curr->next = tmp_node;
                    curr = tmp_node;
	                strcpy(curr->str,line);
	                curr->count = 1;
	                curr->next=NULL;
                }
            }
            
        }
        else{
            Node *ptr = head;
            char tmp[1024] = {'\0'};
            int i=0;
            char *qtr = line+1;
            while((*qtr)!='\0')
                tmp[i++] = *qtr++;
            while(ptr){
                if(strcmp(tmp,ptr->str)==0){
                    ptr->count--;
                }
                ptr = ptr->next;
            }
        }
    }
    
    Node *ptr = head;
    while(ptr){
        printf("%s: %d\n",ptr->str,ptr->count);
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

