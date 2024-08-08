/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:07:45 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/10 18:50:17 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->eat_lock);
	if (get_current_time() - philo->last_meal > philo->args->time_to_death)
		return (pthread_mutex_unlock(&philo->args->eat_lock), 1);
	return (pthread_mutex_unlock(&philo->args->eat_lock), 0);
}

int	is_dead(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
	{
		if (philo_died(&args->philo[i]))
		{
			print_philo(&args->philo[i], DIE);
			pthread_mutex_lock(&args->lock);
			args->is_dead = 1;
			pthread_mutex_unlock(&args->lock);
			return (1);
		}
	}
	return (0);
}

int	everybody_ate(t_args *args)
{
	int	i;
	int	philos_full;

	i = -1;
	philos_full = 0;
	if (args->meals_limit == -1)
		return (0);
	while (++i < args->n_philo)
	{
		pthread_mutex_lock(&args->philo[i].monitor_lock);
		if (args->philo[i].n_meals >= args->meals_limit)
			philos_full++;
		pthread_mutex_unlock(&args->philo[i].monitor_lock);
	}
	if (philos_full == args->n_philo)
	{
		pthread_mutex_lock(&args->lock);
		args->is_dead = 1;
		pthread_mutex_unlock(&args->lock);
		return (1);
	}
	return (0);
}

int	monitor(t_args *args)
{
	while (1)
	{
		if (is_dead(args) || everybody_ate(args))
			break ;
	}
	return (0);
}
