/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:49:38 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 12:38:14 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Contains functons for operations with circular doubly linked lists. */
#include "../include/push_swap.h"

t_node	*list_find_smallest(t_list *lst)
{
	t_node	*curr;
	t_node	*smallest;

	curr = lst->head;
	smallest = curr;
	if (!curr || curr == lst->tail)
		return (curr);
	while (curr)
	{
		if (curr->value < smallest->value)
			smallest = curr;
		curr = curr->next;
		if (curr == lst->head)
			break ;
	}
	return (smallest);
}

t_node	*list_find_biggest(t_list *lst)
{
	t_node	*curr;
	t_node	*biggest;

	curr = lst->head;
	biggest = curr;
	if (!curr || curr == lst->tail)
		return (curr);
	while (curr)
	{
		if (curr->value > biggest->value)
			biggest = curr;
		curr = curr->next;
		if (curr == lst->head)
			break ;
	}
	return (biggest);
}

/* Finds index of a node in the list. */
int	list_find_position(t_node *node, t_list *lst)
{
	int		i;
	t_node	*curr;

	i = 0;
	curr = lst->head;
	while (curr)
	{
		if (curr == node)
			return (i);
		curr = curr->next;
		if (curr == lst->head)
			break ;
		i++;
	}
	return (-1);
}

int	list_is_sorted(t_list *lst)
{
	t_node	*curr;

	curr = lst->head;
	if (!curr || curr == lst->tail)
		return (1);
	curr = curr->next;
	while (curr)
	{
		if (curr->value < curr->prev->value)
			return (0);
		curr = curr->next;
		if (curr == lst->head)
			break ;
	}
	return (1);
}

/* Finds the smallest node that is bigger than node passed as a parameter. */
t_node	*list_find_target(t_node *node, t_list *lst)
{
	t_node	*curr;
	t_node	*target;
	t_node	*smallest;

	curr = lst->head;
	target = list_find_biggest(lst);
	smallest = curr;
	while (curr)
	{
		if (curr->value < smallest->value)
			smallest = curr;
		if ((curr->value > node->value) && (curr->value < target->value))
			target = curr;
		curr = curr->next;
		if (curr == lst->head || (target->value - node->value) == 1)
			break ;
	}
	if (target->value < node->value)
		return (smallest);
	return (target);
}
