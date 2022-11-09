// header files
#include "File_Input_Utility.h"
#include "AVL_Tree_Utility.h"

AvlTreeNodeType* clearTree(AvlTreeNodeType* wkgPtr)
{
    // check if current node is not null
    if ( !isEmpty( wkgPtr ) )
    {    
        // recurse left
        clearTree( wkgPtr->leftChildPtr );

        // recurse right
        clearTree( wkgPtr->rightChildPtr );

        // clear node
        free( wkgPtr );
    }

    // return cleared tree ptr
    return wkgPtr;
}

int compareRoomNumbers(const char* roomNbrOne, const char* roomNbrTwo)
{
    // initialize variables
    int diffVal, index = 0;

    // loop until find the shortest string
    while  ( roomNbrOne[ index ] != NULL_CHAR && 
                                              roomNbrTwo[ index ] != NULL_CHAR )
    {
        // find difference
        diffVal = roomNbrOne[ index ] - roomNbrTwo[ index ];
        index++;

        // check for not zero
        if ( diffVal != 0 )
        {
            // return it
            return diffVal;
        }

        // check for left is digit
        if ( isDigit( roomNbrOne[ index ] ) )
        {
            // return 1
            return 1;
        }
        // check for right is digit
        else if ( isDigit( roomNbrTwo[ index ] ) )
        {
            // return -1
            return -1;
        }
    }

    // return 0
    return 0;
}

void copyString(char* dest, const char* source)
{
    // initialize variables
    int index;
    
    // loop through string
    for ( index = 0; source[index] != '\0'; index++ )
    {
        dest[index] = source[index];
    }
}

AvlTreeNodeType* copyTree(AvlTreeNodeType* rootPtr)
{
    // initialize variables
    AvlTreeNodeType *newNode;

    // check if current node is null
    if ( isEmpty( rootPtr ) )
    {
        // create new node
        newNode = createTreeNodeFromNode( *rootPtr );

        // set left child
        copyTree( rootPtr->leftChildPtr );

        // set right child
        copyTree( rootPtr->rightChildPtr );
    }

    // return pointer to new node
    return newNode;
}

AvlTreeNodeType* createTreeNodeFromData(const char* rmNumber,
    const char* buildingRm, const char* clsSetup, int capacity)
{
    // dynamically create new node
    AvlTreeNodeType *newNode = (AvlTreeNodeType *)malloc(
                                                       sizeof(AvlTreeNodeType));

    // copy data into new node
    copyString( newNode->roomNumber, rmNumber );
    copyString( newNode->buildingRoom, buildingRm );
    copyString( newNode->classSetup, clsSetup );
    newNode->roomCapacity = capacity;

    // set child pointers to NULL
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;

    // return new node
    return newNode;
}

AvlTreeNodeType* createTreeNodeFromNode(const AvlTreeNodeType sourceNode)
{
    return createTreeNodeFromData(sourceNode.roomNumber,sourceNode.buildingRoom,
                                 sourceNode.classSetup,sourceNode.roomCapacity);
}

void displayChars(int numChars, char outChar)
{
    if ( numChars != 0 )
    {
        printf("%c", outChar );
        displayChars( numChars - 1, outChar );
    }
}

int findBalanceFactor(AvlTreeNodeType* wkgPtr)
{
    return findTreeHeight( wkgPtr->leftChildPtr ) - 
                                         findTreeHeight( wkgPtr->rightChildPtr);
}

int findMax(int one, int other)
{
    if ( one > other )
    {
        return one;
    }
    else
    {
        return other;
    }
}

int findTreeHeight(AvlTreeNodeType* wkgPtr)
{
    // initialize variables
    int leftHeight, rightHeight, maxHeight;

    // if current ptr is not NULL
    if ( !isEmpty( wkgPtr ) )
	{
	    // get height of left child
        leftHeight = findTreeHeight( wkgPtr->leftChildPtr );

	    // get height of right child
        rightHeight = findTreeHeight( wkgPtr->rightChildPtr );

	    // find max between them
        maxHeight = findMax( leftHeight, rightHeight );

	    // return max plus one
        return maxHeight + 1;
	}

    return -1;
}

AvlTreeNodeType* initializeTree()
{
    return NULL;
}

void inOrderDisplay(AvlTreeNodeType* wkgPtr)
{
    // check if current node is not null
    if ( !isEmpty( wkgPtr ) )
    {    
        // recurse left
        inOrderDisplay( wkgPtr->leftChildPtr );

        // print current node
        printf( "%s, ", wkgPtr->roomNumber );

        // recurse right
        inOrderDisplay( wkgPtr->rightChildPtr );
    }
    // print new line
    printf("\n");
}

