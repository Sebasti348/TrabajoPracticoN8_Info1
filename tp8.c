#include <stdio.h>
#include <stdlib.h>
#define TAM 20

//	
int cuantas_piezas(int max) {
	int n;
	do {
		printf("Cuántas piezas ingresará? ");
		scanf("%d", &n);
	} while (n < 0 || n > max);
	return n;
}
int rectificable(float diametro, float valor) {
	if (diametro > valor)
		return 1;
	else
		return 0;
}
int rechazada(float diametro, float valor) {
	if (diametro < valor)
		return 1;
	else
		return 0;
}
void cargar_piezas(float *, int);

int contar(int (*)(float, float), float, float *, int);
float* reserva_memoria(int);
void segregar(int (*)(float, float), float, float *, int, float *);
void mostrar_piezas(char *, float *, int);

int main (void) {
	float diametros[TAM] = {0};
	int n;
	float max = 12;
	float min = 10;
	n = cuantas_piezas(TAM);
	cargar_piezas(diametros, n);
	int n_rectificar = contar(rectificable, max, diametros, n);
	float *p_rectificables = reserva_memoria(n_rectificar);
	segregar(rectificable, max, diametros, n, p_rectificables);
	int n_rechazar = contar(rechazada, min, diametros, n);
	float *p_rechazadas = reserva_memoria(n_rechazar);
	segregar(rechazada, min, diametros, n, p_rechazadas);
	
	if(n_rectificar==0)
		printf("No hay piezas para rectificar \n");
	else
		mostrar_piezas("rectificables", p_rectificables, n_rectificar);
	
	if(n_rechazar==0)
		printf("No hay piezas para rechazar \n");
	else
		mostrar_piezas("rechazadas", p_rechazadas, n_rechazar);
	
	
	return 0;
}



void cargar_piezas(float *diametros, int n){

	for(int i=0;i<n;i++) {
		do {
			printf("Ingrese Diámetro %d (> 0): ", i + 1);
			scanf("%f", diametros + i);
			if (*(diametros + i) <= 0) {
				printf("Error: El diámetro debe ser un número positivo.\n");
			}
		} while (*(diametros + i) <= 0);
	}

}

int contar(int (*func)(float , float), float limite, float *vec, int cant){
	
	int cont=0;
	for(int i=0; i<cant; i++){
		cont=cont+func(*(vec+i),limite);
	}
	return cont;
}
	
float* reserva_memoria(int cantidad){
	 float *ptr =malloc(cantidad*sizeof(float));
	if (ptr == NULL) {
		printf("Error, No se pudo asignar memoria\n");
		exit(EXIT_FAILURE); 
	}
	return ptr;
}

void segregar(int (*func)(float, float), float limite, float *vec, int cant, float *vec_carga){
	for(int i=0; i<cant; i++){
		if(func(*(vec+i),limite)){
			*(vec_carga)=*(vec+i);
			vec_carga++;
		}
	}
}

void mostrar_piezas(char *texto, float *vec,int cant){
	printf("\n____%s : %d ____\n",texto,cant);
	for(int i=0; i<cant;i++){
		printf("%.2f \n",*(vec+i));
	}
}
