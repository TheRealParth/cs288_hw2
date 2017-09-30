/*
Parth Patel
CS 288 2017F Section 101
HW 02
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* self-referential structure */
struct Node {
	int studentId;
	int midTerm1Grade;
	int midTerm2Grade;
	int finalExamGrade;
	struct Node *next;
};

struct List {
	int length;
	struct Node *head;
	struct Node *tail;
};


struct List SLL_new(){
	/* construct an empty list */
	struct List list;
	list.head = NULL;
	list.tail = NULL;
	return list;
}

int SLL_empty(struct List *list) {
	/* return true if the list contains no items */
	return list->head == NULL;
}

void SLL_push(struct List *list, struct Node *node) {
	/*  insert the item at the front of the list */
	// struct Node *node = malloc(sizeof(struct Node));
	// node->item = item;
	node->next = list->head;
	if (SLL_empty(list)) {
		list->tail = node;
	}
	list->head = node;
	list->length = list->length + 1;
}

void SLL_append(struct List *list, struct Node *node) {
	/* append the studentId to the end of the list */
	if (SLL_empty(list)) {
		SLL_push(list, node);
	} else {
		// struct Node *node = malloc(sizeof(struct Node));
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	}
}

struct Node *getNodeByStudentId(struct List *list, int studentId) {
	struct Node *node;
	node = list->head;

	if(node->studentId == studentId) return node;

	for(int i = 0; i < list->length; i++){
		node = node->next;
		if(node->studentId == studentId) return node;
	}

	return NULL;

}

int getAverage(struct Node *node) {
	return 0;
}

int main(int argc, char *argv[]) {	
	if(argc == 5){
		FILE *fp;
		char buff[15];
		int studentId;
		struct Node *node;
		int grade;
		char *search = ",";
		struct List list = SLL_new();
		list.length = 0;
		for(int i = 1; i < argc; i++) {
			if(i == (argc-1)) {
				printf("%s\n", "WRITE THE THINGS");
			} else {
				fp = fopen(argv[i], "r");

				printf("%s\n", argv[i]);
				while(fgets(buff, 255, (FILE*)fp) != NULL) {

					studentId = atoi(strtok(buff, search));
					grade = atoi(strtok(NULL, search));
	// node->item = item;
					printf("%i ", studentId );
					printf("%i\n", grade);

					if(i == 1) {
						node = malloc(sizeof(struct Node));
						node->studentId = studentId;
						node->midTerm1Grade = grade;
						SLL_push(&list, node);
					} 
					else if(i == 2) {
						node = getNodeByStudentId(&list, studentId);
						node->midTerm2Grade = grade;
					} else if (i == 3) {
						node = getNodeByStudentId(&list, studentId);
						node->finalExamGrade = grade;
					}
				}

				fclose(fp);
			}
		}

	} else {
		printf("%s\n", "Invalid Arguments");
	}
	
   return 0;
}

