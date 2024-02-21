/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:59:16 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 12:38:17 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Contains functons for operations with circular doubly linked lists. */
#include "../include/push_swap.h"

static t_node	*list_find_value_from_top(int lower, int upper, t_list *lst)
{
	t_node	*curr;
	t_node	*found;

	curr = lst->head;
	found = NULL;
	while (curr)
	{
		if (curr->value >= lower && curr->value <= upper)
		{
			found = curr;
			break ;
		}
		curr = curr->next;
		if (curr == lst->head)
			break ;
	}
	return (found);
}

static t_node	*list_find_value_from_bottom(int lower, int upper, t_list *lst)
{
	t_node	*curr;
	t_node	*found;

	curr = lst->tail;
	found = NULL;
	while (curr)
	{
		if (curr->value >= lower && curr->value <= upper)
		{
			found = curr;
			break ;
		}
		curr = curr->prev;
		if (curr == lst->tail)
			break ;
	}
	return (found);
}

/* Finds closest to the head node between lower and upper inclusively. */
t_node	*list_find_value_in_range(int lower, int upper, t_list *lst)
{
	int		top_cost;
	int		bot_cost;
	t_node	*top;
	t_node	*bot;
	t_node	*curr;

	curr = lst->head;
	if (!curr || curr == lst->tail)
		return (curr);
	top = list_find_value_from_top(lower, upper, lst);
	bot = list_find_value_from_bottom(lower, upper, lst);
	if (!top || !bot)
		return (NULL);
	top_cost = list_find_position(top, lst);
	bot_cost = lst->length - list_find_position(bot, lst);
	if (top_cost <= bot_cost)
		return (top);
	return (bot);
}

int	*list_copy_as_sorted_arr(t_list *lst)
{
	int		i;
	t_node	*curr;
	int		*res;

	if (!lst)
		return (NULL);
	res = malloc(sizeof(int) * lst->length);
	if (!res)
		return (NULL);
	i = 0;
	curr = lst->head;
	while (i < lst->length)
	{
		res[i++] = curr->value;
		curr = curr->next;
	}
	arr_bubble_sort(i, res);
	return (res);
}
