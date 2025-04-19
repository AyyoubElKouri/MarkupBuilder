/***************************************************************************************************
 * @file HashMap.h                                                                                 *
 * @brief Defines the HashMap data structure and its operations                                    *
 *                                                                                                 *
 * @author Ayyoub EL KOURI                                                                         *
 * @date 2025-04-19                                                                                *
 * @version 1.0                                                                                    *
 *                                                                                                 *
 * @copyright Copyright (c) 2025, Ayyoub EL KOURI                                                  *
 *                                                                                                 *
 * @see HashMap.c                                                                                  *
 **************************************************************************************************/

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMap HashMap;

/**
 * @brief Creates a new, empty HashMap
 * 
 * Allocates memory for a new HashMap and initializes its size to 0 and head to NULL
 * 
 * @return A pointer to the newly created HashMap, or NULL if memory allocation fails
 */
HashMap *HashMapNew();


/**
 * @brief Adds a key-value pair to the HashMap
 * 
 * Inserts a new key-value pair into the HashMap. If the key already exists,
 * the value is updated.
 * 
 * @param map Pointer to the HashMap
 * @param key Key to be inserted or updated
 * @param value Value associated with the key
 * @return 1 if successful, 0 if key already exists (value updated), -1 if an error occurs
 */
int HashMapPut(HashMap *map, const char *key, const char *value);


/**
 * @brief Retrieves the value associated with a given key in the HashMap
 * 
 * Searches the HashMap for the specified key and returns its corresponding value.
 * 
 * @param map Pointer to the HashMap to search
 * @param key Key to look up in the HashMap
 * @return The value associated with the key, or NULL if the key is not found
 */
char *HashMapGet(const HashMap *map, const char *key);


/**
 * @brief Removes a key-value pair from the HashMap
 * 
 * Searches for and removes the specified key and its associated value from the HashMap.
 * If the key is not found, no action is taken.
 * 
 * @param map Pointer to the HashMap
 * @param key Key to be removed from the HashMap
 * @return 1 if the key was found and removed, 0 if the key was not found or -1 if an error occurs
 */
int HashMapRemove(HashMap *map, char *key);


/**
 * @brief Checks if a key exists in the HashMap
 * 
 * Determines whether the specified key is present in the HashMap.
 * 
 * @param map Pointer to the HashMap to search
 * @param key Key to check for existence in the HashMap
 * @return 1 if the key is found, 0 if the key is not found, -1 if an error occurs
 */
int HashMapContainsKey(const HashMap *map, const char *key);


/**
 * @brief Checks if a value exists in the HashMap
 * 
 * Determines whether the specified value is present in the HashMap.
 * 
 * @param map Pointer to the HashMap to search
 * @param value Value to check for existence in the HashMap
 * @return 1 if the value is found, 0 if the value is not found, -1 if an error occurs
 */
int HashMapContainsValue(const HashMap *map, const char *value);


/**
 * @brief Returns the number of key-value pairs in the HashMap
 * 
 * Calculates and returns the total count of entries currently stored in the HashMap.
 * 
 * @param map Pointer to the HashMap to count entries
 * @return The number of key-value pairs in the HashMap
 */
int HashMapSize(const HashMap *map);


/**
 * @brief Frees all memory associated with the HashMap
 * 
 * Deallocates the memory used by the HashMap, including all key-value pairs
 * and internal data structures. After calling this function, the HashMap
 * pointer should not be used again.
 * 
 * @param map Pointer to the HashMap to be freed
 */
void HashMapFree(HashMap *map);


/**
 * @brief Prints the contents of the HashMap
 * 
 * Outputs all key-value pairs currently stored in the HashMap to the console.
 * Useful for debugging and inspecting the current state of the HashMap.
 * 
 * @param map Pointer to the HashMap to be printed
 */
void HashMapPrint(const HashMap *map);


/**
 * @brief Creates a deep copy of the HashMap
 * 
 * Allocates a new HashMap and copies all key-value pairs from the source HashMap.
 * The returned HashMap is a completely independent copy of the original.
 * 
 * @param hashMap Pointer to the source HashMap to be copied
 * @return A new HashMap with the same contents as the source, or NULL if copying fails
 */
HashMap *HashMapGetCopy(const HashMap *hashMap);


#endif // HASHMAP_H