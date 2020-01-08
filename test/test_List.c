#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ListItemCompare.h"
#include "LinkListCompare.h"
#include "LinkCompare.h"
NetworkNode node;
List linkList;
ListItem  itemA,itemB,itemC;
Link  linkItemDataA,linkItemDataB,linkItemDataC;
List* outList;
ListItem*outputListItem;
void setUp(void){}
void tearDown(void){}

void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
    link->previous =NULL;
}
void initListItem(ListItem * listItem, ListItem * next ,void* data){
    listItem->next = next;
    listItem->data = data;
}

void test_List_createList(void){
    outList = createList();
    //createList will malloc for List 
    TEST_ASSERT_NULL(outList->head);
    TEST_ASSERT_NULL(outList->tail);
    TEST_ASSERT_NULL(outList->current);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL_PTR(0,outList->count);
}
void test_List_resetList(void){
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initList(&linkList, &itemA ,&itemB ,0 ,&itemB);
    resetCurrentListItem(&linkList);
    //reset will reset the current back to first item
    TEST_ASSERT_EQUAL_PTR(&itemA,linkList.current);
}

void test_List_resetList_NULL(void){
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initList(&linkList, NULL ,NULL ,0 ,NULL);
    resetCurrentListItem(&linkList);
    //reset will reset the current back to first item
    TEST_ASSERT_NULL(linkList.current);
}

/*
*
*   LinkList -> itemA -> itemB -> NULL
*
*/
void test_List_getNextListItem(void){
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initList(&linkList, &itemA ,&itemB ,0 ,&itemA);//er
    //Link list with itemA as head and itemB as tail
    // getCurrentListItem will return the first listitem(listitemA)
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    // getNextListItem will return the second listitem(listitemB)
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem);
    // getNextListItem will return NULL as nextItem is empty
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);
}

/*
*
*   LinkList -> itemA -> itemB -> NULL
*
*/
void test_List_getCurrentListItem(void){
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initList(&linkList, &itemA ,&itemB ,0 ,&itemA);//er
    //Link list with itemA as head and itemB as tail
    // getCurrentListItem will return the first listitem(listitemA)
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
}

/*
*
*   LinkList -> itemA -> NULL
*
*/
void test_List_getNextListItem_second_item_is_NULL(void){
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initList(&linkList, &itemA ,&itemA ,0 ,&itemA);
    //Link list with itemA as head and tail
    // getCurrentListItem will return the first listitem(listitemA)
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    // getNextListItem will return NULL as nextItem is empty
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);
}
/*
*   LinkList -> NULL
*          ↓ add itemA
*   LinkList -> itemA -> NULL
*          ↓ add itemB
*    LinkList -> itemA -> itemB -> NULL
*
*/
void test_List_listAddItemToTail(void){
    initList(&linkList, NULL ,NULL ,0 ,NULL);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //empty linklist add itemA
    // head ,tail and current points to itemA
    // count = 1 as 1 item inside
    outList=listAddItemToTail(&linkList,&itemA);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_NULL(itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
    //linklist add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToTail(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
}

/*
*   LinkList -> itemA -> NULL
*          ↓ add itemB
*    LinkList -> itemA -> itemB -> NULL
*          ↓ add itemC
*    LinkList -> itemA -> itemB -> itemC -> NULL
*/
void test_List_listAddItemToTail_addC(void){
    initList(&linkList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linklist add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToTail(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    //linklist add itemC
    // head and current points to itemA
    // tail now points to itemC
    // count = 3 as 3 item inside
    outList=listAddItemToTail(&linkList,&itemC);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_NULL(itemC.next);
    TEST_ASSERT_EQUAL_PTR(&itemC,itemB.next);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(3,outList->count);

}

/*
*   LinkList -> itemA -> NULL
*          ↓ add itemB
*    LinkList -> itemB -> itemA -> NULL
*          ↓ add itemC
*    LinkList -> itemC -> itemB -> itemA -> NULL
*/
void test_List_listAddItemToHead(void){
    initList(&linkList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linklist add itemB
    // head points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToHead(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemA,itemB.next);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    TEST_ASSERT_NULL(itemA.next);
    //linklist add itemC
    // head points to itemC
    // count = 3 as 3 item inside
    outList=listAddItemToHead(&linkList,&itemC);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemC.next);
    TEST_ASSERT_EQUAL_PTR(&itemA,itemB.next);
    TEST_ASSERT_EQUAL(3,outList->count);
    TEST_ASSERT_NULL(itemA.next);

}

/*
*    LinkList -> itemA -> itemB -> NULL
*          ↓ delete
*   LinkList -> itemB -> NULL
*          ↓ delete
*   LinkList -> NULL
*/
void test_List_deleteListItem(void){
    initList(&linkList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //linklist with itemA and itemB
    //delete itemA
    // head and current points to itemB
    // tail points to itemB
    // count = 1 as 1 item inside
    outList=deleteHeadListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
    //linklist delete itemB
    // head and current points to NULL
    // tail now points to NULL
    // count = 0 as 0 item inside
    outList=deleteHeadListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->head);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->tail);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->current);
    TEST_ASSERT_EQUAL(0,outList->count);
}

/*
*   LinkList -> NULL
*/
void test_List_deleteListItem_NULL(void){
    initList(&linkList, NULL ,NULL ,0 ,NULL );
    //linklist delete but item has nothing
    // count = 0 as 0 item inside
    outList=deleteHeadListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->head);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->tail);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->current);
    TEST_ASSERT_EQUAL(0,outList->count);
}
/*
*    LinkList -> itemA -> itemB -> NULL
*          ↓ deleteA
*   LinkList -> itemB -> NULL
*/
void test_List_checkAndDeleteListItem_delete_firstNode(void){
    initList(&linkList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outList=checkAndDeleteListItem(&linkList,&itemA);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
}

/*
*    LinkList -> itemA -> itemB -> NULL
*          ↓ deleteB
*   LinkList -> itemB -> NULL
*/
void test_List_checkAndDeleteListItem_delete_Tail(void){
    initList(&linkList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //current must points to itemB first before check and delete
    outputListItem=getNextListItem(&linkList);
    outList=checkAndDeleteListItem(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
}

/*
*    LinkList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemB
*    LinkList -> itemC -> itemA -> NULL
*
*/
void test_List_checkAndDeleteListItem_delete_middle(void){
    initList(&linkList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);
    //current must points to itemB first before check and delete
    outputListItem=getNextListItem(&linkList);
    outList=checkAndDeleteListItem(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemC,outputListItem);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);

}
/*
*    LinkList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemB
*    LinkList -> itemC -> itemA -> NULL
*
*/
void test_List_deleteSelectedListItem_delete_middle(void){
    initList(&linkList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);

    outList=deleteSelectedListItem(&linkList,&itemB,(LinkListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemC,outputListItem);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);

}

/*
*    LinkList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemC
*    LinkList -> itemB -> itemA -> NULL
*
*/
void test_List_deleteSelectedListItem_delete_front(void){
    initList(&linkList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);

    outList=deleteSelectedListItem(&linkList,&itemC,(LinkListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);

}

/*
*    LinkList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemA
*    LinkList -> itemC -> itemB -> NULL
*
*/
void test_List_deleteSelectedListItem_delete_last(void){
    initList(&linkList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);

    outList=deleteSelectedListItem(&linkList,&itemA,(LinkListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemC,outputListItem);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);

}
