#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * is_prime - Check if a given number is a prime
 * @n: Number to be checked
 *
 * Return: 1 if true, else -1
 */
int is_prime(int n)
{
	int factor, h_factor;

	factor = 2;
	if (n <= 1)
		return (-1);
	h_factor = n / 2;
	while (n % factor != 0)
	{
		factor++;
		if (factor >= h_factor)
			return (1);
	}
	return (-1);
}

typedef struct dreturn_s {
	char *str;
	int n;
}
dreturn_t;
dreturn_t *freadline(FILE *file)
{
	char c, tmp[32];
	dreturn_t *ptr1;
	int i;

	i = 0;
	ptr1 = malloc(sizeof(dreturn_t));
	if (ptr1 == NULL)
		return (NULL);
	ptr1->n = 1;
	c = fgetc(file);
	while (c != '\n')
	{
		if (c == EOF)
		{
			ptr1->n = -1;
			break;
		}
		tmp[i] = c;
		c = fgetc(file);
		i++;
	}
	tmp[i] = '\0';
	ptr1->str = strdup(tmp);
	return (ptr1);
}
int find_firstfact(int num)
{
	int div;

	if (num == 1 || num == 0)
		return (1);
	if (is_prime(num) == 1)
		return (1);
	div = 2;
	if (num % 2 == 0)
		return (2);
	while (num % div != 0)
	{
		div++;
	}
	return (div);
}
/**
 * raise - Raises a number to a given power
 * @n1: Number to be raised to power
 * @n2: power
 *
 * Return: power result
 */
int raise(int n1, int n2)
{
	int i, result;

	i = 0;
	result = 1;
	if (n2 == 0)
		return (1);
	while (i < n2)
	{
		result *= n1;
		i++;
	}
	return (result);
}
/** my_atoi - Converts a string to integer
 * @s: Pointer to the string to be converted
 * 
 * Return: Number represented by the string
 */

unsigned long int my_atoi(char *s)
{
	int i,flag;
	size_t len;
	unsigned long long int num;

	if (s == NULL)
		return (0);
	len = strlen(s);
	i = 0;
	flag = 1;
	num = 0;
	while (i < len)
	{
		if (s[i] == '-')
		{
			flag = -1;
			continue;
		}
		num += (s[i] - '0') * raise(10, len - i - 1);
		i++;
	}
	if (flag == -1)
		num *= -1;
	return (num);
}
/**
 * main - Factorize a given integer
 * @ac: Number of parameter passed to the function
 * @av: Pointer to args list
 * Return: 0
 */
int main(int ac, char **av)
{
	FILE *file;
	int i, num, factor1, factor2;
	dreturn_t *str;

	if (ac != 2)
		return (-1);
	file = fopen(av[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Failed to open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	str = freadline(file);
	if (str == NULL)
	{
		fprintf(stderr, "Error: Failed to read file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while (str->n != -1)
	{
		num = my_atoi(str->str);
		factor1 = find_firstfact(num);
		factor2 = num / factor1;
		printf("%i=%i*%i\n", num, factor1, factor2);
		free(str);
		str = freadline(file);
	}
	return (0);
}
