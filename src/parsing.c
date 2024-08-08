/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:44:12 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/08 16:14:59 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

int	check_time(int time, int i)
{
	if (i == 1 && (time > 200 || time == 0))
		return (ft_error("Invalid philos!\n"));
	else if (i != 1 && i != 5 && time < 60)
		return (ft_error("Invalid time!\n"));
	return (1);
}

int	check_args(char **argv)
{
	char	*str;
	int		time;
	int		i;

	i = 0;
	while (argv[++i])
	{
		time = ft_atoi(argv[i]);
		if (time < 0)
			return (ft_error("Invalid arguments!\n"));
		str = ft_itoa(time);
		if (ft_strncmp(str, argv[i], ft_strlen(argv[i])) != 0)
		{
			free(str);
			return (ft_error("Invalid arguments!\n"));
		}
		free(str);
		if (!check_time(time, i))
			return (0);
	}
	return (1);
}
