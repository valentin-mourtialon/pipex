/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:51:20 by vmourtia          #+#    #+#             */
/*   Updated: 2023/02/05 20:49:54 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while (c1[i] == c2[i] && i < n)
	{
		if (c1[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	else
		return (c1[i] - c2[i]);
}
