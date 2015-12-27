#include"header.h"

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
