/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:23:11 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/01 14:56:39 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dyn_arr	*create_dyn_arr(void)
{
	t_dyn_arr	*dyn_arr;

	dyn_arr = malloc(sizeof(t_dyn_arr));
	if (dyn_arr == NULL)
		return (perror("CREATE_DYN_ARR"), NULL);
	dyn_arr->arr = malloc(sizeof(char *));
	if (dyn_arr->arr == NULL)
		return (perror("CREATE_DYN_ARR"), NULL);
	dyn_arr->capacity = 1;
	dyn_arr->length = 0;
	return (dyn_arr);
}

int	append(t_dyn_arr *arr, char *value)
{
	char	**new_arr;
	int		i;

	if (arr->length >= arr->capacity)
	{
		new_arr = malloc(sizeof(char *) * 2 * arr->capacity);
		if (new_arr == NULL)
			return (perror("DYN_ARR_APPEND"), -1);
		arr->capacity *= 2;
		i = 0;
		while (i < arr->length)
		{
			new_arr[i] = arr->arr[i];
			i++;
		}
		free(arr->arr);
		arr->arr = new_arr;
	}
	arr->arr[arr->length] = value;
	(arr->length)++;
	return (0);
}

int	pop(t_dyn_arr *arr, int index)
{
	if (arr == NULL)
		return (-1);
	if (index < 0 || index >= arr->length)
		return (-1);
	free(arr->arr[index]);
	while (index < arr->length - 1)
	{
		arr->arr[index] = arr->arr[index + 1];
		index++;
	}
	arr->length -= 1;
	return (0);
}
