#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingresar_usuario.h"
#include "arbol.h"
#include "jugador.h"
#include <conio.h>
#include "gotoxy.h"
#include "titulos.h"

Usuario ingresar_usuario(Usuario ingresando)
{
    char caracter; ///donde voy a almacenar los caracteres leidos por la funcion getch
    int i=0;
    dibujarCuadro(41,11,73,13);
    gotoxy(42,12);
    printf("NOMBRE DEL USUARIO");
    fflush(stdin);
    dibujarCuadro(42,13,71,15);
    gotoxy(43,14);
    gets(ingresando.name);
    dibujarCuadro(41,15,73,17);
    gotoxy(42,16);
    printf("CONTRASEÑA DEL USUARIO:  ");
    dibujarCuadro(42,17,71,19);
    gotoxy(43,18);
    fflush(stdin);
    while(caracter = getch())///el bucle se rompe cuando se toca enter(su codico ASCII es 13)
    {
        if(caracter == 13)
        {
            ingresando.password[i]= '\0'; ///guardo el caracter nulo, me indica el final de una cadena
            break;
        }
        else if (caracter == 8)///el ASCII de la tecla borrar es 8
        {
            if(i>0) ///para que no me borre de mas
            {
                i--;///muevo el indice hacia atras
                printf("\b \b");///me mueve el cursor hacia la izquierda
            }
        }
        else
        {
            printf("*");///por cada caracter que ingreso me imprime un *
            ingresando.password[i]=caracter;
            i++;///para que el siguiente caracter se ingrese en la posicion siguiente
        }
    }
    return ingresando;
}

int validar_ingreso(nodoArbol* arbol, Usuario ingresando)
{
    int rta;

    if(((strcmpi("admin",ingresando.name)) == 0) && ((strcmpi("091218",ingresando.password)) == 0))
    {
        rta = 100;
    }
    else
    {
        if(arbol != NULL)
        {
            if(((strcmpi(arbol->player.alias,ingresando.name)) == 0) && ((strcmpi(arbol->player.password,ingresando.password)) == 0))
            {
                rta = 1;
            }
            else
            {
                if((strcmpi(ingresando.name, arbol->player.alias)) > 0)
                {
                    rta = validar_ingreso(arbol->der,ingresando);
                }
                else
                {
                    rta = validar_ingreso(arbol->izq,ingresando);
                }
            }
        }
    }
    return rta;
}
