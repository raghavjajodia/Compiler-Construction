#include<stdio.h>
#include<string.h>
#define MAXRULES 150
#define MAXCHILDREN 50
#define MAXNONTERMINALS 70
#define MAXTERMINALS 70
#include<stdlib.h>
#define BUFLENGTH 600
#define rows 59
#define columns 50
// struct
typedef struct{                                                                 //move it to .h file
	int lineno;
	char lexeme[100];
	char tokenName[50];
}token;

struct node{
	int terminal;
	int name;
	token info;
	char* type;
	int childrenNumber;
	struct node * children[50];
	struct node* parent;
};

struct stac{
	int ptrtop;
	int arr[10000];
};


struct symbolTableNode {
	char name[100];
	int lineDeclared;
	int lineReferenced[50];
	char dataType[20];
	char value[50];
	int scope;
	struct symbolTableNode *next;
	int scope2;
};


struct hash {
	struct symbolTableNode *head;
	int count;
};


// Typedef
typedef struct node * parseTree;

// Global declarations
token globalTokens[1000];
char ** symanticErrors;
int tokenNumber;

char* resolution[MAXTERMINALS + MAXNONTERMINALS];
int parseTable[59][50];
int rhs[MAXRULES + 1];
int rules[120 + 5][10 + 5];
int input[1000];
parseTree mainTree;
int Label;

struct hash *hashTable;
int eleCount;

//Function Definition
void generateTokens(char buffer[BUFLENGTH], int currenLine, int state);
void copy_string(char *target, char *source);
int isCharacter(char c);
int goto37(char c);
void lexer(FILE * filename, FILE *fp);

struct node * createNode(int terminal, int name);
struct stac push_stack(struct stac inputStack, int el);
struct stac pop_stack(struct stac inputStack);
int top_stack(struct stac inputStack);
int empty_stack(struct stac inputStack);
parseTree backtrack(parseTree treePointer);
int parse(int inputsize);
int findIdByName(char arr[50]);
void printPreorderParseTree(parseTree ptree, FILE * fout);
void printPostorderParseTree(parseTree ptree, FILE * fout);
void print(parseTree ptree, char filePath[50]);
void parseInitialize();

unsigned long hash(unsigned char *str);
struct symbolTableNode * makeSymbolNode(int lineDeclared, int scope, char *name, char *dataType, int lineReference);
void insertToHash(int lineDeclared, int scope, char *name, char *dataType, int lineReference);
void deleteFromHash(char* name);
int searchInHash(char* name);
void display();
void initializeSymbolTable();
void insertWithRefernce(int RefencedLine, char *name);

int useLess(char* c);
parseTree useLessTerminals(parseTree ptree);
parseTree useLessNonTerminals(parseTree ptree);
parseTree ast(parseTree ptree);

void compoundCode(int reg, parseTree ast, FILE *fp);
void assignmentCode(int reg, parseTree ast, FILE *fp);
void selectionCode(int reg, parseTree ast, FILE *fp);


void copy_string(char *target, char *source)
{
	while (*source)
	{
		*target = *source;
		source++;
		target++;
	}
	*target = '\0';
}
int isCharacter(char c)
{
	if (c == ':' || c == '(' || c == '.' || c == '+' || c == '*' || c == '/' || c == '>' || c == '<' || c == '|' || c == '&' || c == '!' || c == ',' || c == '{' || c == '}' || c == ')' || c == ']' || c == '[' || c == ' ' || c == ';' || c == '=' || c == 0)
		return 1;
	else
		return 0;
}

int goto37(char c)
{
	if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z'))
		return 1;
	else
		return 0;
}

void lexer(FILE * filename, FILE *fp)
{
	tokenNumber = 0;
	int currentLine = 1;
	int state = 0;
	char buffer[BUFLENGTH];
	int i;

	while (fgets(buffer, sizeof(buffer), filename))
	{
		i = 0;
		while (buffer[i] != '\n'&&buffer[i] != 0)
		{
			if (buffer[i] == '#')
			{
				buffer[i] = ' ';
				buffer[i + 1] = '\n';
			}
			i++;
		}
		generateTokens(buffer, currentLine, state);
		currentLine++;

	}
	int t = 0;
	for (i = 1; i<currentLine; i++)
	{
		fprintf(fp, "LINE NO. %d   ", i);

		for (t = 0; t<tokenNumber; t++){
			if ((i) == globalTokens[t].lineno)
			{
				fprintf(fp, "  %s", globalTokens[t].tokenName);
			}

		}
		fprintf(fp, " \n");
	}
}

