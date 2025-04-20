/***************************************************************************************************
 * @file HashMapTest.c                                                                             *
 * @brief The unit tests for the HashMap data structure                                            *
 *                                                                                                 *
 * @author Ayyoub EL KOURI                                                                         *
 * @date 2025-04-19                                                                                *
 * @version 1.0                                                                                    *
 *                                                                                                 *
 * @copyright Copyright (c) 2025, Ayyoub EL KOURI                                                  *
 *                                                                                                 *
 * @see HashMap.h                                                                                  *
 **************************************************************************************************/


#include "../../../DataStructure/HashMap/HashMap.h"
#include <assert.h>
#include <string.h>

void test_creation_and_deletion() {
    HashMap* map = HashMapNew();
    assert(map != NULL);
    assert(HashMapSize(map) == 0);
    HashMapFree(map);
    printf("Creation/deletion test passed!\n");
}

void test_put_and_get() {
    HashMap* map = HashMapNew();
    
    // Insert test
    assert(HashMapPut(map, "key1", "value1") == 1);
    assert(HashMapPut(map, NULL, "value2") == -1);
    assert(HashMapSize(map) == 1);
    
    // Retrieve test
    char* val = HashMapGet(map, "key1");
    assert(strcmp(val, "value1") == 0);
    
    // Update test
    assert(HashMapPut(map, "key1", "new_value") == 0);
    assert(strcmp(val, "new_value") == 0);
    
    HashMapFree(map);
    printf("Put/get test passed!\n");
}

void test_remove() {
    HashMap* map = HashMapNew();
    HashMapPut(map, "key1", "value1");
    HashMapPut(map, "key2", "value2");
    
    assert(HashMapRemove(map, "key1") == 1);
    assert(HashMapSize(map) == 1);
    assert(HashMapGet(map, "key1") == NULL);
    
    assert(HashMapRemove(map, "nonexistent") == 0);
    
    HashMapFree(map);
    printf("Remove test passed!\n");
}

void test_contains() {
    HashMap* map = HashMapNew();
    HashMapPut(map, "key1", "value1");
    
    assert(HashMapContainsKey(map, "key1") == 1);
    assert(HashMapContainsValue(map, "value1") == 1);
    
    assert(HashMapContainsKey(map, "nonexistent") == 0);
    assert(HashMapContainsValue(map, "nonexistent") == 0);
    
    HashMapFree(map);
    printf("Contains test passed!\n");
}

void test_edge_cases() {
    // Test NULL parameters
    assert(HashMapPut(NULL, "key", "value") == -1);
    assert(HashMapGet(NULL, "key") == NULL);
    assert(HashMapRemove(NULL, "key") == -1);
    assert(HashMapContainsKey(NULL, "key") == -1);
    assert(HashMapContainsValue(NULL, "value") == -1);
    assert(HashMapSize(NULL) == -1);
    
    HashMap* map = HashMapNew();
    assert(HashMapPut(map, NULL, "value") == -1);
    assert(HashMapPut(map, "key", NULL) == -1);
    assert(HashMapGet(map, NULL) == NULL);
    assert(HashMapRemove(map, NULL) == -1);
    assert(HashMapContainsKey(map, NULL) == -1);
    assert(HashMapContainsValue(map, NULL) == -1);
    
    HashMapFree(map);
    printf("Edge cases test passed!\n");
}

int main() {
    test_creation_and_deletion();
    test_put_and_get();
    test_remove();
    test_contains();
    test_edge_cases();

    HashMap *hashmap = HashMapNew();
    HashMapPut(hashmap, "key-1", "value-1");
    HashMapPut(hashmap, "key-2", "value-2");
    HashMapPut(hashmap, "key-3", "value-3");
    HashMapPut(hashmap, "key-4", "value-4");

    HashMapPrint(hashmap);
    printf("\n\nprint test passed!\n");
    
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}