#include "List.h"
#include "global.h"
#include <stdlib.h>
#include <stdio.h>



ListItem* MakeEmptyList() // tworzy pusta liste
						  // MakeEmptyList ma zrobic pusty element na poczatku
{
	ListItem* list = (ListItem*)calloc( 1, sizeof( ListItem ) );

	if( !list )
		return 0;

	return list;
}

void Insert( ListItem* pAfter, LISTINFO* pInfo ) // wrzuca gdzies po elemencie pAfter
{
   ListItem* pHelp = (ListItem*)calloc( 1, sizeof( ListItem ) );

	if( !pHelp )
	{
		perror( "ERROR MEMORY ALLOCATION INSERT" );
		printf( "\n\n" );
		return;
	}

	pHelp->pInfo = pInfo;
	pHelp->pNext = pAfter->pNext;
	pAfter->pNext = pHelp;
}

void InsertFront( ListItem* pList, LISTINFO* pInfo ) // wrzuca na poczatek ( jak na stos )
{
	Insert( pList, pInfo );
}

void Remove( ListItem* pAfter )
{
	if( !IsEmpty( pAfter ) ) 
	{
		ListItem* pHelp = pAfter->pNext;
		pAfter->pNext = pHelp->pNext;
		free( pHelp );
		//pHelp = NULL;
	}

	else
	{
		perror( "ERROR EMPTY LIST REMOVE LIST.CPP" );
		printf( "\n\n" );
		return;
	}
}

void RemoveFront( ListItem* pList ) // jak w stosie pop
{
	Remove( pList );
}

ListItem* Front( ListItem* pList ) // sprawdza co na poczatku
{
	if( IsEmpty( pList ) ) // jesli pusta
	{
		perror( "ERROR EMPTY LIST- Front" );
		printf( "\n\n" );
		return 0;
	}
	return pList->pNext;
}

void FreeList( ListItem* pList )
{
	while( !IsEmpty( pList ) ) // dopoki nie pusta
		RemoveFront( pList );
}

int IsEmpty( ListItem* pList )
{
	return !pList->pNext;
}

void SortList( ListItem* pList, pFCompare pF )
{
	ListItem* pHelp = pList;

	while( !IsEmpty( pHelp ) ) 
	{
		ListItem* pMin = pHelp;
		ListItem* pTemp = pHelp->pNext;

		while( !IsEmpty( pTemp ) ) 
		{
			if( pF( (const void*)pMin->pNext->pInfo, (const void*)pTemp->pNext->pInfo ) == 1 )
				pMin = pTemp;
			pTemp = pTemp->pNext;
		}

		if( pMin != pHelp )
		{
			pTemp = pHelp->pNext;
			pHelp->pNext = pMin->pNext;
			pMin->pNext = pMin->pNext->pNext;
			pHelp->pNext->pNext = pTemp;
		}
		pHelp = pHelp->pNext;
	}
}

ListItem* Find( ListItem* pList, const void* a, ListItem** pPrev, pFCompare pF )
{
	ListItem* pHelp = pList->pNext;
	*pPrev = pList;

	while( !IsEmpty( pHelp ) ) 
	{
		if( pF( a, ( pHelp->pNext->pInfo ) ) == 0 ) return pHelp;

		*pPrev = pHelp;
		pHelp = pHelp->pNext;
	}

	return *pPrev = NULL;
}

void PrintList( ListItem* pList )
{
	while( pList = pList->pNext )
		printf( "%d ", pList->pInfo->nKey );
	printf( "\n\n" );
}
