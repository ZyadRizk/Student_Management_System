/*
 * project.c
 *
 *  Created on: Jan 6, 2025
 *      Author: zyad
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define true 1
#define false 0

// Defines a structure to store student details including ID, name, age, and GPA.
struct student
{
	int id;
	char name[50];
	int age;
	float GPA;
};
// Defines a node for a linked list, containing student data and a pointer to the next node.
struct node
{
	struct student data;
	struct node* next;
};

struct node* head =NULL;//head pointer

// Function to add a new student to the linked list while ensuring unique IDs.
void addStudent(const struct student *const ptr)
{
	int id;// Reads the student ID from user input.
	struct node *current = NULL;

	printf("please enter student ID\n");
	scanf("%d",&id);
	current = head;
	//Checks if the student ID already exists in the list to prevent duplicates.
	while(current != NULL)
	{
		if((current->data.id) == id)
		{
			printf("student already exist");
			return;
		}
		current = current->next;
	}
	// Allocates memory for a new student node.
	struct node *Nstudent = (struct node*) malloc(sizeof(struct node));
	assert(Nstudent!=NULL);
	Nstudent->next=NULL;

	Nstudent->data=*ptr;
	Nstudent->data.id=id;
	printf("enter student name\n");
	scanf(" %[^\n]",Nstudent->data.name);// Reads the student's full name, including spaces.
	printf("enter student age\n");
	scanf("%d",&Nstudent->data.age);
	printf("enter student GPA\n");
	scanf("%f",&Nstudent->data.GPA);

	if(head==NULL)
	{
		head=Nstudent;
	}
	else
	{
		current = head;
		// Traverses the list to find the last node for appending the new student.
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = Nstudent;
	}
	printf("Student added successfully!\n");
}
// Function to display all students in the linked list.
void displayStudents(void)
{
	struct node *current=NULL;

	if(head==NULL)// Handles the case where the list is empty.
	{
		printf("no students in list\n");
		return;
	}

	current=head;
	while(current!=NULL)
	{
		printf("id= %d \n",current->data.id);
		printf("name:");
		puts(current->data.name);
		printf("age= %d \n",current->data.age);
		printf("GPA= %f \n",current->data.GPA);
		printf("\n \n");

		current=current->next;
	}


}

// Function to search for a student by their ID.
void searchStudentByID(int id)
{
	struct node *current=NULL;
	if(head==NULL)
	{
		printf("no students in list\n");
		return;
	}
	current = head;

	while(current!=NULL)
	{
		if((current->data.id)==id)
		{
			printf("id= %d \n",current->data.id);
			printf("name:");
			puts(current->data.name);
			printf("age= %d \n",current->data.age);
			printf("GPA= %f \n",current->data.GPA);
			return;
		}
		current=current->next;
	}
	printf("student not found\n");

}

// Function to update student details if the ID exists.
void updateStudent(int id)
{
	struct node *current=NULL;
	if(head==NULL)
	{
		printf("no students in list\n");
		return;
	}
	current = head;

	while(current!=NULL)
	{
		if((current->data.id)==id)
		{
			printf("enter student name:");
			scanf(" %[^\n]",current->data.name);
			printf("enter student age:");
			scanf("%d",&current->data.age);
			printf("enter student GPA:");
			scanf("%f",&current->data.GPA);
			printf("done");
			return;

		}
		current=current->next;
	}
	printf("student not found\n");
}

// Function to calculate and return the average GPA of all students
float calculateAverageGPA(void)
{
	int n=0 ;
	float avr=0 ,sum=0 ;
	struct node *current=head;
	if(head==NULL)
	{
		printf("zero student in list");
		avr=0.0;
		return avr;
	}
	while(current != NULL)
	{
		n++;
		sum+=current->data.GPA;
		current=current->next;
	}
	avr=sum/n;

	return avr;
}

// Function to find and display the student with the highest GPA.
void searchHighestGPA(void)
{
	float max=0;
	struct node *current =head;
	struct node *highist =NULL;
	if(head==NULL)
	{
		printf("no students in list\n");
		return;
	}
	while(current!=NULL)
	{
		if((current->data.GPA)>max)
		{
			max=current->data.GPA;
			highist = current;
		}
		current=current->next;
	}
	searchStudentByID(highist->data.id);
}

// Function to remove a student from the list based on ID.
void deleteStudent(int id)
{
	struct node *delete=NULL;
	if(head==NULL)
	{
		printf("no student in list");
		return;
	}
	if(head->next==NULL)
	{
		free(head);
		head=NULL;
	}

	if(head->data.id == id)
	{
		delete=head;
		head=head->next;
		free(delete);
	}
	struct node *current=NULL;
	struct node *prev=NULL;
	prev=head;
	current = head->next;
	while(current!=NULL)
	{
		if(current->data.id==id)
		{
			delete=current;
			prev->next=current->next;
			free(delete);
			printf("student removed successful\n");
		}
		prev=current;
		current=current->next;
	}
	if(delete==NULL)
	{
		printf("student not found\n");
	}

}

// Main function to provide a menu-based interface for managing student records.
int main (void)
{
	// Disables buffering for standard output to ensure immediate display.
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int opration;
	float avr;
	int ID;

	do
	{
		printf("---------------------------------------------------\n");
		printf("1. Add Student\n");
		printf("2. Display Students\n");
		printf("3. Search Student by ID\n");
		printf("4. Update Student\n");
		printf("5. Calculate Average GPA\n");
		printf("6. Search Highest GPA\n");
		printf("7. Delete Student\n");
		printf("8. Exit\n");
		printf("enter choice:");
		scanf("%d",&opration);
		printf("---------------------------------------------------\n");


		switch(opration)
		{
		case 1:
		{
			const struct student *const student=(struct student*) malloc(sizeof(struct student));
			addStudent(student);
			printf("\n\n");
			break;
		}
		case 2:
			displayStudents();
			printf("\n\n");
			break;
		case 3:
		{
			printf("enter student id");
			scanf("%d",&ID);
			searchStudentByID(ID);
			ID=0;
			printf("\n\n");
			break;
		}
		case 4:
		{
			printf("enter student id");
			scanf("%d",&ID);
			updateStudent(ID);
			ID=0;
			printf("\n\n");
			break;
		}
		case 5:
			avr=calculateAverageGPA();
			printf("%f",avr);
			printf("\n\n");
			break;
		case 6:
			searchHighestGPA();
			printf("\n\n");
			break;
		case 7:
		{
			printf("enter student id");
			scanf("%d",&ID);
			deleteStudent(ID);
			ID=0;
			printf("\n\n");
			break;
		}
		case 8:
			break;

		default:
			printf("error please enter correct number\n ");
			break;
		}

	}while(opration!=8);
	return 0;
}


