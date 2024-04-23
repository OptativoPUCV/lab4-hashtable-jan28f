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


void insertMap(HashMap * map, char * key, void * value)
{
  
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


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {
    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }

    return NULL;
}


Pair * nextMap(HashMap * map)
{
  if (map->buckets == NULL) return NULL;
  
  Pair *dato = map->buckets[map->current + 1];
  map->current = map->current + 1;

  return dato;
}

