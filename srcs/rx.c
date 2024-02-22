/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:39 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 08:07:53 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ra, rb, rr operations. */
#include "../include/push_swap.h"

void	_rx(t_list *stack)
{
	if (!stack->head || !stack->tail)
		return ;
	stack->tail = stack->head;
	stack->head = stack->head->next;
}

void	ra(int silent, t_stacks *stacks)
{
	_rx(stacks->stack_a);
	if (!silent)
		ft_putstr_fd("ra\n", STDOUT_FILENO);
}

void	rb(int silent, t_stacks *stacks)
{
	_rx(stacks->stack_b);
	if (!silent)
		ft_putstr_fd("rb\n", STDOUT_FILENO);
}

void	rr(int silent, t_stacks *stacks)
{
	_rx(stacks->stack_a);
	_rx(stacks->stack_b);
	if (!silent)
		ft_putstr_fd("rr\n", STDOUT_FILENO);
}
