#include <stdio.h>


void	ft_search_option(char **av, int pos)
{
	int	i;

	i = 0;
	if (av[pos][0] != '-')
	{
		//J'essai de OPEN pour verifier qu'il s'agit d'un fichier
		if (/*le open a fonctionne*/)
			//J'applique le hashage
		else
			//J'affiche un usage ==> le dossier n'existe pas
	}
	else
	{
		while (av[pos][i] && av[pos][i] != 's')
		{
			if (av[pos][i] == 'p')
				//Il faut attendre un STDIN et executer le reste a l'appel de CTRL + D
			else if (av[pos][i] == 'q')
				//Activation du flag -q pour tout les arguments (les flags suivant sont considere comme argument)
			else if (av[pos][i] == 'r')
				//Activation du flag -q pour tout les arguments (les flags suivant sont considere comme argument)
			else if (av[pos][i] != 's')
				//Print de l'usage de la commande
				//exit
			if (av[pos][i] == 's')
				//Activation du flag -s
		}
	}

	return;
}

int		main(int ac, char **av)
{
	int	a;
	char	**b;
	int	pos;

	a = ac;
	b = av;
	pos = 1;
	while (pos < ac)
	{
		ft_search_option(av, &pos);
	}
	return (0);
}
