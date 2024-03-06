/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:43:32 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/06 13:37:38 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Functions related to parsing the input and handling errors. */
#include "../include/push_swap.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	check_errors(char **values)
{
	int	i;
	int	j;

	if (values[0] == NULL)
		handle_error(NULL, NULL, values, 0);
	i = 0;
	while (values[i])
	{
		if (!is_numeric(values[i])
			|| (ft_atoi(values[i]) != ft_atol(values[i])))
			handle_error(NULL, NULL, values, 0);
		j = i + 1;
		while (values[j])
		{
			if (ft_atoi(values[i]) == ft_atoi(values[j]))
				handle_error(NULL, NULL, values, 0);
			j++;
		}
		i++;
	}
}

void	handle_error(t_list *stack_a, t_list *stack_b, char **arr, int silent)
{
	if (stack_a)
		list_free(stack_a);
	if (stack_b)
		list_free(stack_b);
	if (arr)
		arr_free_split(arr);
	if (!silent)
		ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/* Checks if the input is correct, and if it is,
returns it as a circular doubly linked list. */
t_list	*parse(int argc, char **argv)
{
	char	**values;
	t_list	*result;
	int		i;

	if (argc == 2 && !is_numeric(argv[1]))
		values = ft_split(argv[1], ' ');
	else
		values = arr_duplicate(argc - 1, &argv[1]);
	if (values == NULL)
		handle_error(NULL, NULL, values, 1);
	check_errors(values);
	i = 0;
	while (values[i])
		i++;
	result = list_create(i, values);
	arr_free_split(values);
	if (!result)
		handle_error(NULL, NULL, NULL, 1);
	return (result);
}
