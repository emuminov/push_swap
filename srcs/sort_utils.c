/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:15:26 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 11:21:55 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* Rotates inputted node to the top of stack a. */
void	stack_a_rotate_to_top(t_node *node, t_stacks *stacks)
{
	int	pos;

	pos = list_find_position(node, stacks->stack_a);
	if ((stacks->stack_a->length / 2) >= pos)
	{
		while (pos--)
			ra(0, stacks);
		return ;
	}
	pos = stacks->stack_a->length - pos;
	while (pos--)
		rra(0, stacks);
}

/* Rotates inputted node to the top of stack b. */
void	stack_b_rotate_to_top(t_node *node, t_stacks *stacks)
{
	int	pos;

	pos = list_find_position(node, stacks->stack_b);
	{
		while (pos--)
			rb(0, stacks);
		return ;
	}
	pos = stacks->stack_b->length - pos;
	while (pos--)
		rrb(0, stacks);
}

/* Divides stack_a into n chunks and pushes them to stack_b,
leaving only 6 values at least in stack_a. */
void	divide_in_chunks(int n, t_stacks *stacks)
{
	int		*sorted;
	int		i;
	int		l;
	t_node	*node;

	sorted = list_copy_as_sorted_arr(stacks->stack_a);
	if (!sorted)
		handle_error(stacks->stack_a, stacks->stack_b, NULL, 1);
	i = 0;
	l = stacks->stack_a->length;
	while (i < (n / 2) && stacks->stack_a->length > 6)
	{
		node = list_find_value_in_range(arr_cl(n / 2 - i, n, l, sorted),
				arr_cu(n / 2 + i + 1, n, l, sorted), stacks->stack_a);
		if (!node)
		{
			i++;
			continue ;
		}
		stack_a_rotate_to_top(node, stacks);
		pb(0, stacks);
		if (stacks->stack_b->head->value < arr_cl(n / 2 + i + 1, n, l, sorted))
			rb(0, stacks);
	}
	free(sorted);
}
