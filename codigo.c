# include <stdio.h>
# include <stdlib.h>
# include "Bibliotecas/read_save_codelib.h"
# include "Bibliotecas/addword_codelib.h"

int main(){

	Code* codigo;
	char name[20] = {"Codigo/a.txt"};
	int num = 3000,dist,ordem = 100;

	printf("Ordem:\n");
	scanf("%d", &ordem);

	printf("Numero de palavras:\n");
	scanf("%d", &num);


	codigo = startCode(ordem);
	addRandomWord(codigo,num);
	showCode(codigo);
	// saveCode(codigo);



return EXIT_SUCCESS;
}
