#ifndef _LINKED_LIST_H_ // _LINKED_LIST_H_가 정의되지 않은 경우에만 아래의 코드를 포함하라. 즉, 이 헤더파일이 처음 포함될 때만 아래 코드를 실행함.
#define _LINKED_LIST_H_ // _LINKED_LIST_H_를 정의함. 이렇게 하면 이 파일이 다시 포함될 때 위 코드가 거짓이 되어 두 번째 포함부터는 파일의 내용을 무시하게 됨.

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int DATA; // 원형 연결 리스트에 저장될 데이터의 타입

typedef struct node {
  DATA data;
  struct node *next; // struct node * 타입은 다음 노드의 주소를 저장할 수 있는 포인터를 의미함.
} Node;

typedef struct LL {
  Node *tail; // 리스트의 마지막 노드를 가르키는 포인터.
  Node *cur; // 현재 노드를 가리키는 포인터.
  Node *before; // 현재 노드의 이전 노드를 가리키는 포인터.
  int numData; // 리스트에 저장된 데이터의 개수.
} OList; // 원형 연결 리스트를 정의함.

typedef OList List;

// 리스트 초기화 함수
void ListInit(List *plist) {
  plist->tail = NULL;
  plist->cur = NULL;
  plist->before = NULL;
  plist->numData = 0;
}

// 리스트의 끝에 데이터를 추가하는 함수.
void ListInsert(List *plist, DATA data) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  if(newNode == NULL) {
    printf("메모리 할당 실패\n");
    return;
  }
  newNode->data = data;
  if(plist->tail == NULL) {  
    // 리스트가 비어있을 때
    plist->tail = newNode;
    newNode->next = newNode;
  } else { // 리스트가 비어있지 않을 때
    newNode->next = plist->tail->next;
    plist->tail->next = newNode;
    plist->tail = newNode;
  }
  plist->numData++;
}

// 첫 번째 데이터를 읽어오는 함수. 성공시 True를 반환하고, pdata에 데이터를 저장.
int ListFirst(List *plist, DATA *pdata)
{
  if(plist->tail == NULL)
  { return false; }
  plist->before = plist-> tail;
  plist->cur = plist->tail->next;
  *pdata = plist->cur->data;
  return true;
}

// 현재 위치에서 다음 데이터를 읽어오는 함수.
int ListNext(List *plist, DATA *pdata)
{
  if(plist->tail == NULL) {
    return false;
  }
  plist->before = plist->cur;
  plist->cur = plist->cur->next;
  *pdata = plist->cur->data;
  return true;
}

// 현재노드를 제거하는 함수. 제거된 노드의 데이터를 반환함.
DATA ListRemove(List *plist) {
  Node *rpos = plist->cur;
  DATA rdata = rpos->data;
  if(rpos == plist->tail) { 
    if(plist->tail == plist->tail->next) {
      plist->tail = NULL;
    } else {
      plist->tail = plist->before;
    }
  }
  plist->before->next = plist->cur->next;
  plist->cur = plist->before;
  free(rpos);
  plist->numData--;
  return rdata;
}

// 리스트에 저장된 데이터의 개수를 반환하는 함수.
int ListCount(List *plist) {
  return plist->numData;
}

#endif // #ifndef로 시작한 조건을 종료한다.
