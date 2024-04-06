#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>     //Foi utilizada a constante HUGE_VAL, a qual representa valor INFINITO POSITIVO
#include <windows.h>

//MANIPULAÇÃO DE ARQUIVO
FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        exit(-1);
    }
    return arq;
}


void carregarCidades(FILE * arq, char city[][30]) { //Retira as informações do arquivo e aloca na matriz 
     int i;
	 char total[30]; 
		
	 fscanf(arq, " %30[^\n]s" , total);

     for ( i=0; i<30; i++) { 

		fscanf(arq, " %30[^\n]s" , city[i]);
    }
}


void matriz(FILE * arquivo, float d[][30]){
	int i, j;
     for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            if (fscanf(arquivo, "%f;", &d[i][j]) != 1){
				printf("erro");
			}
		}
     }
}


//FUNÇÕES
void escolher(char c[][30], int *inicio, int *final, int *precedente){
    //Escolhe a cidade inicial e o destino final
    int i;
    
    for ( i=0; i<10; i++) { 
        printf("\n%s\t\t", c[i]);
		printf("%s\t\t",c[i+10]);
		printf("%s",c[i+20]);
    }

	printf("\n\nEscolha a cidade de origem:");
	scanf("%d", inicio);
	while ((*inicio < 0) || (*inicio > 29)){
		printf("\nCidade não existente. Digite um número válido:\n");
		scanf("%d", inicio);
	}

	printf("\nEscolha a cidade de destino:");
	scanf("%d", final);
	while ((*final < 0) || (*final > 29) || (*final == *inicio)){
		
		printf("\nCidade não existente. Digite um número válido:\n");
		scanf("%d", final);
	}  
    *precedente = *inicio; 
}


void dadosIniciais(int inicio, int a[30], int f[30], float caminho[30], int predecessores[30]){ 
    //Adiciona os dados nos vetores correspondentes à cidade de origem
    int i; 

    for(i=0; i<30; i++){
        a[i] = 0;
        f[i] = 1;
        predecessores[i] = -1;   //-1 para não gerar ambiguidadeo.
        caminho[i] = HUGE_VAL;   // O HUGE_VAL disponibiliza um valor alto para garantir que haverá uma comparação.
    }
    caminho[inicio] = 0;   
}


void adjacencia(char municipios[][30], float d[][30]){
	float caminho[30];
    int predecessores[30], aberto[30], fechado[30];
    int origem, destino, anterior, i, parada;
    float menorCaminho, caminhoParalelo;
   
    escolher (municipios, &origem, &destino, &anterior); //anterior recebe o valor da origem (city)
	
    dadosIniciais(anterior, aberto, fechado, caminho, predecessores);

    while ((aberto[destino] != 1) ){ 
        menorCaminho = HUGE_VAL;
        parada = -1;

        for ( i = 0; i < 30; i++) {
            if ((aberto[i] == 0)  && (caminho[i] < menorCaminho)) {
                parada = i;
                menorCaminho = caminho[i];
            }
        }

        if (parada == -1) {
                break; 
            }
        
        aberto[parada] = 1;

         for (i = 0; i < 30; i++) {

            if ((d[parada][i] > 0) && (fechado[i] == 1)) {         
                caminhoParalelo = caminho[parada] + d[parada][i];
                
                if ((caminhoParalelo > 0) && (caminhoParalelo < caminho[i])) {
                    caminho[i] = caminhoParalelo;
                    predecessores[i] = parada;
                }
            }
        }
        fechado[parada]  = 0;
    }


    printf("\n\nO menor caminho entre a cidade %s e a cidade %s é: %.2f\n", municipios[origem], municipios[destino], caminho[destino]);
    
    printf("\nPassando pelas seguintes cidades (Predecessores): ");
    i = destino;
    while( i!=origem){        
		printf("%d\t",predecessores[i]);
        i = predecessores[i];
    }printf("\n\n");  

	system("pause");	
}


int main(){
    SetConsoleOutputCP(65001);
    char cidades[30][30];
    float distancia[30][30];
        	
    FILE * arquivo;

	arquivo = abrirArquivo("entrada_30_cidades.txt", "r");
	carregarCidades(arquivo, cidades);
	matriz(arquivo, distancia);
    fclose(arquivo);
	
    adjacencia(cidades, distancia);
  
    return 0;
}