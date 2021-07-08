//
//  listaEnlazadaSimple.c
//  listaEnlazadaSimple


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaEnlazadaSimple.h"

/*
 * Función presentada en clase de teoría
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
crearVacia(ListaEnlazadaRef raiz)
{
	*raiz = NULL;
	return 0;
}

/*
 * Función presentada en clase de teoría
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
estaVacia(ListaEnlazada raiz)
{
	if(raiz==NULL)
		return 1;
	else
		return 0;
}

/*
 * Función presentada en clase de teoría
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
tipoNodoRef
creaNodo(tipoInfoRef info)
{
	tipoNodoRef nuevo;
	
	if ((nuevo = malloc(sizeof(tipoNodo)))==NULL)
	{
		printf("Error en la reserva de memoria\n");
		return NULL;
	}
	nuevo->info = *info;
	nuevo->sig = NULL;
	return nuevo;
}

/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
insertarDespuesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info)
{
	tipoNodoRef nuevo;
	tipoNodoRef aux;
	
	if((nuevo = creaNodo(info))==NULL)
	{
		printf("Error en la reserva de memoria\n");
		return -1;
	}

	if (estaVacia(*raiz))
	{
		*raiz = nuevo;
		
	}else if (pos == NULL)
	{
		aux = *raiz;
		while (aux->sig != NULL)
		{
			aux = aux->sig;
		}
		aux->sig = nuevo;
		
		return 0;
	}else 
	{
		aux = *raiz;
		while (aux != pos && aux != NULL)
		{
			aux = aux->sig;
		}
		if (aux != NULL)
		{
			nuevo->sig = aux->sig;
			aux->sig = nuevo;
		}
		else
			return -2;
	}
	return 0;
}


/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
insertarAntesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info)
{
	tipoNodoRef nuevo, ant;
	// Se crea el nodo a insertar 
	if ((nuevo = creaNodo(info))==NULL)
	{
		printf("Error en la reserva de memoria\n");
		return -1;
	}
	// Si la lista est� vacia, la posicion dada est� a NULL o pos es la primera posicion => se inseta antes del primer nodo
	if (estaVacia(*raiz) || pos == NULL || pos == *raiz)
	{
		nuevo->sig = *raiz;
		*raiz = nuevo;
	}
	else
	{
		ant = *raiz;
		while (ant->sig != pos && ant != NULL)
		{
			ant = ant->sig;
		}
		if(ant->sig == pos)
		{
			nuevo->sig = pos->sig;
			pos->sig = nuevo;
		}
		else
		{
			free(nuevo);
			return -2;
		}
	}
	return 0;
}



/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
insertarNodoComienzo(ListaEnlazadaRef raiz, tipoInfoRef info)
{
	return(insertarAntesDeNodo(raiz, *raiz, info));
}

/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
insertarNodoFinal(ListaEnlazadaRef raiz, tipoInfoRef info)
{
	/*tipoNodoRef aux;
	aux = *raiz;
	while (aux->sig != NULL)
		aux = aux->sig;*/
	return (insertarDespuesDeNodo(raiz, NULL, info));
}

/*
 * Esta función recibe una lista (por referencia), un índice entero y una
 * variable de tipoInfo por referencia. Debe insertar un nuevo nodo
 * en la posición indicada por el índice entero (implica recorrido contando
 * nodos hasta el valor indicado por indice). Ojo, hay que garantizar que 
 * esa posición existe, es decir, que si la lista tiene 5 nodos, (los numeramos
 * de 0 a 4), las posiciones válidas son 0, 1, 2, 3, 4, 5 (la posición 5
 * es equivalente a añadir al final).
 * Si la posición no existe, no se puede hacer la inserción (en nuestro ejemplo,
 * la posición -1 ya no existe, y la posición 6 tampoco).
 * Se puede hacer uso de alguna de las funciones implementadas, aunque implique 
 * ineficiencias (recorridos adicionales de la lista enlazada). Opcional 
 * escribir una versión eficiente que no implique repetir recorridos.
 */
int
insertarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice, tipoInfoRef info)
{
	tipoNodoRef nuevo, aux;
	int contador = 0;
	if(estaVacia(*raiz))
	{
		printf("Error: la lista esta vacia\n");
		return -1;
	}
	if (indice < 0)
	{
		printf("Error: el indice es negativo\n");
		return -2;
	}
	aux = *raiz;
	while(aux != NULL && contador != indice)
	{
		aux = aux->sig;
		contador++;
	}
	if(aux != NULL)
	{
		insertarAntesDeNodo(raiz, aux, info);
		return 0;
	}
	else
	{
		printf("Error: la posicion introducida no se corresponde con ningun elemento de la lista\n");
		return -3;
	}
}


