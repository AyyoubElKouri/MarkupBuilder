/***************************************************************************************************
 * @file HashMap.c                                                                                 *
 * @brief The implementation of the HashMap data structure                                         *
 *                                                                                                 *
 * @author Ayyoub EL KOURI                                                                         *
 * @date 2025-04-19                                                                                *
 * @version 1.0                                                                                    *
 *                                                                                                 *
 * @copyright Copyright (c) 2025, Ayyoub EL KOURI                                                  *
 *                                                                                                 *
 * @see HashMap.h                                                                                  *
 **************************************************************************************************/

#include "HashMap.h"

/**
 * @brief Represents a HashMap data structure
 * 
 * This structure defines a HashMap with a size and a pointer to the first node
 * 
 * @param size The current number of elements in the HashMap
 * @param head Pointer to the first node in the HashMap's linked list
 */
struct HashMap {
    int size;
    struct Node *head;
};


/**
 * @brief Represents a node in the HashMap's linked list
 * 
 * This structure defines a single node containing a key-value pair
 * and a pointer to the next node in the list
 * 
 * @param key A dynamically allocated string representing the node's key
 * @param value A dynamically allocated string representing the node's value
 * @param next Pointer to the next node in the linked list
 */
struct Node
{
    char *key;
    char *value;
    struct Node *next;
};




HashMap *HashMapNew()
{
    // Allocate memory for the HashMap
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if(!map) return NULL;

    // Initialize the HashMap's size and head pointer
    map->size = 0;
    map->head = NULL;

    return map;
}




int HashMapPut(HashMap *map, const char *key, const char *value)
{
    // Check the input parameters
    if(!map || !key || !value) return -1;

    // Check if the key already exists in the HashMap
    if(HashMapContainsKey(map, key))
    {
        // If the key exists, update the value and return 0
        struct Node *current = map->head;
        while(current)
        {
            if(strcmp(current->key, key) == 0)
            {
                free(current->value);
                current->value = (char *)malloc(strlen(value) + 1);
                if(!current->value) return -1;
                strcpy(current->value, value);
                return 0;
            }
            current = current->next;
        }
    }

    // Allocate memory for the new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if(!newNode) return -1;

    // Allocate memory for the key and value strings
    newNode->key = (char *)malloc(strlen(key) + 1);
    if(!newNode->key){
        free(newNode);
        return -1;
    }

    newNode->value = (char *)malloc(strlen(value) + 1);
    if(!newNode->value) 
    {
        free(newNode->key);
        free(newNode);
        return -1;
    }

    // Copy the key and value strings into the new node
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    
    // Insert the new node at the beginning of the linked list
    newNode->next = map->head;
    map->head = newNode;
    map->size++;

    return 1;
}




char *HashMapGet(const HashMap *map, const char *key)
{
    // Check the input parameters
    if(!map || !key) return NULL;

    // Traverse the linked list to find the node with the specified key
    struct Node *current = map->head;
    while(current)
    {
        if(strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}




int HashMapRemove(HashMap *map, char *key)
{
    // Check the input parameters
    if(!map || !key) return -1;

    // Traverse the linked list to find the node with the specified key
    struct Node *current = map->head;
    
    // Check if the key is in the first node
    if(strcmp(current->key, key) == 0)
    {
        // Remove the first node
        map->head = current->next;
        free(current->key);
        free(current->value);
        free(current);
        map->size--;
        return 1;
    }

    // Traverse the linked list to find the node with the specified key
    while(current->next)
    {
        if(strcmp(current->next->key, key) == 0)
        {
            // Remove the node
            struct Node *temp = current->next;
            current->next = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            map->size--;
            return 1;
        }
        current = current->next;
    }

    return 0;
}




int HashMapContainsKey(const HashMap *map, const char *key)
{
    // Check the input parameters
    if(!map || !key) return -1;

    // Traverse the linked list to find the node with the specified key
    struct Node *current = map->head;
    while(current)
    {
        if(strcmp(current->key, key) == 0) return 1;
        current = current->next;
    }

    return 0;
}




int HashMapContainsValue(const HashMap *map, const char *value)
{
    // Check the input parameters
    if(!map || !value) return -1;

    // Traverse the linked list to find the node with the specified value
    struct Node *current = map->head;
    while(current)
    {
        if(strcmp(current->value, value) == 0) return 1;
        current = current->next;
    }

    return 0;
}




int HashMapSize(const HashMap *map)
{
    // Check the input parameters
    if(!map) return -1;

    return map->size;
}




void HashMapFree(HashMap *map)
{
    // Check the input parameters
    if(!map) return;

    // Traverse the linked list and free the memory for each node
    struct Node *current = map->head;
    while(current)
    {
        struct Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }

    // Free the memory for the HashMap
    free(map);
}




void HashMapPrint(const HashMap *map)
{
    // Check the input parameters
    if(!map) return;

    // Print the HashMap
    printf("\n-------------------------------------\n");
    printf("The current state of the HashMap is :\n");
    printf("-------------------------------------\n");

    // if the HashMap is empty
    if(map->size == 0){
        printf("The HashMap is empty\n");
        printf("-------------------------------------\n");
        return;
    } 

    // Traverse the linked list and print the key-value pairs
    struct Node *current = map->head;
    while(current)
    {
        printf("Key: %s, Value: %s\n", current->key, current->value);
        current = current->next;
    }
    printf("-------------------------------------\n");
}