/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:19:28 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/26 10:20:32 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Contains functons for operations with arrays. */
#include "../include/push_swap.h"

/* Frees a NULL-terminated array of strings. Named after ft_split. */
void	arr_free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/* Sorts an array using simple bubble sort algorithm. */
void	arr_bubble_sort(int l, int *arr)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < l - 1)
	{
		j = 0;
		while (j < l - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/* Duplicates an array of strings as a NULL-terminated array of strings. */
char	**arr_duplicate(int l, char **arr)
{
	int		i;
	char	**result;

	i = 0;
	while (arr[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < l)
	{
		result[i] = ft_strdup(arr[i]);
		if (!result[i])
		{
			arr_free_split(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

/* Used to get lower and upper values for specific chunks in an array
within certain range. Each chunk has its index starting from 1
and its values depends on the number of chunks.
Example of array with lenght (l) == 100 and numbers of chunks (n) == 5:
0-19   | (100 / 5) * 0 | (100 / 5) * 1 - 1
20-39  | (100 / 5) * 1 | (100 / 5) * 2 - 1
40-59  | (100 / 5) * 2 | (100 / 5) * 3 - 1
60-79  | (100 / 5) * 3 | (100 / 5) * 4 - 1
80-99  | (100 / 5) * 4 | (100 / 5) * 5 - 1 */
int	arr_cl(int i, int n, int l, int *arr)
{
	return (arr[(l / n) * (i - 1)]);
}

int	arr_cu(int i, int n, int l, int *arr)
{
	if (i == n)
		return (arr[l - 1]);
	return (arr[((l / n) * i) - 1]);
}
