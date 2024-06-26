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
  if (map == NULL || map->size == map->capacity) return;
  
  long posicion = hash(key,map->capacity);
  for (long contador = 0 ; contador < map->capacity ; contador++)
  {
    if (map->buckets[posicion] == NULL || map->buckets[posicion]->key == NULL)
    {
      map->buckets[posicion] = createPair(key, value);
      map->size++;
      return;
    }
    posicion = (posicion + 1) % map->capacity;
  }
}

void enlarge(HashMap *map)
{
  enlarge_called = 1; //no borrar (testing purposes)

  if (map == NULL) return;
  
  Pair **antiguoBuckets = map->buckets;
  map->capacity *= 2;
  map->buckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);
  map->size = 0;
  for (long i = 0; i < map->capacity / 2 ; i++)
    if (antiguoBuckets[i] != NULL && antiguoBuckets[i]->key != NULL)
    {
      insertMap(map, antiguoBuckets[i]->key, antiguoBuckets[i]->value);
      free(antiguoBuckets[i]);
    }
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

  for (long i = 0 ; i < nuevoHashMap->capacity ; i++)
    nuevoHashMap->buckets[i] = NULL;

  return nuevoHashMap;
}

void eraseMap(HashMap *map,  char *key)
{
  if (map == NULL || map->size == 0) return;

  long posicion = hash(key, map->capacity);
  for (long contador = 0 ; contador < map->capacity ; contador++)
  {
    if (map->buckets[posicion] != NULL && is_equal(map->buckets[posicion]->key, key))
    {
      map->buckets[posicion]->key = NULL;
      map->buckets[posicion]->value = NULL;
      map->size--;
      return;
    }
    posicion = (posicion + 1) % map->capacity;
  }
}

Pair *searchMap(HashMap *map,  char *key)
{
  if (map == NULL || map->size == 0) return NULL;  

  long posicion =  hash(key, map->capacity);
  for (long contador = 0 ; contador < map->capacity ; contador++)
  {
    if (map->buckets[posicion] == NULL) return NULL;
    else
      if (is_equal(map->buckets[posicion]->key, key))
      {
        map->current = posicion;
        return map->buckets[posicion];
      }
    posicion = (posicion + 1) % map->capacity;
  }
  
  return NULL;
}

Pair *firstMap(HashMap *map) 
{
  if (map == NULL || map->size == 0) return NULL;

  for (long i = 0 ; i < map->capacity ; i++)
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) 
    {
      map->current = i;
      return map->buckets[i];
    }

  return NULL;
}

Pair *nextMap(HashMap *map)
{
  if (map == NULL || map->size == 0) return NULL;

  for (long i = map->current + 1 ; i < map->capacity ; i++)
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL)
    {
      map->current = i;
      return map->buckets[i];
    }

  return NULL;
}