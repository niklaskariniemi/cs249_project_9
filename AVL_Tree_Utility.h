#ifndef AVL_TREE_UTILITY_H
#define AVL_TREE_UTILITY_H

// Header files
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "StandardConstants.h"

// Constants

typedef enum { ROOM_NUM_CAPACITY = 10, SETUP_CAPACITY = 42, 
                                       BUILDING_ROOM_CAPACITY = 72 } Capacities;

// Data Structures

typedef struct AvlTreeNodeStruct
   {
    char roomNumber[ ROOM_NUM_CAPACITY ];

    char buildingRoom[ BUILDING_ROOM_CAPACITY ];

    char classSetup[ SETUP_CAPACITY ];

    int roomCapacity;

    struct AvlTreeNodeStruct *leftChildPtr, *rightChildPtr;
   } AvlTreeNodeType;

// Prototypes

/*
Name: clearTree
Process: recursively removes all nodes from tree and returns memory to OS,
         uses post order traversal strategy
Function input/parameters: pointer to root/ working pointer (AvlTreeNodType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free
*/
AvlTreeNodeType *clearTree( AvlTreeNodeType *wkgPtr );

/*
Name: compareRoomNumbers
Process: compares room numbers as follows:
         - if left room number is greater than the right room number, 
         returns value greater than zero (not necessarily 1)
         - if left room number is less than the right room number, 
         returns value less than zero (not necessarily -1)
         - if room numbers are equal but one is longer, longer one is greater
         - otherwise, returns zero
Function input/parameters: two room numbers (as strings)
                           to be compared (const char *)
Function output/parameters: none
Function output/returned: result as specified above (int)
Device input/---: none
Device output/---: none
Dependencies: isDigit
*/
int compareRoomNumbers( const char *roomNbrOne, const char *roomNbrTwo );

/*
Name: copyString
Process: copies string from source to destination
Function input/parameters: source string (const char *)
Function output/parameters: destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void copyString( char *dest, const char *source );

/*
Name: copyTree
Process: creates duplicate copy of given tree, allocates all new nodes,
         returns pointer to root of new tree or NULL if original tree was empty,
         uses pre order traversal strategy
Function input/parameters: tree root/working pointer (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: tree root of copied tree
                          or NULL as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
AvlTreeNodeType *copyTree( AvlTreeNodeType *rootPtr );

/*
Name: createTreeNodeFromData
Process: captures data from individual data items, 
         dynamically creates new node,
         copies data, sets child pointers to NULL,
         and returns pointer to new node         
Function input/parameters: room number, building room, 
                           and class setup (const char *), capacity (int)
Function output/parameters: none
Function output/returned: pointer to new node as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof, copyString
*/
AvlTreeNodeType *createTreeNodeFromData( const char *rmNumber, 
                   const char *buildingRm, const char *clsSetup, int capacity );

/*
Name: createTreeNodeFromNode
Process: captures data from source node pointer, dynamically creates new node,
         copies data, sets child pointers to NULL, 
         and returns pointer to new node,
         one line of code         
Function input/parameters: node to be copied (const AvlTreeNodeType)
Function output/parameters: none
Function output/returned: pointer to new node as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
AvlTreeNodeType *createTreeNodeFromNode( const AvlTreeNodeType sourceNode );

/*
Name: displayChars
Process: recursively displays a specified number of characters
Function input/parameters: number of characters (int), output character (char)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: characters displayed as specified
Dependencies: displayChars (recursively)
*/
void displayChars( int numChars, char outChar );

/*
Name: findBalanceFactor
Process: finds balance factor by subtracting
         height differences between left and right subtrees
Function input/parameters: pointer to current tree location (TreeNodeType *)
Function output/parameters: none
Function output/returned: difference between two subtree heights (int)
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
int findBalanceFactor( AvlTreeNodeType *wkgPtr );

/*
Name: findMax
Process: finds maximum between two values, returns larger
Function input/parameters: two values (int)
Function output/parameters: none
Function output/returned: larger of two values (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int findMax( int one, int other );

/*
Name: findTreeHeight
Process: recursively finds tree height from current node to bottom of tree
Function input/parameters: pointer to current tree location (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: -1 if empty tree, 0 if no subtrees,
                          max height of subtrees otherwise
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
int findTreeHeight( AvlTreeNodeType *wkgPtr );

/*
Name: initializeTree
Process: returns NULL to set tree to empty
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: none
*/
AvlTreeNodeType *initializeTree();

/*
Name: inOrderDisplay
Process: recursively iterates across tree using in order strategy,
         displays node values
Function input/parameters: pointer to current tree location (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: inOrderDisplay (recursively)
*/
void inOrderDisplay( AvlTreeNodeType *wkgPtr );

/*
Name: insert
Process: recursively finds location to insert node, inserts node,
         then follows recursion back up tree to implement balancing,
         does not allow duplicate entries
Function input/parameters: pointer to current tree location (AvlTreeNodeType *),
                           room number, building room data, class setup (char *)
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: actions displayed as function progresses
Dependencies: createDataNode, compareRoomNumbers, findBalanceFactor,
              insert (recursively), printf, rotateLeft, rotateRight
*/
AvlTreeNodeType *insert( AvlTreeNodeType *wkgPtr, 
                     char *rmNmbr, char *bldgRm, char *clsSetup, int capacity );

/*
Name: isDigit
Process: reports if character provided is a character digit
Function input/parameters: test character (char)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isDigit( char testChar );

/*
Name: isEmpty
Process: reports if tree is empty, using one line of code
Function input/parameters: pointer to current root node (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( AvlTreeNodeType *rootPtr );

/*
Name: rotateLeft
Process: conducts left rotation by manipulation of given pointer
Function input/parameters: pointer to given subtree to rotate
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: rotation action displayed  ("- Rotating Left")
Dependencies: printf
*/
AvlTreeNodeType *rotateLeft( AvlTreeNodeType *oldParentPtr );

/*
Name: rotateRight
Process: conducts right rotation by manipulation of given pointer
Function input/parameters: pointer to given subtree to rotate
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: rotation action displayed  ("- Rotating Right")
Dependencies: printf
*/
AvlTreeNodeType *rotateRight( AvlTreeNodeType *oldParentPtr );

/*
Name: search
Process: recursively searches tree for specified data using room number key
Function input/parameters: pointer to working subtree (AvlTreeNodeType *),
                           room number (const char *)
Function output/parameters: none
Function output/returned: pointer to found node (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: search (recursively)
*/
AvlTreeNodeType *search( AvlTreeNodeType *wkgPtr, const char *roomNumber );



#endif   // AVL_TREE_UTILITY_H



