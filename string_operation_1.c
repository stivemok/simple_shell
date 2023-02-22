#include "shell.h"

/**
 * word_count - counts words given a char delimiter
 * @str: string of words
 * Return: word count as unsigned int
 */
unsigned int word_count(char *str)
{
	unsigned int i, wc, flag;
	char *delims = "\n \t";

	for (i = 0, wc = 1, flag = 0; str[i]; i++)
	{
		if (flag == 0 &&
			  (str[i] == delims[0]
			|| str[i] == delims[1]
			|| str[i] == delims[2])
			&& str[i + 1] != delims[0]
			&& str[i + 1] != delims[1]
			&& str[i + 1] != delims[2])
			flag = 1, wc++;
		else
			flag = 0;
	}
	return (wc);
}

/**
 * _strlen_const - strlen for const strings
 * @s: string to be measured
 * Return: length of string
 */
int _strlen_const(const char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}

/**
 * simple_print - allows us to print simple lines
 * @str: const string to print
 */
void simple_print(const char *str)
{
	int len;

	len = _strlen_const(str);
	write(STDOUT_FILENO, str, len);
}

/**
 * _atoi - converts a string to an integer
 * @s: the input string
 * Return: the converted int
 */
int _atoi(char *s)
{
	int n, sign, result;

	for (n = result = 0, sign = 1; s[n]; n++)
	{
		if (s[n] == '-')
			sign *= -1;
		if (s[n] >= '0' && s[n] <= '9')
			result = 10 * result - (s[n] - '0');
		if (result < 0 && (s[n] < '0' || s[n] > '9'))
			break;
	}
	if (sign > 0)
		result *= -1;
	return (result);
}
