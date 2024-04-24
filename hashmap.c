#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

/*
2.- Implemente la función void insertMap(HashMap * map, char * key, void * value). Esta función inserta un nuevo dato (key,value) en el mapa y actualiza el índice current a esa posición. Recuerde que para insertar un par (clave,valor) debe:

a - Aplicar la función hash a la clave para obtener la posición donde debería insertar el nuevo par

b - Si la casilla se encuentra ocupada, avance hasta una casilla disponible (método de resolución de colisiones). Una casilla disponible es una casilla nula, pero también una que tenga un par inválido (key==NULL).

c - Ingrese el par en la casilla que encontró.

No inserte claves repetidas. Recuerde que el arreglo es circular. Recuerde actualizar la variable size.
*/
void insertMap(HashMap * map, char * key, void * value)
{
  if (map == NULL || map->size == map->capacity) return;
  
  long posicion = hash(key,map->capacity);
  if (map->buckets[posicion] == NULL || map->buckets[posicion]->key == NULL)
  {
    map->buckets[posicion] = createPair(key, value);
    map->size++;
    map->current = posicion;
  }
  else
  {
    while (map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL)
      {
        posicion = (posicion + 1) % map->capacity;
      }
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity)
{
  HashMap *nuevoHashMap = (HashMap *)malloc(sizeof(HashMap));
  if (nuevoHashMap == NULL) exit(EXIT_FAILURE);
  nuevoHashMap->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);
  if (nuevoHashMap->buckets == NULL) exit(EXIT_FAILURE);
  
  nuevoHashMap->capacity = capacity;
  nuevoHashMap->size = 0;
  nuevoHashMap->current = -1;

  for (long i = 0 ; i < nuevoHashMap->size ; i++)
    nuevoHashMap->buckets[i] = NULL;

  return nuevoHashMap;
}

void eraseMap(HashMap * map,  char * key)
{
  if (map == NULL || map->size == 0) return;

  long posicion = hash(key, map->capacity);
  if (map->buckets[posicion] == NULL)
  {
    map->buckets[posicion]->key = NULL;
    map->buckets[posicion]->value = NULL;
    map->size--;
  }
  else
    nextMap(map);
}

Pair * searchMap(HashMap * map,  char * key)
{   
  
  
  return NULL;
}

Pair *firstMap(HashMap *map) 
{
  if (map == NULL || map->size == 0) return NULL;

  for (long i = 0 ; i < map->capacity ; i++)
    if (map->buckets[i] != NULL) 
    {
      map->current = i + 1;
      return map->buckets[i];
    }

  return NULL;
}

Pair *nextMap(HashMap *map)
{
  if (map == NULL || map->size == 0) return NULL;

  for (long i = map->current + 1 ; i < map->capacity ; i++)
    if (map->buckets[i] != NULL)
    {
      map->current = i;
      return map->buckets[i];
    }

  return NULL;
}