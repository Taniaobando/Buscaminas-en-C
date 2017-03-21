#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct casilla{
	char tipo;// es un caracter o es un mina?
	int nuMinas;// numero de minas alrededor de la casilla
	char estado;// si esta tapada o no ?
	char etiqueta; // tiene bandera o no ?
};
	
typedef struct casilla tipoCasilla;


 int bombas(int filas, int cols, int numBom, tipoCasilla **matrix){
 	srand(time(NULL));
 	int px,py,cm; // contador de cuantas minas hay
 	for(int i=0;i<numBom;i++){

 			px = rand()%filas;
 			py = rand()%cols;
 		if ((matrix[px][py].tipo=='O') && (px>0 && px<filas-1) && (py>0 &&  py<cols-1)){
 			matrix [px][py].tipo='M';
 		}
 		else{
 			i--;
 		}

 		}
 	for(int i=1;i<filas-1;i++){	
 		for (int j=1;j<cols-1;j++){

  		if(matrix[i][j].tipo!='M') {

  			cm=0;
 			
 			if (matrix[i+1][j+1].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i+1][j].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i+1][j-1].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i-1][j+1].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i-1][j-1].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i-1][j].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i][j+1].tipo=='M'){
 				cm++;
 			}
 			if (matrix[i][j-1].tipo=='M'){
 				cm++;
 			}
 			matrix[i][j].nuMinas=cm;
 		}
 	    }
    }
}
void imprimirTablero (int filas, int cols, tipoCasilla**tablero){
	int i,j;
	for (i=1; i<filas-1; i++){
		for (j=1; j <cols-1;j++){
			if (tablero[i][j].etiqueta=='t'){
				printf(" %c |",tablero[i][j].etiqueta);
		    }
		    			
			else if((tablero[i][j].estado=='d')&&(tablero[i][j].tipo!='M')&&(tablero[i][j].etiqueta!='t')){
				printf(" %d |",tablero[i][j].nuMinas);
			}
			
			else if((tablero[i][j].tipo=='M')&&(tablero[i][j].estado=='d')){
				printf(" %c |",tablero[i][j].tipo);
			}
			else{
				printf(" %c |",tablero[i][j].estado);
			}
		}	
		printf("\n");

	}
		printf("\n____________________\n");

}
// imprime  cada pocision de la matrix filas columnas 

void JugarJuego(int filas, int cols,tipoCasilla **matrix,int numBom) {
	int px,py,gameAc=1,contE=0; //gameAC=1  esta jugando // QDque quiere hacer
	int QD;
	while (gameAc==1){
		printf ("Si Quiere destapar casilla escriba 3\nSi quiere poner bandera escriba 5\nSi quiere quitar etiqueta escriba 7\n");
		scanf("%d",&QD);
		printf ("Ingrese la fila\n");
		scanf("%d",&px);
		printf("Ingrese la columna\n");
		scanf("%d",&py);
		if (QD==7 && px>0 && px < filas-1 && py>0 &&py<cols-1){
			matrix[px][py].etiqueta='O';

		}

		if (QD==5 && px>0 && px < filas-1 && py>0 &&py<cols-1){ //asignar bandera 
				matrix[px][py].etiqueta='t'; //t quiere decir que tiene una etiqueta 
			if ((matrix[px][py].etiqueta=='t'&& matrix[px][py].tipo=='M')&&(contE<numBom)){
				contE++;
				if (numBom==contE){
					gameAc=0;
					imprimirTablero(filas,cols,matrix);
					printf("BUENA ESA GANASTE!!\n");
					break;
				}
			}
		}
		else if  (QD==3 && px>0 && px < filas-1 && py>0 &&py<cols-1){ //destapar casilla
			matrix[px][py].estado='d'; //d quiere decir que esta destapada

			if ((matrix[px][py].estado=='d')&&(matrix[px][py].tipo=='M')){
				for(int i=1;i<filas-1;i++){
					for (int j=1;j<cols-1;j++){
						if (matrix[i][j].tipo=='M'){
							matrix[i][j].estado	='d';
						}
					}
				}
				imprimirTablero(filas,cols,matrix);
				printf(" Era una mina perdiste\n");
				break;
			}
			else if ((matrix[px][py].estado==1)&&(matrix[px][py].tipo!='M')&&(matrix[px][py].nuMinas==0)){
				if (matrix[px+1][py+1].tipo=='O'){
	 				matrix[px+1][py+1].estado=1;
	 			}
	 			if (matrix[px+1][py].tipo=='O'){
	 				matrix[px+1][py].estado=1;
	 			}
	 			if (matrix[px+1][py-1].tipo=='O'){
	 				matrix[px+1][py-1].estado=1;	
	 			}
	 			if (matrix[px-1][py+1].tipo=='O'){
	 				matrix[px-1][py+1].estado=1;
	 			}
	 			if (matrix[px-1][py-1].tipo=='O'){
	 				matrix[px-1][py-1].estado=1;
	 			}
	 			if (matrix[px-1][py].tipo=='O'){
	 				matrix[px-1][py].estado=1;
	 			}
	 			if (matrix[px][py+1].tipo=='O'){
	 				matrix[px][py+1].estado=1;
	 			}
	 			if (matrix[px][py-1].tipo=='O'){
	 				matrix[px][py-1].estado=1;
	 			}
			}

		}
	imprimirTablero(filas,cols,matrix);
	
	}

}



tipoCasilla **crearTablero(int filas, int cols){
	tipoCasilla **matrix;
	matrix= (tipoCasilla **)malloc (filas*sizeof(tipoCasilla*));
	for (int i=0; i <filas; i++){
		matrix[i]= (tipoCasilla *)malloc (cols*sizeof (tipoCasilla));
		for (int j=0; j<cols;j++){
			matrix[i][j].tipo='O';
			matrix[i][j].estado = 'c';// 0 es esta tapada 
			matrix[i][j].etiqueta='n';// n quiere decir que no tiene etiqueta 
			matrix[i][j].nuMinas=0;
		}
	}
	return matrix;
}
//crea y le asigna memoria a cada pocision de la matrix  y a todas las casillas les asigna "0"




void main (){
	int IN,filas,cols,numBom;//VARIABLE NIVEL
	printf ("BIENVENIDO A MI BUSCAMINAS!!\nMENU\nINGRESE EL NIVEL DE DIFICULTAD DE LA SIGUIENTE MANERA 0 PARA PRINCIPIANTE 1 PARA MEDIO 2 PARA DIFICIL 3 PERSONALIZADO\n");
	scanf("%d",&IN);

	if(IN==0){
		 filas=10;
		 cols= 10;
		 numBom= 10;

	}else

	if(IN==1){//medio
		 filas=18;
		 cols=18;
		 numBom=40;
	}else
	if(IN==2){ // dificil
		 filas=18;
		 cols=32;
		 numBom=99;
	}else
	if (IN==3){
		printf("Escriba  la fila seguido de un enter\n");
		scanf("%d",&filas);
		printf("Escriba la columna seguido de un enter\n");
		scanf("%d",&cols);
		printf("Escriba el número de bombas seguido de un enter\n");
		scanf("%d",&numBom);
		filas=filas+2;
		cols=cols+2;
	}
	tipoCasilla **tablero;
	tablero= crearTablero(filas,cols);
	imprimirTablero(filas, cols, tablero);
	bombas(filas,cols,numBom,tablero);
	JugarJuego (filas, cols,tablero,numBom);
	


}