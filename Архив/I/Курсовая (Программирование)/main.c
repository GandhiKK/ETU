#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*One of the most alarming forms of air pollution is acid rain. It results from the release into the atmosphere of sulphur and nitrogen oxides that react with water droplets and return to earth in the form of acid rain, mist or snow. Acid rain is killing forests in Canada, the USA, and central and northern Europe. Nearly every species of tree is affected. It has acidified lakes and streams and they can’t support fish, wildlife, plants or insects. In the USA 1 in 5 lakes suffer from this type of pollution.*/

#define STRSIZE 500//Первоначальный текст
#define SYMBOL 100//Количество символов в предложении
#define SENTENCE 50//Количество предложений

int Text(char*** text, char** str);
int RemoveTheSame(char*** text, int* num);
int Menu(void);
int Garbage(char*** text, int num);
int Replace(char*** text, int num);
int Delete(char*** text, int num);
int Sort(char*** text, int num);
int cmp(const void*a, const void *b);

int main()
{
	char** text;
	int flag = 0;
	char* str;
	char* s;
	int sentences = Text(&text, &str);
	int delete_sentences = RemoveTheSame(&text, &sentences);
	do
	{
		int cmdf = Menu();
		printf("\n");
		switch(cmdf){
    		case 1: delete_sentences = Garbage(&text, delete_sentences); 
				if (delete_sentences == 0)
				{
					puts("<-----> Выход <----->\n");
					flag = 1;
					}
				break;
        	case 2: delete_sentences = Replace(&text, delete_sentences);
				if (delete_sentences == 0){
						puts("<-----> Выход <----->\n");
						flag = 1;}
					break;
        	case 3: delete_sentences = Delete(&text, delete_sentences);
				if (delete_sentences == 0){
					puts("<-----> Выход <----->\n");
					flag = 1;}
				break;
        	case 4: delete_sentences = Sort(&text, delete_sentences); 
				if (delete_sentences == 0){
					puts("<-----> Выход <----->\n");
					flag = 1;}
				break;
			case 5: for (int i = 0; i < delete_sentences; i++)
						printf("%s.\n", text[i]);
					break;
			case 6: printf("Текущее количество предложений равно %d.\n", delete_sentences); break;
        	default: puts("<-----> Выход <----->\n"); flag = 1; break;
		}
		if (flag == 1){
			break;}
	}
	while (1);
    return 0;
}

int Text(char*** text, char** str)
{
    char currentLetter = 0;
	int line = 0;
	int sym = 0;
	int max_sentences = SENTENCE;
	int str_size = STRSIZE;
	int max_symbols = SYMBOL;
	*str = (char*)calloc(str_size, sizeof(char));

    puts("Введите текст:");

    for (int counter = 0; (currentLetter = getchar()) != '\n'; counter++)
	{
		if ((currentLetter == ' ') && (sym == 0))
		{
			counter--;
			continue;
		}
		sym++;
		if (currentLetter == '.')
			sym = 0;
		if (str_size < counter + 1)
		{
			str_size += STRSIZE;
			*str = (char*)realloc(*str, str_size * sizeof(char));
		}
        (*str)[counter] = currentLetter;
	}

	char** new_text = (char**)calloc(max_sentences, sizeof(char*));

    char *s = strtok (*str, "."); 
	while (s != NULL)
	{
		new_text[line] = (char*)calloc(max_symbols, sizeof(char));
		if (strlen(s) > max_symbols)
		{
			max_symbols += SYMBOL;
			new_text[line] = (char*)realloc(new_text[line], max_symbols * sizeof(char));
		}
		new_text[line++] = s;
        s = strtok (NULL, ".");
		if (max_sentences > line + 1)
		{
			max_sentences += SENTENCE;
            new_text = (char**)realloc(new_text, max_sentences * sizeof(char*));
		}
    }
	*text = new_text;
    return line;
}

int RemoveTheSame(char*** text, int* num)
{
	int j = 0;
	int flag = 1;
	for (int i = 0; i < *num; i++)
	{
		j = i + 1;
		while (j < *num)
		{
			flag = 1;
			if (strlen((*text)[i]) != strlen((*text)[j]))
        		flag = 0;
    		for (int k = 0; k < strlen((*text)[i]); k++)
			{
        		if (tolower((*text)[i][k]) != tolower((*text)[j][k]))
            		flag = 0;
    		}
			if (flag == 1)
			{
				for(int new_i = j; new_i < *num - 1; new_i++)
        			(*text)[new_i] = (*text)[new_i + 1];
     			num -= 1;
			}
			else
				j++;
		}
	}
	
	return *num;
}

int Menu(void)
{
	int cmd;
	puts("\nДействия:");
	puts("Введите 1, чтобы посчитать количество слов {garbage} в каждом предложении.");
	puts("Введите 2, чтобы заменить все цифры в предложении на введенную строку.");
	puts("Введите 3, чтобы удалить все предложения в которых есть три подряд идущие буквы в верхнем регистре.");
	puts("Введите 4, чтобы отсортировать предложения по уменьшению количества слов начинающихся с гласной буквы.");
	puts("Введите 5, чтобы вывести текущий текст.");
	puts("Введите 6, чтобы узнать текущее количество предложений в тексте.");
	puts("Введите любой отличный символ, чтобы выйти.");
	scanf("%d", &cmd);
	return (cmd);	
}

