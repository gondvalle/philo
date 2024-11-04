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

t_ini_vals	*philo_values(int argn, char **argv)
{
	t_ini_vals		*philo_vals;

	philo_vals = ft_calloc(1, sizeof(t_ini_vals));
	if (!philo_vals)
		ft_error(MALLOC, NULL);
	philo_vals->num_philo = philo_atoi(argv[1]);
	philo_vals->time_die = philo_atoi(argv[2]);
	philo_vals->time_eat = philo_atoi(argv[3]);
	philo_vals->time_sleep = philo_atoi(argv[4]);
	if (argn == 6)
		philo_vals->num_times = philo_atoi(argv[5]);
	else
		philo_vals->num_times = -1;
	gettimeofday(&philo_vals->ini_time, NULL);
	return (philo_vals);
}

void	print_philo_info(t_ini_vals *ini_vals)
{
	printf("Número de filósofo: %d\n", ini_vals->num_philo);
	printf("Tiempo para morir: %d ms\n", ini_vals->time_die);
	printf("Tiempo para comer: %d ms\n", ini_vals->time_eat);
	printf("Tiempo para dormir: %d ms\n", ini_vals->time_sleep);
	printf("Número de veces que come: %d\n", ini_vals->num_times);
	printf("El tiempo inicial en seg: %ld\n", ini_vals->ini_time.tv_sec);
}

t_table	*create_table(void)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	table->head = NULL;
	return (table);
}

void	philo_append(t_table *list, int id)
{
	t_philo	*new_philo;
	t_philo	*last_philo;

	new_philo = ft_calloc(1, sizeof(t_philo));
	if (!new_philo)
		ft_error(MALLOC, NULL);
	new_philo->id = id;
	new_philo->next = new_philo;
	new_philo->prev = new_philo;
	if (list->head == NULL)
		list->head = new_philo;
	else
	{
		last_philo = list->head->prev;
		last_philo->next = new_philo;
		new_philo->prev = last_philo;
	}
	new_philo->next = list->head;
	list->head->prev = new_philo;
}

void	free_table(t_table *table)
{
	t_philo	*current;
	t_philo	*next;

	current = table->head;
	while (current != NULL)
	{
		next = current->next;
		if (next == table->head)
			next = NULL;
		free(current);
		current = NULL;
		current = next;
	}
	free(table);
}

struct timeval dif_time(struct timeval	ini, struct timeval	fin)
{
	long			seconds;
	long			microseconds;
	struct timeval	time;

	seconds = fin.tv_sec - ini.tv_sec;
	microseconds = fin.tv_usec - ini.tv_usec;
	if (microseconds < 0)
	{
		seconds--;
		microseconds += 1000000;
	}
	time.tv_sec = seconds;
	time.tv_usec = microseconds;
	return (time);
}

int	main(int argn, char **argv)
{
	t_ini_vals		*philo_vals;
	t_table			*table;
	// pthread_t		t1;
	int				i;
	struct timeval	tv;
	struct timeval	final;

	arg_checker(argn, argv);
	philo_vals = philo_values(argn, argv);
	print_philo_info(philo_vals);
	// if (pthread_create(&t1, NULL, &voiffun, NULL))
	// 	ft_error(PTHREAD, NULL);
	table = create_table();
	i = -1;
	while (++i < philo_vals->num_philo)
		philo_append(table, i);
	i = -1;
	while (++i < 8)
	{
		printf("El id es: %i\n", table->head->id);
		table->head = table->head->next;
	}
	usleep(3000000);
	gettimeofday(&tv, NULL);
	// Calcula la diferencia en segundos y microsegundos
	final = dif_time(philo_vals->ini_time, tv);
    printf("Han pasado: %ld segundos y %ld microsegundos\n", final.tv_sec, final.tv_usec);
	free(philo_vals);
	free_table(table);
}
