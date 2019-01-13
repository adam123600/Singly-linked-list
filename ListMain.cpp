// ListMain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include "global.h"
#include <stdlib.h>
#include <time.h>


#define SIZE 100
#define DEBUG


int main()
{
	LISTINFO* pInfo = (LISTINFO*)calloc( SIZE, sizeof( LISTINFO ) );
	if( !pInfo )
	{
		perror( "ERROR, MEMORY ALLOCATION LISTINFO" );
		return 0;
	}

	ListItem* pList = NULL;
	if( !( pList = MakeEmptyList() ) )
	{
		perror( "ERROR MEMORY ALLOCATION- pList ListMain.cpp" );
		return 0;
	}

	srand( (unsigned)time( NULL ) );
	
	// wypelnienie LISTINFO rand
	LISTINFO* pHelpINFO = pInfo; // pomocniczy wskaznik 
	for( int i = 0; i < SIZE; i++ )
	{
		pHelpINFO->nKey = rand() % SIZE;
		Insert( pList, pHelpINFO++ );
	}
	
#ifdef DEBUG
	////////// WYPISANIE ROZMIARU LISTY
	printf( "SIZE OF LIST: %d\n\n", SIZE );
	//////////////////////////////////////
#endif


#ifdef DEBUG
	///////////////////////////////////////
	// WYPISANIE LISTY
	PrintList( pList );
	////////////////////////////////////////
#endif

	SortList( pList, Compare );

#ifdef DEBUG
	/////////////////////////////////////
	//////////// POSORTOWANE
	printf( "SORTED:\n");
	PrintList( pList );
	////////////////////////////////////
#endif
	
	ListItem* pPrevious = NULL;
	LISTINFO* pElement = (LISTINFO*)calloc( 1, sizeof( LISTINFO ) );
	if( !pElement )
	{
		perror( "ERROR MEMORY ALLOCATION PELEMENT MAIN" );
		return 0;
	}

	pElement->nKey = rand() % SIZE;

	ListItem* searchElement = Find( pList, pElement, &pPrevious, Compare );

	if( searchElement )
		printf( "Searching element: %d.\nPreviousElement: %d.\n\n", pElement->nKey, pPrevious->pNext->pInfo->nKey ); 

	else
		printf( "Searching element: %d not exist.\n\n", pElement->nKey );
	


#ifdef DEBUG
	///////////////////////////////////////////////////
	///////// LISTA BEZ 3 PIERWSZYCH ELEMENTOW
	RemoveFront( pList );
	RemoveFront( pList );
	RemoveFront( pList );
	printf( "List without 3 first elements:\n" ); // Lista bez 3 pierwszych elementow
	PrintList( pList );
	/////////////////////////////////////////////////

	////////////////////////////////////////////////
	/////// FrontList
	printf( "FRONT LIST: %d \n\n", Front( pList )->pInfo->nKey );
	/////////////////////////////////////////////////
#endif

	FreeList( pList );

#ifdef DEBUG
	printf( "Remove element from empty list:\n" );
	RemoveFront( pList );
#endif

	free( pInfo );
	pList = NULL;
	pInfo = NULL;
	pHelpINFO = NULL;

	free( pElement );
	pElement = NULL;
	pPrevious = NULL;
	
	return 0;
}

int Compare( const void* element1, const void* element2 )
{
	if( ( (ListInfo*)element1 )->nKey < ( (ListInfo*)element2 )->nKey )
		return -1;
	else if( ( (ListInfo*)element1 )->nKey > ( (ListInfo*)element2 )->nKey )
		return 1;
	else
		return 0;

	//	-1 jesli pierwszy jest mniejszy od drugiego
	//	0 jesli rowne
	//	1 jesli pierwszy jest wiekszy od drugiego
}