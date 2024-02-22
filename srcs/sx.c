/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:07:09 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 08:08:02 by emuminov         ###   ########.fr       */
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

void	sa(int silent, t_stacks *stacks)
{
	_sx(stacks->stack_a);
	if (!silent)
		ft_putstr_fd("sa\n", STDOUT_FILENO);
}

void	sb(int silent, t_stacks *stacks)
{
	_sx(stacks->stack_b);
	if (!silent)
		ft_putstr_fd("sb\n", STDOUT_FILENO);
}

void	ss(int silent, t_stacks *stacks)
{
	_sx(stacks->stack_a);
	_sx(stacks->stack_b);
	if (!silent)
		ft_putstr_fd("ss\n", STDOUT_FILENO);
}
