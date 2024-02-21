/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:41:05 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 13:00:35 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Contains functons for operations with circular doubly linked lists. */
#include "../include/push_swap.h"

t_list	*list_create(int nums_len, char **values)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
	if (nums_len == 0 || !values)
		return (lst);
	while (lst->length < nums_len)
	{
		if (!list_append_value(ft_atoi(values[lst->length++]), lst))
		{
			list_free(lst);
			return (NULL);
		}
	}
	return (lst);
}

void	list_free(t_list *lst)
{
	t_node	*curr;
	t_node	*next;

	if (!lst)
		return ;
	curr = lst->head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
		if (curr == lst->head)
			break ;
	}
	free(lst);
}

/* Adds value as node as tail to the list. */
t_list	*list_append_value(int num, t_list *lst)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = num;
	if (!lst->head)
	{
		node->next = node;
		node->prev = node;
		lst->head = node;
		lst->tail = node;
		return (lst);
	}
	node->next = lst->head;
	node->prev = lst->tail;
	lst->tail->next = node;
	lst->tail = node;
	lst->head->prev = node;
	return (lst);
}

/* Adds existing node as the head to the list. */
void	list_prepend_node(t_node *node, t_list *lst)
{
	if (!lst->head || !lst->tail)
	{
		lst->head = node;
		lst->tail = node;
		node->next = node;
		node->prev = node;
		lst->length = 1;
		return ;
	}
	node->next = lst->head;
	node->prev = lst->tail;
	lst->head->prev = node;
	lst->head = node;
	lst->tail->next = node;
	lst->length++;
}

/* Removes the head from the list and returns it. */
t_node	*list_unlink_head(t_list *lst)
{
	t_node	*node;

	node = lst->head;
	if (!node)
		return (NULL);
	if (node && node == lst->tail)
	{
		lst->head = NULL;
		lst->tail = NULL;
		lst->length = 0;
		return (node);
	}
	lst->head = node->next;
	lst->head->prev = lst->tail;
	lst->tail->next = lst->head;
	lst->length--;
	return (node);
}
