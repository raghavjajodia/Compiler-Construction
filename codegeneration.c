#include"header.h"

void generateArithmetic(char *, int id,int reg1, int reg2,FILE * fp)
{
	if (id == 99)
	{
		fprintf(fp, "ADD R%d, R%d\n", reg1, reg2);
	}
	else if (id == 100)
	{
		fprintf(fp, "SUB R%d, R%d\n", reg1, reg2);
	}
	else if (id == 101)
	{
		fprintf(fp, "MOV AX, R%d\n",reg1);
		fprintf(fp,"MUL R%d\nMOV R%d, EAX\n", reg2,reg1);
		
	}
	else if (id == 102)
	{
		fprintf(fp, "MOV AX, R%d\nDIV R%d\nMOV R%d,AX\n", reg1,reg2,reg1);
	}
	else if (id == 90)
	{
		fprintf(fp, "OR R%d, R%d\n", reg1, reg2);
	}
	else if (id == 91)
	{
		fprintf(fp, "XOR R%d, R%d\n", reg1, reg2);
	}
	else if (id = 92)
	{
		fprintf(fp, "AND R%d, R%d\n", reg1, reg2);
	}
}

void generateRelational(int id,int reg1,int reg2,FILE * fp)
{
	if (id == 93)
		fprintf(fp, "COMP R%d R%d\nSETE R%d\n", reg1, reg2, reg1);
	else if (id == 94)
		fprintf(fp, "COMP R%d R%d\nSETNE R%d\n", reg1, reg2, reg1);
	else if (id==95)
		fprintf(fp, "COMP R%d R%d\nSETLE R%d\n", reg1, reg2, reg1);
	else if (id==96)
		fprintf(fp, "COMP R%d R%d\nSETGE R%d\n", reg1, reg2, reg1);
	else if (id==67)
		fprintf(fp, "COMP R%d R%d\nSETL R%d\n", reg1, reg2, reg1);
	else if (id==68)
		fprintf(fp, "COMP R%d R%d\nSETG R%d\n", reg1, reg2, reg1);
}

void generateLogical(int id, int reg1, int reg2,FILE * fp)
{
	if (id==88)
		fprintf(fp, "OR R%d R%d\n", reg1, reg2);
	else if (id==89)
		fprintf(fp, "AND R%d R%d\n", reg1, reg2);
}



void expressionCode(int reg, parseTree ast,FILE * fp)
{
	//arithmetic
	if ((ast->name >= 97 && ast->name <= 102) || (ast->name >= 90 && ast->name <= 92))
	{
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		expressionCode(reg, ast->children[l],fp);
		expressionCode(reg + 1, ast->children[k],fp);
		
		generateArithmetic(ast->children[l]->type,ast->name, reg, reg + 1,fp);
	}
	//relational
	else if (ast->name >= 93 && ast->name <= 96 || (ast->name >= 67 && ast->name <= 68))
	{
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		expressionCode(reg, ast->children[l],fp);
		expressionCode(reg + 1, ast->children[k],fp);

		generateRelational(ast->name, reg, reg + 1,fp);
	}
	//logical
	else if (ast->name == 88 || ast->name == 89)
	{
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		expressionCode(reg, ast->children[l],fp);
		expressionCode(reg + 1, ast->children[k],fp);

		generateLogical(ast->name, reg, reg + 1,fp);
	}
	else if (ast->name == 64)
	{
		fprintf(fp, "MOV R%d, %s\n", reg , ast->info.lexeme);
	}
	else if (ast->name == 83)
	{
		int k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		fprintf(fp, "LEA R%d, %s\n", reg + 1, ast->children[l]->info.lexeme);
		if (strcmp(ast->children[k]->info.lexeme, "first") == 0)
			{
				fprintf(fp, "MOV R%d, [R%d]\n", reg, reg+1);
			}
			
		else
			{
				fprintf(fp, "MOV R%d, [R%d+32]\n", reg, reg + 1);
			}
			
	}
	else if (ast->name >= 103 && ast->name <= 107)
	{
		fprintf(fp, "MOV R%d, %s\n", reg, ast->info.lexeme);
	}
	else{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				expressionCode(reg,ast->children[k],fp);
	}
}

