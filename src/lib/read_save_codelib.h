/* Biblioteca com as funções de leitura e armazenamento do cidigo*/ 

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "List.h"
# include "distmin_codelib.h"
# include "time.h"

/* Essa função vai ler o txt e retornar uma martriz com o codigo */
/* inicialmente ela passa para uma lista encadeda pois nao é conhecido o numero de palavras do codigo */
Code* readCode(char name[]){

	FILE * file = NULL;
	char line[20];
	char ch ;
	int i;
    short int* word_vet = NULL;

    List* word_list = NULL;
    CodeList* code_list = NULL;

    //tenta abrir o arquivo
    file = fopen(("%s",name),"r");
    
    Code* c = (Code*)malloc(sizeof(Code));

    //verifica se o arquivo foi encontrado
    if(file == NULL){
        c->code = NULL;
        return c;
    }
   

    while( (fscanf(file,"%s",line)) != EOF){ // pega string por string

        if(!strcmp(line,"SOF")){              // compara com SOF    
            //encontrou o inicio da leitura
            break;
        }
    }

    while( (fscanf(file,"%s",line)) != EOF){

        if(!strcmp(line,"EOF")){              // compara com EOF    
            break;
        }


        i = 0;
        
        while(line[i] != '\0'){
            word_list = addListWord(word_list,line[i]-48);
            i++;
        }
        
        word_vet = (short int*)calloc(i,sizeof(short int));

        
        convertListtoArray(word_list,word_vet,0);
        
        code_list = addListCode(code_list,word_vet);

        word_list = freeList(word_list);
    }   
    
    c->order = i;
    c->length = countNode(code_list);
    c->code = code_list;
    calcDistMin(c);

    return c;
}

void showCode(Code* code){
    CodeList* c = code->code;
    int i;

    for (i = 0; i < code->order; i++)
        printf("-");
    printf("--\n");

    while(c != NULL){
        printf("[");
        for (i = 0; i < code->order; i++){
            printf("%u", c->word[i] );
        }
        printf("]\n");
        c = c->next;
    }
    
    for (i = 0; i < code->order; i++)
        printf("-");
    printf("--\n\n");

    printf("\nCodigo:\n-----------------------\n");

    printf("Ordem:              [%d]\n",code->order);
    printf("Numero de palavras: [%0.0lf]\n",code->length);
    printf("Distancia Minima:   [%d]\n", code->minimum_hamming_distance);

    printf("-----------------------\n\n");

}

void saveCode(Code* c){
    int i;

    char name[20];
    char num[4];
    int ramdom; 

    srand((unsigned)time(NULL)); //alimenta a semente

    ramdom = rand()%1000;

    sprintf(name,"Code %d",ramdom);

    system("cd Codigo");


    FILE* file;

    file = fopen(("%s",name),"w");

    fprintf(file, "SOF\n");

    CodeList* code = c->code;

    while(code != NULL){

        for (i = 0; i < c->order; i++){
            fprintf(file, "%u",code->word[i]);
        }
        fprintf(file,"\n");

        code = code->next;

    }
    fprintf(file,"EOF");

    fclose(file);

    strcat(name,"_Doc");

    file = fopen(("%s",name),"w");

    fprintf(file,"Codigo:\n-----------------------\n");
    fprintf(file,"Ordem:              [%d]\n",c->order);
    fprintf(file,"Numero de palavras: [%0.0lf]\n",c->length);
    fprintf(file,"Distancia Minima:   [%d]\n", c->minimum_hamming_distance);
    fprintf(file,"-----------------------\n\n");

    fclose(file);

}

