/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:12:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 08:07:56 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* rra, rrb, rrr operations. */
#include "../include/push_swap.h"

void	_rrx(t_list *stack)
{
	if (!stack->head || !stack->tail)
		return ;
	stack->head = stack->tail;
	stack->tail = stack->tail->prev;
}

void	rra(int silent, t_stacks *stacks)
{
	_rrx(stacks->stack_a);
	if (!silent)
		ft_putstr_fd("rra\n", STDOUT_FILENO);
}

void	rrb(int silent, t_stacks *stacks)
{
	_rrx(stacks->stack_b);
	if (!silent)
		ft_putstr_fd("rrb\n", STDOUT_FILENO);
}

void	rrr(int silent, t_stacks *stacks)
{
	_rrx(stacks->stack_a);
	_rrx(stacks->stack_b);
	if (!silent)
		ft_putstr_fd("rrr\n", STDOUT_FILENO);
}
