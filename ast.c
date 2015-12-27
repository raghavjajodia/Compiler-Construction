#include"header.h"

int useLess(char* c)
{
	if ((strcmp(c, "tk_leftpa") == 0) || (strcmp(c, "tk_rightpa") == 0) || (strcmp(c, "tk_leftbr") == 0) || (strcmp(c, "tk_rightbr") == 0) || (strcmp(c, "tk_leftsq") == 0) || (strcmp(c, "tk_rightsq") == 0)
		|| (strcmp(c, "tk_colon") == 0) || (strcmp(c, "tk_comma") == 0))
		return 1;
	else
		return 0;
}

parseTree useLessTerminals(parseTree ptree)
{
	if (ptree == NULL)
		return ptree;
	if (ptree->terminal == 1 && useLess(resolution[ptree->name]))
		return NULL;
	if (ptree->terminal == 1)
		return ptree;
	int count = 0;
	int i = 0;
	int num = ptree->childrenNumber;
	while (count< num)
	{
		if (ptree->children[i] == NULL)
			i++;
		else
		{
			count++;

			if (ptree->children[i]->name != -1 && ptree->children[i]->terminal == 1 && useLess(resolution[ptree->children[i]->name])){
				ptree->children[i] = NULL;
				ptree->childrenNumber = ptree->childrenNumber - 1;
			}
			else if (ptree->children[i]->terminal == 0)
				ptree->children[i] = useLessTerminals(ptree->children[i]);
			i++;
		}
	}
	return ptree;
}

parseTree useLessNonTerminals(parseTree ptree)
{
	if (ptree == NULL)
		return ptree;
	if (ptree->terminal == 1)
		return ptree;

	int count = 0;
	int i = 0;
	while (count<ptree->childrenNumber)
	{
		if (ptree->children[i] == NULL)
			i++;
		else
		{
			count++;

			if (ptree->children[i]->terminal == 1)
				i++;
			else
			{
				ptree->children[i] = useLessNonTerminals(ptree->children[i]);
				if (ptree->children[i]->childrenNumber == 1)
				{
					int j = 0;
					while (ptree->children[i]->children[j] == NULL)
						j++;
					ptree->children[i] = ptree->children[i]->children[j];
					ptree->children[i]->parent = ptree;
				}
				i++;
			}


		}

	}
	return ptree;
}

parseTree epsilonReduce(parseTree ptree)
{

	if (ptree == NULL)
		return ptree;
	if (ptree->terminal == 1)
		return ptree;
	int i = 0;
	int count = 0;
	int flag = 1;
	int num = ptree->childrenNumber;
	// printf("%d\n",num);
	while (count<num)
	{
		if (ptree->children[i] != NULL)
		{
			count++;
			if (ptree->children[i]->terminal == 1 && ptree->children[i]->name == -1)
			{
				ptree->children[i] = NULL;
				ptree->childrenNumber = ptree->childrenNumber - 1;
			}
			else if (ptree->children[i]->terminal == 1 && ptree->children[i]->name != -1)
				flag = 0;
			else if (ptree->children[i]->terminal == 0){
				ptree->children[i] = epsilonReduce(ptree->children[i]);
				if (ptree->children[i] == NULL)
					ptree->childrenNumber = ptree->childrenNumber - 1;
				else
					flag = 0;
			}
		}
		i++;
	}

	if (flag == 1)
		return NULL;
	else
		return ptree;

}


