#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "queue_stu.h"

void fillQueue(FILE* inp, queue_t* q) {
	int len;
	village_t temp;
	while (fscanf(inp, " %[^0-9]%d %d", temp.houseHolder, &temp.distance, &temp.noOfPeople) != EOF)
	{
		len = strlen(temp.houseHolder);
		temp.houseHolder[len - 1] = '\0';

		if (temp.noOfPeople % 2 == 1)
			temp.noOfPackage = (temp.noOfPeople + 1) / 2;
		else
			temp.noOfPackage = temp.noOfPeople / 2;

		insert(q, temp);
	}
}

void displayQueue(queue_t q) {
	printf("The List of People;\n\n");
	village_t dispTemp;
	printf("    House Holder       Distance        # of People        # of Packages\n");
	printf("**************************************************************************\n");
	while (!isEmptyQ(&q))
	{
		dispTemp = remove(&q);
		printf("%-17s %10d %15d %18d\n", dispTemp.houseHolder, dispTemp.distance, dispTemp.noOfPeople, dispTemp.noOfPackage);
	}
}

void removeQueue(queue_t* q, char *key) {
	queue_t temp;
	initializeQ(&temp);
	
	village_t stuTemp;
	int packageDamaged, check = 0;
	while (!isEmptyQ(q))
	{
		stuTemp = remove(q);
		if (strcmp(stuTemp.houseHolder, key) == 0)
		{
			printf("\nEnter how many packages were damaged? : ");
			scanf(" %d", &packageDamaged);
			stuTemp.noOfPackage -= packageDamaged;
			check = 1;
			while (!isEmptyQ(q))
				insert(&temp, remove(q));
		}
		insert(&temp, stuTemp);
	}
	if (check == 0)
		printf("There is no householder with that specified name!\n\n");

	while (!isEmptyQ(&temp))
		insert(q, remove(&temp));
}

int main(void)
{
	FILE* inp;
	inp = fopen("village.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		queue_t q;
		initializeQ(&q);
		fillQueue(inp, &q);
		fclose(inp);

		char damage, key[SIZE];
		do {
			displayQueue(q);

			do {
				printf("\nDo we have damaged package? (Y/N): ");
				scanf(" %c", &damage);
			} while (damage != 'Y' && damage != 'N');

			switch (damage)
			{
			case 'Y':
				printf("\nEnter the household: ");
				scanf(" %[^\n]", key);
				removeQueue(&q, key);
				break;
			case 'N':
				printf("\nThank you for your help! :)\n");
			}
		} while (damage != 'N');
	}
	return 0;
}