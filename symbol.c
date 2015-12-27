#include"header.h"

void populateSymbolTable(parseTree ast)
{
	if (ast->name >= 75 && ast->name <= 79)
	{
		int k = 0;
		for (k = 0; k < 50; k++)
		{
			if (ast->children[k] != NULL)
				insertToHash(ast->children[k]->info.lineno,-1,ast->children[k]->info.lexeme,ast->info.lexeme,0);
		}
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				populateSymbolTable(ast->children[k]);
	}
}


unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}


struct symbolTableNode * makeSymbolNode(int lineDeclared, int scope, char *name, char *dataType, int lineReference) {
	struct symbolTableNode *newnode;
	newnode = (struct symbolTableNode *)malloc(sizeof(struct symbolTableNode));
	newnode->lineDeclared = lineDeclared;
	int i;
	for (i = 0; i<50; i++)
		newnode->lineReferenced[i] = lineReference;
	strcpy(newnode->name, name);
	strcpy(newnode->dataType, dataType);
	newnode->scope = scope;
	newnode->scope2=-1;
	newnode->next = NULL;
	return newnode;
}


void insertToHash(int lineDeclared, int scope, char *name, char *dataType, int lineReference) {
	int hashIndex = hash((unsigned char*)name) % 100;
	struct symbolTableNode *newnode = makeSymbolNode(lineDeclared, scope, name, dataType, lineReference);
	/* head of list for the bucket with index "hashIndex" */
	if (!hashTable[hashIndex].head) {
		hashTable[hashIndex].head = newnode;
		hashTable[hashIndex].count = 1;
		return;
	}
	/* adding new node to the list */
	newnode->next = (hashTable[hashIndex].head);
	hashTable[hashIndex].head = newnode;
	hashTable[hashIndex].count++;
	return;
}


void deleteFromHash(char* name) {
	/* find the bucket using hash index */
	int hashIndex = hash((unsigned char*)name) % 100; int flag = 0;
	struct symbolTableNode *temp, *myNode;
	/* get the list head from current bucket */
	myNode = hashTable[hashIndex].head;
	if (!myNode) {
		printf("Given data is not present in hash Table!!\n");
		return;
	}
	temp = myNode;
	while (myNode != NULL) {
		/* delete the node with given key */
		if (strcmp(myNode->name, name) == 0) {
			flag = 1;// tells us that data is found
			if (myNode == hashTable[hashIndex].head)
				hashTable[hashIndex].head = myNode->next;
			else
				temp->next = myNode->next;

			hashTable[hashIndex].count--;
			free(myNode);
			break;
		}
		temp = myNode;
		myNode = myNode->next;
	}
}

int searchInHash(char* name) {
	int hashIndex = hash((unsigned char*)name) % 100; int flag = 0;
	struct symbolTableNode *myNode;
	myNode = hashTable[hashIndex].head;
	if (!myNode) {
		return 0;
	}
	while (myNode != NULL) {
		if (strcmp(myNode->name, name) == 0) {
			flag = 1;
			break;
		}
		myNode = myNode->next;
	}

	return flag;
}

struct symbolTableNode * searchNodeInHash(char* name) {
	int hashIndex = hash((unsigned char*)name) % 100; int flag = 0;
	struct symbolTableNode *myNode;
	myNode = hashTable[hashIndex].head;
	if (!myNode) {
		return NULL;
	}
	while (myNode != NULL) {
		if (strcmp(myNode->name, name) == 0) {
			flag = 1;
			break;
		}
		myNode = myNode->next;
	}

	return myNode;
}

void display() {
	FILE *fp = fopen("SymbolTableOutput.txt", "w");
	struct symbolTableNode *myNode;
	int i;
	//         fprintf(fp,"\nSymbol Table:\n", i);
	fprintf(fp, "------------------------------------------------------------------------------------------\n");
	for (i = 0; i < eleCount; i++) {
		if (hashTable[i].count == 0)
			continue;
		myNode = hashTable[i].head;
		if (!myNode)
			continue;

		while (myNode != NULL) {

			fprintf(fp, "%s :: ", myNode->name);
			fprintf(fp, " declared at line %d , ", myNode->lineDeclared);
			fprintf(fp, " scope : %d %d , ", myNode->scope, myNode->scope2);
			if (myNode->lineReferenced[0] != 0)
			{
				fprintf(fp, "referenced line:  ");
				int i = 0;
				while (myNode->lineReferenced[i] != 0)
				{

					fprintf(fp, "%d ", myNode->lineReferenced[i]);
					i++;

				}
				fprintf(fp, ", ");
			}
			else fprintf(fp, "not referenced yet ,");
			fprintf(fp, "Type:%s  ", myNode->dataType);
			fprintf(fp, "\n\n");

			myNode = myNode->next;
		}
	}
	fclose(fp);
	return;
}


