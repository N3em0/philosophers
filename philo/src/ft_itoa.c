/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:37:00 by egache            #+#    #+#             */
/*   Updated: 2025/09/12 16:39:05 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_getsize(long nbr)
{
	int	size;

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

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	nbr;

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