int Garbage(char*** text, int num)
{
	int count = 0;
	char garbage_str[8] = "garbage";
	for (int i = 0; i < num; i++)
	{
		count = 0;
		int letter = 0;
    	int j;
    	while ((*text)[i][letter] != '\0')
		{     
        	if (tolower((*text)[i][letter]) == garbage_str[0])
			{
        		j = 0;
        		while (garbage_str[j] == tolower((*text)[i][letter + j]))				
				{
					j++;
				}
            	if (j == 7 || j == 8) 
						count++;
        	}
        	letter++;
    	}
		printf("%s. ---> ", (*text)[i]);
		if (count > 5)
			printf("It is a dump\n");
		else if (count == 0)
			printf("Clean\n");
		else
			printf("Must be washed\n");
		}
		return num;
}	

int Replace(char*** text, int num)
{
	int count = 0, symbol = 0;
	int j, k;
	int current = 0;	
	char buffer[100];
	int max = SYMBOL * 3;
	for (int i = 0; i < num; i++)
	{
		symbol = 0;
		while ((*text)[i][symbol] != '\0')
		{
			if (isdigit((*text)[i][symbol])) 
				count++;
			symbol++;
		}
	}
	if (count == 0)
		printf("В предложениях отсутствуют цифры\n");
	else
	{
		printf("Введите строку:\n");
		char c = getchar();	
		c = getchar();	
		for (int j = 0; c != '\n'; j++){			
			buffer[j] = c;
			c = getchar();
		}
		int p;
		/* 
	
	
	
		ВОТ ЭТА ХУЙНЯ НЕ РАБОТАЕТ НОРМАЛЬНО
		ПОЧЕМУ ТО МЕНЯЕТ СЛЕДУЮЩУЮ СТРОЧКУ


		
		for (int i = 0; i < num; i++)
		{
			symbol = 0;
			while ((*text)[i][symbol] != '\0')
			{
				if (isdigit((*text)[i][symbol]))
				{			
					p = 0;		
					int len = strlen(buffer);
					int lenstr = strlen((*text)[i]); 

        			//(*text)[i] = (char*)realloc((*text)[i], max + (len * sizeof(char)));				
					max += SYMBOL;

					for (j = lenstr; j >= symbol + 1; j--) {
        				(*text)[i][j + len - 2] = (*text)[i][j - 1]; 
    				}
					
					for (k = symbol; k < symbol + len; k++)
					{
						(*text)[i][k] = buffer[p];
						p++;
					}
				}
				symbol++;
			}
		}*/
	}
	return num;
}

int Delete(char*** text, int num)
{
	int flag = 0, symbol = 0;
	for (int i = 0; i < num; i++)
	{
		symbol = 0;
		flag = 0;
		while ((*text)[i][symbol] != '\0')
		{
			if (isupper((*text)[i][symbol])) 
				flag++;
			if ((isupper((*text)[i][symbol + 1])) && (flag == 3))
				flag = 0;
			if (flag == 3)
			{
				for (int h = i; h < num - 1; h++)
					(*text)[h] = (*text)[h+1];
				num--;
				i--;
				flag = 0;
				break;
			}
			if ((isblank((*text)[i][symbol + 1])) || (islower((*text)[i][symbol + 1])) || (ispunct((*text)[i][symbol + 1])) || (isdigit((*text)[i][symbol + 1])))
				flag = 0;
			symbol++;
		}
	}
	if (num == 0)
		puts("Удалены все предложения");
	else
		for (int i = 0; i < num; i++)
			printf("%s.\n", (*text)[i]);
	return num;
}

int cmp(const void*a, const void *b)
{
	int counter_for_s = 0, counter_for_p = 0;
	char* str1 = *((char**)a), *str2 = *((char**)b);

	for (int i = 0; i < strlen(str1); i++)
	{
		if (i != 0)
		{
		if (((tolower(str1[i]) == 'a') || (tolower(str1[i]) == 'e') || (tolower(str1[i]) == 'i') || (tolower(str1[i]) == 'o') || (tolower(str1[i]) == 'u') || (tolower(str1[i]) == 'y')) && ((str1[i - 1] == ' ') || (str1[i - 1] == ',')))
			counter_for_s++;
			}
		else
			{
		if ((((tolower(str1[i])) == 'a') || (tolower(str1[i]) == 'e') || (tolower(str1[i]) == 'i') || (tolower(str1[i]) == 'o') || (tolower(str1[i]) == 'u') || (tolower(str1[i]) == 'y')))
			counter_for_s++;
			}
	}

	for (int i = 0; i < strlen(str2); i++)
	{
		if (i != 0)
		{
		if (((tolower(str2[i]) == 'a') || (tolower(str2[i]) == 'e') || (tolower(str2[i]) == 'i') || (tolower(str2[i]) == 'o') || (tolower(str2[i])== 'u') || (tolower(str2[i]) == 'y')) && ((str2[i - 1] == ' ') || (str2[i - 1] == ',')))
			counter_for_p++;
			}
		else
			{
		if (((tolower(str2[i]) == 'a') || (tolower(str2[i]) == 'e') || (tolower(str2[i]) == 'i') || (tolower(str2[i]) == 'o') || (tolower(str2[i]) == 'u') || (tolower(str2[i]) == 'y')))
			counter_for_p++;
			}
	}
	if (counter_for_s > counter_for_p)
		return -1;
	else if (counter_for_s < counter_for_p)
		return 1;
	else
		return 0;
}

int Sort(char*** text, int num)
{
	qsort(*text, num, sizeof(char*), cmp);
	for (int i = 0; i < num; i++)
		printf("%s.\n", (*text)[i]);
	return num;
}