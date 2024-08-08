/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:50:58 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/08 16:14:15 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	init_mutex(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_mutex_init(&args->fork[i], 0))
			return (ft_error("failed to initialize mutex"));
	}
	if (pthread_mutex_init(&args->lock, 0))
		return (ft_error("failed to initialize mutex"));
	if (pthread_mutex_init(&args->print_lock, 0))
		return (ft_error("failed to initialize mutex"));
	if (pthread_mutex_init(&args->eat_lock, 0))
		return (ft_error("failed to initialize mutex"));
	return (1);
}

int	init_philo(t_args *args)
{
	int	i;

	i = args->n_philo;
	while (--i >= 0)
	{
		args->philo[i].id = i;
		args->philo[i].left_fork = i;
		args->philo[i].right_fork = (i + 1) % args->n_philo;
		args->philo[i].last_meal = 0;
		args->philo[i].args = args;
		args->philo[i].philo_ate = 0;
		args->philo[i].death_status = 0;
		args->philo[i].is_eating = 0;
		args->philo[i].n_meals = 0;
		if (pthread_mutex_init(&args->philo[i].monitor_lock, 0))
			return (ft_error("failed to initialize mutex"));
	}
	return (1);
}

void	init_vars(t_args *args)
{
	args->is_dead = 0;
	args->n_philo = ft_atoi(args->argv[1]);
	args->time_to_death = ft_atoi(args->argv[2]);
	args->time_to_eat = ft_atoi(args->argv[3]);
	args->time_to_sleep = ft_atoi(args->argv[4]);
	args->meals_limit = -1;
	args->all_ate = 0;
}

int	ft_init(t_args *args)
{
	int	i;

	i = -1;
	init_vars(args);
	if (args->argc == 6)
		args->meals_limit = ft_atoi(args->argv[5]);
	args->curr_time = 0;
	args->fork = malloc(sizeof(pthread_mutex_t) * args->n_philo);
	if (!args->fork)
		return (ft_error("allocation fail\n"));
	args->tid = malloc(sizeof(pthread_t) * args->n_philo);
	if (!args->tid)
		return (ft_error("allocation fail\n"));
	args->philo = malloc(sizeof(t_philo) * args->n_philo);
	if (!args->philo)
		return (ft_error("allocation fail\n"));
	if (!(init_philo(args)))
		return (ft_error("failed to initialize"));
	return (1);
}
