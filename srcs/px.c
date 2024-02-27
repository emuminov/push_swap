/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:10:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/27 13:28:47 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* pa, pb operations. */
#include "../include/push_swap.h"

void	_px(t_list *src_stack, t_list *dest_stack)
{
	t_node	*pushed_node;

	if (!src_stack->head)
		return ;
	pushed_node = list_unlink_head(src_stack);
	list_prepend_node(pushed_node, dest_stack);
}

void	pa(int silent, t_stacks *stacks)
{
	_px(stacks->stack_b, stacks->stack_a);
	if (!silent)
		ft_putstr_fd("pa\n", STDOUT_FILENO);
}

void	pb(int silent, t_stacks *stacks)
{
	_px(stacks->stack_a, stacks->stack_b);
	if (!silent)
		ft_putstr_fd("pb\n", STDOUT_FILENO);
}
