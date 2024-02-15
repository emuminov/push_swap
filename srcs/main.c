/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:15:33 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/15 07:43:58 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: REMOVE!!!!!!!!!!!!!!!
#include <stdio.h>

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

// TODO: handle case where lst or lst->head are NULL
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

int		list_find_position(t_node *node, t_list *lst)
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

void	_bubble_sort(int nums_len, int *arr)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < nums_len - 1)
	{
		j = 0;
		while (j < nums_len - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	*copy_as_sorted(t_list *src)
{
	int		i;
	t_node	*curr;
	int		*res;

	res = malloc(sizeof(int) * src->length);
	if (!res)
		return (NULL);
	i = 0;
	curr = src->head;
	while (i < src->length)
	{
		res[i++] = curr->value;
		curr = curr->next;
	}
	_bubble_sort(i, res);
	return (res);
}

void	_sort_3(t_stacks *stacks)
{
	t_node	*smallest;
	t_node	*biggest;

	smallest = list_find_smallest(stacks->stack_a);
	biggest = list_find_biggest(stacks->stack_a);
	if (stacks->stack_a->head == smallest && stacks->stack_a->tail != biggest)
		return (rra(stacks), sa(stacks));
	if (stacks->stack_a->head != smallest && stacks->stack_a->tail == biggest)
		return sa(stacks);
	if (stacks->stack_a->head != biggest && stacks->stack_a->tail == smallest)
		return rra(stacks);
	if (stacks->stack_a->head == biggest && stacks->stack_a->tail != smallest)
		return ra(stacks);
	if (stacks->stack_a->head == biggest && stacks->stack_a->tail == smallest)
		return (sa(stacks), rra(stacks));
}

// TODO: handle error if smallest is NULL
void	_simple_sort(int n, t_stacks *stacks)
{
	t_node	*smallest;
	int		pos;

	while (stacks->stack_a->length > 3)
	{
		smallest = list_find_smallest(stacks->stack_a);
		pos = list_find_position(smallest, stacks->stack_a);
		while (pos != 0)
		{
			if ((stacks->stack_a->length / 2) >= pos)
				ra(stacks);
			else
				rra(stacks);
			pos = list_find_position(smallest, stacks->stack_a);
		}
		pb(stacks);
	}
	_sort_3(stacks);
	while (n - 3 > 0)
	{
		pa(stacks);
		n--;
	}
}

// TODO: handle all possible errors
t_node	*list_find_value_in_range(int lower, int upper, t_list *lst)
{
	int		top_cost;
	int		bottom_cost;
	t_node	*top;
	t_node	*bottom;
	t_node	*curr;

	curr = lst->head;
	if (!curr || curr == lst->tail)
		return (curr);
	top_cost = 0;
	bottom_cost = 1;
	top = NULL;
	bottom = NULL;
	while (curr)
	{
		if (curr->value >= lower && curr->value <= upper)
		{
			top = curr;
			break ;
		}
		curr = curr->next;
		top_cost++;
		if (curr == lst->head)
			break ;
	}
	curr = lst->tail;
	while (curr)
	{
		if (curr->value >= lower && curr->value <= upper)
		{
			bottom = curr;
			break ;
		}
		curr = curr->prev;
		bottom_cost++;
		if (curr == lst->tail)
			break ;
	}
	if (top_cost <= bottom_cost)
		return (top);
	return (bottom);
}

// 0-19   | (100 / 5) * 0 | (100 / 5) * 1 - 1
// 20-39  | (100 / 5) * 1 | (100 / 5) * 2 - 1
// 40-59  | (100 / 5) * 2 | (100 / 5) * 3 - 1
// 60-79  | (100 / 5) * 3 | (100 / 5) * 4 - 1
// 80-99  | (100 / 5) * 4 | (100 / 5) * 5 - 1
int	chunk_get_lower(int chunk_index, int num_of_chunks, int arr_length, int *arr)
{
	return (arr[(arr_length / num_of_chunks) * (chunk_index - 1)]);
}

int	chunk_get_upper(int chunk_index, int num_of_chunks, int arr_length, int *arr)
{
	if (chunk_index == num_of_chunks)
		return (arr[arr_length - 1]);
	return (arr[((arr_length / num_of_chunks) * chunk_index) - 1]);
}

void	_optimal_sort(int num_of_chunks, t_stacks *stacks)
{
	int		i;
	int		lower_chunk;
	int		upper_chunk;
	int		pos;
	int		l;
	int		*sorted;
	t_node	*smallest;
	t_node	*biggest;

	//TODO: handle null error from copy_as_sorted
	sorted = copy_as_sorted(stacks->stack_a);
	i = 0;
	l = stacks->stack_a->length;
	while (i < (num_of_chunks / 2))
	{
		lower_chunk = (num_of_chunks / 2) - i;
		upper_chunk = (num_of_chunks / 2) + i + 1;
		smallest = list_find_value_in_range(chunk_get_lower(lower_chunk, num_of_chunks, l, sorted), chunk_get_upper(upper_chunk, num_of_chunks, l, sorted), stacks->stack_a);
		if (smallest)
		{
			// ft_putnbr_fd(smallest->value, 1);
			// ft_putstr_fd("\n", 1);
			pos = list_find_position(smallest, stacks->stack_a);
			while (pos != 0)
			{
				if ((stacks->stack_a->length / 2) >= pos)
					ra(stacks);
				else if ((stacks->stack_a->length / 2) < pos)
					rra(stacks);
				pos = list_find_position(smallest, stacks->stack_a);
			}
			pb(stacks);
			if (stacks->stack_b->head->value < chunk_get_lower(upper_chunk, num_of_chunks, l, sorted))
				rb(stacks);
		}
		else
			i++;
	}
	while (stacks->stack_a->length)
		pb(stacks);
	while (stacks->stack_b->length > 0)
	{
		biggest = list_find_biggest(stacks->stack_b);
		pos = list_find_position(biggest, stacks->stack_b);
		while (pos != 0)
		{
			if ((stacks->stack_b->length / 2) >= pos)
				rb(stacks);
			else if ((stacks->stack_b->length / 2) < pos)
				rrb(stacks);
			pos = list_find_position(biggest, stacks->stack_b);
		}
		pa(stacks);
	}
}

// 0 1 2 3 4 5 6 7 8 9 10 11 12 || 13 / 4 = 3
// 9 1 3 8 2 0 4 5 6 7 11 10 12
// 1 3 8 2 0 4 5 6 7 11 10 12 9 | ra
// 3 8 2 0 4 5 6 7 11 10 12 9   | pb  1
// 8 2 0 4 5 6 7 11 10 12 9     | pb  3 1
// 2 0 4 5 6 7 11 10 12 9 8     | ra  3 1
// 0 4 5 6 7 11 10 12 9 8       | pb  2 3 1
// 5 6 7 11 10 12 9 8           | pb  4 0 2 3 1
// 6 7 11 10 12 9 8             | pb  5 4 0 2 3 1
// 7 11 10 12 9 8               | pb  6 5 4 0 2 3 1
// 11 10 12 9 8                 | pb  7 6 5 4 0 2 3 1
// 8 11 10 12 9                 | rra 7 6 5 4 0 2 3 1
// 11 10 12 9                   | pb  8 7 6 5 4 0 2 3 1
// 9 11 10 12                   | rra 8 7 6 5 4 0 2 3 1
// 11 10 12                     | pb  9 8 7 6 5 4 0 2 3 1
// 10 12                        | pb 10 9 8 7 6 5 4 0 2 3 1
// 12                           | pb 11 10 9 8 7 6 5 4 0 2 3 1
//                              | pb 12 11 10 9 8 7 6 5 4 0 2 3 1

void	push_swap(t_stacks *stacks)
{
	if (stacks->stack_a->length == 3)
		return (_sort_3(stacks));
	else if (stacks->stack_a->length <= 10)
		return (_simple_sort(stacks->stack_a->length, stacks));
	else
		// 8 works best for 100
		// 16 works best for 500
		return (_optimal_sort(8, stacks));
}

// [115-150]
// 147
// 138 147
//

//TODO: refactor swapping functions into their own files
//TODO: store more information on structs (len, smallest, biggest etc)
//TODO: add error checking
//TODO: add handling of both multiple arguments and a single string
int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc == 2)
	{
		
	}
	if (argc < 2)
		return (0);
	stacks.stack_a = list_init(argc - 1, &argv[1]);
	if (!stacks.stack_a)
		return (1);
	stacks.stack_b = list_init(0, NULL);
	if (!stacks.stack_b)
	{
		list_free(stacks.stack_a);
		return (1);
	}
	push_swap(&stacks);
	// t_node *curr_a = stacks.stack_a->head;
	// while (curr_a) {
	// 	printf("%d\n", curr_a->value);
	// 	curr_a = curr_a->next;
	// 	if (curr_a == stacks.stack_a->head)
	// 		break;
	// }
}
