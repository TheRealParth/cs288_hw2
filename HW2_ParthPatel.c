/*
Parth Patel
CS 288 2017F Section 101
HW 02
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* self-referential structure */
struct Node {
	int studentId;
	int midTerm1Grade;
	int midTerm2Grade;
	int finalExamGrade;
	int finalGrade;
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
		list->length = list->length + 1;
	}
}

int SLL_sortInsert(struct List *list, struct Node *node) {
	if (SLL_empty(list)) {
		SLL_push(list, node);
	} else {
		if(list->head->studentId >= node->studentId){
			SLL_push(list, node);
		} else if (list->tail->studentId <= node->studentId) {
			SLL_append(list, node);
		} else {
			struct Node *prev = list->head;
			struct Node *next = prev->next;
 			while(1) {
				if(prev->studentId <= node->studentId) {
					prev->next = node;
					node->next = next;
					return 1;
				}
				prev = next;
				next = next->next;
			}
		}
		list->length = list->length + 1;
	}
	return 0;
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

void printSortedLst(struct List *list) {
	struct Node *node = list->head;
	while(node != NULL){
		printf("%i ", node->studentId);
		printf("%i ", node->midTerm1Grade);
		printf("%i ", node->midTerm2Grade);
		printf("%i ", node->finalExamGrade);
		printf("%i\n", node->finalGrade);
		node = node->next;
	}
}


int setAverage(struct Node *node) {
	int total = node->midTerm1Grade + node->midTerm2Grade + node->finalExamGrade;
	float average = (total/3.0);
	float rounded = (average > (floor(average)+0.5f)) ? ceil(average) : floor(average);
	node->finalGrade = (int)rounded;
	return 0;
}



int main(int argc, char *argv[]) {	
	if(argc == 5){
		FILE *fp;
		char buff[255];
		int studentId;
		struct Node *node;
		int grade;
		char *search = ",";
		struct List list = SLL_new();
		char sId[255];
		char finalGrade[255];
		char finalOut[255];	
		list.length = 0;

		for(int i = 1; i < argc; i++) {
			if(i == (argc-1)) {
				// buff = 
				fp = fopen(argv[i], "w");
				node = list.head;
				while(node != NULL){
					sprintf( sId, "%d", node->studentId);
					sprintf(finalGrade, "%d", node->finalGrade);
					strcpy(finalOut, sId);
					strcat(finalOut, ",");
					strcat(finalOut, finalGrade);
					strcat(finalOut, "\n");

					fputs(finalOut, fp);
					node = node->next;
				}
				printf("%s", "The results were successfully written to ");
				printf("%s\n", argv[i]);
				fclose(fp);
			} else {
				fp = fopen(argv[i], "r");

				// printf("%s\n", argv[i]);
				while(fgets(buff, 255, (FILE*)fp) != NULL) {

					studentId = atoi(strtok(buff, search));
					grade = atoi(strtok(NULL, search));

					if(i == 1) {
						node = malloc(sizeof(struct Node));
						node->studentId = studentId;
						node->midTerm1Grade = grade;
						SLL_sortInsert(&list, node);
					} 
					else if(i == 2) {
						node = getNodeByStudentId(&list, studentId);
						node->midTerm2Grade = grade;
					} else if (i == 3) {
						node = getNodeByStudentId(&list, studentId);
						node->finalExamGrade = grade;
						setAverage(node);
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

