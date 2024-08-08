/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:45:05 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/10 18:48:23 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	n_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i ++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	cifra;
	int		len;

	cifra = n;
	len = n_len(cifra);
	str = (char *) malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	len -= 1;
	if (cifra < 0)
	{
		cifra *= -1;
		str[0] = '-';
	}
	if (cifra == 0)
		str[0] = '0';
	str[len + 1] = 0;
	while (cifra > 0)
	{
		str[len] = cifra % 10 + 48;
		cifra /= 10;
		len --;
	}
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long int	i;
	long int	number;
	long int	neg;

	neg = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n'
		|| str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i ++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * neg);
}