int checkIfOperator(int id)
{
	int flag = 0;
	for (int i = 38; i <= 54; i = i + 2)
	{
		if (id == i)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int checkIfRecursive(int id)
{
	int flag = 0;
	for (int i = 39; i <= 55; i = i + 2)
	{
		if (id == i)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int firstChildIndex(parseTree ptree)
{
	int k = 0;
	while (ptree->children[k] == NULL && k < 50)
		k++;
	return k;
}

parseTree optimize_operator(parseTree ptree)
{
	parseTree ans;
	if (checkIfOperator(ptree->name))
	{
		int k = 0;
		while (ptree->children[k] == NULL && k<50)
			k++;

		parseTree a = optimize_operator(ptree->children[k]);
		k++;
		while (ptree->children[k] == NULL && k<50)
			k++;
		parseTree b = optimize_operator(ptree->children[k]);
		ans = ptree->children[k]->children[firstChildIndex(ptree->children[k])];

		ans->childrenNumber = 2;
		ans->children[0] = a;
		ans->children[0]->parent = ans;
		ans->children[1] = b;
		ans->children[1]->parent = ans;
		ans->parent = ptree->parent;
		return ans;

	}
	else if (checkIfRecursive(ptree->name))
	{
		if (ptree->childrenNumber == 2)
		{
			int o = firstChildIndex(ptree);
			o++;
			while (ptree->children[o] == NULL && o < 50)
				o++;
			return ptree->children[o];
		}
		else
		{
			int o = firstChildIndex(ptree);
			o++;
			while (ptree->children[o] == NULL && o < 50)
				o++;
			parseTree a = optimize_operator(ptree->children[o]);
			o++;
			while (ptree->children[o] == NULL && o < 50)
				o++;
			parseTree b = optimize_operator(ptree->children[o]);
			ans = ptree->children[o]->children[firstChildIndex(ptree->children[o])];
			ans->childrenNumber = 2;
			ans->children[0] = a;
			ans->children[0]->parent = ans;
			ans->children[1] = b;
			ans->children[1]->parent = ans;
			ans->parent = ptree->parent;
			return ans;
		}
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
		{
			if (ptree->children[k] != NULL)
				ptree->children[k] = optimize_operator(ptree->children[k]);
		}
		return ptree;
	}
}


parseTree addLeaves(parseTree ans, parseTree travel)
{
	if (travel == NULL)
		return ans;
	if (travel->childrenNumber == 0)
	{
		ans->children[ans->childrenNumber] = travel;
		ans->children[ans->childrenNumber]->parent = ans;
		ans->childrenNumber++;	
		return ans;
	}
	int k;
	k = firstChildIndex(travel);
	ans = addLeaves(ans, travel->children[k]);
	k++;
	while (travel->children[k] == NULL && k < 50)
		k++;
	ans = addLeaves(ans, travel->children[k]);
	return ans;
}


parseTree optimize_declaration(parseTree ptree)
{
	parseTree ans;
	if (ptree->name == 8 && ptree->children[firstChildIndex(ptree)]->name >= 75 && ptree->children[firstChildIndex(ptree)]->name <= 79)
	{
		int k = 0;
		while (ptree->children[k] == NULL && k<50)
			k++;

		parseTree ans = (ptree->children[k]);
		k++;

		while (ptree->children[k] == NULL && k<50)
			k++;
		parseTree a = ptree->children[k];

		ans->childrenNumber = 1;
		ans->children[0] = a;
		ans->children[0]->parent = ans;
		ans->parent = ptree->parent;
		
		if (ptree->childrenNumber == 3){
			k++;
			while (ptree->children[k] == NULL && k<50)
				k++;
			parseTree travel = ptree->children[k];
			ans=addLeaves(ans, travel);
		}
		return ans;

	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
		{
			if (ptree->children[k] != NULL)
				ptree->children[k] = optimize_declaration(ptree->children[k]);
		}
		return ptree;
	}
}



parseTree assignHandler(parseTree ptree)
{

	if (ptree->name == 22)
	{
		int k;
		k = firstChildIndex(ptree);
		parseTree a = assignHandler(ptree->children[k]);
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		parseTree ans = ptree->children[k];
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		parseTree b = assignHandler(ptree->children[k]);
		ans->childrenNumber = 2;
		ans->children[0] = a;
		ans->children[0]->parent = ans;
		ans->children[1] = b;
		ans->children[1]->parent = ans;
		ans->parent = ptree->parent;
		return ans;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ptree->children[k] != NULL)
				ptree->children[k] = assignHandler(ptree->children[k]);
		return ptree;
	}
}


parseTree selectionHandler(parseTree ptree)
{
	if (ptree->name == 34)
	{
		int k;
		k = firstChildIndex(ptree);
		parseTree ans = ptree->children[k];
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		parseTree a = ptree->children[k];
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		parseTree b = selectionHandler(ptree->children[k]);

		ans->childrenNumber = 2;
		ans->children[0] = a;
		ans->children[0]->parent = ans;
		ans->children[1] = b;
		ans->children[1]->parent = ans;
		ans->parent = ptree->parent;

		if (ptree->childrenNumber == 4){
			k++;
			while (ptree->children[k] == NULL && k < 50)
				k++;
			int l = firstChildIndex(ptree->children[k]);
			l++;
			while (ptree->children[k]->children[l] == NULL && l < 50)
				l++;
			parseTree c = selectionHandler(ptree->children[k]->children[l]);
			ans->childrenNumber = 3;
			ans->children[2] = c;
			ans->children[2]->parent = ans;
		}
		return ans;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ptree->children[k] != NULL)
				ptree->children[k] = selectionHandler(ptree->children[k]);
		return ptree;
	}
}

parseTree iterationHandler(parseTree ptree)
{

	if (ptree->name == 36)
	{
		int k;
		k = firstChildIndex(ptree);
		parseTree ans = ptree->children[k];
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		parseTree a = ptree->children[k];
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		parseTree b = iterationHandler(ptree->children[k]);
		ans->childrenNumber = 2;
		ans->children[0] = a;
		ans->children[0]->parent = ans;
		ans->children[1] = b;
		ans->children[1]->parent = ans;
		ans->parent = ptree->parent;
		
		return ans;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ptree->children[k] != NULL)
				ptree->children[k] = iterationHandler(ptree->children[k]);
		return ptree;
	}
}



parseTree referenceHandler(parseTree ptree)
{
	if (ptree->name == 27)
	{
		int k;
		k = firstChildIndex(ptree);
		parseTree a = ptree->children[k];
		k++;
		while (ptree->children[k] == NULL && k < 50)
			k++;
		int l = firstChildIndex(ptree->children[k]);
		parseTree ans = (ptree->children[k]->children[l]);
		l++;
		while (ptree->children[k]->children[l] == NULL && l < 50)
			l++;
		parseTree b =(ptree->children[k]->children[l]);

		ans->childrenNumber = 2;
		ans->children[0] = a;
		ans->children[0]->parent = ans;
		ans->children[1] = b;
		ans->children[1]->parent = ans;
		ans->parent = ptree->parent;
		return ans;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ptree->children[k] != NULL)
				ptree->children[k] = referenceHandler(ptree->children[k]);
		return ptree;
	}
}

