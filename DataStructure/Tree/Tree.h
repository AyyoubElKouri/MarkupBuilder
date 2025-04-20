/***************************************************************************************************
 * @file Tree.h                                                                                    *
 * @brief Defines the Tree data structure and its operations                                       *
 *                                                                                                 *
 * @author Ayyoub EL KOURI                                                                         *
 * @date 2025-04-19                                                                                *
 * @version 1.0                                                                                    *
 *                                                                                                 *
 * @copyright Copyright (c) 2025, Ayyoub EL KOURI                                                  *
 *                                                                                                 *
 * @see Tree.c                                                                                     *
 **************************************************************************************************/

#ifndef TREE_H
#define TREE_H

#include <gtk/gtk.h>
#include "../HashMap/HashMap.h"
#include "../../Utils/Enums.h"

typedef struct Tree Tree;

/**
 * @brief Creates a new Tree instance
 * 
 * @return Tree* A pointer to the newly created Tree, or NULL if allocation fails
 */
Tree *TreeNew(const widgetType type, const char *id, GtkWidget *widget, HashMap *attributes);


/**
 * @brief Adds a child node to a parent tree
 * 
 * @param parent The parent tree to which the child will be added
 * @param child The child tree to be added to the parent
 * @return 1 on successful addition, -1 on failure
 */
int TreeAddChild(Tree *parent, Tree *child);


/**
 * @brief Removes a specific child node from a parent tree by its identifier
 * 
 * @param parent The parent tree from which the child node will be removed
 * @param id The identifier of the child node to remove
 * @return 1 on successful removal, -1 on failure or if child node not found
 */
int TreeRemoveChild(Tree *parent, const char *id);


/**
 * @brief Retrieves a specific child node from a parent tree by its identifier
 * 
 * @param parent The parent tree to search within
 * @param id The identifier of the child node to retrieve
 * @return Tree* A pointer to the found child node, or NULL if no matching node is found
 */
Tree *TreeGetNode(Tree *parent, const char *id);


/**
 * @brief Updates a specific node in the tree with a new child node
 * 
 * @param root The root of the tree to search within
 * @param id The identifier of the node to be updated
 * @param newChild The new child node to replace the existing node
 * @return 1 on success, -1 on failure, (if newChild has children, the old will be replaced)
 */
int TreeUpdateNode(Tree *root , char *id, Tree *newChild);


/**
 * @brief Frees all memory associated with a Tree (not including the children)
 * 
 * @param tree The Tree to be destroyed and deallocated
 */
void TreeDestroy(Tree *tree);


/**
 * @brief Recursively frees all memory associated with a Tree, including its children
 * 
 * @param tree The Tree to be destroyed, including all of its child nodes
 */
void TreeDestroyAll(Tree *tree);


/**
 * @brief Checks if a given tree node is a leaf node
 * 
 * @param tree The tree node to check
 * @return 1 if the node is a leaf (has no children), 0 iff it has children, -1 if any error occurs
 */
int TreeIsLeaf(const Tree *tree);


/**
 * @brief Prints a tree structure to the console in a visual format.
 *
 * @param tree    Pointer to the Tree node to print (must not be NULL).
 * @param prefix  String used for indentation (use "" at the root level).
 * @param isLast  Set to 1 if the node is the last child, 0 otherwise.
 */
void TreePrint(const Tree *tree, const char *prefix, int isLast);


/**
 * @brief Finds the parent node of a given tree node within a root tree
 * 
 * @param root The root tree to search within
 * @param tree The tree node whose parent is to be found
 * @return Tree* A pointer to the parent node, or NULL if no parent is found
 */
Tree *TreeGetParent(Tree *root , const Tree *tree);


/**
 * @brief Retrieves the type of a given tree node
 * 
 * @param tree The tree node whose type is to be retrieved
 * @return widgetType The type of the tree node
 */
widgetType TreeGetType(const Tree *tree);



/**
 * @brief Retrieves the unique identifier of a given tree node
 * 
 * @param tree The tree node whose identifier is to be retrieved
 * @return const char* A pointer to the string containing the node's unique identifier
 */
const char *TreeGetId(const Tree *tree);



/**
 * @brief Retrieves the list of children for a given tree node
 * 
 * @param tree The tree node whose children list is to be retrieved
 * @return A pointer to the first child, or NULL if no children exist
 * 
 * @warning This function is used only for unit testing
 */
struct ChildNode *TreeGetFirstChild(const Tree *tree);

#endif // TREE_H