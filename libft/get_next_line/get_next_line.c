/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:24:59 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/03 19:26:53 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	put_line(char **buffer, char **result, char **save)
{
	ssize_t		index;

	index = find_char(*buffer, '\n');
	if (index == -1)
	{
		*result = append_buffer(*result, *buffer, ft_strlen(*buffer));
		if (*result == NULL)
			return (-1);
		free(*save);
		*save = NULL;
		return (0);
	}
	*result = append_buffer(*result, *buffer, index + 1);
	if (*result == NULL)
		return (-1);
	if (BUFFER_SIZE - (index + 1) > 0)
	{
		*save = append_buffer(*save, (*buffer + index + 1), \
			BUFFER_SIZE - (index + 1));
		if (*save == NULL)
			return (-1);
	}
	return (1);
}

static char	*exit_free(char **buffer, char **result, char **save)
{
	free(*buffer);
	(*buffer) = NULL;
	free(*save);
	(*save) = NULL;
	free(*result);
	(*result) = NULL;
	return (NULL);
}

static int	save_to_result(char **buffer, char **result, char **save)
{
	if ((*save) == NULL)
		return (-2);
	ft_strlcpy(*buffer, *save, ft_strlen(*save) + 1);
	free(*save);
	*save = NULL;
	return (put_line(buffer, result, save));
}

static int	read_line_continue(char **buffer, \
char **result, char **save, int *fd)
{
	ssize_t		return_val;

	while (1)
	{
		return_val = read(*fd, *buffer, BUFFER_SIZE);
		if (return_val <= 0)
			break ;
		*(*buffer + return_val) = '\0';
		return_val = put_line(buffer, result, save);
		if (return_val == 1 || return_val == -1)
			break ;
	}
	return (return_val);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*result;
	ssize_t		return_val;
	char		*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	*(buffer + BUFFER_SIZE) = '\0';
	result = NULL;
	return_val = save_to_result(&buffer, &result, &save);
	if (return_val == 1)
	{
		free(buffer);
		return (result);
	}
	else if (return_val == -1)
		return (exit_free(&buffer, &result, &save));
	return_val = read_line_continue(&buffer, &result, &save, &fd);
	if ((return_val == -1) || (result != NULL && ft_strlen(result) < 1))
		return (exit_free(&buffer, &result, &save));
	free(buffer);
	return (result);
}