AvlTreeNodeType* insert(AvlTreeNodeType* wkgPtr,
    char* rmNmbr, char* bldgRm, char* clsSetup, int capacity)
{
    // initialize variables
    AvlTreeNodeType *newNode;
    int comparisonVal, balanceFactor;

    // check for working pointer null
    if ( isEmpty( wkgPtr ) )
    {
        // create and return new node
        newNode = createTreeNodeFromData( rmNmbr, bldgRm, clsSetup, capacity );
    }

    // find comparison value
    comparisonVal = compareRoomNumbers( wkgPtr->roomNumber, rmNmbr );

    // check for room number less than current
    if ( comparisonVal > 0 )
    {
        // call left recursion, assign to left child pointer
        wkgPtr->leftChildPtr = insert( wkgPtr->leftChildPtr, 
           wkgPtr->leftChildPtr->roomNumber, wkgPtr->leftChildPtr->buildingRoom,
                                           wkgPtr->leftChildPtr->classSetup, 
                                           wkgPtr->leftChildPtr->roomCapacity );
    }
    // otherwise, check for room number greater than current
    else if ( comparisonVal < 0 )
    {
        // call right recursion, assign to right child pointer
        wkgPtr->rightChildPtr = insert( wkgPtr->rightChildPtr, 
         wkgPtr->rightChildPtr->roomNumber, wkgPtr->rightChildPtr->buildingRoom,
                                          wkgPtr->rightChildPtr->classSetup,
                                          wkgPtr->rightChildPtr->roomCapacity );
    }
    // otherwise, assume duplicate item found
    else
    {
        // return working pointer
        return wkgPtr;
    }
    // find balance factor
    balanceFactor = findBalanceFactor( wkgPtr );

    // check for left left case
    if ( balanceFactor > 1 && rmNmbr < wkgPtr->roomNumber )
    {
        // rotate current to the right and return
        return rotateRight( wkgPtr );
    }
    // check for right right case
    else if ( balanceFactor < -1 && rmNmbr > wkgPtr->roomNumber )
    {
        displayChars( findTreeHeight( wkgPtr ), SPACE );
        printf( "Identified: Right Right Case\n" );

        // rotate current pointer to the left and return
        return rotateLeft( wkgPtr );
    }
    // check for left right case
    else if ( balanceFactor > 1 && rmNmbr > wkgPtr->roomNumber )
    {
        // rotate current pointer's left child to the left, assign to left child
        wkgPtr->leftChildPtr = rotateLeft( wkgPtr->leftChildPtr );

        // rotate current pointer to the right and return
        return rotateRight( wkgPtr );
    }
    // check for right left case
    else if ( balanceFactor < -1 && rmNmbr < wkgPtr->roomNumber )
    {
        // rotate working pointer's right child to the right
        // assign to the righ child
        wkgPtr->rightChildPtr = rotateRight( wkgPtr->rightChildPtr );

        // rotate current pointer to the left and return
        return rotateLeft( wkgPtr );
    }

    return newNode;
}

bool isDigit(char testChar)
{
    return testChar >= '0' && testChar <= '9';
}

bool isEmpty(AvlTreeNodeType* rootPtr)
{
    return rootPtr == NULL;
}

AvlTreeNodeType* rotateLeft(AvlTreeNodeType* oldParentPtr)
{
    // initialize variables
    AvlTreeNodeType *tempPtr;

    // print output text
    printf( "- Rotating Left" );

    // set temp pointer to right child
    tempPtr = oldParentPtr->rightChildPtr;

    // set left child of right child to old parent
    oldParentPtr->rightChildPtr->leftChildPtr = oldParentPtr;

    // set right child of old parent to null
    oldParentPtr->rightChildPtr = NULL;

    // return rotated tree
    return tempPtr;
}

AvlTreeNodeType* rotateRight(AvlTreeNodeType* oldParentPtr)
{
    // initialize variables
    AvlTreeNodeType *tempPtr;

    // print output text
    printf( "- Rotating Right" );

    // set temp pointer to left child
    tempPtr = oldParentPtr->leftChildPtr;

    // set right child of left child to old parent
    oldParentPtr->leftChildPtr->rightChildPtr = oldParentPtr;

    // set left child of old parent to null
    oldParentPtr->leftChildPtr = NULL;

    // return rotated tree
    return tempPtr;
}

AvlTreeNodeType* search(AvlTreeNodeType* wkgPtr, const char* roomNumber)
{
    // check if null
    if ( isEmpty( wkgPtr ) )
    {
        // return pointer
        return NULL;
    }
    // check if search data is greater
    if ( compareRoomNumbers( roomNumber, wkgPtr->roomNumber ) > 0 )
    {
        // recurse right
        return search( wkgPtr->rightChildPtr, roomNumber );
    }
    // check if search data is smaller
    else
    {
        // recurse left
        return search( wkgPtr->leftChildPtr, roomNumber );
    }
}