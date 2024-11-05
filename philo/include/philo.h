/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:47 by gdel-val          #+#    #+#             */
/*   Updated: 2024/04/23 16:37:49 by gdel-val         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

# define READ 0
# define WRITE 1

# define ARGUMENTS "Error: bad number of arguments"
# define SYMBOL "write the arguments without + or - symbols"
# define NUMBERS "write the arguments only with numbers"
# define BIG_NUM "The number entered is too large"
# define MALLOC "memory error"
# define PTHREAD "pthread error"

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*fork;
	struct s_philo		*next;
	struct s_philo		*prev;
}				t_philo;

typedef struct s_table
{
	t_philo	*head;
}				t_table;

typedef struct s_ini_vals
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_times;
	struct timeval	ini_time;
}				t_ini_vals;

typedef struct s_args_thread
{
	int					id;
	struct s_philo		*philo;
	struct s_philo		*next;
	struct s_ini_vals	*ini_vals;
}				t_args_thread;

char	**ft_free(char **mat);
void	ft_error(char *str, char *file);
void	null_check(int argn, char **argv);
int		philo_atoi(const char *nscr);
void	arg_checker(int argn, char **argv);

#endif
