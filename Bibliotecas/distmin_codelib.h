/* Biblioteca com funçoes de calculo de distancia de Hamming*/
# include <stdio.h>
# include <stdlib.h>


/*
void calcDistMin(Code* code){
	
	int dist = 0 ,distMin = code->order;
	int i;
	CodeList* w1 = code->code;
	CodeList* w2 = code->code;

	while(w1 != NULL){
		while(w2 != NULL){
			
			for (i = 0; i < code->order; i++)
				dist += (w1->word[i] + w2->word[i])%2;

			if(dist < distMin && dist != 0)
				distMin = dist;

			dist = 0;
			w2 = w2->next;
		}
		w2 = code->code;
		w1 = w1->next;
	}

	
	code->distMin = distMin;


}
*/


void calcDistMin(Code* code){
	
	int dist = 0 ,distMin = code->order;
	int i;
	CodeList* w1 = code->code;
	CodeList* w2 = code->code->next;

	while(w1 != NULL){
		while(w2 != NULL){
			
			for (i = 0; i < code->order; i++)
				dist += (w1->word[i] + w2->word[i])%2;

			distMin = (dist < distMin && dist != 0)?dist:distMin;

			dist = 0;
			w2 = w2->next;
		}
		w2 = w1->next;
		w1 = w1->next;
	}

	
	code->distMin = distMin;


}