//#pragma once
#ifndef LIST
#define LIST
#include "global.h"

typedef struct tagListItem
{
	LISTINFO* pInfo;
	tagListItem* pNext;

}ListItem;

int IsEmpty( ListItem* pList ); // zwraca 1 jak pusta
void InsertFront( ListItem* pList, LISTINFO* pInfo ); // wrzuca na poczatek ( jak na stos )
void Insert( ListItem* pList, LISTINFO* pInfo ); // wrzuca gdzies po elemencie pAfter
void Remove( ListItem* pAfter );
void RemoveFront( ListItem* pList ); // jak w stosie pop
void FreeList( ListItem* pList );


typedef int( __cdecl* pFCompare )( const void* element1, const void* element2 );	// wskaznik do funkcji Compare

ListItem* MakeEmptyList(); // tworzy pusta liste, Ma zrobic pusty element na poczatku
ListItem* Front( ListItem* pList ); // sprawdza co na poczatku
ListItem* Find( ListItem* pList, const void* a, ListItem** pPrev, pFCompare pF );


void SortList( ListItem* pList, pFCompare pF );
int Compare( const void* element1, const void* element2 ); // definicja w ListMain.cpp
void PrintList( ListItem* pList );

#endif