/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
eliminarNodo(ListaEnlazadaRef raiz, tipoNodoRef pos)
{
	tipoNodoRef ant;
	
	// Si la lista esta vacia
	if (estaVacia(*raiz))
	{
		printf("Error: la lista ya estaba vacia\n");
		return -1;
	}
	// Si la posicion dada esta a NULL
	if (pos == NULL)
	{
		printf("Error: la posici�n introducida es incorrecta(NULL)\n");
		return -2;
	}
	else
	{
		// Si es el primer nodo de la lista
		if (pos == *raiz)
		{
			*raiz = pos->sig;
			free(pos);
			return 0;
		}
		// Se recorre la lista
		ant = *raiz;
		while(ant->sig != pos && ant != NULL)
		{
			ant = ant->sig;
		}
		// Si se encuentra en el medio de la lista o es el ultimo nodo
		if(ant != NULL)
		{
			ant->sig = pos->sig;
			free(pos);
			return 0;
		}
		// Si la posicion del nodo no se corresponde con ningun elemento de la lista
		else
		{
			printf("La posicion introducida no se corresponde con ningun elemento de la lista\n");
			return -3;
		}
	}
}


/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
eliminarNodoComienzo(ListaEnlazadaRef raiz)
{
	return (eliminarNodoPosicionIndice(raiz, 0));
}


/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
eliminarNodoFinal(ListaEnlazadaRef raiz)
{
	tipoNodoRef aux;
	int final = 0;
	aux = *raiz;
	while (aux->sig != NULL)
	{
		aux = aux->sig;
		final++;
	}
	return (eliminarNodoPosicionIndice(raiz, final));
}

/*
 * Esta función recibe una lista (por referencia) y un índice entero
 * Debe eliminar el nodo situado en en la posición indicada por el
 * índice entero (implica recorrido contando nodos hasta el valor
 * indicado por indice). Ojo, hay que garantizar que
 * esa posición existe, es decir, que si la lista tiene 5 nodos (los numeramos
 * de 0 a 4), las posiciones válidas son 0, 1, 2, 3, 4.
 * Si la posición no existe, no se puede hacer la eliminación (en nuestro ejemplo,
 * la posición -1 ya no existe, y la posición 5 tampoco).
 * Se puede hacer uso de alguna de las funciones implementadas, aunque 
 * implique ineficiencias (recorridos adicionales de la lista enlazada). 
 * Opcional escribir una versión eficiente que no implique repetir recorridos.
 */
int
eliminarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice)
{
	tipoNodoRef aux;
	int contador = 0;
	if(estaVacia(*raiz))
	{
		printf("Error: la lista ya estaba vacia\n");
		return -1;
	}
	if(indice < 0)
	{
		printf("Error: el indice es negativo\n");
		return -2;
	}
	aux = *raiz;
	while (aux != NULL && contador != indice)
	{
		aux = aux->sig;
		contador++;
	}
	if (aux != NULL)
	{
		eliminarNodo(raiz, aux);
		return 0;
	}
	else
	{
		printf("Error: El indice se pasa de rango\n");
		return -3;
	}
}



/*
 * Función presentada en clase de teoría. Se debe implementar
 * la última versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
liberarListaEnlazada(ListaEnlazadaRef raiz)
{
	tipoNodoRef aux, liberar;
	if (estaVacia(*raiz))
	{
		printf("La lista enlazada ya esta vacia\n");
		return -1;
	}
	aux = *raiz;
	while (aux->sig != NULL)
	{
		liberar = aux;
		aux = aux->sig;
		free(liberar);
	}
	*raiz = NULL;
	return 0;
}


/********************************************************************
 *                                                                  *
 * Las cuatro funciones que vienen a continuación dependen de cómo  *
 * está definido el tipo de dato tipoInfo. No es lo mismo mostrar   *
 * por pantalla el contenido de los datos almacenados en una lista  *
 * enlazada si éste es de tipo entero, o si se trata de un registro.*
 * Adicionalmente, y para que el alumno no pierda el tiempo         *
 * en implementar funciones que aportan poco desde un punto de vista*
 * docente, se proporcionan ya implementadas las funciones          *
 * mostrarListaEnlazada() y crearListaValoresAleatorios(). Las otras*
 * dos son sencillas y se dejan al alumno su implementación.        *
 *                                                                  *
 *******************************************************************/

/*
 * Esta función recibe una lista (por referencia) y un índice entero
 * Debe devolver la información almacenada en el nodo situado en la 
 * posición indicada por el índice entero (implica recorrido contando nodos 
 * hasta el valor indicado por indice). Ojo, hay que garantizar que
 * esa posición existe, es decir, que si la lista tiene 5 nodos (los numeramos
 * de 0 a 4), las posiciones válidas son 0, 1, 2, 3, 4.
 * Si la posición no existe, no se puede devolver nada (en nuestro ejemplo,
 * la posición -1 ya no existe, y la posición 5 tampoco).
 * IMPORTANTE: tipoInfo es, en este caso particular, un entero. Aunque
 * la dependencia es pequeña, si existe. ¿Cómo se devuelve el código de error
 * en caso de no existir la posición indicada por el parámetro indice?. Si 
 * tipoInfo es un int es sencillo, si es un registro también, pero ya es
 * diferente implementación.
 */
