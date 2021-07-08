//
//  main.c
//  listaEnlazadaSimple


#include <stdio.h>
#include <ctype.h>
#include "listaEnlazadaSimple.h"

int main(int argc, const char * argv[])
{
	char menu[] = "Listas enlazadas:\n A) Crear lista aleatoria\n B) ANadir al principio\n C) ANadir al final\n D) Insertar en posicion por indice\n E) Devolver valor en posicion por índice\n F) Eliminar al principio\n G) Eliminar al final\n H) Eliminar en posicion por indice\n I) Crear lista ordenada\n J) Mostrar lista\n K) Liberar listas\n L) Escribir lista en el fichero\n M) Cargar lista de fichero\n Q) Salir\n";
    ListaEnlazada raiz,raizOrdenada;
	tipoNodoRef aux;
	int indice,i;
    char opcion;
    char nombreFichero[25] = "Textot.txt";
    char nombreFicheroLectura[25] = "lectura.txt";
	tipoInfo temp=1234,
				temp2 = 4321;
	   
    crearVacia(&raiz);
	crearVacia(&raizOrdenada);
	
    do {
        system("cls");
		printf("%s ",menu);
        printf("Introduce opcion: ");
        scanf("%c%*c",&opcion);
		opcion = toupper(opcion);
		switch (opcion) {
			case 'A':
                printf("\nIntroduce el numero de nodos: ");
                scanf("%d%*c", &i);
                printf("\nAhora la cargo con valores aleatorios: %d\n",
                       crearListaValoresAleatorios(&raiz, i));
                break;
			case 'B':
				printf("\n\nInsertando nodo comienzo: %d", insertarNodoComienzo(&raiz, &temp));
				break;
			case 'C':
				//printf("\n\nInsertando nodo final: %d", insertarDespuesDeNodo(&raiz, NULL, &temp2));
                //Comentar la linea anterior, y descomentar la siguiente en cuanto ya tenga implementada
                //la función inertarNodoFinal.
                printf("\n\nInsertando nodo final: %d", insertarNodoFinal(&raiz, &temp2));
				break;
			case 'D':
				printf("\nIntroduce una posicion como entero: ");
                scanf("%d%*c", &indice);
                
                insertarNodoPosicionIndice(&raiz, indice, &temp2);
                
                //En cuanto tenga implementada la función insertarNodoPosicionIndice debe
                //descomentar la línea anterior y comentar las restantes líneas de este case.
                //Utilizar comentarios adecuadamente para ir probando cada función según se van
                //implementando
               /* aux = raiz;
                i=0;
                while (aux != NULL && i++ < indice) {
                    aux = aux->sig;
                }
                if (aux != NULL) {
                    //printf("\n\nInsertando nodo antes: %d",insertarAntesDeNodo(&raiz, aux, &temp));
                    printf("\n\nInsertando nodo despues: %d",insertarDespuesDeNodo(&raiz, aux, &temp2));
                }*/
                break;
            case 'E':
                printf("\nIntroduce una posicion como entero: ");
                scanf("%d%*c", &indice);
                
                printf("\nEl valor almacendo en la posicion %d es %d\n", indice,devolverInfoPosicionIndice(raiz, indice));
                break;
            case 'F':
				printf("\n\nEliminando nodo comienzo: %d", eliminarNodoComienzo(&raiz));
				break;
			case 'G':
				printf("\n\nEliminando nodo final: %d", eliminarNodoFinal(&raiz));
				break;
			case 'H':
                printf("\nIntroduce una posicion como entero: ");
                scanf("%d%*c", &indice);
                printf("\n\nEliminando nodo: %d",eliminarNodoPosicionIndice(&raiz, indice));
                //                aux = raiz;
                //                i=0;
                //                while (aux != NULL && i++ < indice) {
                //                    aux = aux->sig;
                //                }
                //                if (aux != NULL)
                //                    printf("\n\Eliminando nodo: %d",eliminarNodo(&raiz, aux));
                break;

            case 'I':
                printf("\n\nCreando raizOrdenada...\n\n");
                while (!estaVacia(raiz)) {
                    insertarOrdenada(&raizOrdenada, &raiz->info);
                    eliminarNodoComienzo(&raiz);
                }
                printf("\n\nAhora raizOrdenada contiene los elementos ordenados. raiz esta vacia.\n\n");
                break;
            case 'J':
                printf("Mostrando lista raiz: %d\n",mostrarListaEnlazada(raiz));
                printf("Mostrando lista raizOrdenada: %d\n",mostrarListaEnlazada(raizOrdenada));
                break;
            case 'Q':
				printf("\n\nSaliendo.\n\n");
				break;
            case 'K':
                printf("Liberacion raiz: %d\n",liberarListaEnlazada(&raiz));
                printf("Liberacion raiz Ordenada: %d\n",liberarListaEnlazada(&raizOrdenada));
                break;
            case 'L':
            	printf("Guardando lista en el el fichero...\n");
            	if(guardarListaEnlazadaTexto(raiz, nombreFichero)==0)
            	{
            		printf("--Guardado con exito---\n");
				}
				else
				{
					printf("--Error al guardar---\n");
				}
				break;
			case 'M':
				printf ("Leyendo lista almacenada en el fichero: %s\n", nombreFicheroLectura);
				if((cargarListaEnlazadaTexto (&raiz, nombreFicheroLectura))<0)
				{
					printf("--Error al leer---\n");
				}
				else
					printf("--Leido con exito---\n");
				break;
            default:
				printf("\n\nOpcion incorrecta!\a\n\n");
				break;
		}
        printf("\nPulse enter...");
        getchar();
	} while ('Q' != opcion);
	printf("\n\nTerminacion normal del programa.\n\n");
    return 0;
}


