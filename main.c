/*
 ============================================================================
 Author      : William Mabia
 Description : Chain Hash Encrytpiton
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int SIZE = 10;

//Node
struct HashTablenode {
	char data[50];
	struct HashTablenode *next;
};
typedef struct HashTablenode Node;

//Create New Node
Node* newNode(char value[]) {
	Node *nnode = (Node*) malloc(sizeof(Node));
	if (nnode != NULL) {
		nnode->next = NULL;
		strcpy(nnode->data, value);

	}
	return nnode;
}

void addUsrPass(char *data, char *newUser) {
	//format string to join user and password

	int spaceCounter = 0; //This counter counts space

	//Goes through string
	while ((*data != '\0') && (*data != '\n') && (*data != '\r')) {

		if (*data != ' ') {
			//This if statement takes out space when copying
			strncpy(newUser, data, 1); //Copy character one at a time
			newUser += 1; //Move to next array spot

		}

		//if char is space and there has only been one space fill new user with backslash
		else if ((*data == ' ') && (spaceCounter == 0)) {
			strncpy(newUser, "/", 1);
			spaceCounter += 1;
			newUser += 1;

		}
		data += 1;
	}

	//make last NULL
	*newUser = '\0';

	return;
}

//Haash Function Using division method
int hashfunction(int key) {
	int hashValue;
	hashValue = key % SIZE;
	return hashValue;
}

int asciiSum(char user[]) {
	//ascii sum of characters
	int i = 0, total = 0;
	//get ascii sum
	while (user[i] != '\0') {

		total += user[i];
		i += 1;

	}

	return total;
}

int main() {
	char login[25], password[25], newUser[25], emptyTest[25];
	Node *currptr = NULL, *testP = NULL;
	int key, hashValue;
	FILE *fptr;

	//Initialize an array of null pointer
	int *hashTable[10] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL };

	//open file for reading
	fptr = fopen("password.txt", "r");

	fgets(emptyTest, 50, fptr);

	//printf("%s\n", emptyTest);

	int length = strlen(emptyTest);

	if (length == NULL) {
		printf("File did not open");
		exit(1);
	}

	//go through file
	while (!feof(fptr)) {
		//read a line in file, and store it in user
		fgets(login, 50, fptr);

		//format string to join user and password
		addUsrPass(login, newUser);

		//get the key and then the hash
		key = asciiSum(newUser);
		hashValue = hashfunction(key);

		//store regularly if spot is empty
		if (hashTable[hashValue] == NULL)
			hashTable[hashValue] = newNode(newUser);

		else {
			//make a curr node and if the addres is thesame
			//change the next pointer to the newNode
			currptr = (hashTable[hashValue]);
			currptr->next = newNode(newUser);
		}

	}
	fclose(fptr);            //Close the file

	printf("\nLogin: ");
	scanf("%s", &login);
	printf("Password: ");
	scanf("%s", &password);

	//Make User Password format so input matches addUsrPass
	strcat(login, "/");
	strcat(login, password);

	key = asciiSum(login);
	hashValue = hashfunction(key);

	if (hashTable[hashValue] == NULL) {
		printf("Authentication: Failed");
	}

	else {
		testP = hashTable[hashValue];
		while ((testP != NULL) && (strcmp(testP->data, login) != 0)) {
			testP = testP->next;
		}
		if (testP != NULL)
			printf("Authentication: Successful ");
		else
			printf("Authentication: Failed");
	}

}