void iterationCode(int reg, parseTree ast,FILE *fp)
{
	if (ast->name == 87){
		Label = Label + 2;
		fprintf(fp, "Label %d:\n", Label - 1);

		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		int n = firstChildIndex(ast->children[l]);
		int o = n;
		n++;
		while (ast->children[l]->children[n] == NULL & n < 50)
			n++;
		
		expressionCode(reg, ast->children[l]->children[o], fp);
		expressionCode(reg + 1, ast->children[l]->children[n], fp);
		fprintf(fp, "CMP R%d, R%d\n", reg, reg + 1);

		if (ast->children[l]->name==93)			
			fprintf(fp, "SETNE R%d\n", reg);
		else if (ast->children[l]->name == 94)
			fprintf(fp, "SETE R%d\n", reg);
		else if (ast->children[l]->name == 95)
			fprintf(fp, "SETGE R%d\n", reg);
		else if (ast->children[l]->name == 96)
			fprintf(fp, "SETLE R%d\n", reg);
		else if (ast->children[l]->name == 67)
			fprintf(fp, "SETG R%d\n", reg);
		else if (ast->children[l]->name == 68)
			fprintf(fp, "SETL R%d\n", reg);


		fprintf(fp, "CMP R%d, 0\n", reg);
		fprintf(fp, "JNE Label %d\n", Label);

		//code for compound statement of ast->children[k]
		compoundCode(reg, ast->children[k], fp);
		fprintf(fp, "JMP Label %d", Label - 1);
		fprintf(fp, "Label %d:\n", Label);
	}
}

void compoundCode(int reg, parseTree ast, FILE *fp)
{
	if (ast->name == 82)
		assignmentCode(reg, ast, fp);
	else if (ast->name == 85)
		selectionCode(reg, ast, fp);
	else if (ast->name == 87)
		iterationCode(reg, ast, fp);
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				compoundCode(reg, ast->children[k], fp);
	}
}



void selectionCode(int reg, parseTree ast,FILE * fp)
{
	if (ast->name == 85)
	{
		int num = ast->childrenNumber;
		int k;
		k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;
		int m = k;

		int n = firstChildIndex(ast->children[l]);
		int o = n;
		n++;
		while (ast->children[l]->children[n] == NULL & n < 50)
			n++;
		Label++;

		expressionCode(reg, ast->children[l]->children[o], fp);
		expressionCode(reg + 1, ast->children[l]->children[n], fp);
		fprintf(fp, "CMP R%d, R%d\n",reg,reg+1);

		if (ast->children[l]->name == 93)
			fprintf(fp, "SETNE R%d\n", reg);
		else if (ast->children[l]->name == 94)
			fprintf(fp, "SETE R%d\n", reg);
		else if (ast->children[l]->name == 95)
			fprintf(fp, "SETGE R%d\n", reg);
		else if (ast->children[l]->name == 96)
			fprintf(fp, "SETLE R%d\n", reg);
		else if (ast->children[l]->name == 67)
			fprintf(fp, "SETG R%d\n", reg);
		else if (ast->children[l]->name == 68)
			fprintf(fp, "SETL R%d\n", reg);


		fprintf(fp, "CMP R%d, 0\n",reg);
		fprintf(fp, "JNE Label %d\n",Label);
		
		if (num == 2)
		{
		//generate code for compound statement ast->children[m]
			compoundCode(reg, ast->children[m], fp);
			fprintf(fp, "Label %d:\n", Label);		
		}
		else
		{
			Label++;
			k++;
			while (ast->children[k] == NULL && k < 50)
				k++;

			//generate code for compound statement ast->children[m]
			compoundCode(reg, ast->children[m], fp);
			fprintf(fp, "JMP Label %d\n", Label);
			fprintf(fp, "Label %d:\n", Label-1);
			//generate code for compound statement ast->children[k]
			compoundCode(reg, ast->children[k], fp);
			fprintf(fp, "Label %d:\n", Label);
		}
	}
}

void assignmentCode(int reg, parseTree ast,FILE * fp)
{
	if (ast->name == 82)
	{
		int k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;
		expressionCode(reg, ast->children[k], fp);
		fprintf(fp, "MOV %s,R%d\n", ast->children[l]->info.lexeme, reg);
	}

}
