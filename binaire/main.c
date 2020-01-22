#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*char *reversebin(char *bin)
{
	int i = strlen(bin) - 1;
	int j = 0;
	char temp;

	while (i > j)
	{
		temp = bin[j];
		bin[j] = bin[i];
		bin[i] = temp;
		i--;
		j++;
	}
	return (bin);
}*/

/*char *convertbin(int c, int mode)
{
	char *bin;
	int letter = c;
	int pos = 0;
	//printf("%d\n", letter);

	bin = NULL;
	if (mode == 0)
	{
		//bin = malloc(sizeof(char) * 9);
		bin = strdup("00000000\0");
	}
	else
	{
		//bin = malloc(sizeof(char) * 65);
		bin = strdup("0000000000000000000000000000000000000000000000000000000000000000\0");
	}
	while (letter > 0)
	{
		if (letter % 2 != 0)
		{
			bin[pos] = '1';
			pos++;
		}
		else
		{
			pos++;
		}
		letter = letter / 2;
	}
	bin = reversebin(bin);
	return (bin);
}*/

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if ((str = malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (strdup((char*)s2));
	else if (s2 == NULL)
		return (strdup((char*)s1));
	sjoin = ft_strnew(strlen(s1) + strlen(s2));
	if (sjoin == NULL)
		return (NULL);
	strcpy(sjoin, s1);
	strcat(sjoin, s2);
	return (sjoin);
}

int numberofpadding(int len)
{
	int num;

	num = (448 - (len % 512));
	//printf("%d\n", num);
	if (num == 0)
		return (512);
	else if (num < 0)
		return (512 + num);
	else
		return (num);
	return (0);
}

char *addpadding(int padding, char *chaine, char *taillebin)
{
	int i;

	i = 1;
	//printf("taillebin = %s\n", taillebin);
	if (chaine == NULL)
	{
		chaine = malloc(sizeof(char) * 512);
		chaine[0] = '1';
		while (i < 511)
		{
			chaine[i] = '0';
			i++;
		}
		chaine[i] = '\0';
		printf("%s\n", chaine);
	}
	return (chaine);
}

void	addbinaireint(char **chaine2, unsigned long c, int i)
{
	//printf("I = %d\n", i);
	//printf("C = %ld\n", c);
	//printf("CHAINE2 = %s\n", *chaine2);
	while (c > 0)
	{
		if (c % 2 != 0)
		{
			(*chaine2)[i] = '1';
			i--;
		}
		else
		{
			(*chaine2)[i] = '0';
			i--;
		}
		c = c / 2;
	}
	(*chaine2)[0] = '1';
	return ;
}

char *addother(unsigned long len, char *chaine)
{
	char *completechaine = NULL;
	char *chaine2 = NULL;
	int padding;
	int taillechaine;
	int i;

	i = 0;

	//printf("LEN = %ld\n", len);
	if (len == 0)
	{
		padding = 512;
		//printf("PADDING = %d\n", 512);
		//completechaine = addpadding(padding, chaine, 0);
	}
	else
	{
		taillechaine = strlen(chaine);
		//printf("TAILLE CHAINE = %d\n", taillechaine);
		padding = numberofpadding(len);
		chaine2 = malloc(sizeof(char) * (padding + 65));
		while (i < padding + 64)
		{
			chaine2[i] = '0';
			i++;
		}
		chaine2[i] = '\0';
		//printf("CHAINE2 = %s\n", chaine2);
		//printf("%ld\n", len);
		addbinaireint(&chaine2, len, padding + 63);
		printf("CHAINE2 = %s\n", chaine2);
		//printf("%s\n", convertbin(taillechaine, 1));
		//completechaine = addpadding(padding, chaine, convertbin(taillechaine, 1));
	}
	//printf("PADDING = %d\n", padding);
	return (completechaine);
}

void	addbinairechar(char **chaine1, int c, int i, int len)
{
	int j;
	int index;

	j = 0;
	index = (i * 8) - 1;
	while (c > 0)
	{
		if (c % 2 != 0)
		{
			(*chaine1)[index] = '1';
			index--;
		}
		else
		{
			(*chaine1)[index] = '0';
			index--;
		}
		c = c / 2;
	}
	return ;
}

int main(int ac, char **av)
{
	ac = 1;
	size_t i = 0;
	size_t j = 0;

	char *test = strdup(av[1]);
	char *chaine1;
	size_t len;

	len = 0;
	chaine1 = NULL;
	if (!strcmp(test, ""))
	{
		addother(0, chaine1);
		return (1);
	}
	len = strlen(test);
	if (len == 0)
	{
		chaine1 = malloc(sizeof(char) * 513);
		//Remplir chaine de charactere
	}
	else if (len > 0)
	{
		chaine1 = malloc(sizeof(char) * (numberofpadding(len * 8) + 1));
		while (j < (len * 8))
		{
			chaine1[j] = '0';
			j++;
		}
		chaine1[j] = '\0';
		free(chaine1);
		while (i < len)
		{
			addbinairechar(&chaine1, test[i], i + 1, len);
			i++;
		}
		printf("CHAINE1 = %s\n", chaine1);
		//printf("STRLEN = %ld\n", strlen(chaineconcat));
		//printf("CALCUL %ld\n", len * 8);
	}
	addother(len * 8, chaine1);
	return (0);
}
