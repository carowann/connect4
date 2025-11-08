/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:34:59 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 17:35:13 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect.h"

char	**ft_duplicate_char_matrix(const char **matrix)
{
	int		count_rows;
	int		str_len;
	char	**result;
	int		i;

	count_rows = ft_count_matrix_row((const void **) matrix);
	result = malloc(sizeof(char *) * (count_rows + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		str_len = ft_strlen(matrix[i]);
		result[i] = ft_calloc(str_len + 1, sizeof(char));
		ft_strlcpy(result[i], matrix[i], str_len + 1);
		i++;
	}
	result[i] = NULL;
	return (result);
}

size_t	ft_count_matrix_row(const void **matrix)
{
	size_t	i;

	if (matrix == NULL)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