void insertWithRefernce(int RefencedLine, char *name)
{
	int hashIndex = hash((unsigned char*)name) % 100; int flag = 0;
	struct symbolTableNode *myNode;
	myNode = hashTable[hashIndex].head;
	if (!myNode) {
		return;
	}
	while (myNode != NULL) {
		if (strcmp(myNode->name, name) == 0) {
			flag = 1;
			int i = 0;
			while (myNode->lineReferenced[i] != 0)
				i++;
			myNode->lineReferenced[i] = RefencedLine;
			break;
		}
		myNode = myNode->next;
	}

	return;

}


void insertScope(int scope,int scope2, char *name)
{
	int hashIndex = hash((unsigned char*)name) % 100; int flag = 0;
	struct symbolTableNode *myNode;
	myNode = hashTable[hashIndex].head;
	if (!myNode) {
		return;
	}
	while (myNode != NULL) {
		if (strcmp(myNode->name, name) == 0) {
			flag = 1;
			myNode->scope = scope;
			myNode->scope2=scope2;
			break;
		}
		myNode = myNode->next;
	}

	return;

}


//int lineDeclared,int scope, char *name,char *dataType,int lineReference;
void initializeSymbolTable(parseTree astTree) {
	int n = 100;
	eleCount = 100;
	/* create hash table with "n" no of buckets */
	hashTable = (struct hash *)calloc(n, sizeof(struct hash));
	
	populateSymbolTable(astTree);
	struct symbolTableNode *myNode;
	FILE *fp=fopen("SemanticOutput.txt","a");
	
	
	int i; int scope = 0;int scope2=-1;
	for (i = 0; i<tokenNumber; i++)
	{
		if (strcmp(globalTokens[i].tokenName, "tk_leftbr") == 0)
		{
			scope++;scope2++;
		}

		if (strcmp(globalTokens[i].tokenName, "tk_rightbr") == 0)
			scope--;

		if (strcmp(globalTokens[i].tokenName, "tk_id") == 0)
		{
			
			
			if (searchInHash(globalTokens[i].lexeme))// already declared
			{
				myNode=searchNodeInHash(globalTokens[i].lexeme);
					if(myNode->lineDeclared !=globalTokens[i].lineno)
					insertWithRefernce(globalTokens[i].lineno, globalTokens[i].lexeme);
					if(myNode->lineDeclared ==globalTokens[i].lineno)
						insertScope(scope,scope2,globalTokens[i].lexeme);
					else{
						if(scope<myNode->scope)
							fprintf(fp,"ERROR : %s out of scope , Line No: %d\n",globalTokens[i].lexeme,globalTokens[i].lineno);
						if(scope==myNode->scope)
							if(scope2!=myNode->scope2)
								fprintf(fp,"ERROR : %s out of scope , Line No: %d\n",globalTokens[i].lexeme,globalTokens[i].lineno);
					}

					if(myNode->lineDeclared>globalTokens[i].lineno)
						fprintf(fp,"ERROR : %s declared later but referenced here , Line No: %d\n",globalTokens[i].lexeme,globalTokens[i].lineno);
			}
			else                                    // not declared yet
			{
				if(strcmp(globalTokens[i].lexeme,"first")!=0)
				fprintf(fp,"ERROR : %s not declared, Line No: %d\n",globalTokens[i].lexeme,globalTokens[i].lineno);
				
				/*int j;
				for (j = i - 1; j >= 0; j--)
				{
					if (strcmp(globalTokens[j].tokenName, "tk_int") == 0 || strcmp(globalTokens[j].tokenName, "tk_char") == 0 || strcmp(globalTokens[j].tokenName, "tk_char") == 0 || strcmp(globalTokens[j].tokenName, "tk_bool") == 0
						|| strcmp(globalTokens[j].tokenName, "tk_array") == 0 || strcmp(globalTokens[j].tokenName, "tk_func") == 0)
						break;
				}
				insertToHash(globalTokens[i].lineno, scope, globalTokens[i].lexeme, globalTokens[j].tokenName, 0);*/

			}
		}
	}
	fclose(fp);
	
	display();

}
