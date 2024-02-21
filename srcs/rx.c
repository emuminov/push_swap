/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:11:39 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 13:13:47 by emuminov         ###   ########.fr       */
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

void	ra(t_stacks *stacks)
{
	_rx(stacks->stack_a);
	ft_putstr_fd("ra\n", STDOUT_FILENO);
}

void	rb(t_stacks *stacks)
{
	_rx(stacks->stack_b);
	ft_putstr_fd("rb\n", STDOUT_FILENO);
}

void	rr(t_stacks *stacks)
{
	_rx(stacks->stack_a);
	_rx(stacks->stack_b);
	ft_putstr_fd("rr\n", STDOUT_FILENO);
}
