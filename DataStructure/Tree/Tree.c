/***************************************************************************************************
 * @file Tree.c                                                                                    *
 * @brief The implementation of the Tree data structure                                            *
 *                                                                                                 *
 * @author Ayyoub EL KOURI                                                                         *
 * @date 2025-04-19                                                                                *
 * @version 1.0                                                                                    *
 *                                                                                                 *
 * @copyright Copyright (c) 2025, Ayyoub EL KOURI                                                  *
 *                                                                                                 *
 * @see Tree.h                                                                                     *
 **************************************************************************************************/

#include "Tree.h"

/**
 * @brief Represents a tree structure for GUI elements with associated metadata
 *
 * This structure defines a tree node containing type, identifier, widget, attributes,
 * and child nodes for building hierarchical graphical interfaces.
 */
struct Tree
{
    widgetType type;            ///< The type of the tree element (e.g., button, label, etc.)
    char *id;                   ///< A unique identifier for the tree element (the widget)
    GtkWidget *widget;          ///< The GTK widget associated with this tree element
    HashMap *attributes;        ///< A HashMap containing additional properties or metadata
    struct ChildNode *children; ///< Pointer to child nodes in the tree structure
};


/**
 * @brief Represents a node in a tree data structure
 *
 * A Node contains a pointer to a Tree, and left and right child nodes,
 * enabling the creation of a hierarchical tree-like structure.
 */
struct ChildNode
{
    Tree *child;            ///< Pointer to the Tree data associated with this node
    struct ChildNode *next; ///< Pointer to the next node in the linked list
};




Tree *TreeNew(const widgetType type, const char *id, GtkWidget *widget, HashMap *attributes)
{
    // Allocate memory for the Tree structure
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if(!tree) return NULL;

    // Initialize the Tree structure
    tree->type = type;
    tree->id = g_strdup(id);
    tree->widget = widget;
    
    // Copy the HashMap attributes
    tree->attributes = HashMapGetCopy(attributes);
    if(!tree->attributes)
    {
        free(tree);
        return NULL;
    }

    // Initialize the child nodes
    tree->children = NULL;

    return tree;
}




int TreeAddChild(Tree *parent, Tree *child)
{
    // Check the input parameters
    if(!parent || !child) return -1;

    // Traverse the child nodes list to find the last one
    struct ChildNode *lastChild = parent->children;
    while(lastChild && lastChild->next) lastChild = lastChild->next;

    // Create a new child node and add it to the list
    struct ChildNode *newChild = (struct ChildNode *)malloc(sizeof(struct ChildNode));
    if(!newChild) return -1;

    newChild->child = child;
    newChild->next = NULL;

    // Add the new child node to the list
    if(lastChild) lastChild->next = newChild;
    else parent->children = newChild;

    return 1;
}




int TreeRemoveChild(Tree *parent, const char *id) {
    // Check the input parameters
    if (!parent || !id) return -1;

    struct ChildNode *curr = parent->children;
    struct ChildNode *prev = NULL;

    // Traverse the child nodes list to find the node with the specified identifier
    while (curr) {
        if (strcmp(curr->child->id, id) == 0) {
            Tree *child = curr->child;

            // Check if the child node has children
            if (!TreeIsLeaf(child)) {
                return -1;
            }

            // Remove the child node from the parent's children list
            if (prev) {
                prev->next = curr->next;
            } else {
                parent->children = curr->next;
            }

            // Free the memory allocated for the
            free(curr);
            TreeDestroy(child);

            return 1;
        }
        prev = curr;
        curr = curr->next;
    }

    // Node with the specified identifier not found
    return -1;
}




Tree *TreeGetNode(Tree *parent, const char *id)
{
    // Check the input parameters
    if(!parent || !id) return NULL;

    // Check if the parent node is the search target
    if(strcmp(parent->id, id) == 0) return parent;

    Tree *node = NULL;

    // Traverse the child nodes list to find the node with the specified identifier
    struct ChildNode *curr = parent->children;
    while(curr)
    {
        if(strcmp(curr->child->id, id) == 0) return curr->child;
        node = TreeGetNode(curr->child, id);
        if(node) return node;
        curr = curr->next;
    }

    return NULL;
}




int TreeUpdateNode(Tree *root, char *id, Tree *newChild)
{
    // Check the input parameters
    if(!root || !id || !newChild) return -1;

    // Get the node with the specified identifier
    Tree *node = TreeGetNode(root, id);
    if(!node) return -1;

    // Update the node with the new child
    g_free(node->id); node->id = g_strdup(newChild->id);
    node->widget = newChild->widget;

    if(node->attributes) HashMapFree(node->attributes);
    node->attributes = HashMapGetCopy(newChild->attributes);

    if(newChild->children)
    {
        // Free the old children nodes
        struct ChildNode *curr = node->children;
        while(curr)
        {
            struct ChildNode *next = curr->next;
            TreeDestroy(curr->child);
            free(curr);
            curr = next;
        }
        node->children = newChild->children;
        newChild->children = NULL;
    }

    return 1;
}




void TreeDestroy(Tree *tree)
{
    // Check the input parameter
    if(!tree) return;

    // Free the attributes HashMap
    if(tree->attributes) HashMapFree(tree->attributes);
    
    g_free(tree->id);
    g_free(tree);
}




void TreeDestroyAll(Tree *tree)
{
    // Check the input parameter
    if(!tree) return;

    // Save the children nodes
    struct ChildNode *curr = tree->children;

    // Destroy the children nodes
    while(curr)
    {
        // Save the next node
        struct ChildNode *next = curr->next;

        TreeDestroyAll(curr->child);
        free(curr);

        curr = next;
    }

    // Destroy the current node
    TreeDestroy(tree);
}




int TreeIsLeaf(const Tree *tree)
{
    // Check the input parameter
    if(!tree) return -1;

    // Check if the tree has any children
    return (tree->children == NULL) ? 1 : 0;
}




void TreePrint(const Tree *tree, int depth)
{
    // Check the input parameter
    if(!tree) return;

    // Print the indentation
    for(int index = 0 ; index < depth ; index++) printf("  ");

    // Print the tree structure
    printf("%s\n", tree->id);

    struct ChildNode *curr = tree->children;
    while(curr)
    {
        TreePrint(curr->child, depth + 1);
        curr = curr->next;
    }
}




Tree *TreeGetParent(Tree *root, const Tree *tree)
{
    // Check the input parameters
    if (!root || !tree) return NULL;

    // Traverse all children of the current node
    struct ChildNode *curr = root->children;
    while (curr)
    {
        // If the current child is the target node, return the parent node
        if (curr->child == tree)
            return root;

        // Recursively check the descendants of the current child node
        Tree *parent = TreeGetParent(curr->child, tree);
        if (parent) return parent; // If found, return the parent

        curr = curr->next; // Move to the next child
    }

    return NULL; // Parent not found
}




widgetType TreeGetType(const Tree *tree)
{
    // Check the input parameter
    if(!tree) return -1;

    return tree->type;
}




const char *TreeGetId(const Tree *tree)
{
    // Check the input parameter
    if(!tree) return NULL;

    return tree->id;
}




struct ChildNode *TreeGetFirstChild(const Tree *tree)
{
    // Check the input parameter
    if(!tree) return NULL;

    return tree->children;
}