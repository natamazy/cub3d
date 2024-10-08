/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:22:48 by natamazy          #+#    #+#             */
/*   Updated: 2024/09/09 12:43:18 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	pred_free(t_dyn_arr *buf)
{
	pred("cub3D: Validation failed\n", BOLD, 2);
	free_nmatrix(buf->arr, buf->length);
	free(buf);
}

int	parse_scene_file(int fd, t_scene_info *sc_info)
{
	t_dyn_arr	*buf;
	char		*next_line;

	buf = create_dyn_arr();
	while (true)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		if (append(buf, next_line) == -1)
		{
			free_nmatrix(buf->arr, buf->length);
			free(buf);
			return (-1);
		}
	}
	if (validate_scene_file(sc_info, buf) == 0)
	{
		free_nmatrix(buf->arr, buf->length);
		free(buf);
		return (0);
	}
	pred_free(buf);
	return (-1);
}

void	remove_extra_lines(t_dyn_arr *buf)
{
	int	i;

	i = 0;
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
	{
		if (is_only_spaces(buf->arr[i]) == 1)
			pop(buf, i);
		else
			i++;
	}
	i = buf->length - 1;
	while (i >= 0 && is_only_spaces(buf->arr[i]) == 1)
	{
		pop(buf, i);
		i--;
	}
}

int	validate_scene_file(t_scene_info *sc_info, t_dyn_arr *buf)
{
	remove_extra_lines(buf);
	if (buf == NULL || buf->length < 1)
		return (pred("Invalid scene file\n", BOLD, 2), -1);
	if (set_texures_info(sc_info, buf) == -1)
		return (-1);
	if (are_all_colors_valid(sc_info) == -1)
		return (-1);
	if (are_all_textures_valid(sc_info) == -1)
		return (-1);
	sc_info->map = get_converted_map(buf, 0, 0);
	if (sc_info->map == NULL)
		return (-1);
	if (map_validation(sc_info->map) == -1)
		return (-1);
	return (0);
}

int	set_texures_info(t_scene_info *sc_info, t_dyn_arr *buf)
{
	int		i;
	char	**s;

	i = 0;
	while (i < buf->length && starts_with_digit(buf->arr[i]) == 0)
	{
		s = ft_split(buf->arr[i], " \t\n");
		if (s == NULL)
			return (-1);
		else if (arrlen(s) != 2)
			return (pred("Incorrect texture format\n", BOLD, 2),
				free_nmatrix(s, arrlen(s)), -1);
		if (get_value(sc_info->texs, s[0]) == NULL)
		{
			if (set_value(sc_info->texs, s[0], s[1]) == -1)
				return (pred("Unknown texture title\n", BOLD, 2),
					free_nmatrix(s, arrlen(s)), -1);
		}
		else
			return (pred(D, BOLD, 2), free(s[0]), free(s[1]), free(s), -1);
		free(s[0]);
		free(s);
		i++;
	}
	return (0);
}
