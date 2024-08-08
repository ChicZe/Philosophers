/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:11:17 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/10 15:50:36 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char **argv)
{
	t_args	args;

	args.argv = argv;
	args.argc = argc;
	if (argc < 5 || argc > 6)
		return (1);
	if (!(check_args(argv)))
		return (1);
	if (!(ft_init(&args)))
		return (1);
	if (!(init_mutex(&args)))
		return (1);
	if (!(starting_threads(&args)))
		return (1);
}
