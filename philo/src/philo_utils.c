/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/10/09 20:30:52 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

char	**ft_free(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i] = NULL;
		i++;
	}
	free(mat);
	mat = NULL;
	return (NULL);
}

void	ft_error(char *str, char *file)
{
	char	*msg;

	if (file)
	{
		msg = ft_strjoin(str, file);
		if (!msg)
			return (perror("Error\n"));
		ft_putstr_fd(msg, 2);
	}
	else
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	null_check(int argn, char **argv)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < argn)
	{
		if (ft_strncmp(argv[i], "", 1) == 0)
			ft_error("Error null argument", NULL);
		j = 0;
		while (argv[i][j] == ' ')
			j++;
		if (j == ft_strlen(argv[i]))
			ft_error("Error spaces argument", NULL);
		i++;
	}
}

int	philo_atoi(const char *nscr)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (nscr[i] == ' ' || nscr[i] == '\n' || nscr[i] == '\r'
		|| nscr[i] == '\t' || nscr[i] == '\v' || nscr[i] == '\f')
		i++;
	if (nscr[i] == '-' || nscr[i] == '+')
		ft_error(SYMBOL, NULL);
	while (nscr[i] != '\0')
	{
		if ('0' <= nscr[i] && nscr[i] <= '9')
			num = num * 10 + (nscr[i] - '0');
		else
			ft_error(NUMBERS, NULL);
		i++;
	}
	return (num);
}

void	arg_checker(int argn, char **argv)
{
	int		i;
	int		num;
	char	*test;

	if (argn > 6 || argn < 5)
		ft_error(ARGUMENTS, NULL);
	null_check(argn, argv);
	i = 0;
	while (argv[++i])
	{
		num = philo_atoi(argv[i]);
		test = ft_itoa(num);
		if (ft_strncmp(test, argv[i], ft_strlen(argv[i])) != 0)
		{
			free(test);
			ft_error(BIG_NUM, NULL);
		}
		free(test);
	}
}
