/*****************************************
* @Instructor: Prof. Alaa Mohammed Salih *
* @Autor: Alqassam Firwana		 *
* @id: ________				 *
* @course: PROG20799			 *
* @Assignment: 3			 *
* @Date: July 2021			 *
*****************************************/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*********************************************************************************
 * MY COLORS <-- this time will make it more  					 *
 * readable without cluttering my code						 *
 * @source https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a *
 *********************************************************************************/
//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
//reset
#define reset "\e[0m"

#define STR_LEN 50
//part struct
struct part
{
	int number;
	char name[STR_LEN + 1];
	int on_hand;
	struct part *next;
};

//functions prototypes
void insertPart(struct part *head, int num, char name[], int onHand);
void searchPart(int num, struct part *inventroy);
void updatePart(int num, int newNum, struct part *inventory);
struct part *locate_part(int number, struct part *inventory);
void display();
int validate(int valid);
void isEmpty();
int getCount(struct part *inventory);

//return part
struct part *locate_part(int number, struct part *inventory)
{
	struct part *p;

	for (p = inventory;
	     p != NULL && number > p->number;
	     p = p->next)
		;
	if (p != NULL && number == p->number)
		return p;
	return NULL;
}

//insert new part
void insertPart(struct part *inventory, int num, char name[], int onHand)
{
	struct part *current, *previous, *new_part;
	new_part = malloc(sizeof(struct part));
	if (locate_part(num, inventory) == NULL)
	{
		new_part->number = num;
		strcpy(new_part->name, name);
		new_part->on_hand = onHand;
		new_part->next = NULL;
		for (current = inventory, previous = NULL;
		     current != NULL && new_part->number > current->number;
		     previous = current, current = current->next)
			;
		//   if (current != NULL && new_part->number == current->number) {
		//     printf("Part already exists.\n");
		//     free(new_part);
		//     return;
		//   }
		new_part->next = current;
		if (previous == NULL)
			inventory = new_part;
		else
			previous->next = new_part;
		printf(BGRN "\nPart added successfully !\n" reset);
	}
	else
	{
		printf(BRED "\nPart number already exists !\n" reset);
		free(new_part);
		return;
	}
}
//updaste existing part
void updatePart(int num, int newNum, struct part *inventory)
{
	struct part *p = inventory;
	p = locate_part(num, inventory);
	if (p != NULL)
	{
		p->on_hand += newNum;
		printf(BGRN "\nPart updated successfully !\n" reset);
	}
	else printf(BRED "\nPart not in the inventroy !\n"reset);
}

//search for part
void searchPart(int num, struct part *inventory)
{
	int i = 0;
	int j = 0;
	if (getCount(inventory) == 1)
	{
		printf(BRED"\nInventory is empty !\n\n"reset);
	}else {

	struct part *temp = inventory;
	while (temp != NULL)
	{
		if (temp->number == num)
		{
			j++;
			printf("\033[0;32m"); //color
			printf(BGRN "\nPart name: %s\n", temp->name);
			printf("Part Quantity: %d\n\n" reset, temp->on_hand );
			printf("\033[0m"); //reset color
		}
		temp = temp->next;
		i++;
	}
	if (j == 0)
	{
		printf(BRED "\nPart not found !\n\n" reset);
	}
	}
}
//
//count nodes
int getCount(struct part *inventory)
{
	int count = 0;			  // Initialize count
	struct part *current = inventory; // Initialize current
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}
//display all parts
void display(struct part *inventory)
{
	int num = 1;
	struct part *p = inventory;
	p = p->next;
	if(getCount(inventory) > 1){
	printf(BBLU "\n------------------------------------------------------------------\n");
	printf("Part Number\t\tPart Name\t\tQuantity available\n");
	printf("------------------------------------------------------------------\n" reset);
	while (p != NULL)
	{

		//printf("display() << inside for");
		//printf(BBLU "------------------------------------------------------------------\n");
		printf("%-10d\t\t%-9s\t\t%d\n", p->number, p->name, p->on_hand);
		//printf("------------------------------------------------------------------\n"reset);
		p = p->next;
		num++;
		printf(BBLU "------------------------------------------------------------------\n" reset);
	}

	} if (num == 0 || getCount(inventory) == 1)
	{
		printf(BRED "\nInventory is Empty !\n"reset);
	}
	printf("\n");
}

int validate(int valid)
{
	char x;
	if (valid != 1)
	{
		printf("\033[1;31m");
		//validate user input
		printf("\nPlease Enter numeric value only!, Press Enter to continue...\n");
		printf("\033[0m");
		while ((x = getchar()) != '\n' && x != EOF)
			;
		scanf("%c", &x);
		return -1;
	}
	return 0;
}

int main()
{ //main start

	struct part *inventroy = malloc(sizeof(struct part)); //inventroy start here
	//bool flag = true;	//flag to exit while loop
	int partNum = 0;    //Part num
	char name[STR_LEN]; //name string length
	char option;	    //option from the  list
	int onHand;	    //temp for on_hand
	int validNum;	    //to validate numeric input
	int validOnHand;    //to validate on_hand
	int check;	    //recive -1 or 0 from validate
	do
	{
				      //list label
		printf("\033[0;36m"); //Cyan color
		printf(BCYN"=========================\n");
		printf("Please enter your option\n");
		printf(GRN"<case-Insensitive> \n" BCYN);
		printf("=========================\n"CYN);
		printf("1.(" MAG "i" CYN ")nsert\n");
		printf("2.(" MAG "s" CYN ")earch\n");
		printf("3.(" MAG "u" CYN ")pdate\n");
		printf("4.(" MAG "p" CYN ")rint\n");
		printf("5.(" MAG "q" CYN ")uit\n");
		printf("\033[0m"); //reset color
		printf(BGRN "Enter option: " reset);
		int ch;
		printf(BMAG);
		scanf(" %c", &option);
		while ((ch = getchar()) != '\n')
			;
		printf(reset);
		//printf("%c option\n", option); //test
		switch (option)
		{
		case 'i':
		case 'I':
		case1:
			printf(BYEL "\nPlease Enter Part Number: " reset);
			validNum = scanf("%d", &partNum);
			check = validate(validNum);
			if (check == -1)
				goto case1;
			printf(BYEL "Please Enter Part Name: " reset);
			validNum = scanf("%s", name);
			check = validate(validNum);
			if (check == -1)
				goto case1;
			printf(BYEL "Please Enter Part Quantity: " reset);
			validOnHand = scanf("%d", &onHand);
			check = validate(validOnHand);
			if(check == -1) goto case1;
			insertPart(inventroy, partNum, name, onHand);
			break;
		case 's':
		case 'S':
		case2:
			printf(BYEL "\nPlease Enter Part Number to search for: " reset);
			validNum = scanf("%d", &partNum);
			check = validate(validNum);
			if(check == -1) goto case2;
			searchPart(partNum, inventroy);
			break;
		case 'u':
		case 'U':
			printf(BYEL "\nPlease Enter Part Number you want to Update: " reset);
			validNum = scanf("%d", &partNum);
			check = validate(validNum);
			if(check == -1) goto case2;
			printf(BYEL "Please Enter new value: " reset);
			int newOnHand;
			int newValidNum = scanf("%d", &newOnHand);
			check = validate(newValidNum);
			if(check == -1) goto case2;
			updatePart(partNum, newOnHand, inventroy);
			break;
		case 'p':
		case 'P':
			display(inventroy);
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			printf(BRED "\nEnter valid character !\n" reset);
			break;
		}
	} while (option != 'q');

	return 0;
} //main  end
