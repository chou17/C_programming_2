#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

void d_space(char *,char *,int);
void in_to_post(char*, char*);
int priority(char);
long long int eval(char*);
long long int cal(char,long long int,long long int);

int main(){
    char input[1024];

    while(fgets(input,1024,stdin)){
        char new_line[1024];
        char *ptr=input+3;
        int len= strlen(input)-1;
        char postfix[1024]= {'\0'};
        long long int val;

        if(input[0]=='i'){
            d_space(ptr,new_line,len);
            in_to_post(new_line,postfix);
            printf("%s \n", postfix);
        }
        else if(input[0]=='p'){
            val=eval(ptr);
	        printf("%lld\n", val);
        }
    }
}

void d_space(char *input,char *new_line,int len){
    char *ptr=input;
    char *qtr=new_line;

    for(int i=0;i<len;i++){
        while (isspace(*ptr)){
        ptr++;
        }
        while (!isspace(*ptr) && (*ptr)){
            *qtr++ = *ptr++;
        }
    }
    *qtr='\0';
}


void in_to_post(char* infix, char* postfix){
    char stack[1024] = {'\0'};
    int top=0;
    int j=0;

    for(int i = 0; infix[i] != '\0'; i++){
		switch(infix[i]){
        	case '(':
            	stack[++top] = infix[i];
            	break;

        	case '+': case '-': case '*': case '/': case '%':
				while(priority(stack[top]) >= priority(infix[i])){
                	if(postfix[j-1]!=' '){
                		postfix[j++] = ' ';
                	}
					postfix[j++] = stack[top--];
            	}
            	postfix[j++] = ' ';
            	stack[++top] = infix[i];
            	break;

        	case ')':
            	while(stack[top] != '('){
                	postfix[j++] = ' ';
					postfix[j++] = stack[top--];
            	}
            	top--;
            	break;

        	default:
            	postfix[j++] = infix[i];
    	}
    }

    while(top > 0){
		postfix[j++] = ' ';
        postfix[j++] = stack[top--];
    }
}


int priority(char op){
    switch(op){
        case '+': case '-':
			return 1;
        case '*': case '/': case '%':
			return 2;
        default:
			return 0;
    }
}


long long int eval(char* postfix) {
    char tmp[128] = {'\0'};
    long long int stack[1024];
    int j;
    int top=0;
    for(int  i = 0; postfix[i] != '\n'; i++) switch(postfix[i]) {
        case ' ':
            break;
        case '+': case '-': case '*': case '/':
            stack[top-1] = cal(postfix[i], stack[top - 1], stack[top]);
            top--;
            break;
        default:
            j=0;
            while(postfix[i]!=' ')
                tmp[j++] = postfix[i++];
            stack[++top] = atoll(tmp);
            memset(tmp, '\0', sizeof(tmp));
            break;
    }

    return stack[top];
}

long long int cal(char op, long long int p1, long long int p2) {
    switch(op) {
        case '+': return p1 + p2;
        case '-': return p1 - p2;
        case '*': return p1 * p2;
        case '/': return p1 / p2;
    }
}