parseTree multipleAssignHandler(parseTree ast)
{
	if (ast->name == 82)
	{
		int k;
		k = firstChildIndex(ast);

		if (ast->children[k]->name == 25){
			int l = firstChildIndex(ast->children[k]);
			l++;
			while (ast->children[k]->children[l] == NULL && l < 50)
				l++;
			ast->children[k]->childrenNumber = 1;
			ast->children[k] = addLeaves(ast->children[k], ast->children[k]->children[l]);
		}
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;
		if (ast->children[k]->name == 23)
		{
			int l = firstChildIndex(ast->children[k]);
			l++;
			while (ast->children[k]->children[l] == NULL && l < 50)
				l++;
			ast->children[k]->childrenNumber = 1;
			ast->children[k] = addLeaves(ast->children[k], ast->children[k]->children[l]);
		}
		return ast;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				ast->children[k] =  multipleAssignHandler(ast->children[k]);
		return ast;
	}
}


parseTree handleDeclarator(parseTree ast)
{
	if (ast->name == 18)
	{
		int k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		int ptr = l + 1;
		ast->childrenNumber = ast->childrenNumber - 1;

		parseTree travel = ast->children[k];
		ast->children[k] = NULL;
		while (travel->name == 18)
		{
			int y = firstChildIndex(travel);
			ast->children[ptr++] = travel->children[y];
			ast->childrenNumber++;

			y++;
			while (travel->children[y] == NULL && y < 50)
				y++;
			travel = travel->children[y];
		}

		ast->children[ptr] = travel;
		ast->childrenNumber++;
		return ast;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				ast->children[k]=handleDeclarator(ast->children[k]);
		return ast;
	}
}

parseTree handleManyAssignments(parseTree ast)
{
	if (ast->name == 19)
	{
		int k = firstChildIndex(ast);
		int l = k;
		k++;
		while (ast->children[k] == NULL && k < 50)
			k++;

		int ptr = l + 1;
		ast->childrenNumber = ast->childrenNumber - 1;

		parseTree travel = ast->children[k];
		ast->children[k] = NULL;
		while (travel->name == 19)
		{
			int y = firstChildIndex(travel);
			ast->children[ptr++] = travel->children[y];
			ast->childrenNumber++;

			y++;
			while (travel->children[y] == NULL && y < 50)
				y++;
			travel = travel->children[y];
		}

		ast->children[ptr] = travel;
		ast->childrenNumber++;
		return ast;
	}
	else
	{
		int k = 0;
		for (k = 0; k < 50; k++)
			if (ast->children[k] != NULL)
				ast->children[k] = handleManyAssignments(ast->children[k]);
		return ast;
	}


}


parseTree ast(parseTree ptree)
{
	ptree = epsilonReduce(ptree);
	ptree = useLessTerminals(ptree);
	ptree = useLessNonTerminals(ptree);
	ptree = optimize_operator(ptree);
	ptree = assignHandler(ptree);
	ptree = multipleAssignHandler(ptree);
	ptree = handleManyAssignments(ptree);
	ptree = selectionHandler(ptree);
	ptree = iterationHandler(ptree);
	ptree = optimize_declaration(ptree);
	ptree = handleDeclarator(ptree);
	ptree = referenceHandler(ptree);
	print(ptree, "./astOutput.txt");
	return ptree;
}
