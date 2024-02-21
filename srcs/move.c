/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:56:06 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 13:00:10 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Move struct represents the amount of rotations needed to be done
for the node to appear in the top of its own stack.
This file has functions related to it. */
#include "../include/push_swap.h"

static int	move_total(t_move *move)
{
	int	total_rx;
	int	total_rrx;

	if (move->ra > move->rb)
		total_rx = move->ra;
	else
		total_rx = move->rb;
	if (move->rra > move->rrb)
		total_rrx = move->rra;
	else
		total_rrx = move->rrb;
	move->total = total_rx + total_rrx;
	return (move->total);
}

static t_move	*move_init(t_move *move)
{
	move->ra = 0;
	move->rb = 0;
	move->rra = 0;
	move->rrb = 0;
	move->total = INT_MAX;
	return (move);
}

static void	move_calculate(t_node *node, t_stacks *stacks, t_move *move)
{
	t_node	*target;
	int		target_pos;
	int		curr_pos;

	target = list_find_target(node, stacks->stack_a);
	target_pos = list_find_position(target, stacks->stack_a);
	curr_pos = list_find_position(node, stacks->stack_b);
	if (target_pos <= (stacks->stack_a->length / 2))
		move->ra = target_pos;
	else
		move->rra = stacks->stack_a->length - target_pos;
	if (curr_pos <= (stacks->stack_b->length / 2))
		move->rb = curr_pos;
	else
		move->rrb = stacks->stack_b->length - curr_pos;
	move_total(move);
}

t_move	move_find_best(t_stacks *stacks)
{
	t_move	best_move;
	t_move	curr_move;
	t_node	*curr;

	move_init(&best_move);
	curr = stacks->stack_b->head;
	while (curr)
	{
		move_init(&curr_move);
		move_calculate(curr, stacks, &curr_move);
		if (best_move.total > curr_move.total)
		{
			best_move.ra = curr_move.ra;
			best_move.rb = curr_move.rb;
			best_move.rra = curr_move.rra;
			best_move.rrb = curr_move.rrb;
			best_move.total = curr_move.total;
		}
		curr = curr->next;
		if (curr == stacks->stack_b->head || best_move.total < 2)
			break ;
	}
	return (best_move);
}

void	move_apply(t_move *move, t_stacks *stacks)
{
	while (move->ra && move->rb)
	{
		move->ra--;
		move->rb--;
		rr(stacks);
	}
	while (move->rra && move->rrb)
	{
		move->rra--;
		move->rrb--;
		rrr(stacks);
	}
	while (move->ra--)
		ra(stacks);
	while (move->rb--)
		rb(stacks);
	while (move->rra--)
		rra(stacks);
	while (move->rrb--)
		rrb(stacks);
}
