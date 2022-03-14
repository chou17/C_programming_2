#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 512

struct data{
    char name[32];
    char email[128];
    char url[128];
    char phone[15];
};

void store_data(struct data *people,char *ptr,int num);
void update_data(struct data *people,char *ptr,int num);
void delete_data(struct data *people,char *ptr,int num);
void find_data(struct data *people,char *ptr,int num);
void sort_data(struct data *people,char *ptr,int num);
void print_data(struct data *people,int num);


int main(int argc, char **argv){
    if(argc==2){
        int num = atoi(argv[1]);
        if (num<1)
            return 0;
        struct data people[3000];
        for(int i=0;i<num;i++)
            scanf("%s\t%s\t%s\t%s",people[i].name,people[i].email,people[i].url,people[i].phone);
        char line[MAX];
        while(fgets(line,MAX,stdin)){
            if(line[0]=='q')
                return 0;
            char *ptr = line+2;
            if(line[0]=='i'){
                store_data(people,ptr,num);
                num++;
            }
            else if(line[0]=='u')
                update_data(people,ptr,num);
            else if(line[0]=='d'){
                delete_data(people,ptr,num);
                num--;
            }
            else if(line[0]=='f')
                find_data(people,ptr,num);
            else if(line[0]=='s')
                sort_data(people,ptr,num);
            else if(line[0]=='p')
                print_data(people,num);
        }
    }
}

void store_data(struct data *people,char *ptr,int num){
    char tmp[128];
    char *qtr = tmp;
    while(*ptr!='\t' && *ptr!='\n' && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    strcpy(people[num].name,tmp);
    ptr++;
    qtr = tmp;
    while(*ptr!='\t' && *ptr!='\n' && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    strcpy(people[num].email,tmp);
    ptr++;
    qtr = tmp;
    while(*ptr!='\t' && *ptr!='\n' && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    strcpy(people[num].url,tmp);
    ptr++;
    qtr = tmp;
    while((*ptr!='\t' || *ptr!='\n') && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    strcpy(people[num].phone,tmp);
}

void update_data(struct data *people,char *ptr,int num){
    char u_name[32];
    char *qtr = u_name;
    while(!isspace(*ptr) && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    for(int i=0;i<num;i++){
        if(strcmp(people[i].name,u_name)==0){
            ptr++;
            char tmp[128];
            char *qtr = tmp;
            while(*ptr!='\t' && *ptr!='\n' && (*ptr))
                *qtr++ = *ptr++;
            *qtr = '\0';
            strcpy(people[i].email,tmp);
            ptr++;
            qtr = tmp;
            while(*ptr!='\t' && *ptr!='\n'&& (*ptr))
                *qtr++ = *ptr++;
            *qtr = '\0';
            strcpy(people[i].url,tmp);
            ptr++;
            qtr = tmp;
            while(*ptr!='\t' && *ptr!='\n' && (*ptr))
                *qtr++ = *ptr++;
            *qtr = '\0';
            strcpy(people[i].phone,tmp);
        }
    }
}

void delete_data(struct data *people,char *ptr,int num){
    char d_name[32];
    char *qtr = d_name;
    while(*ptr!='\t' && *ptr!='\n' && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    int d = 0;
    for(int i=0;i<num;i++){
        if(strcmp(people[i].name,d_name)==0){
            d=i;
            break;
        }
    }
    if(d!=(num-1)){
        for(int i=d;i<(num-1);i++)
            people[i] = people[i+1];
    }
}

void find_data(struct data *people,char *ptr,int num){
    char f_word[32];
    char *qtr = f_word;
    while(*ptr!='\t' && *ptr!='\n' && (*ptr))
        *qtr++ = *ptr++;
    *qtr = '\0';
    int find = 0;
    int f_flag[num];
    for(int i=0;i<num;i++){
        f_flag[i] = 0;
        if(strstr(people[i].name,f_word)!=NULL){
            find = 1;
            f_flag[i]=1;
        }
    }
    if(find==1){
        printf("Find %s result:",f_word);
        for(int i=0;i<num;i++){
            if(f_flag[i]==1)
                printf(" %s",people[i].name);
        }
        printf(" \n");
    }
    else
        printf("%s not found!\n",f_word);
}

void sort_data(struct data *people,char *ptr,int num){
    if(*ptr == 'n'){
        for (int i=0;i<num-1;i++){
            for (int j=0;j<num-1-i;j++){
                if (strcmp(people[j].name,people[j+1].name)>0){
                    struct data tmp;
                    tmp = people[j];
                    people[j] = people[j+1];
                    people[j+1] = tmp;
                }
            }
        }
    }
    else if(*ptr == 'e'){
        for (int i=0;i<num-1;i++){
            for (int j=0;j<num-1-i;j++){
                if (strcmp(people[j].email,people[j+1].email)>0){
                    struct data tmp;
                    tmp = people[j];
                    people[j] = people[j+1];
                    people[j+1] = tmp;
                }
            }
        }
    }

    else if(*ptr == 'u'){
        for (int i=0;i<num-1;i++){
            for (int j=0;j<num-1-i;j++){
                if (strcmp(people[j].url,people[j+1].url)>0){
                    struct data tmp;
                    tmp = people[j];
                    people[j] = people[j+1];
                    people[j+1] = tmp;
                }
            }
        }
    }

    else if(*ptr == 'p'){
        int phone_num[num];
        for(int i=0;i<num;i++)
            phone_num[i] = atoi(people[i].phone);
        for (int i=0;i<num-1;i++){
            for (int j=0;j<num-1-i;j++){
                if (phone_num[j] > phone_num[j+1]){
                    struct data tmp;
                    tmp = people[j];
                    people[j] = people[j+1];
                    people[j+1] = tmp;

                    int tmp_n;
                    tmp_n = phone_num[j];
                    phone_num[j] = phone_num[j+1];
                    phone_num[j+1] = tmp_n;
                }
            }
        }
    }
}

void print_data(struct data *people,int num){
    printf("number\tname\temail\tsite\tphone number\n");
    printf("----------------------------------------------------\n");
    for(int i=0;i<num;i++)
        printf("[%d] %s\t%s\t%s\t%s\n",i+1,people[i].name,people[i].email,people[i].url,people[i].phone);
    printf("\n");
}
