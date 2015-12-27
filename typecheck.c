#include"header.h"

void populateTypes(parseTree ast)
{

	int k = 0;
	for (k = 0; k < 50; k++)
	{
		if (ast->children[k] != NULL)
			populateTypes(ast->children[k]);
	}

	if (ast->name == 64 && searchNodeInHash(ast->info.lexeme) != NULL)
		ast->type = searchNodeInHash(ast->info.lexeme)->dataType;
	else if (ast->name == 103)
		ast->type = "char";
	else if (ast->name == 104)
		ast->type = "int";
	else if (ast->name == 105)
		ast->type = "real";
	else if (ast->name == 106)
		ast->type = "bool";
	else if (ast->name == 107)
		ast->type = "bool";
	else if (ast->name == 108)
		ast->type = "char *";
	else if (ast->name == 83)
		ast->type = "real";
	else if ((ast->name >= 97 && ast->name <= 102)|| (ast->name>=90 && ast->name<=92))
	{
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;
		if (strcmp(ast->children[l]->type, "int") == 0 && strcmp(ast->children[l]->type, "int") == 0)
			ast->type = "int";
		else if (strcmp(ast->children[l]->type, "real") == 0 && strcmp(ast->children[l]->type, "real") == 0)
			ast->type = "real";
		else if (strcmp(ast->children[l]->type, "complex") == 0 && strcmp(ast->children[l]->type, "complex") == 0 && (ast->name == 99 || ast->name == 100))
			ast->type = "complex";
		else
			ast->type = "error";
	}
	else if (ast->name >= 93 && ast->name <= 96 || (ast->name >=67 && ast->name<=68))
	{
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;
		if (strcmp(ast->children[l]->type, ast->children[k]->type) == 0)
			ast->type = "bool";
		else
			ast->type = "error";
	}
	else if (ast->name == 88 || ast->name == 89)
	{
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;
		if (strcmp(ast->children[l]->type, "bool") == 0 && strcmp(ast->children[l]->type, "bool") == 0)
			ast->type = "bool";
		else if (strcmp(ast->children[l]->type, "int") == 0 && strcmp(ast->children[l]->type, "int") == 0)
			ast->type = "int";
		else
			ast->type = "error";
	}
	else
		ast->type = "error";	
}

void checkAssignment(parseTree ast)
{
	if (ast->name == 82)
	{
		int k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		if (ast->children[l]->name == 25 && ast->children[k]->name == 23)
		{
			if (ast->children[l]->childrenNumber != ast->children[k]->childrenNumber)
			{
				FILE * fp = fopen("./SemanticOutput.txt", "a");
				fprintf(fp, "Error in line: %d, Number of arguments do not match on both sides\n", ast->info.lineno);
				fclose(fp);
			}
			else
			{
				int num = ast->children[l]->childrenNumber;
				int ptr1 = 0;
				int ptr2 = 0;
				while (num > 0)
				{
					while (ast->children[l]->children[ptr1] == NULL &&  ptr1 < 50)
						ptr1++;
					while (ast->children[k]->children[ptr2] == NULL &&  ptr2 < 50)
						ptr2++;
					if (strcmp(ast->children[l]->children[ptr1]->type, ast->children[k]->children[ptr2]->type) != 0)
					{
						FILE * fp = fopen("./SemanticOutput.txt", "a");
						fprintf(fp, "Error in line: %d, type of %s and %s do not match on both sides\n", ast->info.lineno, ast->children[l]->children[ptr1]->info.lexeme, ast->children[k]->children[ptr2]->info.lexeme);
						fclose(fp);
					}
					ptr1++;
					ptr2++;
					num--;
				}
			}
		}
		else if ((ast->children[l]->name == 64 || ast->children[l]->name == 83) && (ast->children[k]->name == 68 || ast->children[k]->name == 67 || ast->children[k]->name == 64 || ast->children[k]->name == 83 || (ast->children[k]->name>=103 && ast->children[k]->name<=107)  || (ast->children[k]->name >= 88 && ast->children[k]->name <= 102)))
		{
			if (strcmp(ast->children[l]->type, ast->children[k]->type) != 0)
			{

				FILE * fp = fopen("./SemanticOutput.txt", "a");
				fprintf(fp, "Error in line: %d, Types do not match on both sides\n", ast->info.lineno);
				fclose(fp);
			}
		}
		else
		{
			FILE * fp = fopen("./SemanticOutput.txt", "a");
			fprintf(fp, "Error in line: %d, Number of arguments do not match on both sides\n", ast->info.lineno);
			fclose(fp);
		}
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				checkAssignment(ast->children[k]);
	}
}
 
void checkWhile(parseTree ast)
{
	if (ast->name == 87 || ast->name == 85)
	{
		int k = firstChildIndex(ast);
		if (strcmp(ast->children[k]->type, "bool") != 0)
		{
			FILE * fp = fopen("./SemanticOutput.txt", "a");
			fprintf(fp, "Error in line: %d, Type not boolean expression\n", ast->info.lineno);
			fclose(fp);
		}

	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				checkWhile(ast->children[k]);

	}
}

void typeChecking(parseTree ast)
{
	populateTypes(ast);
	checkAssignment(ast);
	checkWhile(ast);
}