void generateTokens(char buffer[BUFLENGTH], int currenLine, int state)
{
	int current = 0;
	char lexeme[BUFLENGTH];
	memset(lexeme, NULL, sizeof(lexeme));
	int lexemeptr = 0;
	char c;
	token temp;
	int slashnflag = 0;

	while (1)
	{
		c = buffer[current++];

		if (c == '\n' || c == NULL)
		{
			slashnflag = 1;
			break;
		}

		switch (state)
		{
		case 0: {
			// c=buffer[current++];
			if (c == ' '){
				state = 0;
				break;
			}
			else if (c == 't')
			{
				state = 1;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'f')
			{
				state = 2;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'i')
			{
				state = 3;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'b')
			{
				state = 4;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'c')
			{
				state = 5;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'a')
			{
				state = 6;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 's')
			{
				state = 7;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'e')
			{
				state = 8;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'w')
			{
				state = 9;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'r')
			{
				state = 10;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'm')
			{
				state = 11;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'o')
			{
				state = 12;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'x')
			{
				state = 13;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				state = 14;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'n')
			{
				state = 15;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '.')
			{
				state = 16;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ':')
			{
				state = 17;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '&')
			{
				state = 18;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '<')
			{
				state = 19;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '>')
			{
				state = 20;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '=')
			{
				state = 21;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '+')
			{
				state = 22;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '|')
			{
				state = 23;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '*')
			{
				state = 24;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '!')
			{
				state = 25;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '/')
			{
				state = 26;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ']')
			{
				state = 27;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '{')
			{
				state = 28;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '}')
			{
				state = 29;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '(')
			{
				state = 30;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ')')
			{
				state = 31;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '\"')
			{
				state = 32;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '\'')
			{
				state = 33;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ',')
			{
				state = 34;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ';')
			{
				state = 35;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '[')
			{
				state = 36;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z'))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		}


		case 1:{
			if (c == 'r')
			{
				state = 38;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z'))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}


			else
			{
				state = 500;                                      //default
				break;
			}

		}



		case 2:{

			if (c == 'u')
			{
				state = 39;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'a')
			{
				state = 40;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}
		}

		case 3:

			if (c == 'f')
			{
				state = 41;
				lexeme[lexemeptr++] = c;
				break;
			}

			if (c == 'n')
			{
				state = 42;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 4:

			if (c == 'o')
			{
				state = 43;
				lexeme[lexemeptr++] = c;
				break;
			}


			if (c == 'r')
			{
				state = 44;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				//  lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 5:

			if (c == 'h')
			{
				state = 45;
				lexeme[lexemeptr++] = c;
				break;
			}

			if (c == 'o')
			{
				state = 46;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200; current--;
				//lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 6:

			if (c == 'n')
			{
				state = 47;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (c == 'r')
			{
				state = 48;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				//lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 7:

			if (c == 't')
			{
				state = 49;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 8:

			if (c == 'l')
			{
				state = 50;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				// lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 9:

			if (c == 'h')
			{
				state = 51;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 10:

			if (c == 'e')
			{
				state = 52;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}
		case 11:

			if (c == 'a')
			{
				state = 53;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 12:

			if (c == 'r')
			{
				state = 54;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				// lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}
		case 13:

			if (c == 'o')
			{
				state = 55;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 14:

			if (c == '.')
			{
				state = 56;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (isCharacter(c))
			{
				state = 57;
				current--;
				break;
			}
			if (c >= '0'&&c <= '9')
			{
				state = 14;
				lexeme[lexemeptr++] = c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 15:

			if (c == 'e')
			{
				state = 58;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 16:

			if (c >= '0'&&c <= '9')                                    {
				state = 60;
				lexeme[lexemeptr++] = c;
				break;
			}
			else                      // check this
			{
				state = 59; current--;
				break;
			}

		case 17:                                                            // fianal state check
			temp.lineno = currenLine;
			copy_string(temp.lexeme, ":");
			copy_string(temp.tokenName, "tk_slic");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			memset(lexeme, NULL, sizeof(lexeme));
			state = 0;
			current--;
			break;

		case 18:

			if (c == '&')
			{
				state = 61;
				lexeme[lexemeptr++] = c;
				break;
			}
			else
			{
				state = 500;                                      //default
				break;
			}
		case 19:

			if (c == '=')
			{
				state = 63;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (c == '<')
			{
				state = 62;
				lexeme[lexemeptr++] = c;
				break;
			}
			else
			{
				state = 64;  current--;                                    //default
				break;
			}

		case 20:

			if (c == '=')
			{
				state = 67;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (c == '>')
			{
				state = 66;
				lexeme[lexemeptr++] = c;
				break;
			}

			else
			{
				state = 65; current--;
				break;
			}

		case 21:

			if (c == '=')
			{
				state = 69;
				lexeme[lexemeptr++] = c;
				break;
			}
			else
			{
				state = 68; current--;
				break;
			}

		case 22:       					// why current++
			temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_add");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 23:		if (c == '|')
		{
			state = 70;
			lexeme[lexemeptr++] = c;
			break;
		}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 24:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_mul");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 25:		if (c == '=')
		{
			state = 71;
			lexeme[lexemeptr++] = c;
			break;
		}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 26:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_div");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 27:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_rightsq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 28:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_leftbr");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 29:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_rightbr");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 30:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_leftpa");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 31:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_rightpa");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 32:		if (c != '\"')
		{
			state = 32;
			lexeme[lexemeptr++] = c;
			break;

		}
						else
						{
							state = 72;
							lexeme[lexemeptr++] = c;
							break;
						}




		case 33:		if (c != '\'')
		{
			state = 150;
			lexeme[lexemeptr++] = c;
			break;

		}
						else
						{
							state = 200;
							break;
						}
		case 150:		if (c == '\'')
		{
			state = 73;
			lexeme[lexemeptr++] = c;
			break;

		}
						else
						{
							state = 200;
							break;
						}

		case 34:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_comma");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 35:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_colon");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 36:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_leftsq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 37:		if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z') || (c >= '0'&&c <= '9'))
		{
			state = 37;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (isCharacter(c))                    // check this
						{
							state = 200;
							current--;
							break;
						}

		case 200:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_id");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 38:		if (c == 'u')
		{
			state = 74;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200;
							//lexeme[lexemeptr++]= c;
							current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 39:		if (c == 'n')
		{
			state = 75;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200;
							//lexeme[lexemeptr++]= c;
							current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 40:		if (c == 'l')
		{
			state = 76;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200;
							current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 41:	if (c == ' ' || c == '(')
		{
			state = 78; current--;
			break;
		}
					else if (goto37(c))
					{
						state = 37;
						lexeme[lexemeptr++] = c;
						break;
					}
					else
					{
						state = 500;                                      //default
						break;
					}

		case 42:	if (c == 't')
		{
			state = 79;
			lexeme[lexemeptr++] = c;
			break;
		}
					else if (goto37(c))
					{
						state = 37;
						lexeme[lexemeptr++] = c;
						break;
					}

					else if (isCharacter(c))
					{
						state = 200; current--;
						//lexeme[lexemeptr++]= c;
						break;
					}
					else
					{
						state = 500;                                      //default
						break;
					}

		case 43:		if (c == 'o')
		{
			state = 80;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 44:	if (c == 'e')
		{
			state = 81;
			lexeme[lexemeptr++] = c;
			break;
		}
					else if (goto37(c))
					{
						state = 37;
						lexeme[lexemeptr++] = c;
						break;
					}

					else if (isCharacter(c))
					{
						state = 200; current--;
						//lexeme[lexemeptr++]= c;
						break;
					}
					else
					{
						state = 500;                                      //default
						break;
					}
		case 45:		if (c == 'a')
		{
			state = 82;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 46:		if (c == 'm')
		{
			state = 83;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 47:		if (c == 'd')
		{
			state = 84;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 48:		if (c == 'r')
		{
			state = 85;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 49:		if (c == 'r')
		{
			state = 86;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 50:		if (c == 's')
		{
			state = 87;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 51:		if (c == 'i')
		{
			state = 88;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 52:		if (c == 't')
		{
			state = 89;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if(c=='a'){
							state = 501;
							lexeme[lexemeptr++] = c;
							break;
						}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 53:		if (c == 'i')
		{
			state = 90;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 54:		if (c == ' ')
		{
			state = 91; current--;
			//lexeme[lexemeptr++]= c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 55:		if (c == 'r')
		{
			state = 92;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 56:		if (c >= '0'&&c <= '9')
		{
			state = 93;
			lexeme[lexemeptr++] = c;
			break;
		}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 57:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_intlit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 58:		if (c == 'g')
		{
			state = 94;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 59:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_ref");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 60:		if (c >= '0'&&c <= '9')
		{
			state = 60;
			lexeme[lexemeptr++] = c;
			break;
		}
						if (isCharacter(c))
						{
							state = 95; current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 61:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_logand");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 62:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_bitshift");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 63:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_lseq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 64:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_ls");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 65:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_gr");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 66:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_bitrshift");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 67:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_greq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 68:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_assign");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 69:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_eq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 70:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_logor");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 71:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_ne");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 72:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_string_literal");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 73:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_charlit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 74:		if (c == 'e')
		{
			state = 96;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 75:		if (c == 'c')
		{
			state = 97;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 76:		if (c == 's')
		{
			state = 98;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 77: // missing
		case 78:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_if");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current = current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 79:		if (c == ' ' || c == ')')
		{
			state = 99;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 80:		if (c == 'l')
		{
			state = 100;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 81:		if (c == 'a')
		{
			state = 101;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 82:		if (c == 'r')
		{
			state = 102;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 83:		if (c == 'p')
		{
			state = 103;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 84:		if (c == ' ')
		{
			state = 104;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 85:		if (c == 'a')
		{
			state = 105;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 86:		if (c == 'u')
		{
			state = 106;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 87:		if (c == 'e')
		{
			state = 107;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 88:		if (c == 'l')
		{
			state = 108;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 89:		if (c == 'u')
		{
			state = 109;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 90:		if (c == 'n')
		{
			state = 110;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 91:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_or");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 92:		if (c == ' ')
		{
			state = 111; current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 93:		if (c >= '0'&&c <= '9')
		{
			state = 93;
			lexeme[lexemeptr++] = c;
			break;

		}
						if (isCharacter(c))
						{
							state = 112; current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 94:		if (c == ' ')
		{
			state = 113;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 95:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_reallit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 96:		if (c == ' ' || c == ')' || c == ';'||c==',')
		{
			state = 114;
			current--;
			break;

		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 97:		if (c == 't')
		{
			state = 115;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 98:		if (c == 'e')
		{
			state = 116;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 99:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_int");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 100:		if (c == ' ')
		{
			state = 117; current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;
							current--;//default
							break;
						}
		case 101:		if (c == 'k')
		{
			state = 118;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 102:		if (c == ' ')
		{
			state = 119;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 103:		if (c == 'l')
		{
			state = 120;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 104:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_and");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 105:		if (c == 'y')
		{
			state = 121;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 106:		if (c == 'c')
		{
			state = 122;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 107:		if (c == ' ' || c == '{'||c=='\n' || c == NULL)
		{
			state = 123;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 108:		if (c == 'e')
		{
			state = 124;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 109:		if (c == 'r')
		{
			state = 125;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 110:		if (c == ' ' || c == '(')
		{
			state = 126;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 111:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_xor");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 112:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_reallit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 113:		if (c == '.')
		{
			state = 129;
			lexeme[lexemeptr++] = c;
			break;
		}
						if (c >= '0'&&c <= '9')
						{
							state = 128;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 114:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_true");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;

			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 115:		if (c == 'i')
		{
			state = 130;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 116:		if (c == ' ' || c == ')' || c == ';'||c==',')
		{
			state = 131;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 117:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_bool");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 118:		if (c == ' ' || c == ';')
		{
			state = 132; current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 119:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_char");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 120:		if (c == 'e')
		{
			state = 133;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 121:			if (c == ' ')
		{
			state = 134;
			current--;
			break;
		}
							else if (goto37(c))
							{
								state = 37;
								lexeme[lexemeptr++] = c;
								break;
							}
							else
							{
								state = 500;                                      //default
								break;
							}
		case 122:		 if (c == 't')
		{
			state = 135;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 123:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_else");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 124:		if (c == ' ' || c == '(')
		{
			state = 136;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 125:		 if (c == 'n')
		{
			state = 137;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 126:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_main");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 128:		 if (c >= '0'&&c <= '9')
		{
			state = 128;
			lexeme[lexemeptr++] = c;
			break;
		}
						 if (c == ' ')
						 {
							 state = 139; current--;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 129:		 if (c >= '0'&&c <= '9')
		{
			state = 138;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 130:		 if (c == 'o')
		{
			state = 140;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 131:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_false");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 132:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_break");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 133:		 if (c == 'x')
		{
			state = 141;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 134:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_array");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 135:		if (c == ' ')
		{
			state = 142;
			current--;
			break;

		}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 136:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_while");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 137:		if (c == ' ' || c == ';' || c == '(')
		{
			state = 143;
			current--;
			break;

		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 138:		if (c >= '0'&&c <= '9')
		{
			state = 138;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (isCharacter(c))
						{
							state = 144; current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 139:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_intlit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 140:		 if (c == 'n')
		{
			state = 145;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 141:		if (c == ' ')
		{
			state = 146;
			current--;
			break;

		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 142:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_struct");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 143:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_return");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 144:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_reallit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 145:		if (c == ' ')
		{
			state = 147;
			current--;
			break;


		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 146:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_complex");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 147:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_func");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 501:		if (c == 'l')
						{
							state = 502;
							lexeme[lexemeptr++] = c;
							break;
						}

						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }

		case 502:		if (c == ' ' || c == ';' || c == '(')
							{
								state = 503;
								current--;
								break;
		
							}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 503:	temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_real");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 500:		printf("\nLEXICAL ERROR in line no. %d\n", currenLine);
			return;



		}

	}

	if (slashnflag == 1)
	{


		switch (state)
		{
		case 0: {
			// c=buffer[current++];
			if (c == ' '){
				state = 0;
				break;
			}
			else if (c == 't')
			{
				state = 1;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'f')
			{
				state = 2;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'i')
			{
				state = 3;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'b')
			{
				state = 4;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'c')
			{
				state = 5;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'a')
			{
				state = 6;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 's')
			{
				state = 7;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'e')
			{
				state = 8;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'w')
			{
				state = 9;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'r')
			{
				state = 10;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'm')
			{
				state = 11;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'o')
			{
				state = 12;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'x')
			{
				state = 13;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c >= '0' && c <= '9')
			{
				state = 14;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'n')
			{
				state = 15;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '.')
			{
				state = 16;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ':')
			{
				state = 17;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '&')
			{
				state = 18;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '<')
			{
				state = 19;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '>')
			{
				state = 20;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '=')
			{
				state = 21;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '+')
			{
				state = 22;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '|')
			{
				state = 23;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '*')
			{
				state = 24;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '!')
			{
				state = 25;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '/')
			{
				state = 26;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ']')
			{
				state = 27;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '{')
			{
				state = 28;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '}')
			{
				state = 29;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '(')
			{
				state = 30;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ')')
			{
				state = 31;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '\"')
			{
				state = 32;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '\'')
			{
				state = 33;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ',')
			{
				state = 34;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == ';')
			{
				state = 35;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '[')
			{
				state = 36;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z'))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		}


		case 1:{
			if (c == 'r')
			{
				state = 38;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z'))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}


			else
			{
				state = 500;                                      //default
				break;
			}

		}



		case 2:{

			if (c == 'u')
			{
				state = 39;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (c == 'a')
			{
				state = 40;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}
		}

		case 3:

			if (c == 'f')
			{
				state = 41;
				lexeme[lexemeptr++] = c;
				break;
			}

			if (c == 'n')
			{
				state = 42;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 4:

			if (c == 'o')
			{
				state = 43;
				lexeme[lexemeptr++] = c;
				break;
			}


			if (c == 'r')
			{
				state = 44;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				//  lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 5:

			if (c == 'h')
			{
				state = 45;
				lexeme[lexemeptr++] = c;
				break;
			}

			if (c == 'o')
			{
				state = 46;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200; current--;
				//lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 6:

			if (c == 'n')
			{
				state = 47;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (c == 'r')
			{
				state = 48;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				//lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 7:

			if (c == 't')
			{
				state = 49;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				current--;
				// lexeme[lexemeptr++]= c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 8:

			if (c == 'l')
			{
				state = 50;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				// lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 9:

			if (c == 'h')
			{
				state = 51;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 10:

			if (c == 'e')
			{
				state = 52;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}
		case 11:

			if (c == 'a')
			{
				state = 53;
				lexeme[lexemeptr++] = c;
				break;
			}


			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 12:

			if (c == 'r')
			{
				state = 54;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				// lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}
		case 13:

			if (c == 'o')
			{
				state = 55;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 14:

			if (c == '.')
			{
				state = 56;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (isCharacter(c))
			{
				state = 57;
				current--;
				break;
			}
			if (c >= '0'&&c <= '9')
			{
				state = 14;
				lexeme[lexemeptr++] = c;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 15:

			if (c == 'e')
			{
				state = 58;
				lexeme[lexemeptr++] = c;
				break;
			}
			else if (goto37(c))
			{
				state = 37;
				lexeme[lexemeptr++] = c;
				break;
			}

			else if (isCharacter(c))
			{
				state = 200;
				//lexeme[lexemeptr++]= c;
				current--;
				break;
			}

			else
			{
				state = 500;                                      //default
				break;
			}

		case 16:

			if (c >= '0'&&c <= '9')                                    {
				state = 60;
				lexeme[lexemeptr++] = c;
				break;
			}
			else                      // check this
			{
				state = 59; current--;
				break;
			}

		case 17:                                                            // fianal state check
			temp.lineno = currenLine;
			copy_string(temp.lexeme, ":");
			copy_string(temp.tokenName, "tk_slic");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			memset(lexeme, NULL, sizeof(lexeme));
			state = 0;
			current--;
			break;

		case 18:

			if (c == '&')
			{
				state = 61;
				lexeme[lexemeptr++] = c;
				break;
			}
			else
			{
				state = 500;                                      //default
				break;
			}
		case 19:

			if (c == '=')
			{
				state = 63;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (c == '<')
			{
				state = 62;
				lexeme[lexemeptr++] = c;
				break;
			}
			else
			{
				state = 64;  current--;                                    //default
				break;
			}

		case 20:

			if (c == '=')
			{
				state = 67;
				lexeme[lexemeptr++] = c;
				break;
			}
			if (c == '>')
			{
				state = 66;
				lexeme[lexemeptr++] = c;
				break;
			}

			else
			{
				state = 65; current--;
				break;
			}

		case 21:

			if (c == '=')
			{
				state = 69;
				lexeme[lexemeptr++] = c;
				break;
			}
			else
			{
				state = 68; current--;
				break;
			}

		case 22:       					// why current++
			temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_add");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 23:		if (c == '|')
		{
			state = 70;
			lexeme[lexemeptr++] = c;
			break;
		}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 24:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_mul");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 25:		if (c == '=')
		{
			state = 71;
			lexeme[lexemeptr++] = c;
			break;
		}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 26:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_div");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 27:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_rightsq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 28:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_leftbr");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 29:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_rightbr");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 30:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_leftpa");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 31:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_rightpa");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 32:		if (c != '\"')
		{
			state = 32;
			lexeme[lexemeptr++] = c;
			break;

		}
						else
						{
							state = 72;
							lexeme[lexemeptr++] = c;
							break;
						}




		case 33:		if (c != '\'')
		{
			state = 150;
			lexeme[lexemeptr++] = c;
			break;

		}
						else
						{
							state = 200;
							break;
						}
		case 150:		if (c == '\'')
		{
			state = 73;
			lexeme[lexemeptr++] = c;
			break;

		}
						else
						{
							state = 200;
							break;
						}

		case 34:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_comma");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 35:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_colon");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 36:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_leftsq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 37:		if (c == '_' || (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z') || (c >= '0'&&c <= '9'))
		{
			state = 37;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (isCharacter(c))                    // check this
						{
							state = 200;
							current--;
							break;
						}

		case 200:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_id");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 38:		if (c == 'u')
		{
			state = 74;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200;
							//lexeme[lexemeptr++]= c;
							current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 39:		if (c == 'n')
		{
			state = 75;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200;
							//lexeme[lexemeptr++]= c;
							current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 40:		if (c == 'l')
		{
			state = 76;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200;
							current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 41:	if (c == ' ' || c == '(')
		{
			state = 78; current--;
			break;
		}
					else if (goto37(c))
					{
						state = 37;
						lexeme[lexemeptr++] = c;
						break;
					}
					else
					{
						state = 500;                                      //default
						break;
					}

		case 42:	if (c == 't')
		{
			state = 79;
			lexeme[lexemeptr++] = c;
			break;
		}
					else if (goto37(c))
					{
						state = 37;
						lexeme[lexemeptr++] = c;
						break;
					}

					else if (isCharacter(c))
					{
						state = 200; current--;
						//lexeme[lexemeptr++]= c;
						break;
					}
					else
					{
						state = 500;                                      //default
						break;
					}

		case 43:		if (c == 'o')
		{
			state = 80;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 44:	if (c == 'e')
		{
			state = 81;
			lexeme[lexemeptr++] = c;
			break;
		}
					else if (goto37(c))
					{
						state = 37;
						lexeme[lexemeptr++] = c;
						break;
					}

					else if (isCharacter(c))
					{
						state = 200; current--;
						//lexeme[lexemeptr++]= c;
						break;
					}
					else
					{
						state = 500;                                      //default
						break;
					}
		case 45:		if (c == 'a')
		{
			state = 82;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 46:		if (c == 'm')
		{
			state = 83;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 47:		if (c == 'd')
		{
			state = 84;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 48:		if (c == 'r')
		{
			state = 85;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 49:		if (c == 'r')
		{
			state = 86;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 50:		if (c == 's')
		{
			state = 87;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 51:		if (c == 'i')
		{
			state = 88;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 52:		if (c == 't')
		{
			state = 89;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 53:		if (c == 'i')
		{
			state = 90;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 54:		if (c == ' ')
		{
			state = 91; current--;
			//lexeme[lexemeptr++]= c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 55:		if (c == 'r')
		{
			state = 92;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 56:		if (c >= '0'&&c <= '9')
		{
			state = 93;
			lexeme[lexemeptr++] = c;
			break;
		}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 57:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_intlit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 58:		if (c == 'g')
		{
			state = 94;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 59:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_ref");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 60:		if (c >= '0'&&c <= '9')
		{
			state = 60;
			lexeme[lexemeptr++] = c;
			break;
		}
						if (isCharacter(c))
						{
							state = 95; current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 61:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_logand");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 62:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_bitshift");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 63:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_lseq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 64:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_ls");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 65:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_gr");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 66:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_bitrshift");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 67:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_greq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 68:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_assign");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 69:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_eq");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 70:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_logor");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 71:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_ne");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 72:		temp.lineno = currenLine;
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_string_literal");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 73:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_charlit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 74:		if (c == 'e')
		{
			state = 96;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 75:		if (c == 'c')
		{
			state = 97;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 76:		if (c == 's')
		{
			state = 98;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 77: // missing
		case 78:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_if");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current = current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 79:		if (c == ' ' || c == ')')
		{
			state = 99;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 80:		if (c == 'l')
		{
			state = 100;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 81:		if (c == 'a')
		{
			state = 101;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 82:		if (c == 'r')
		{
			state = 102;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 83:		if (c == 'p')
		{
			state = 103;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 84:		if (c == ' ')
		{
			state = 104;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 85:		if (c == 'a')
		{
			state = 105;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 86:		if (c == 'u')
		{
			state = 106;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 87:		if (c == 'e')
		{
			state = 107;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 88:		if (c == 'l')
		{
			state = 108;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 89:		if (c == 'u')
		{
			state = 109;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 90:		if (c == 'n')
		{
			state = 110;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 91:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_or");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 92:		if (c == ' ')
		{
			state = 111; current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 93:		if (c >= '0'&&c <= '9')
		{
			state = 93;
			lexeme[lexemeptr++] = c;
			break;

		}
						if (isCharacter(c))
						{
							state = 112; current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 94:		if (c == ' ')
		{
			state = 113;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 95:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_reallit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 96:		if (c == ' ' || c == ')' || c == ';'||c==',')
		{
			state = 114;
			current--;
			break;

		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 97:		if (c == 't')
		{
			state = 115;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 98:		if (c == 'e')
		{
			state = 116;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 99:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_int");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 100:		if (c == ' ')
		{
			state = 117; current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;
							current--;//default
							break;
						}
		case 101:		if (c == 'k')
		{
			state = 118;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 102:		if (c == ' ')
		{
			state = 119;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 103:		if (c == 'l')
		{
			state = 120;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 104:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_and");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 105:		if (c == 'y')
		{
			state = 121;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 106:		if (c == 'c')
		{
			state = 122;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 107:		if (c == ' ' || c == '{'||c=='\n' || c == NULL)
		{
			state = 123;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}

		case 108:		if (c == 'e')
		{
			state = 124;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 109:		if (c == 'r')
		{
			state = 125;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 110:		if (c == ' ' || c == '(')
		{
			state = 126;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 111:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_xor");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 112:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_reallit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 113:		if (c == '.')
		{
			state = 129;
			lexeme[lexemeptr++] = c;
			break;
		}
						if (c >= '0'&&c <= '9')
						{
							state = 128;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 114:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_true");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;

			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 115:		if (c == 'i')
		{
			state = 130;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 116:		if (c == ' ' || c == ')' || c == ';'||c==',')
		{
			state = 131;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 117:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_bool");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 118:		if (c == ' ' || c == ';')
		{
			state = 132; current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 119:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_char");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 120:		if (c == 'e')
		{
			state = 133;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}

						else if (isCharacter(c))
						{
							state = 200; current--;
							//lexeme[lexemeptr++]= c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 121:			if (c == ' ')
		{
			state = 134;
			current--;
			break;
		}
							else if (goto37(c))
							{
								state = 37;
								lexeme[lexemeptr++] = c;
								break;
							}
							else
							{
								state = 500;                                      //default
								break;
							}
		case 122:		 if (c == 't')
		{
			state = 135;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 123:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_else");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 124:		if (c == ' ' || c == '(')
		{
			state = 136;
			current--;
			break;
		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 125:		 if (c == 'n')
		{
			state = 137;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 126:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_main");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 128:		 if (c >= '0'&&c <= '9')
		{
			state = 128;
			lexeme[lexemeptr++] = c;
			break;
		}
						 if (c == ' ')
						 {
							 state = 139; current--;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 129:		 if (c >= '0'&&c <= '9')
		{
			state = 138;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 130:		 if (c == 'o')
		{
			state = 140;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 131:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_false");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 132:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_break");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 133:		 if (c == 'x')
		{
			state = 141;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 134:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_array");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 135:		if (c == ' ')
		{
			state = 142;
			current--;
			break;

		}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 136:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_while");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 137:		if (c == ' ' || c == ';' || c == '(')
		{
			state = 143;
			current--;
			break;

		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 138:		if (c >= '0'&&c <= '9')
		{
			state = 138;
			lexeme[lexemeptr++] = c;
			break;
		}
						else if (isCharacter(c))
						{
							state = 144; current--;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 139:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_intlit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 140:		 if (c == 'n')
		{
			state = 145;
			lexeme[lexemeptr++] = c;
			break;
		}
						 else if (goto37(c))
						 {
							 state = 37;
							 lexeme[lexemeptr++] = c;
							 break;
						 }

						 else if (isCharacter(c))
						 {
							 state = 200; current--;
							 //lexeme[lexemeptr++]= c;
							 break;
						 }
						 else
						 {
							 state = 500;                                      //default
							 break;
						 }
		case 141:		if (c == ' ')
		{
			state = 146;
			current--;
			break;

		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 142:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_struct");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 143:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_return");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 144:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_reallit");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 145:		if (c == ' ')
		{
			state = 147;
			current--;
			break;


		}
						else if (goto37(c))
						{
							state = 37;
							lexeme[lexemeptr++] = c;
							break;
						}
						else
						{
							state = 500;                                      //default
							break;
						}
		case 146:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_complex");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;
		case 147:		temp.lineno = currenLine;						// check this
			copy_string(temp.lexeme, lexeme);
			copy_string(temp.tokenName, "tk_func");
			globalTokens[tokenNumber++] = temp;
			lexemeptr = 0;
			state = 0;
			current--;
			memset(lexeme, NULL, sizeof(lexeme));
			break;

		case 500:		printf("\nLEXICAL ERROR in line no. %d\n", currenLine);
			return;



		}

	}
}


struct node * createNode(int terminal, int name)
{
	struct node* temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->terminal = terminal;
	temp->childrenNumber = 0;
	temp->name = name;
	temp->parent = NULL;
	int i;
	for (i = 0; i<MAXCHILDREN; i++)
	{
		temp->children[i] = NULL;
	}
	return temp;
}

struct stac push_stack(struct stac inputStack, int el)
{
	if (inputStack.ptrtop == 9999){
		printf("Memory full for stack\n");
		return inputStack;
	}
	inputStack.ptrtop++;
	inputStack.arr[inputStack.ptrtop] = el;
	return inputStack;
}

struct stac pop_stack(struct stac inputStack)
{
	if (inputStack.ptrtop == 0)
	{
		printf("error, stack already empty\n");
		return inputStack;
	}
	inputStack.ptrtop = inputStack.ptrtop - 1;
	return inputStack;
}

int top_stack(struct stac inputStack)
{
	if (inputStack.ptrtop == 0)
	{
		printf("Error, stack empty");
		return -9999999;
	}
	return inputStack.arr[inputStack.ptrtop];
}

int empty_stack(struct stac inputStack)
{
	return (inputStack.ptrtop == 0);
}

parseTree backtrack(parseTree treePointer)
{
	if (treePointer == NULL)
		return NULL;
	parseTree parent = treePointer->parent;
	if (parent == NULL)
		return NULL;
	int i;
	for (i = 0; i<parent->childrenNumber; i++)
	{
		if (parent->children[i] == treePointer)
			break;
	}
	if (parent->children[i + 1] != NULL)
		return parent->children[i + 1];
	return backtrack(parent);
}


int parse(int inputsize)
{
	FILE * fout = fopen("./parseTreeOutput.txt", "w+");
	// int rows=strlen(parseTable);
	mainTree = createNode(0, 0);

	parseTree treePointer = mainTree;
	// mainTree->childrenNumber=rhs[1];
	struct stac st;
	st.ptrtop = 0;
	st = push_stack(st, rows);
	st = push_stack(st, 0);
	int inputptr = 0;
	int errorflag = 0;

	while (!empty_stack(st) && inputptr<inputsize && !errorflag)
	{
		//		int input_top = input[inputptr];
		if (top_stack(st) == -1)
		{
			st = pop_stack(st);
			treePointer = backtrack(treePointer);
		}
		else if (top_stack(st) == input[inputptr])
		{
			//		printf("terminal\n");
			if (input[inputptr] != 59){
				treePointer->info.lineno = globalTokens[inputptr].lineno;
				strcpy(treePointer->info.lexeme, globalTokens[inputptr].lexeme);
				strcpy(treePointer->info.tokenName, globalTokens[inputptr].tokenName);
				if (top_stack(st) != -1)
					inputptr++;
				st = pop_stack(st);
				treePointer = backtrack(treePointer);
			}
			else{
				inputptr++;
				st = pop_stack(st);
			}
		}
		else if (parseTable[top_stack(st)][input[inputptr] - rows] != 0)
		{
			//	printf("%d--->", top_stack(st));
			int top = top_stack(st);
			st = pop_stack(st);
			treePointer->childrenNumber = rhs[parseTable[top][input[inputptr] - rows]];
			int i;
			for (i = rhs[parseTable[top][input[inputptr] - rows]] - 1; i >= 0; i--)
			{
				int nodeNum = rules[parseTable[top][input[inputptr] - rows]][i];

				st = push_stack(st, rules[parseTable[top][input[inputptr] - rows]][i]);
				if (nodeNum >= rows || nodeNum == -1){
					treePointer->children[i] = createNode(1, nodeNum);
					treePointer->children[i]->parent = treePointer;

				}
				else{
					treePointer->children[i] = createNode(0, nodeNum);
					treePointer->children[i]->parent = treePointer;
				}
			}
			treePointer = treePointer->children[0];
		}
		else if (top_stack(st) >= rows)
		{
			fprintf(fout, "Error, not expected %s ", resolution[input[inputptr]]);
			errorflag = 1;
			break;
		}
		else
		{
			fprintf(fout, "Rule not found for %s, %s", resolution[top_stack(st)], resolution[input[inputptr]]);
			errorflag = 1;
			break;
		}

	}

	fclose(fout);
	return errorflag;
}

int findIdByName(char arr[50])
{
	int i = 0;
	int flag = 0;
	for (i = 0; i<109; i++)
	{
		if (strcmp(resolution[i], arr) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0){
		printf("Error, could not find id of %s by name\n", arr);
		return -1;
	}
	else
		return i;
}


void printPreorderParseTree(parseTree ptree, FILE * fout)
{
	if (ptree != NULL)
	{
		if (ptree->name == -1)
			fprintf(fout, "Epsilon\n");
		else
			fprintf(fout, "%s\n", resolution[ptree->name]);
		int i;
		for (i = 0; i<50; i++)
			if (ptree->children[i] != NULL)
				printPreorderParseTree(ptree->children[i], fout);
	}
}

void printPostorderParseTree(parseTree ptree, FILE * fout)
{
	if (ptree != NULL)
	{
		int i;
		for (i = 0; i<50; i++)
			if (ptree->children[i] != NULL)
				printPostorderParseTree(ptree->children[i], fout);

		if (ptree->name == -1)
			fprintf(fout, "Epsilon\n");
		else
			fprintf(fout, "%s\n", resolution[ptree->name]);
	}
}

void print(parseTree ptree, char filePath[50])
{
	FILE * fout = fopen(filePath, "w+");
	fprintf(fout, "Preorder Traversal: \n\n");
	printPreorderParseTree(ptree, fout);
	fprintf(fout, "\nPostorder Traversal: \n\n");
	printPostorderParseTree(ptree, fout);
	fclose(fout);
}


void parseInitialize()
{
	memset(parseTable, 0, sizeof parseTable);
	parseTable[1][0] = 3;
	parseTable[0][1] = 1;
	parseTable[1][4] = 2;
	parseTable[1][7] = 2;
	parseTable[1][13] = 2;
	parseTable[1][75 - 59] = 2;
	parseTable[1][76 - 59] = 2;
	parseTable[1][77 - 59] = 2;
	parseTable[1][78 - 59] = 2;
	parseTable[1][79 - 59] = 2;
	parseTable[2][4] = 4;
	parseTable[2][66 - 59] = 5;
	parseTable[2][72 - 59] = 5;
	parseTable[2][75 - 59] = 5;
	parseTable[2][76 - 59] = 5;
	parseTable[2][77 - 59] = 5;
	parseTable[2][78 - 59] = 5;
	parseTable[2][79 - 59] = 5;
	parseTable[3][1] = 6;
	parseTable[4][63 - 59] = 7;
	parseTable[5][62 - 59] = 9;
	parseTable[5][66 - 59] = 8;
	parseTable[5][75 - 59] = 8;
	parseTable[5][76 - 59] = 8;
	parseTable[5][77 - 59] = 8;
	parseTable[5][78 - 59] = 8;
	parseTable[5][79 - 59] = 8;
	parseTable[6][62 - 59] = 11;
	parseTable[6][65 - 59] = 10;
	parseTable[7][66 - 59] = 13;
	parseTable[7][75 - 59] = 12;
	parseTable[7][76 - 59] = 12;
	parseTable[7][77 - 59] = 12;
	parseTable[7][78 - 59] = 12;
	parseTable[7][79 - 59] = 12;
	parseTable[8][66 - 59] = 15;
	parseTable[8][72 - 59] = 16;
	parseTable[8][75 - 59] = 14;
	parseTable[8][76 - 59] = 14;
	parseTable[8][77 - 59] = 14;
	parseTable[8][78 - 59] = 14;
	parseTable[8][79 - 59] = 14;
	parseTable[9][64 - 59] = 18;
	parseTable[9][73 - 59] = 17;
	parseTable[10][65 - 59] = 19;
	parseTable[10][71 - 59] = 20;
	parseTable[11][75 - 59] = 21;
	parseTable[11][76 - 59] = 22;
	parseTable[11][77 - 59] = 23;
	parseTable[11][78 - 59] = 24;
	parseTable[11][79 - 59] = 25;
	parseTable[12][66 - 59] = 26;
	parseTable[13][6] = 27;
	parseTable[13][12] = 28;
	parseTable[14][7] = 30;
	parseTable[14][16] = 29;
	parseTable[14][17] = 29;
	parseTable[14][18] = 29;
	parseTable[14][19] = 29;
	parseTable[14][20] = 29;
	parseTable[15][7] = 31;
	parseTable[15][15] = 32;
	parseTable[15][16] = 31;
	parseTable[15][17] = 31;
	parseTable[15][18] = 31;
	parseTable[15][19] = 31;
	parseTable[15][20] = 31;
	parseTable[16][5] = 33;
	parseTable[17][14] = 34;
	parseTable[18][4] = 36;
	parseTable[18][5] = 36;
	parseTable[18][7] = 35;
	parseTable[18][13] = 35;
	parseTable[18][14] = 36;
	parseTable[18][15] = 36;
	parseTable[18][16] = 35;
	parseTable[18][17] = 35;
	parseTable[18][18] = 35;
	parseTable[18][19] = 35;
	parseTable[18][20] = 35;
	parseTable[18][21] = 36;
	parseTable[18][22] = 36;
	parseTable[18][26] = 36;
	parseTable[18][28] = 36;
	parseTable[19][4] = 37;
	parseTable[19][5] = 37;
	parseTable[19][14] = 37;
	parseTable[19][15] = 38;
	parseTable[19][21] = 37;
	parseTable[19][22] = 37;
	parseTable[19][26] = 37;
	parseTable[19][28] = 37;
	parseTable[20][4] = 44;
	parseTable[20][5] = 43;
	parseTable[20][14] = 39;
	parseTable[20][21] = 42;
	parseTable[20][22] = 42;
	parseTable[20][26] = 40;
	parseTable[20][28] = 41;
	parseTable[21][21] = 45;
	parseTable[21][22] = 46;
	parseTable[22][5] = 47;
	parseTable[23][2] = 48;
	parseTable[23][4] = 49;
	parseTable[23][5] = 48;
	parseTable[23][44] = 48;
	parseTable[23][45] = 48;
	parseTable[23][46] = 48;
	parseTable[23][47] = 48;
	parseTable[23][48] = 48;
	parseTable[23][49] = 48;
	parseTable[24][6] = 50;
	parseTable[25][5] = 51;
	parseTable[26][6] = 52;
	parseTable[26][23] = 53;
	parseTable[27][5] = 54;
	parseTable[28][3] = 57;
	parseTable[28][6] = 57;
	parseTable[28][8] = 57;
	parseTable[28][9] = 57;
	parseTable[28][10] = 56;
	parseTable[28][11] = 57;
	parseTable[28][12] = 57;
	parseTable[28][23] = 57;
	parseTable[28][24] = 55;
	parseTable[28][25] = 57;
	parseTable[28][29] = 57;
	parseTable[28][30] = 57;
	parseTable[28][31] = 57;
	parseTable[28][32] = 57;
	parseTable[28][33] = 57;
	parseTable[28][34] = 57;
	parseTable[28][35] = 57;
	parseTable[28][36] = 57;
	parseTable[28][37] = 57;
	parseTable[28][38] = 57;
	parseTable[28][39] = 57;
	parseTable[28][40] = 57;
	parseTable[28][41] = 57;
	parseTable[28][42] = 57;
	parseTable[28][43] = 57;
	parseTable[29][2] = 58;
	parseTable[29][5] = 58;
	parseTable[29][44] = 58;
	parseTable[29][45] = 58;
	parseTable[29][46] = 58;
	parseTable[29][47] = 58;
	parseTable[29][48] = 58;
	parseTable[29][49] = 58;
	parseTable[30][11] = 60;
	parseTable[30][25] = 59;
	parseTable[31][4] = 61;
	parseTable[32][2] = 62;
	parseTable[32][3] = 63;
	parseTable[32][5] = 62;
	parseTable[32][44] = 62;
	parseTable[32][45] = 62;
	parseTable[32][46] = 62;
	parseTable[32][47] = 62;
	parseTable[32][48] = 62;
	parseTable[32][49] = 62;
	parseTable[33][3] = 65;
	parseTable[33][6] = 64;
	parseTable[33][12] = 65;
	parseTable[34][26] = 66;
	parseTable[35][4] = 68;
	parseTable[35][5] = 68;
	parseTable[35][14] = 68;
	parseTable[35][15] = 68;
	parseTable[35][21] = 68;
	parseTable[35][22] = 68;
	parseTable[35][26] = 68;
	parseTable[35][27] = 67;
	parseTable[35][28] = 68;
	parseTable[36][28] = 69;
	parseTable[37][2] = 70;
	parseTable[37][5] = 70;
	parseTable[37][44] = 70;
	parseTable[37][45] = 70;
	parseTable[37][46] = 70;
	parseTable[37][47] = 70;
	parseTable[37][48] = 70;
	parseTable[37][49] = 70;
	parseTable[38][2] = 71;
	parseTable[38][5] = 71;
	parseTable[38][44] = 71;
	parseTable[38][45] = 71;
	parseTable[38][46] = 71;
	parseTable[38][47] = 71;
	parseTable[38][48] = 71;
	parseTable[38][49] = 71;
	parseTable[39][3] = 73;
	parseTable[39][6] = 73;
	parseTable[39][12] = 73;
	parseTable[39][29] = 72;
	parseTable[40][2] = 74;
	parseTable[40][5] = 74;
	parseTable[40][44] = 74;
	parseTable[40][45] = 74;
	parseTable[40][46] = 74;
	parseTable[40][47] = 74;
	parseTable[40][48] = 74;
	parseTable[40][49] = 74;
	parseTable[41][3] = 76;
	parseTable[41][6] = 76;
	parseTable[41][12] = 76;
	parseTable[41][29] = 76;
	parseTable[41][30] = 75;
	parseTable[42][2] = 77;
	parseTable[42][5] = 77;
	parseTable[42][44] = 77;
	parseTable[42][45] = 77;
	parseTable[42][46] = 77;
	parseTable[42][47] = 77;
	parseTable[42][48] = 77;
	parseTable[42][49] = 77;
	parseTable[43][3] = 79;
	parseTable[43][6] = 79;
	parseTable[43][12] = 79;
	parseTable[43][29] = 79;
	parseTable[43][30] = 79;
	parseTable[43][31] = 78;
	parseTable[44][2] = 80;
	parseTable[44][5] = 80;
	parseTable[44][44] = 80;
	parseTable[44][45] = 80;
	parseTable[44][46] = 80;
	parseTable[44][47] = 80;
	parseTable[44][48] = 80;
	parseTable[45][3] = 82;
	parseTable[45][6] = 82;
	parseTable[45][12] = 82;
	parseTable[45][29] = 82;
	parseTable[45][30] = 82;
	parseTable[45][31] = 82;
	parseTable[45][32] = 81;
	parseTable[46][2] = 83;
	parseTable[46][5] = 83;
	parseTable[46][44] = 83;
	parseTable[46][45] = 83;
	parseTable[46][46] = 83;
	parseTable[46][47] = 83;
	parseTable[46][48] = 83;
	parseTable[46][49] = 83;
	parseTable[47][3] = 85;
	parseTable[47][6] = 85;
	parseTable[47][12] = 85;
	parseTable[47][29] = 85;
	parseTable[47][30] = 85;
	parseTable[47][31] = 85;
	parseTable[47][32] = 85;
	parseTable[47][33] = 84;
	parseTable[48][2] = 86;
	parseTable[48][5] = 86;
	parseTable[48][44] = 86;
	parseTable[48][45] = 86;
	parseTable[48][46] = 86;
	parseTable[48][47] = 86;
	parseTable[48][48] = 86;
	parseTable[48][49] = 86;
	parseTable[49][3] = 93;
	parseTable[49][6] = 93;
	parseTable[49][8] = 89;
	parseTable[49][9] = 90;
	parseTable[49][12] = 93;
	parseTable[49][29] = 93;
	parseTable[49][30] = 93;
	parseTable[49][31] = 93;
	parseTable[49][32] = 93;
	parseTable[49][33] = 93;
	parseTable[49][34] = 87;
	parseTable[49][35] = 88;
	parseTable[49][36] = 91;
	parseTable[49][37] = 92;
	parseTable[50][2] = 94;
	parseTable[50][5] = 94;
	parseTable[50][44] = 94;
	parseTable[50][45] = 94;
	parseTable[50][46] = 94;
	parseTable[50][47] = 94;
	parseTable[50][48] = 94;
	parseTable[50][49] = 94;
	parseTable[51][3] = 97;
	parseTable[51][6] = 97;
	parseTable[51][8] = 97;
	parseTable[51][9] = 97;
	parseTable[51][12] = 97;
	parseTable[51][29] = 97;
	parseTable[51][30] = 97;
	parseTable[51][31] = 97;
	parseTable[51][32] = 97;
	parseTable[51][33] = 97;
	parseTable[51][34] = 97;
	parseTable[51][35] = 97;
	parseTable[51][36] = 97;
	parseTable[51][37] = 97;
	parseTable[51][38] = 95;
	parseTable[51][39] = 96;
	parseTable[52][2] = 98;
	parseTable[52][5] = 98;
	parseTable[52][44] = 98;
	parseTable[52][45] = 98;
	parseTable[52][46] = 98;
	parseTable[52][47] = 98;
	parseTable[52][48] = 98;
	parseTable[52][49] = 98;
	parseTable[53][3] = 101;
	parseTable[53][6] = 101;
	parseTable[53][8] = 101;
	parseTable[53][9] = 101;
	parseTable[53][11] = 101;
	parseTable[53][12] = 101;
	parseTable[53][29] = 101;
	parseTable[53][30] = 101;
	parseTable[53][31] = 101;
	parseTable[53][32] = 101;
	parseTable[53][33] = 101;
	parseTable[53][34] = 101;
	parseTable[53][35] = 101;
	parseTable[53][36] = 101;
	parseTable[53][37] = 101;
	parseTable[53][38] = 101;
	parseTable[53][39] = 101;
	parseTable[53][40] = 99;
	parseTable[53][41] = 100;
	parseTable[54][2] = 102;
	parseTable[54][5] = 102;
	parseTable[54][44] = 102;
	parseTable[54][45] = 102;
	parseTable[54][46] = 102;
	parseTable[54][47] = 102;
	parseTable[54][48] = 102;
	parseTable[54][49] = 102;
	parseTable[55][3] = 105;
	parseTable[55][6] = 105;
	parseTable[55][8] = 105;
	parseTable[55][9] = 105;
	parseTable[55][11] = 105;
	parseTable[55][12] = 105;
	parseTable[55][25] = 105;
	parseTable[55][29] = 105;
	parseTable[55][30] = 105;
	parseTable[55][31] = 105;
	parseTable[55][32] = 105;
	parseTable[55][33] = 105;
	parseTable[55][34] = 105;
	parseTable[55][35] = 105;
	parseTable[55][36] = 105;
	parseTable[55][37] = 105;
	parseTable[55][38] = 105;
	parseTable[55][39] = 105;
	parseTable[55][40] = 105;
	parseTable[55][41] = 105;
	parseTable[55][42] = 103;
	parseTable[55][43] = 104;
	parseTable[56][2] = 106;
	parseTable[56][5] = 108;
	parseTable[56][44] = 107;
	parseTable[56][45] = 107;
	parseTable[56][46] = 107;
	parseTable[56][47] = 107;
	parseTable[56][48] = 107;
	parseTable[56][49] = 107;
	parseTable[57][2] = 110;
	parseTable[57][5] = 110;
	parseTable[57][16] = 109;
	parseTable[57][17] = 109;
	parseTable[57][19] = 109;
	parseTable[57][20] = 109;
	parseTable[57][44] = 110;
	parseTable[57][45] = 110;
	parseTable[57][46] = 110;
	parseTable[57][47] = 110;
	parseTable[57][48] = 110;
	parseTable[57][49] = 110;
	parseTable[58][44] = 111;
	parseTable[58][45] = 112;
	parseTable[58][46] = 113;
	parseTable[58][47] = 114;
	parseTable[58][48] = 115;
	parseTable[58][49] = 116;
	parseTable[24][12] = 117;

	rhs[1] = 2;
	rhs[2] = 2;
	rhs[3] = 1;
	rhs[4] = 1;
	rhs[5] = 1;
	rhs[6] = 4;
	rhs[7] = 6;
	rhs[8] = 2;
	rhs[9] = 1;
	rhs[10] = 3;
	rhs[11] = 1;
	rhs[12] = 2;
	rhs[13] = 8;
	rhs[14] = 4;
	rhs[15] = 2;
	rhs[16] = 3;
	rhs[17] = 3;
	rhs[18] = 3;
	rhs[19] = 3;
	rhs[20] = 1;
	rhs[21] = 1;
	rhs[22] = 1;
	rhs[23] = 1;
	rhs[24] = 1;
	rhs[25] = 1;
	rhs[26] = 9;
	rhs[27] = 6;
	rhs[28] = 1;
	rhs[29] = 5;
	rhs[30] = 3;
	rhs[31] = 1;
	rhs[32] = 1;
	rhs[33] = 1;
	rhs[34] = 4;
	rhs[35] = 2;
	rhs[36] = 1;
	rhs[37] = 2;
	rhs[38] = 1;
	rhs[39] = 1;
	rhs[40] = 1;
	rhs[41] = 1;
	rhs[42] = 1;
	rhs[43] = 1;
	rhs[44] = 2;
	rhs[45] = 2;
	rhs[46] = 4;
	rhs[47] = 4;
	rhs[48] = 2;
	rhs[49] = 2;
	rhs[50] = 2;
	rhs[51] = 2;
	rhs[52] = 3;
	rhs[53] = 1;
	rhs[54] = 2;
	rhs[55] = 2;
	rhs[56] = 3;
	rhs[57] = 1;
	rhs[58] = 2;
	rhs[59] = 2;
	rhs[60] = 1;
	rhs[61] = 5;
	rhs[62] = 2;
	rhs[63] = 1;
	rhs[64] = 3;
	rhs[65] = 1;
	rhs[66] = 6;
	rhs[67] = 2;
	rhs[68] = 1;
	rhs[69] = 5;
	rhs[70] = 1;
	rhs[71] = 2;
	rhs[72] = 3;
	rhs[73] = 1;
	rhs[74] = 2;
	rhs[75] = 3;
	rhs[76] = 1;
	rhs[77] = 2;
	rhs[78] = 3;
	rhs[79] = 1;
	rhs[80] = 2;
	rhs[81] = 3;
	rhs[82] = 1;
	rhs[83] = 2;
	rhs[84] = 3;
	rhs[85] = 1;
	rhs[86] = 2;
	rhs[87] = 3;
	rhs[88] = 3;
	rhs[89] = 3;
	rhs[90] = 3;
	rhs[91] = 3;
	rhs[92] = 3;
	rhs[93] = 1;
	rhs[94] = 2;
	rhs[95] = 3;
	rhs[96] = 3;
	rhs[97] = 1;
	rhs[98] = 2;
	rhs[99] = 3;
	rhs[100] = 3;
	rhs[101] = 1;
	rhs[102] = 2;
	rhs[103] = 3;
	rhs[104] = 3;
	rhs[105] = 1;
	rhs[106] = 2;
	rhs[107] = 1;
	rhs[108] = 1;
	rhs[109] = 5;
	rhs[110] = 2;
	rhs[111] = 1;
	rhs[112] = 1;
	rhs[113] = 1;
	rhs[114] = 1;
	rhs[115] = 1;
	rhs[116] = 1;
	rhs[117] = 1;

	rules[1][0] = 3;
	rules[1][1] = 1;
	rules[2][0] = 2;
	rules[2][1] = 1;
	rules[3][0] = -1;
	rules[4][0] = 4;
	rules[5][0] = 8;
	rules[6][0] = 60;
	rules[6][1] = 61;
	rules[6][2] = 62;
	rules[6][3] = 17;
	rules[7][0] = 63;
	rules[7][1] = 64;
	rules[7][2] = 61;
	rules[7][3] = 5;
	rules[7][4] = 62;
	rules[7][5] = 17;
	rules[8][0] = 7;
	rules[8][1] = 6;
	rules[9][0] = -1;
	rules[10][0] = 65;
	rules[10][1] = 7;
	rules[10][2] = 6;
	rules[11][0] = -1;
	rules[12][0] = 11;
	rules[12][1] = 64;
	rules[13][0] = 66;
	rules[13][1] = 67;
	rules[13][2] = 11;
	rules[13][3] = 68;
	rules[13][4] = 64;
	rules[13][5] = 69;
	rules[13][6] = 52;
	rules[13][7] = 70;
	rules[14][0] = 11;
	rules[14][1] = 64;
	rules[14][2] = 10;
	rules[14][3] = 71;
	rules[15][0] = 12;
	rules[15][1] = 71;
	rules[16][0] = 72;
	rules[16][1] = 16;
	rules[16][2] = 9;
	rules[17][0] = 73;
	rules[17][1] = 14;
	rules[17][2] = 74;
	rules[18][0] = 64;
	rules[18][1] = 10;
	rules[18][2] = 71;
	rules[19][0] = 65;
	rules[19][1] = 64;
	rules[19][2] = 10;
	rules[20][0] = -1;
	rules[21][0] = 75;
	rules[22][0] = 76;
	rules[23][0] = 77;
	rules[24][0] = 78;
	rules[25][0] = 79;
	rules[26][0] = 66;
	rules[26][1] = 67;
	rules[26][2] = 11;
	rules[26][3] = 68;
	rules[26][4] = 64;
	rules[26][5] = 69;
	rules[26][6] = 52;
	rules[26][7] = 70;
	rules[26][8] = 13;
	rules[27][0] = 65;
	rules[27][1] = 64;
	rules[27][2] = 69;
	rules[27][3] = 52;
	rules[27][4] = 70;
	rules[27][5] = 13;
	rules[28][0] = -1;
	rules[29][0] = 11;
	rules[29][1] = 64;
	rules[29][2] = 10;
	rules[29][3] = 71;
	rules[29][4] = 15;
	rules[30][0] = 12;
	rules[30][1] = 71;
	rules[30][2] = 15;
	rules[31][0] = 14;
	rules[32][0] = -1;
	rules[33][0] = 64;
	rules[34][0] = 73;
	rules[34][1] = 18;
	rules[34][2] = 19;
	rules[34][3] = 74;
	rules[35][0] = 8;
	rules[35][1] = 18;
	rules[36][0] = -1;
	rules[37][0] = 20;
	rules[37][1] = 19;
	rules[38][0] = -1;
	rules[39][0] = 17;
	rules[40][0] = 34;
	rules[41][0] = 36;
	rules[42][0] = 21;
	rules[43][0] = 22;
	rules[44][0] = 31;
	rules[44][1] = 71;
	rules[45][0] = 80;
	rules[45][1] = 71;
	rules[46][0] = 81;
	rules[46][1] = 37;
	rules[46][2] = 33;
	rules[46][3] = 71;
	rules[47][0] = 25;
	rules[47][1] = 82;
	rules[47][2] = 23;
	rules[47][3] = 71;
	rules[48][0] = 37;
	rules[48][1] = 24;
	rules[49][0] = 31;
	rules[49][1] = 24;
	rules[50][0] = 65;
	rules[50][1] = 23;
	rules[51][0] = 27;
	rules[51][1] = 26;
	rules[52][0] = 65;
	rules[52][1] = 27;
	rules[52][2] = 26;
	rules[53][0] = -1;
	rules[54][0] = 64;
	rules[54][1] = 28;
	rules[55][0] = 83;
	rules[55][1] = 64;
	rules[56][0] = 69;
	rules[56][1] = 29;
	rules[56][2] = 70;
	rules[57][0] = -1;
	rules[58][0] = 52;
	rules[58][1] = 30;
	rules[59][0] = 84;
	rules[59][1] = 52;
	rules[60][0] = -1;
	rules[61][0] = 63;
	rules[61][1] = 64;
	rules[61][2] = 61;
	rules[61][3] = 32;
	rules[61][4] = 62;
	rules[62][0] = 37;
	rules[62][1] = 33;
	rules[63][0] = -1;
	rules[64][0] = 65;
	rules[64][1] = 37;
	rules[64][2] = 33;
	rules[65][0] = -1;
	rules[66][0] = 85;
	rules[66][1] = 61;
	rules[66][2] = 37;
	rules[66][3] = 62;
	rules[66][4] = 17;
	rules[66][5] = 35;
	rules[67][0] = 86;
	rules[67][1] = 17;
	rules[68][0] = -1;
	rules[69][0] = 87;
	rules[69][1] = 61;
	rules[69][2] = 37;
	rules[69][3] = 62;
	rules[69][4] = 17;
	rules[70][0] = 38;
	rules[71][0] = 40;
	rules[71][1] = 39;
	rules[72][0] = 88;
	rules[72][1] = 40;
	rules[72][2] = 39;
	rules[73][0] = -1;
	rules[74][0] = 42;
	rules[74][1] = 41;
	rules[75][0] = 89;
	rules[75][1] = 42;
	rules[75][2] = 41;
	rules[76][0] = -1;
	rules[77][0] = 44;
	rules[77][1] = 43;
	rules[78][0] = 90;
	rules[78][1] = 44;
	rules[78][2] = 43;
	rules[79][0] = -1;
	rules[80][0] = 46;
	rules[80][1] = 45;
	rules[81][0] = 91;
	rules[81][1] = 46;
	rules[81][2] = 45;
	rules[82][0] = -1;
	rules[83][0] = 48;
	rules[83][1] = 47;
	rules[84][0] = 92;
	rules[84][1] = 48;
	rules[84][2] = 47;
	rules[85][0] = -1;
	rules[86][0] = 50;
	rules[86][1] = 49;
	rules[87][0] = 93;
	rules[87][1] = 50;
	rules[87][2] = 49;
	rules[88][0] = 94;
	rules[88][1] = 50;
	rules[88][2] = 49;
	rules[89][0] = 67;
	rules[89][1] = 50;
	rules[89][2] = 49;
	rules[90][0] = 68;
	rules[90][1] = 50;
	rules[90][2] = 49;
	rules[91][0] = 95;
	rules[91][1] = 50;
	rules[91][2] = 49;
	rules[92][0] = 96;
	rules[92][1] = 50;
	rules[92][2] = 49;
	rules[93][0] = -1;
	rules[94][0] = 52;
	rules[94][1] = 51;
	rules[95][0] = 97;
	rules[95][1] = 52;
	rules[95][2] = 51;
	rules[96][0] = 98;
	rules[96][1] = 52;
	rules[96][2] = 51;
	rules[97][0] = -1;
	rules[98][0] = 54;
	rules[98][1] = 53;
	rules[99][0] = 99;
	rules[99][1] = 54;
	rules[99][2] = 53;
	rules[100][0] = 100;
	rules[100][1] = 54;
	rules[100][2] = 53;
	rules[101][0] = -1;
	rules[102][0] = 56;
	rules[102][1] = 55;
	rules[103][0] = 101;
	rules[103][1] = 56;
	rules[103][2] = 55;
	rules[104][0] = 102;
	rules[104][1] = 56;
	rules[104][2] = 55;
	rules[105][0] = -1;
	rules[106][0] = 61;
	rules[106][1] = 57;
	rules[107][0] = 58;
	rules[108][0] = 27;
	rules[109][0] = 11;
	rules[109][1] = 62;
	rules[109][2] = 61;
	rules[109][3] = 37;
	rules[109][4] = 62;
	rules[110][0] = 37;
	rules[110][1] = 62;
	rules[111][0] = 103;
	rules[112][0] = 104;
	rules[113][0] = 105;
	rules[114][0] = 106;
	rules[115][0] = 107;
	rules[116][0] = 108;
	rules[117][0] = -1;

	resolution[0] = "Start";
	resolution[1] = "Externals";
	resolution[2] = "External_declaration";
	resolution[3] = "Main";
	resolution[4] = "Function_definition";
	resolution[5] = "Arglist";
	resolution[6] = "Arglist_extended";
	resolution[7] = "Arg_declaration";
	resolution[8] = "Declaration";
	resolution[9] = "Struct_left_factored";
	resolution[10] = "Extending_declarator";
	resolution[11] = "Primitive_type_specifier";
	resolution[12] = "Array_declaration";
	resolution[13] = "Array_declarator";
	resolution[14] = "Struct_list";
	resolution[15] = "Struct_list_declarator";
	resolution[16] = "Struct_name";
	resolution[17] = "Compound_statement";
	resolution[18] = "Declarator";
	resolution[19] = "Many_statements";
	resolution[20] = "Statement";
	resolution[21] = "Jump_statement";
	resolution[22] = "Assignment_statement";
	resolution[23] = "Variable_list_left_factored";
	resolution[24] = "Multi_assignment";
	resolution[25] = "Variable_list";
	resolution[26] = "Variable_extender";
	resolution[27] = "Lhs";
	resolution[28] = "Id_left_factored";
	resolution[29] = "Locator";
	resolution[30] = "Additive_expression_left_factored";
	resolution[31] = "Function_call";
	resolution[32] = "Parameters";
	resolution[33] = "Return_values";
	resolution[34] = "Selection_statement";
	resolution[35] = "If_left_factored";
	resolution[36] = "Iteration_statement";
	resolution[37] = "Expression";
	resolution[38] = "Logical_or_expression";
	resolution[39] = "Logical_or_left_recursion";
	resolution[40] = "Logical_and_expression";
	resolution[41] = "Logical_and_left_recursion";
	resolution[42] = "Inclusive_or_expression";
	resolution[43] = "Inclusive_or_left_recursion";
	resolution[44] = "Exclusive_or_expression";
	resolution[45] = "Exclusive_or_left_recursion";
	resolution[46] = "And_expression";
	resolution[47] = "And_left_recursion";
	resolution[48] = "Relational_expression";
	resolution[49] = "Relational_left_recursion";
	resolution[50] = "Shift_expression";
	resolution[51] = "Shift_left_recursive";
	resolution[52] = "Additive_expression";
	resolution[53] = "Additive_left_recursive";
	resolution[54] = "Multiplicative_expression";
	resolution[55] = "Multiplicative_left_recursive";
	resolution[56] = "Cast_expression";
	resolution[57] = "Root_expression_left_factored";
	resolution[58] = "Literal";
	resolution[59] = "$";
	resolution[60] = "tk_main";
	resolution[61] = "tk_leftpa";
	resolution[62] = "tk_rightpa";
	resolution[63] = "tk_func";
	resolution[64] = "tk_id";
	resolution[65] = "tk_comma";
	resolution[66] = "tk_array";
	resolution[67] = "tk_ls";
	resolution[68] = "tk_gr";
	resolution[69] = "tk_leftsq";
	resolution[70] = "tk_rightsq";
	resolution[71] = "tk_colon";
	resolution[72] = "tk_struct";
	resolution[73] = "tk_leftbr";
	resolution[74] = "tk_rightbr";
	resolution[75] = "tk_char";
	resolution[76] = "tk_int";
	resolution[77] = "tk_real";
	resolution[78] = "tk_bool";
	resolution[79] = "tk_complex";
	resolution[80] = "tk_break";
	resolution[81] = "tk_return";
	resolution[82] = "tk_assign";
	resolution[83] = "tk_ref";
	resolution[84] = "tk_slic";
	resolution[85] = "tk_if";
	resolution[86] = "tk_else";
	resolution[87] = "tk_while";
	resolution[88] = "tk_logor";
	resolution[89] = "tk_logand";
	resolution[90] = "tk_bitor";
	resolution[91] = "tk_xor";
	resolution[92] = "tk_bitand";
	resolution[93] = "tk_eq";
	resolution[94] = "tk_neq";
	resolution[95] = "tk_lseq";
	resolution[96] = "tk_greq";
	resolution[97] = "tk_bitlshift";
	resolution[98] = "tk_bitrshift";
	resolution[99] = "tk_add";
	resolution[100] = "tk_sub";
	resolution[101] = "tk_mul";
	resolution[102] = "tk_div";
	resolution[103] = "tk_charlit";
	resolution[104] = "tk_intlit";
	resolution[105] = "tk_reallit";
	resolution[106] = "tk_true";
	resolution[107] = "tk_false";
	resolution[108] = "tk_string_literal";

	/*
	input[0] = findIdByName("tk_main");
	input[1] = findIdByName("tk_leftpa");
	input[2] = findIdByName("tk_rightpa");
	input[3] = findIdByName("tk_leftbr");
	input[4] = findIdByName("tk_real");
	input[5] = findIdByName("tk_id");
	input[6] = findIdByName("tk_comma");
	input[7] = findIdByName("tk_id");
	input[8] = findIdByName("tk_colon");
	input[9] = findIdByName("tk_rightbr");
	input[10] = 59;
	*/
}

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
		ans = optimize_operator(ptree->children[k]);
		
		int l = firstChildIndex(ans);
		ans->childrenNumber = ans->childrenNumber + 1;
		ans->children[l - 1] = a;
		ans->children[l - 1]->parent = ans;
		return ans;

	}
	else if (checkIfRecursive(ptree->name))
	{
		if (ptree->childrenNumber == 2)
		{
			int o = firstChildIndex(ptree);
			int p = o;
			o++;
			while (ptree->children[o] == NULL && o < 50)
				o++;
			parseTree ans = ptree->children[p];
			ans->childrenNumber = ans->childrenNumber + 1;
			ans->children[49] = optimize_operator(ptree->children[o]);
			ans->children[49]->parent = ans;

			return ans;
		}
		else
		{
			int o = firstChildIndex(ptree);
			int p = o;
			o++;
			while (ptree->children[o] == NULL && o < 50)
				o++;
			int q = o;
			o++;
			while (ptree->children[o] == NULL && o < 50)
				o++;

			parseTree a = optimize_operator(ptree->children[o]);
			
			parseTree b = optimize_operator(ptree->children[q]);

			int l = firstChildIndex(a);
			a->childrenNumber++;
			a->children[l - 1] = b;
			a->children[l - 1]->parent = a;


			ans = ptree->children[p];
			ans->childrenNumber = 1;
			ans->children[49] = a;
			ans->children[49]->parent = ans;
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


// Symbol Table

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


//---------------------------------Type Checking-----------------------------------------------

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
		if (strcmp(ast->children[l]->type, "int") == 0 && strcmp(ast->children[k]->type, "int") == 0)
			ast->type = "int";
		else if (strcmp(ast->children[l]->type, "real") == 0 && strcmp(ast->children[k]->type, "real") == 0)
			ast->type = "real";
		else if (strcmp(ast->children[l]->type, "complex") == 0 && strcmp(ast->children[k]->type, "complex") == 0 && (ast->name == 99 || ast->name == 100))
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
		if (strcmp(ast->children[l]->type, "bool") == 0 && strcmp(ast->children[k]->type, "bool") == 0)
			ast->type = "bool";
		else if (strcmp(ast->children[l]->type, "int") == 0 && strcmp(ast->children[k]->type, "int") == 0)
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
//----------------------------------------------------Code generation---------------------------------------------------


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

		fprintf(fp, "LEA R%d, %s\n", reg, ast->children[l]->info.lexeme);
		if (strcmp(ast->children[k]->info.lexeme, "first") == 0)
			{
				fprintf(fp, "MOV R%d, [R%d]\n", reg, reg);
			}
			
		else
			{
				fprintf(fp, "MOV R%d, [R%d+4]\n", reg, reg);
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




//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char * argv[])
{

	FILE * filename;
	filename = fopen("./input9.txt", "r");
	FILE *fp;
	fp = fopen("./lexerOutput.txt", "w");
	lexer(filename, fp);
	fclose(filename);
	fclose(fp);

	strcpy(globalTokens[tokenNumber].lexeme, "dollar");
	globalTokens[tokenNumber].lineno = -1;
	strcpy(globalTokens[tokenNumber].tokenName, "$");
	tokenNumber++;

	parseInitialize();

	int i;
	for (i = 0; i<tokenNumber; i++)
		input[i] = findIdByName(globalTokens[i].tokenName);

	if (!parse(tokenNumber))
		print(mainTree, "./parseTreeOutput.txt");
	else
		printf("ERROR!\n");


	parseTree astTree = ast(mainTree);

	
	initializeSymbolTable(astTree);
	typeChecking(astTree);
	
	FILE * fo = fopen("./Code.txt", "w+");
	expressionCode(1,astTree,fo);
	fclose(fo);
	
	return 0;
}