//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// This is for question 2. You should not change the prototype of this function
void appendLL(LinkedList *ll_a , LinkedList *ll_b);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll_a , ll_b, ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list ll as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the linked list ll_a as an empty linked list
	ll_a.head = NULL;
	ll_a.size = 0;

	//Initialize the linked list ll_b as an empty linked list
	ll_b.head = NULL;
	ll_b.size = 0;


	printf("1: Insert an integer to the linked list a:\n");
	printf("2: Insert an integer to the linked list b:\n");
	printf("3: Merge two sorted linked lists:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list a: ");
			scanf("%d", &i);
			j =  insertNode(&ll_a,ll_a.size,i);
			printf("The resulting linked list a: ");
			printList(&ll_a);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list b: ");
			scanf("%d", &i);
			j = insertNode(&ll_b, ll_b.size,i);
			printf("The resulting linked list b: ");
			printList(&ll_b);
			break;
		case 3:
		    printf("The resulting linked lists after appending list b to list a are: \n");
			appendLL(&ll_a, &ll_b); // You need to code this function
			printf("The resulting linked list a: ");
			printList(&ll_a);
			printf("The resulting linked list b: ");
			printList(&ll_b);
			removeAllItems(&ll_a);
			break;
		case 0:
			removeAllItems(&ll_a);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void appendLL(LinkedList *ll_a , LinkedList *ll_b)
{
    /*add your code here */
	if (ll_a->head == NULL && ll_b->head == NULL) return;
	if (ll_a->head == NULL) {
		ll_a->head = ll_b->head;
		ll_b->head = NULL;
		return;
	}
	if (ll_b->head == NULL) return;
	ListNode *currNodeA = ll_a->head;
	while (currNodeA->next != NULL) {
		currNodeA = currNodeA->next;
	}
	currNodeA->next = ll_b->head;
	ll_b->head = NULL;
}
//1 1 1 2 1 3 1 4 2 5 2 6 2 7 2 8 3
///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
