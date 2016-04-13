# include <stdio.h>
# include <stdlib.h>

typedef struct List{	
	
	short int num;
	struct List *next;

}List;

typedef struct CodeList{	
	
	short int* word;
	struct CodeList *next;

}CodeList;

typedef struct Code{

	CodeList* code;
	int order;
	double numWord;
	int distMin;
	
}Code;


CodeList* addListCode(CodeList* l, short int word[]){
	if(l == NULL){
		CodeList* newnode = (CodeList*)malloc(sizeof(CodeList));

		newnode->word = word;
		newnode->next = NULL;

		return newnode;
	}
	
	l->next = addListCode(l->next,word);

	return l;
}

List* addListWord(List* l, short int num){
	if(l == NULL){
		List* newnode = (List*)malloc(sizeof(List));

		newnode->num = num;
		newnode->next = NULL;

		return newnode;
	}
	
	l->next = addListWord(l->next,num);

	return l;
}

void rmvLastWord(Code* c){
	CodeList* aux =  c->code;
	CodeList* aux_ant = NULL;


	while(aux->next!=NULL){ // caminha ate o final da lista;
		aux_ant = aux;
		aux = aux->next;
	}

	if(aux_ant != NULL){ // nao eh o primeiro
		aux_ant->next = NULL;
		free(aux);
	}

	else{ // eh o primeiro 
		free(aux);
		c->code = NULL;
	}
}




void printList(List* l){
	if(l != NULL){
		printf("[%u]",l->num );
		printList(l->next);
	}
}

double countNode(CodeList* l){
	if(l != NULL)
		return 1 + countNode(l->next);
	else
		return 0;
}

void convertListtoArray(List* l, short int array[], int i){
	if(l != NULL){

		array[i] = l->num;
		convertListtoArray(l->next,array,i+1);

	}	
}




List* freeList(List* l){
	if(l != NULL){
		List* aux;

		while(l->next != NULL){
			aux = l->next;
			free(l);
			l = aux;

		}

	return NULL;

	}

}

CodeList* freeCodeList(CodeList* l){
	if(l != NULL){
		CodeList* aux;

		while(l->next != NULL){
			aux = l->next;
			free(l);
			l = aux;

		}

	return NULL;

	}

}


	
