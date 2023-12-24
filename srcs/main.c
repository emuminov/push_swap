/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:15:33 by emuminov          #+#    #+#             */
/*   Updated: 2023/12/24 03:11:47 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				value;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		length;
}	t_list;

typedef struct s_stacks
{
	t_list	*stack_a;
	t_list	*stack_b;
}	t_stacks;

void	list_free(t_list *lst)
{
	t_node	*curr;
	t_node	*next;

	if (!lst)
		return ;
	curr = lst->head;
	next = lst->head->next;
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

t_list	*list_append(int num, t_list *lst)
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

t_list	*list_init(int nums_len, char **nums)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
	if (nums_len == 0 || !nums)
		return (lst);
	while (lst->length < nums_len)
	{
		if (!list_append(ft_atoi(nums[lst->length++]), lst))
		{
			list_free(lst);
			return (NULL);
		}
	}
	return (lst);
}

void	_s(t_list *stack)
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
	_s(stacks->stack_a);
	ft_putstr_fd("sa\n", STDOUT_FILENO);
}

void	sb(t_stacks *stacks)
{
	_s(stacks->stack_b);
	ft_putstr_fd("sb\n", STDOUT_FILENO);
}

void	ss(t_stacks *stacks)
{
	_s(stacks->stack_a);
	_s(stacks->stack_b);
	ft_putstr_fd("ss\n", STDOUT_FILENO);
}

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

void	_p(t_list *src_stack, t_list *dest_stack)
{
	t_node	*pushed_node;

	if (!src_stack->head)
		return ;
	pushed_node = list_unlink_head(src_stack);
	list_prepend_node(pushed_node, dest_stack);
}

void	pa(t_stacks *stacks)
{
	_p(stacks->stack_b, stacks->stack_a);
	ft_putstr_fd("pa\n", STDOUT_FILENO);
}

void	pb(t_stacks *stacks)
{
	_p(stacks->stack_a, stacks->stack_b);
	ft_putstr_fd("pb\n", STDOUT_FILENO);
}

void	_r(t_list *stack)
{
	if (!stack->head || !stack->tail)
		return ;
	stack->tail = stack->head;
	stack->head = stack->head->next;
}

void	ra(t_stacks *stacks)
{
	_r(stacks->stack_a);
	ft_putstr_fd("ra\n", STDOUT_FILENO);
}

void	rb(t_stacks *stacks)
{
	_r(stacks->stack_b);
	ft_putstr_fd("rb\n", STDOUT_FILENO);
}

void	rr(t_stacks *stacks)
{
	_r(stacks->stack_a);
	_r(stacks->stack_b);
	ft_putstr_fd("rr\n", STDOUT_FILENO);
}

void	_rr(t_list *stack)
{
	if (!stack->head || !stack->tail)
		return ;
	stack->head = stack->tail;
	stack->tail = stack->tail->prev;
}

void	rra(t_stacks *stacks)
{
	_rr(stacks->stack_a);
	ft_putstr_fd("rra\n", STDOUT_FILENO);
}

void	rrb(t_stacks *stacks)
{
	_rr(stacks->stack_b);
	ft_putstr_fd("rrb\n", STDOUT_FILENO);
}

void	rrr(t_stacks *stacks)
{
	_rr(stacks->stack_a);
	_rr(stacks->stack_b);
	ft_putstr_fd("rrr\n", STDOUT_FILENO);
}

void	_sort_3(t_stacks *stacks)
{
	t_list	*stack_a;

	stack_a = stacks->stack_a;
	if (stack_a->head->value == 1 && stack_a->tail->value == 3)
		return ;
	if (stack_a->head->value == 1 && stack_a->tail->value == 2)
	{
		rra(stacks);
		return sa(stacks);
	}
	if (stack_a->head->value == 2 && stack_a->tail->value == 3)
		return sa(stacks);
	if (stack_a->head->value == 2 && stack_a->tail->value == 1)
		return rra(stacks);
	if (stack_a->head->value == 3 && stack_a->tail->value == 2)
		return ra(stacks);
	if (stack_a->head->value == 3 && stack_a->tail->value == 1)
	{
		sa(stacks);
		return rra(stacks);
	}
}

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

// void	_sort(t_stacks *stacks)
// {
// 	
// }
//    3 1 2 5 4  |
// sa 1 3 2 5 4  |
// pb 3 2 5 4    | 1
// sa 2 3 5 4    | 1
// pb 3 5 4      | 2 1
// pb 5 4        | 3 2 1
// sa 4 5        | 3 2 1
// pa 3 4 5      | 2 1
// pa 2 3 4 5    | 1
// pa 1 2 3 4 5

void	push_swap(int nums_len, t_stacks *stacks)
{
	if (nums_len == 3)
		return _sort_3(stacks);
}

//TODO: refactor swapping functions into their own files
//TODO: store more information on structs (len, smallest, biggest etc)
//TODO: add error checking
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	t_stacks	stacks;

	stacks.stack_a = list_init(argc - 1, &argv[1]);
	if (!stacks.stack_a)
		return (1);
	stacks.stack_b = list_init(0, NULL);
	if (!stacks.stack_b)
		return (1);
	// push_swap(argc - 1, &stacks);
	ra(&stacks);
	pb(&stacks);
	pb(&stacks);
	sa(&stacks);
	rra(&stacks);
	pa(&stacks);
	pa(&stacks);
	ft_putstr_fd("---\n", 1);
	t_node *curr_a = stacks.stack_a->head;
	while (curr_a) {
		printf("%d\n", curr_a->value);
		curr_a = curr_a->next;
		if (curr_a == stacks.stack_a->head)
			break;
	}
	ft_putstr_fd("---\n", 1);
	printf("%d\n", list_is_sorted(stacks.stack_a));
	// t_node *curr_b = stacks.stack_b->head;
	// while (curr_b) {
	// 	printf("%d\n", curr_b->value);
	// 	curr_b = curr_b->next;
	// 	if (curr_b == stacks.stack_b->head)
	// 		break;
	// }
}
