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


#include "../../DataStructure/Tree/Tree.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void testTreeNew() {
    printf("Testing TreeNew... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");

    // Test valid creation
    Tree *tree = TreeNew(button, "root", NULL, attributes);

    assert(tree != NULL);
    assert(TreeGetType(tree) == button);
    assert(strcmp(TreeGetId(tree), "root") == 0);
    assert(TreeGetFirstChild(tree) == NULL);
    TreeDestroyAll(tree);


    printf("Passed!\n");
}

void testTreeAddChild() {
    printf("Testing TreeAddChild... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    Tree *parent = TreeNew(window, "parent", NULL, attributes);
    Tree *child1 = TreeNew(label, "child1", NULL, attributes);
    Tree *child2 = TreeNew(box, "child2", NULL, attributes);

    // Basic addition
    assert(TreeAddChild(parent, child1) == 1);
    assert(TreeGetFirstChild(parent) != NULL);

    // Add second child
    assert(TreeAddChild(parent, child2) == 1);

    // Invalid inputs
    assert(TreeAddChild(NULL, child1) == -1);
    assert(TreeAddChild(parent, NULL) == -1);

    TreeDestroyAll(parent);
    printf("Passed!\n");
}

void testTreeRemoveChild() {
    printf("Testing TreeRemoveChild... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    Tree *parent = TreeNew(window, "parent", NULL, attributes);
    Tree *child = TreeNew(button, "child", NULL, attributes);
    TreeAddChild(parent, child);

    // Valid removal
    assert(TreeRemoveChild(parent, "child") == 1);
    assert(TreeGetFirstChild(parent) == NULL);

    // Remove non-existent child
    assert(TreeRemoveChild(parent, "ghost") == -1);

    // Try remove non-leaf node
    Tree *parent2 = TreeNew(window, "p2", NULL, attributes);
    Tree *child2 = TreeNew(button, "c2", NULL, attributes);
    TreeAddChild(parent2, child2);
    TreeAddChild(child2, TreeNew(label, "grandchild", NULL, attributes));
    assert(TreeRemoveChild(parent2, "c2") == -1);

    TreeDestroyAll(parent);
    TreeDestroyAll(parent2);
    printf("Passed!\n");
}

void testTreeGetNode() {
    printf("Testing TreeGetNode... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    Tree *root = TreeNew(box, "root", NULL, attributes);
    Tree *child = TreeNew(button, "child", NULL, attributes);
    Tree *grandchild = TreeNew(label, "grandchild", NULL, attributes);
    
    TreeAddChild(root, child);
    TreeAddChild(child, grandchild);

    // Find root
    assert(TreeGetNode(root, "root") == root);

    // Find direct child
    assert(TreeGetNode(root, "child") == child);

    // Find grandchild
    assert(TreeGetNode(root, "grandchild") == grandchild);

    // Non-existent node
    assert(TreeGetNode(root, "invalid") == NULL);

    TreeDestroyAll(root);
    printf("Passed!\n");
}

void testTreeUpdateNode() {
    printf("Testing TreeUpdateNode... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    Tree *root = TreeNew(window, "root", NULL, attributes);
    Tree *oldNode = TreeNew(box, "old", NULL, attributes);
    Tree *newNode = TreeNew(label, "new", NULL, attributes);
    TreeAddChild(root, oldNode);

    // Basic update
    assert(TreeUpdateNode(root, "old", newNode) == 1);
    assert(TreeGetNode(root, "new") != NULL);
    assert(TreeGetNode(root, "old") == NULL);

    // Test children transfer
    Tree *parent = TreeNew(window, "parent", NULL, attributes);
    Tree *child = TreeNew(button, "child", NULL, attributes);
    TreeAddChild(child, TreeNew(label, "gc", NULL, attributes));
    TreeAddChild(parent, TreeNew(button, "to_replace", NULL, attributes));
    
    assert(TreeUpdateNode(parent, "to_replace", child) == 1);
    assert(TreeGetNode(parent, "child") != NULL);
    
    TreeDestroyAll(root);
    TreeDestroyAll(parent);
    printf("Passed!\n");
}

void testTreeDestroy() {
    printf("Testing TreeDestroy... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    // Single node destruction
    Tree *single = TreeNew(button, "single", NULL, attributes);
    TreeDestroy(single);

    // Tree destruction
    Tree *root = TreeNew(window, "root", NULL, attributes);
    TreeAddChild(root, TreeNew(button, "c1", NULL, attributes));
    TreeAddChild(root, TreeNew(label, "c2", NULL, attributes));
    TreeDestroyAll(root);

    printf("Passed!\n");
}

void testTreeIsLeaf() {
    printf("Testing TreeIsLeaf... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    Tree *leaf = TreeNew(button, "leaf", NULL, attributes);
    Tree *nonLeaf = TreeNew(window, "parent", NULL, attributes);
    TreeAddChild(nonLeaf, leaf);

    assert(TreeIsLeaf(leaf) == 1);
    assert(TreeIsLeaf(nonLeaf) == 0);
    assert(TreeIsLeaf(NULL) == -1);

    TreeDestroyAll(nonLeaf);
    printf("Passed!\n");
}

void testTreeGetParent() {
    printf("Testing TreeGetParent... ");

    HashMap *attributes = HashMapNew();
    HashMapPut(attributes, "key1", "value1");
    
    Tree *root = TreeNew(window, "root", NULL, attributes);
    Tree *child = TreeNew(button, "child", NULL, attributes);
    Tree *grandchild = TreeNew(label, "grandchild", NULL, attributes);
    
    TreeAddChild(root, child);
    TreeAddChild(child, grandchild);

    assert(TreeGetParent(root, child) == root);
    assert(TreeGetParent(root, grandchild) == child);
    assert(TreeGetParent(root, root) == NULL);

    TreeDestroyAll(root);
    printf("Passed!\n");
}

int main() {
    testTreeNew();
    testTreeAddChild();
    testTreeRemoveChild();
    testTreeGetNode();
    testTreeUpdateNode();
    testTreeDestroy();
    testTreeIsLeaf();
    testTreeGetParent();

    HashMap *hashmap = HashMapNew();
    HashMapPut(hashmap, "key-1", "value-1");

    Tree *myTree = TreeNew(window, "id-window", NULL, hashmap);
    
    Tree *child1 = TreeNew(window, "id-child1", NULL, hashmap);
    Tree *child2 = TreeNew(window, "id-child2", NULL, hashmap);
    
    TreeAddChild(myTree, child1);
    TreeAddChild(myTree, child2);

    Tree *child11 = TreeNew(window, "id-child1-1", NULL, hashmap);
    Tree *child12 = TreeNew(window, "id-child1-2", NULL, hashmap);
    Tree *child13 = TreeNew(window, "id-child1-3", NULL, hashmap);

    TreeAddChild(child1, child11);
    TreeAddChild(child1, child12);
    TreeAddChild(child1, child13);


    Tree *child111 = TreeNew(window, "id-child1-1-1", NULL, hashmap);
    Tree *child112 = TreeNew(window, "id-child1-1-2", NULL, hashmap);
    Tree *child113 = TreeNew(window, "id-child1-1-3", NULL, hashmap);

    TreeAddChild(child11, child111);
    TreeAddChild(child11, child112);
    TreeAddChild(child11, child113);

    Tree *child3 = TreeNew(window, "id-child3", NULL, hashmap);
    TreeAddChild(myTree, child3);   



    
    TreePrint(myTree, "", 1);
    printf("\n\nTesting TreePrint...  Passed!\n");

    printf("\nAll tests passed successfully!\n");
    return 0;
}