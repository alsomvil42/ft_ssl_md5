#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./md5.h"
#include "./libft/libft.h"


t_flag	*retrieve(int mode)
{
	static t_flag	*flag;
	
	if (mode == 1)
		flag = NULL;
	if (!flag && mode == 1)
	{
		flag = malloc(sizeof(t_flag));
		flag->p = 0;
		flag->r = 0;
		flag->s = 0;
		flag->q = 0;
		return (flag);
	}
	return (flag);
}

void	hashage(char *chaine)
{
	if (retrieve(0)->r)
	{
		printf("JE HASH ===>\n");
		printf("-----------------------------------\n");
		printf("%s", chaine);
		printf("-----------------------------------\n");
	}
	else
	{
		printf("JE HASH ===>\n");
		printf("-----------------------------------\n");
		printf("%s", chaine);
		printf("-----------------------------------\n");
	}
	return ;
}

void	wait_input(void)
{
	void	*buf;
	char *temp;
	int test;

	temp = NULL;
	while ((test = read(0, buf, 1)) > 0)
	{
		if (temp == NULL)
		{
			temp = ft_strdup(buf);
		}
		else
			temp = ft_strjoin(temp, buf);
	}
	if (test == -1)
	{
		printf("NIQUE TOI\n");
		exit(0);
	}
	//printf("%s\n", temp);
	if (retrieve(0)->p)
	{
		printf("INPUT =\n");
		printf("----------------------------\n");
		printf("%s", temp);
		printf("----------------------------\n");
	}
	hashage(temp);
	return ;
}

void	overrides(void)
{
	if (retrieve(0)->q)
		retrieve(0)->r = 0;
	if (retrieve(0)->p)
		retrieve(0)->r = 0;
}

void	print_option(t_flag *flag)
{
	printf("flag p = %d\n", flag->p);
	printf("flag q = %d\n", flag->q);
	printf("flag r = %d\n", flag->r);
	printf("flag s = %d\n", flag->s);
}

int		ft_execute(char *next_arg)
{
	t_flag *flag = retrieve(0);
	
	overrides();
	//printf("l'argument a exec est : %s\n", next_arg);
	if (retrieve(0)->p)
	{
		wait_input();
		//printf("En utilisant le flag : p\n");
	}
	if (retrieve(0)->q)
	{
		wait_input();
		//printf("En utilisant le flag : q\n");
	}
	if (retrieve(0)->r)
	{
		if (next_arg == NULL)
		{
			wait_input();
			//printf("En utilisant le flag : r\n");
		}
		else
		{
			hashage(next_arg);
			printf("Suivi de ==> %s\n", next_arg);
		}
	}
	if (retrieve(0)->s)
	{
		if (next_arg == NULL)
		{
			printf("md5: option requires an argument --s\n");
			printf("usage: md5 [-pqrs] [-s] [files ...]\n");
		}
		else
		{
			hashage(next_arg);
		}
		//printf("En utilisant le flag : s\n");
	}
	return (0);
}

int		search_option(char **av, int *pos)
{
	int	i;

	i = 1;
	if (av[*pos][0] != '-')
	{
		//J'essai de OPEN pour verifier qu'il s'agit d'un fichier
		/*if (le open a fonctionne)
		{
			//J'applique le hashage
		}
		else
		{
			//J'affiche un usage ==> le dossier n'existe pas
		}*/
	}
	else
	{
		while (av[*pos][i])
		{
			if (av[*pos][i] == 'p')
			{
				retrieve(0)->p = 1;
				//Il faut attendre un STDIN et executer le reste a l'appel de CTRL + D
			}
			else if (av[*pos][i] == 'q')
			{
				retrieve(0)->q = 1;
				//Activation du flag -q pour tout les arguments
			}
			else if (av[*pos][i] == 'r')
			{
				retrieve(0)->r = 1;
				//Activation du flag -r pour tout les arguments
			}
			else if (av[*pos][i] != 's')
			{
				//Print de l'usage de la commande
				return (3);
			}
			if (av[*pos][i] == 's')
			{
				retrieve(0)->s = 1;
				//Activation du flag -s
				if (av[*pos][i + 1])
					ft_execute(&(av[*pos][i + 1]));
				else
					ft_execute(av[(*pos) + 1]);
				return ((*pos)++);
			}
			i++;
		}
		ft_execute(av[(*pos) + 1]);
	}

	return (0);
}

int		main(int ac, char **av)
{
	int	a;
	char	**b;
	int	pos;
	t_flag	flag;

	a = ac;
	b = av;
	pos = 1;
	retrieve(1);
	while (pos < ac)
	{
		if (search_option(av, &pos) == 3)
		{
//			print_option(retrieve(0));
			printf("usage: invalid option\n");
			return (0);
		}
		pos++;

	}
	//print_option(retrieve(0));
	return (0);
}
