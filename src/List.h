#ifndef _LIST_H
#define _LIST_H
#include "ListItem.h"
#include "LinkedListCompare.h"
#include "LinkedListProcessor.h"
#include <stdlib.h>
typedef struct List List ;

struct List{
    ListItem * head ;
    ListItem * tail ;
    int count ;
    ListItem * previous;
    ListItem * current ;
};

List * createList(void);
void resetCurrentListItem(List * linkedList);
ListItem *createListItem(void* data);
ListItem * getCurrentListItem(List * linkedList);
ListItem * getNextListItem(List * linkedList);
List*  listAddItemToHead(List * linkedList, void * data );
List*  listAddItemToTail(List * linkedList, void * data );
ListItem * findListItem(List * linkedList,void * listItemData,LinkedListCompare compare );
List* listAddItemToNext(List * linkedList, ListItem * listItem,void * data );
void * deleteHeadListItem(List * linkedList);
void * deleteSelectedListItem(List * linkedList,void  * listItemData,LinkedListCompare compare);
void * checkAndDeleteListItem(List * linkedList,ListItem * deleteListItem);
void listForEach(List *linkedList,LinkedListProcessor processor);

#define freeList(list)                                      \
                          do{if(list) free(list);}while(0)
#endif // _LIST_H
