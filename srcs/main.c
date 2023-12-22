/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:15:33 by emuminov          #+#    #+#             */
/*   Updated: 2023/12/22 11:46:34 by emuminov         ###   ########.fr       */
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
	int		i;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	if (nums_len == 0 || !nums)
		return (lst);
	i = 0;
	while (i < nums_len)
	{
		if (!list_append(ft_atoi(nums[i++]), lst))
		{
			list_free(lst);
			return (NULL);
		}
	}
	return (lst);
}

void	_s(t_list *stack)
{
	int	tmp;

	if (!stack->head)
		return ;
	tmp = stack->head->value;
	stack->head->value = stack->head->next->value;
	stack->head->next->value = tmp;
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

void	_p(t_list *src_stack, t_list *dest_stack)
{
	t_node	*src_head;
	t_node	*dest_head;

	if (!src_stack->head || !src_stack->tail)
		return ;
	src_head = src_stack->head;
	dest_head = dest_stack->head;
	src_stack->head = src_head->next;
	src_stack->head->prev = src_head->prev;
	src_stack->tail->next = src_stack->head;
	if (!dest_stack->tail)
	{
		dest_stack->tail = src_head;
		src_head->next = src_head;
	}
	else
	{
		dest_head->prev = src_head;
		src_head->next = dest_head;
		dest_stack->head->prev = src_head;
		dest_stack->tail->next = src_head;
	}
	src_head->prev = dest_stack->tail;
	dest_stack->head = src_head;
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

// void	_sort(t_stacks *stacks)
// {
// 	
// }
// 3 1 2 5 4
// ra pb pb sa pb pa pa pa pa

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
	pb(&stacks);
	pa(&stacks);
	pa(&stacks);
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
	// t_node *curr_b = stacks.stack_b->head;
	// while (curr_b) {
	// 	printf("%d\n", curr_b->value);
	// 	curr_b = curr_b->next;
	// 	if (curr_b == stacks.stack_b->head)
	// 		break;
	// }
}
