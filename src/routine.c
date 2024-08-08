/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:55:46 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/10 18:51:21 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	death_status(t_args *arg)
{
	int	ret;

	pthread_mutex_lock(&arg->lock);
	ret = arg->is_dead;
	pthread_mutex_unlock(&arg->lock);
	return (ret);
}

int	eat_status(t_args *arg)
{
	int	ret;

	pthread_mutex_lock(&arg->lock);
	ret = arg->all_ate;
	pthread_mutex_unlock(&arg->lock);
	return (ret);
}

void	*ft_routine(void *args)
{
	t_philo	*philo;
	t_args	*arg;

	philo = (t_philo *)args;
	arg = philo->args;
	if (philo->id % 2 != 0)
	{
		print_philo(philo, THINK);
		ft_usleep(100);
	}
	while (1)
	{
		if (!philo_eat(philo))
			break ;
		print_philo(philo, SLEEP);
		ft_usleep(arg->time_to_sleep);
		if (!print_philo(philo, THINK))
			return (0);
	}
	return (0);
}

int	exit_threads(t_args *args)
{
	int	i;

	free(args->tid);
	i = -1;
	while (++i < args->n_philo)
	{
		pthread_mutex_destroy(&args->fork[i]);
		pthread_mutex_destroy(&args->philo[i].monitor_lock);
	}
	pthread_mutex_destroy(&args->lock);
	pthread_mutex_destroy(&args->print_lock);
	pthread_mutex_destroy(&args->eat_lock);
	free(args->fork);
	free(args->philo);
	return (1);
}

int	starting_threads(t_args *args)
{
	int	i;

	i = -1;
	args->initial_time = get_current_time();
	while (++i < args->n_philo)
	{
		args->philo[i].last_meal = args->initial_time;
		if (pthread_create(&args->tid[i], 0, &ft_routine, &args->philo[i]))
			return (ft_error("failed to create thread\n"));
	}
	monitor(args);
	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_join(args->tid[i], 0))
			return (ft_error("pthread_join failed\n"));
	}
	exit_threads(args);
	return (1);
}
