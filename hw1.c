#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  

#define MAX 1024
  
int main(int argc, char **argv){  
    char line[MAX];
    char *lines[MAX];
    int l_len[MAX];  
    char *result[MAX];
    int l_count=0;
    
    while(fgets(line,MAX,stdin)){
        int len = strlen(line);
        line[len-1]='\0';
        lines[l_count] = malloc(len);  
        l_len[l_count] = len;  
        strcpy(lines[l_count++],line);

    }  	
    if(argc == 4){
    	if(strcmp(argv[1],"-g") == 0){
            for(int i=0;i<l_count;i++){
                int gap = 0;
                result[i] = malloc(l_len[i]);  
                strcpy(result[i], lines[i]);
                char *o_line = lines[i];  
                int s_len = strlen(argv[2]);  
                int t_len = strlen(argv[3]);  
                char *s_location = strstr(o_line, argv[2]);  
                while(s_location != NULL){
                    gap += (s_location - o_line);  
                    result[i][gap] = '\0'; 
                    l_len[i] += (t_len-s_len);  
                    result[i] = realloc(result[i],l_len[i] );
                    strcat(result[i], argv[3]);
                    gap += t_len;  
                    o_line = s_location + s_len;  
                    strcat(result[i], o_line);  
                    s_location = strstr(o_line, argv[2]);  
                }      
            }
            for(int i=0;i<l_count;i++)
                printf("%s\n",result[i]);
            }
            else{
            	printf("Usage:\n./sed [-g(optional)] [-source(required)] [-target(required)]\n");
			}
		}
		else if(argc == 3){
            for(int i=0;i<l_count;i++){
                int gap = 0;
                result[i] = malloc(l_len[i]);  
                strcpy(result[i], lines[i]);
                char *o_line = lines[i];  
                int s_len = strlen(argv[1]);  
                int t_len = strlen(argv[2]);  
                char *s_location = strstr(o_line, argv[1]);  
                
                    gap += (s_location - o_line);  
                    result[i][gap] = '\0'; 
                    l_len[i] += (t_len-s_len);  
                    result[i] = realloc(result[i],l_len[i] );
                    strcat(result[i], argv[2]);
                    o_line = s_location + s_len;  
                    strcat(result[i], o_line);  
                       
            }
            for(int i=0;i<l_count;i++)
                printf("%s\n",result[i]);   
		}
		else{
			printf("Usage:\n./sed [-g(optional)] [-source(required)] [-target(required)]\n");
		}	
}