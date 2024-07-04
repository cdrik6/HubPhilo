/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:52:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/04 23:09:52 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

void	putstr_fd(char *str, int fd)
{
	int	i;

	if (!str || fd < 0)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	is_space(char c)
{
	if (9 <= c && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

long long	check_limit(int sign, unsigned long long nbr)
{
	if (nbr > LLONG_MAX - 1 && sign == -1)
		return (LLONG_MIN);
	if (nbr > LLONG_MAX && sign == 1)
		return (LLONG_MAX);
	return (sign * nbr);
}

long long	ft_atoll(char *str)
{
	int					i;
	int					sign;
	unsigned long long	nbr;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && 48 <= str[i] && str[i] <= 57)
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (check_limit(sign, nbr));
}

// int ft_atoi(char *str)
// {
// 	int					i;
// 	int					sign;
// 	unsigned long long	nbr;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	sign = 1;
// 	nbr = 0;
// 	while (str[i] && is_space(str[i]) == 1)
// 		i++;
// 	while (str[i] && (str[i] == '+' || str[i] == '-'))
// 	{
// 		if (str[i] == '-')
// 			sign = -sign;
// 		i++;
// 	}
// 	while (str[i] && 48 <= str[i] && str[i] <= 57)
// 	{
// 		nbr = nbr * 10 + (str[i] - 48);
// 		i++;
// 	}
// 	return (sign *nbr);
// }

void	*ft_calloc(size_t nb_elem, size_t elem_size)
{
	size_t	i;
	void	*res;

	if (elem_size != 0 && nb_elem > (size_t)(-1) / elem_size)
		return (NULL);
	res = malloc(nb_elem * elem_size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < nb_elem * elem_size)
	{
		((unsigned char *)res)[i] = 0;
		i++;
	}
	return (res);
}
