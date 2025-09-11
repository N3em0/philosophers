/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfbil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:47:14 by egache            #+#    #+#             */
/*   Updated: 2025/09/11 16:55:14 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int ft_overflow(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

int ft_atoi(const char *str)
{
	int i;
	int sign;
	long result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX)
			return (ft_overflow(sign));
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		return (ft_overflow(sign));
	return ((int)result * sign);
}

void ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void *ft_calloc(size_t nitems, size_t size)
{
	char *str;

	if (size != 0 && nitems > SIZE_MAX / size)
		return (NULL);
	str = malloc(nitems * size);
	if (!str)
		return (NULL);
	ft_bzero(str, nitems * size);
	return (str);
}

void *ft_memset(void *str, int c, size_t n)
{
	char *s;

	s = (char *)str;
	while (n > 0)
	{
		s[n - 1] = c;
		n--;
	}
	return (str);
}

static int ft_getsize(long nbr)
{
	int size;

	size = 1;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		size++;
	}
	while (nbr > 9)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

char *ft_itoa(int n)
{
	char *result;
	int size;
	long nbr;

	nbr = n;
	size = ft_getsize(nbr);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		nbr = nbr * -1;
		result[0] = '-';
	}
	while (nbr)
	{
		result[size--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}