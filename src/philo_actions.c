/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:38:16 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/10 18:44:30 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	print_philo(t_philo *philo, char *action)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->print_lock);
	if (!death_status(args))
	{
		printf("%lli ", get_current_time() - args->initial_time);
		printf("%d ", philo->id + 1);
		printf("%s\n", action);
		pthread_mutex_unlock(&args->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&args->print_lock);
	return (0);
}

void	unlock_forks(t_args *args, int first_fork, int second_fork)
{
	pthread_mutex_unlock(&args->fork[first_fork]);
	pthread_mutex_unlock(&args->fork[second_fork]);
}

int	perform_eat(t_philo *philo, int first_fork, int second_fork)
{
	t_args	*args;

	args = philo->args;
	if (args->n_philo == 1)
	{
		pthread_mutex_unlock(&args->fork[first_fork]);
		return (0);
	}
	pthread_mutex_lock(&args->fork[second_fork]);
	print_philo(philo, TAKEN_FORK);
	philo->is_eating = 1;
	if (!print_philo(philo, EAT))
		return (unlock_forks(args, first_fork, second_fork), 0);
	ft_usleep(args->time_to_eat);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	t_args	*args;
	int		first_fork;
	int		second_fork;

	args = (t_args *)philo->args;
	first_fork = philo->right_fork;
	second_fork = philo->left_fork;
	if (first_fork > second_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(&args->fork[first_fork]);
	print_philo(philo, TAKEN_FORK);
	if (!perform_eat(philo, first_fork, second_fork))
		return (0);
	philo->is_eating = 0;
	pthread_mutex_lock(&args->eat_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&args->eat_lock);
	pthread_mutex_lock(&philo->monitor_lock);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->monitor_lock);
	return (unlock_forks(args, first_fork, second_fork), 1);
}