tipoInfo
devolverInfoPosicionIndice(ListaEnlazada raiz, int indice)
{
	tipoNodoRef aux;
	int cont  = 0;
	if (raiz == NULL)
	{
		printf("Error: La lista esta vacia\n");
		return -1;
	}
	if(indice < 0)
	{
		printf("Error: indice negativo\n");
		return -2;
	}
	aux = raiz;
	while(aux != NULL && indice != cont)
	{
		aux = aux->sig;
		cont++;
	}
	if(aux != NULL)
	{
		return aux->info;
	}
	else
	{
		printf("Error: el indice introducido no se corresponde con ningun relemento de la lista\n");
		return -3;
	}
}


/*
 * Función presentada en clase de teoría. Se debe implementar
 * la versión presentada en clase y disponible en las diapositivas.
 * Todos los aspectos sobre funcionamiento y valor a devolver
 * están descritos en las diapositivas
 */
int
insertarOrdenada(ListaEnlazadaRef raiz, tipoInfoRef info)
{
	tipoNodoRef aux;
	aux = *raiz;
	if(estaVacia(*raiz) || aux->info > *info)
	{
		return insertarNodoComienzo(raiz, info);
	}
	else
	{
		aux = *raiz;
		while (aux->sig != NULL && aux->sig->info < *info)
			aux = aux->sig;
		return insertarDespuesDeNodo(raiz, aux, info);
	}
}

int
mostrarListaEnlazada(ListaEnlazada raiz)
{
	tipoNodoRef aImprimir;
	int res = 0,i = 0;
	
	printf("\n\n");
	printf("%-14s%-10s\n","  Posición", "Valor");
	printf("%-14s%-10s\n","  ==========", "======");


	aImprimir = raiz;
	while (aImprimir != NULL) {
		printf("\t%3d)\t%7d\n",i++, aImprimir->info);
		aImprimir = aImprimir->sig;
	}
	return res;
}


int
crearListaValoresAleatorios(ListaEnlazadaRef raiz, int numNodos)
{
	int i;
	tipoInfo temp;
	
	if (estaVacia(*raiz)) {
		srand(time(NULL));
		for (i = 0; i < numNodos; i++) {
            temp = rand()%10000;
            //insertarDespuesDeNodo(raiz, NULL, &temp);
            //insertarAntesDeNodo(raiz, NULL, &temp);
            //insertarNodoFinal(raiz, &temp);
			insertarNodoComienzo(raiz, &temp);
		}
		return 0;
	}
	return -1;
}

int guardarListaEnlazadaTexto(ListaEnlazada raiz, char *nombreFichero)
{
	FILE *pt;
	tipoNodoRef aux;
	if(raiz == NULL)
	{
		printf("Error: la lista esta vacia\n");
		return -2;
	}
	else
	{
		if((pt = fopen(nombreFichero, "w+"))==NULL)
		{
			return -1;
		}
		fprintf(pt, "Lista enlazada:\n");
		aux = raiz;
		while(aux != NULL)
		{
			fprintf(pt, "%-4d\n", aux->info);
			aux = aux->sig;
		}
		fclose(pt);
		return 0;
	}
}



int cargarListaEnlazadaTexto (ListaEnlazadaRef raiz, char *nombreFichero)
{
	FILE *pt;
	tipoNodoRef aux, nuevo, ant;
	char num[28];
	int *numero;
	if((pt = fopen(nombreFichero, "r"))==NULL)
	{
		printf("Error: en la apertura del fichero\n");
		return -1;
	}
	*raiz = NULL;
	while((fscanf(pt, "%[^\n]%*c", num))!=EOF)
	{
		*numero = atoi(num);
		if((nuevo = creaNodo(numero))==NULL)
		{
			return -2;
		}
		if(*raiz == NULL) // Si se inserta como el primero de la lista
		{
			*raiz = nuevo;
		}
		else
		{
			aux = *raiz;
			ant = NULL;
			while (aux->sig != NULL && *numero > aux->info)
			{
				ant = aux;
				aux = aux->sig;
			}
			if(ant == NULL && nuevo->info < aux->info) // Se inserta en la primera posicion
			{
				nuevo->sig = aux;
				*raiz = nuevo;
			}
			else if(aux->sig == NULL && nuevo->info > aux->info) // Se inserta al final
	   		{
	   			aux->sig = nuevo;
			}
			else// Se inserta en el medio
			{
				ant->sig = nuevo;
				nuevo->sig = aux;
			}
		}
	}
	return 0;
}













