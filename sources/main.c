/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:54:16 by aggrigor          #+#    #+#             */
/*   Updated: 2024/07/19 11:40:45 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (pred("Error: ./cub3d <filename>.cub\n", BOLD, 2), 1);
	if (validation(argv[1]) == -1)
		return (1);
	printf("FILENAME:%s\n", argv[1]);
	return (0);
}
