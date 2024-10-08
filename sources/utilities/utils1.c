/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:23:01 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/03 18:08:08 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pred(char *str, int is_bold, int fd)
{
	if (is_bold == BOLD)
		write(fd, BOLD_RED, 9);
	else if (is_bold == NOT_BOLD)
		write(fd, RED, 9);
	else
	{
		write(2, "use 'BOLD' or 'NOT_BOLD'\n", 25);
		return ;
	}
	if (str == NULL)
		return ;
	while (*str)
		write(fd, str++, 1);
	write(fd, "\033[0m", 5);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - s2[i]);
		i++;
	}
	return (0);
}

unsigned long	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

unsigned long	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i] != NULL)
		i++;
	return (i);
}

void	free_nmatrix(char **matrix, int n)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] && i < n)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}
