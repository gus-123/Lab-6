/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

//연결 리스트의 노드 구조를 구조체로 정의
typedef struct Node {
	int key;
	struct Node* link;
} listNode;
//리스트 시작을 나타내는 Head 노드를 구조체로 정의
typedef struct Head {
	struct Node* first;
}headNode;


//함수 리스트
headNode* initialize(headNode* h); //메모리 할당 초기화 함수
int freeList(headNode* h);  //메모리 해제 함수

int insertFirst(headNode* h, int key);  //연결 리스트의 첫 번째 노드 삽입 함수
int insertNode(headNode* h, int key);   //연결 리스트의 중간 노드 삽입 함수
int insertLast(headNode* h, int key);   //연결 리스트의 마지막 노드 삽입 함수

int deleteFirst(headNode* h);  //연결 리스트의 첫 번째 노드 삭제 함수
int deleteNode(headNode* h, int key);  //연결 리스트의 중간 노드 삭제 함수
int deleteLast(headNode* h);  //연결 리스트의 마지막 노드 삭제 함수
int invertList(headNode* h); //연결 리스트의 노드 순서를 역순으로 바꾸는 함수

void printList(headNode* h); //연결 리스트를 순서대로 출력하는 함수

int main()
{
	char command;
	printf("[----- [김현민]  [2018038088] -----]\n");
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	//headNode가 공백이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(h != NULL)
		freeList(h);

	//headNode에 대한 메모리를 할당하여 다시 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;  //p는 head가 가리키는 노드를 할당

	listNode* prev = NULL;  //prev 노드를 초기화
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);  //prev의 메모리 할당 해제
	}
	free(h); //h의 메모리 할당 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 node 동적 메모리 할당
	node->key = key; //node의 데이터필드에 key 저장

	node->link = h->first; //node의 link는 head를 참조
	h->first = node; //head의 link가 node를 참조하도록 함

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h,int key) {
	listNode* preNode = h->first; //head가 가리키는 노드를 할당
    listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 node 동적 메모리 할당
	node->key = key; //node의 데이터필드에 key 저장

    node->link = NULL;  //node의 link는 null을 할당하여 연결을 해제

    if (h->first == NULL) { //head 노드가 null인 경우
        h->first = node;  //head 노드가 node를 참조
    }
    else { //head 노드가 null이 아닌 경우
		if (node->key < h->first->key) { //삽입할 위치가 맨 앞인 경우
			node->link = h->first->link;  //head는 head의 다음 노드를 참조하도록 함
            h->first->link = node;  //head의 link가 다음 노드를 참조하도록 함
        }
        else {
            while (preNode->link) { //preNode 노드의 link인 경우
				if (node->key < preNode->link->key) {  //삽입할 위치 찾기
					break;
				}
                preNode = preNode->link; //preNode는 preNode의 다음 노드를 할당
            }
            node->link = preNode->link;  //node의 link가 preNode의 다음 노드를 참조하도록 함
            preNode->link = node; //preNode의 link가 node를 참조하도록 함
        }
    }

    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* temp;  //연결리스트의 마지막 노드를 찾아서 참조하기 위해 노드를 할당
	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 node 동적 메모리 할당
	node->key = key; //node의 데이터필드에 key 저장
    
	node->link = NULL;  //node의 link는 null을 할당하여 연결을 해제

	if(h->first == NULL) {  //head 노드가 null인 경우
		h->first = node;  //head 노드가 node를 참조

		return 0;
	}
	
	temp = h->first;  //temp 노드가 head를 참조
	while(temp->link != NULL) {  //temp 노드의 link가 null이 아닌 경우
		temp = temp->link;  //temp는 temp의 다음 노드를 참조하도록 함
	}
	temp->link = node;  //temp의 link가 node를 참조하도록함

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp; //temp는 head가 가리키는 노드를 할당
	
	if(h->first== NULL) { //head 노드가 공백인 경우 리턴

		return 0;
	}
	else { //head 노드가 공백이 아닌 경우
		temp = h->first;
		h->first = h->first->link;  //head는 head의 다음 노드를 참조 함 
	}
	free(temp); //temp의 메모리 할당 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* preNode = h->first; //head가 가리키는 노드를 할당
	listNode* temp = h->first->link; //head가 가리키는 노드의 다음 노드를 할당

	if (key == preNode->key) { //첫번째 노드의 데이터와 일치하는 경우
		h->first = preNode->link; //head가 preNode의 다음 노드를 참조하도록 함
		preNode->link = NULL; //preNode의 link는 null을 할당하여 연결을 해제
	}
	else {
		while (temp != NULL) { //temp가 null일 때까지 반복하여 탐색
            if (key == preNode->link->key) {  //삭제할 위치 찾기
                preNode->link = temp->link;  //preNode의 link는 temp의 다음 노드를 참조
                
                return 0;
            }
            preNode = preNode->link;  //preNode에 preNode에 다음 노드를 할당
        }
	}
	free(temp); //temp의 메모리 할당 해제

    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* preNode;
    listNode* temp;
        
    if(h->first == NULL) {  //head 노드가 nulldls 경우 모든 노드가 삭제 되었으므로 리턴
	
		return 0;
    }
    
	if(h->first->link == NULL) {  //head 노드의 link가 null인 경우
		h->first = NULL;  //head에 null을 할당하여 남은 노드와의 연결을 해제
    } 
	else {  //head 노드의 link가 null이 아닌 경우
		preNode = h->first; //preNode는 head가 가리키느 노드를 할당
        temp = h->first->link;  //preNode의 다음 노드를 할당     
            
        while(temp->link != NULL) { //temp의 link가 null이 아닐 때 까지 한 노드씩 다음 노드로 이동
			preNode = temp;  //preNode는 temp를 할당
            temp = temp->link;  //temp는 temp의 다음 노드를 할당
        }
        preNode->link = NULL;  //preNode의 다음 노드인 temp로의 연결 해제
    }
	free(temp); //temp의 메모리 할당 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* nextNode = h->first; //head가 참조하는 첫번째 노드를 할당
	listNode* currentNode = NULL;  //현재 위치를 참조하는 할당
	listNode* preNode = NULL;  //이전 위치를 참조하느 할당

	while (nextNode!= NULL) {  //head가 참조하는 첫번째 노드가 null이 아닌 경우
		preNode = currentNode;  //preNode는 currentNode 위치로 이동
		currentNode = nextNode;  //currentNode 위치로 이동
		nextNode = nextNode->link;  //nextNode는 다음 노드 위치로 이동
		currentNode->link = preNode;  //currentNode의 link에 preNode를 할당하여 역순 만듦
	}
	h->first = currentNode;  //currentNode가 마지막 노드를 가리킬 때, head는 currentNord를 참조 함

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //headNord가 null인 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;  //p는 head가 가리키는 노드를 할당

	while(p != NULL) {  //p가 null이 아닌 경우
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;  //p는 p의 다음 노드를 할당
		i++;
	}

	printf("  items = %d\n", i);
}
