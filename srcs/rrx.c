/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:12:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 13:13:37 by emuminov         ###   ########.fr       */
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

void	rra(t_stacks *stacks)
{
	_rrx(stacks->stack_a);
	ft_putstr_fd("rra\n", STDOUT_FILENO);
}

void	rrb(t_stacks *stacks)
{
	_rrx(stacks->stack_b);
	ft_putstr_fd("rrb\n", STDOUT_FILENO);
}

void	rrr(t_stacks *stacks)
{
	_rrx(stacks->stack_a);
	_rrx(stacks->stack_b);
	ft_putstr_fd("rrr\n", STDOUT_FILENO);
}
