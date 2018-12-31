# include <stdlib.h>
# include <stdlib.h>
# include <time.h>


void addRandomWord(Code* c, int numWord){
	
	int o =  c->order;
	CodeList *code = c->code;
	short int* newWord = NULL;
	int i,t,aux,dist = 0;

	srand((unsigned)time(NULL)); //alimenta a semente

	

	for (t= 0; t <numWord; t++){	
		
		newWord = (short int*)calloc(o,sizeof(short int));

		aux = 1;

		while(aux){
		
			aux = 0;		
			
			for(i=0; i<o; i++)		//cria palavra randomica
				newWord[i] = (rand()%2);


			while(code != NULL){
				
				for(i=0; i<o; i++) //calcula  a distancia da palavra com o enésima do codico
					dist += (code->word[i] + newWord[i])%2;

				if(dist == 0 ){ // se a distancia for 0 significa q ela esta repetida
					aux = 1; // executa o laço novamente
					code = c->code;// volta ao inicio do codigo
					dist = 0;
					break;	
				}
				dist = 0;

				code = code->next; 
			}
		}	

		c->code = addListCode(c->code,newWord); // adiciona palavra ao codigo;
		c->numWord++;



	}

	calcDistMin(c); // calcula nova distancia minima

}

Code* startCode(int order){
	
	Code* c = (Code*)malloc(sizeof(Code));
	
	c->code = NULL;
	c->order = order;
	c->numWord = 0;
	c->distMin = -1;

	return c;
}

void makeCodeDistMinLimited(Code* c, int distMin, int min){
	int boolean,i;
	


		boolean = 1;

		while(boolean){
 		
		addRandomWord(c,1);

		if(c->distMin < distMin){
            removeLastWord(c);
			c->numWord--;
			boolean = 0;
		}
	

	calcDistMin(c);

}

}

void shift(int* w, int n, int x){
	int last;
	int i,t;

	for (t = 0; t < x; t++){

		last =  w[n-1];
		
		for (i = n-1; i > 0 ; i--)
			w[i] = w[i-1];
	
		w[0] = last;
	}


}

long int pow2(int n){
	if(n != 0)
		return 2*pow2(n-1);
	else
		return 1;

}

long int binaryToDec(int* word, int n){
	long int num = 0;
	int i;
	n--;

	for (i = 0; i < n; i++)
		num += word[i]*pow2(i);		

	return num;	
}
