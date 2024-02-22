/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:20:32 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 08:10:42 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	sort_2(t_stacks *stacks)
{
	if (stacks->stack_a->head->value > stacks->stack_a->tail->value)
		sa(0, stacks);
}

static void	sort_3(t_stacks *stacks)
{
	t_node	*smallest;
	t_node	*biggest;

	smallest = list_find_smallest(stacks->stack_a);
	biggest = list_find_biggest(stacks->stack_a);
	if (stacks->stack_a->head == smallest && stacks->stack_a->tail != biggest)
		return (rra(0, stacks), sa(0, stacks));
	if (stacks->stack_a->head != smallest && stacks->stack_a->tail == biggest)
		return (sa(0, stacks));
	if (stacks->stack_a->head != biggest && stacks->stack_a->tail == smallest)
		return (rra(0, stacks));
	if (stacks->stack_a->head == biggest && stacks->stack_a->tail != smallest)
		return (ra(0, stacks));
	if (stacks->stack_a->head == biggest && stacks->stack_a->tail == smallest)
		return (sa(0, stacks), rra(0, stacks));
}

static void	simple_sort(int n, t_stacks *stacks)
{
	t_node	*smallest;

	while (stacks->stack_a->length > 3)
	{
		smallest = list_find_smallest(stacks->stack_a);
		stack_a_rotate_to_top(smallest, stacks);
		pb(0, stacks);
	}
	sort_3(stacks);
	while (n - 3 > 0)
	{
		pa(0, stacks);
		n--;
	}
}

static void	optimal_sort(int num_of_chunks, t_stacks *stacks)
{
	t_move	best_move;

	divide_in_chunks(num_of_chunks, stacks);
	simple_sort(stacks->stack_a->length, stacks);
	while (stacks->stack_b->length)
	{
		best_move = move_find_best(stacks);
		move_apply(&best_move, stacks);
		pa(0, stacks);
	}
	stack_a_rotate_to_top(list_find_smallest(stacks->stack_a), stacks);
}

void	push_swap(t_stacks *stacks)
{
	if (stacks->stack_a->length == 1 || list_is_sorted(stacks->stack_a))
		return ;
	else if (stacks->stack_a->length == 2)
		return (sort_2(stacks));
	else if (stacks->stack_a->length == 3)
		return (sort_3(stacks));
	else if (stacks->stack_a->length <= 10)
		return (simple_sort(stacks->stack_a->length, stacks));
	else if (stacks->stack_a->length <= 200)
		return (optimal_sort(2, stacks));
	else
		return (optimal_sort(4, stacks));
}
