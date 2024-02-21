/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:07:09 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 13:08:05 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* sa, sb, ss operations. */
#include "../include/push_swap.h"

/* Generic function for swapping top to values on the stack. */
void	_sx(t_list *stack)
{
	t_node	*tmp;

	if (!stack->head)
		return ;
	tmp = stack->head;
	stack->head = tmp->next;
	tmp->prev = stack->head;
	tmp->next = stack->head->next;
	tmp->next->prev = tmp;
	stack->head->next = tmp;
	stack->head->prev = stack->tail;
	stack->tail->next = stack->head;
}

void	sa(t_stacks *stacks)
{
	_sx(stacks->stack_a);
	ft_putstr_fd("sa\n", STDOUT_FILENO);
}

void	sb(t_stacks *stacks)
{
	_sx(stacks->stack_b);
	ft_putstr_fd("sb\n", STDOUT_FILENO);
}

void	ss(t_stacks *stacks)
{
	_sx(stacks->stack_a);
	_sx(stacks->stack_b);
	ft_putstr_fd("ss\n", STDOUT_FILENO);
}
