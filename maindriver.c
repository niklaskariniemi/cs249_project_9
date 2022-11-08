// header files
#include "File_Input_Utility.h"
#include "AVL_Tree_Utility.h"

// constant definitions

const char DOUBLE_QUOTE = '"';

// prototypes
void displayNode( const AvlTreeNodeType dispPtr );
int getDataFromFile( const char *fileName, AvlTreeNodeType **rootPtr );

// main function
int main( int argc, char *argv[] )
   {
    AvlTreeNodeType *rootPtr, *cpdRootPtr;
    char fileName[ STD_STR_LEN ] = "RoomData_50B.csv";
    int numItems, treeHt;

    // set title
    printf( "\nAVL BST Test Program\n" );
    printf(   "====================\n" );

    // initialize iterator
    rootPtr = initializeTree();

    // upload data
       // function: getDataFromFile
    numItems = getDataFromFile( fileName, &rootPtr );
    printf( "File uploaded, %d items found\n", numItems );

    // show in order traversal
       // function: displayInOrder
    treeHt = findTreeHeight( rootPtr );
    printf( "\nIn order display of input tree, with height: %d: \n", treeHt );
    inOrderDisplay( rootPtr );

    printf( "\n\nCreating duplicate tree\n" );
    cpdRootPtr = copyTree( rootPtr );

    treeHt = findTreeHeight( cpdRootPtr );
    printf( "\nIn order display of copied tree, with height: %d: \n", treeHt );
    inOrderDisplay( cpdRootPtr );

    // end program

       // clear BST
          // function: clearTree
       rootPtr = clearTree( rootPtr );
       cpdRootPtr = clearTree( cpdRootPtr );

       // show program end
          // function: printf
       printf( "\n\nEnd Program\n" );

       // return success
       return 0;
   }

/*
Name: displayNode
Process: displays node data
Function input/parameters: node pointer (TreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: node data displayed
Dependencies: 
*/
void displayNode( const AvlTreeNodeType dispPtr )
   {
    printf( "Room Number: %s, Building/Room: %s, Class Setup: %s, Room Capacity: %d\n",
                       dispPtr.roomNumber, dispPtr.buildingRoom, 
                                      dispPtr.classSetup, dispPtr.roomCapacity );
   }

/*
Name: getDataFromFile
Process: uploads data from file with unknown number of data sets,
         has internal Verbose Boolean to display input operation
Function input/parameters: file name (char *)
Function output/parameters: root pointer (TreeNodeType **)
Function output/returned: number of values found (int)
Device input/file: data from HD
Device output/monitor: none
Dependencies: malloc, sizeof, openInputFile, readStringToLineEndFromFile,
              readStringToDelimiterFromFile, checkForEndOfInputFile, 
              readCharacterFromFile, readIntegerFromFile,
              insert, printf, closeInputFile, free
*/
int getDataFromFile( const char *fileName, AvlTreeNodeType **rootPtr )
   {
    char dummyStr[ MAX_STR_LEN ];
    char roomNumStr[ ROOM_NUM_CAPACITY ];
    char bldgRoomStr[ BUILDING_ROOM_CAPACITY ];
    char clsSetup[ SETUP_CAPACITY ];
    int roomCap;
    int index = 0;
    bool verbose = true;  // Set to true to verify data upload, false otherwise

    if( openInputFile( fileName ) )
       {
        if( verbose )
           {
            printf( "\n     ----- Verbose: Begin Loading Data From File\n" );
           }

        // to be ignored - buildingRoom string used as dummy
        readStringToLineEndFromFile( dummyStr ); 

        readStringToDelimiterFromFile( COMMA, roomNumStr );

        while( !checkForEndOfInputFile() )
           {
            // gets rid of first double quote
            readCharacterFromFile();

            readStringToDelimiterFromFile( DOUBLE_QUOTE, bldgRoomStr );

            // gets rid of comma
            readCharacterFromFile();

            readStringToDelimiterFromFile( COMMA, clsSetup );

            roomCap = readIntegerFromFile();

            printf( "\n%3d) Inserting %s and balancing\n", 
                                                        index + 1, roomNumStr );

            *rootPtr = insert( *rootPtr, roomNumStr, 
                                               bldgRoomStr, clsSetup, roomCap );

            if( verbose )
               {
                printf( "Room number: %s | ", roomNumStr );

                printf( "Building/Classroom: %s | ", bldgRoomStr );

                printf( "Classroom setup: %s | ", clsSetup );

                printf( "Room capacity: %d\n", roomCap );
               }

            // reprime - read next state name
            readStringToDelimiterFromFile( COMMA, roomNumStr );

            index++;
           }

        if( verbose )
           {
            printf( "\n     ----- Verbose: End Loading Data From File\n\n" );
           }

        closeInputFile();
       }

    // file not found
    else
       {
        *rootPtr = NULL;
       }

    return index;
   }

