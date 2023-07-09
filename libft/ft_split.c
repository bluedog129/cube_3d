/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:46:47 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/30 16:47:22 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char separator)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == separator)
			i++;
		else if (s[i] != separator)
		{
			count++;
			while (s[i] != separator && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static void	*ft_free_result(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	**ft_divide_str(char **result, char const *str, \
char charset, int result_index)
{
	int	i;
	int	word_len;

	i = 0;
	result_index = 0;
	while (str[i])
	{
		if (str[i] == charset)
			i++;
		else
		{
			word_len = 0;
			while (str[i] != charset && str[i] != '\0')
			{
				word_len++;
				i++;
			}
			result[result_index] = ft_substr(str, i - word_len, word_len);
			if (result[result_index] == NULL)
				return (ft_free_result(result));
			result_index++;
		}
	}
	result[result_index] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		result_index;
	char	**result;

	word_count = ft_count_word(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	result_index = 0;
	result = ft_divide_str(result, s, c, result_index);
	return (result);
}
