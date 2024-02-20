/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:15:33 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/20 17:36:52 by emuminov         ###   ########.fr       */
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

typedef struct s_move
{
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	total;
}	t_move;

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

t_list	*list_init(int nums_len, char **values)
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
		if (!list_append(ft_atoi(values[lst->length++]), lst))
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

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	handle_error(t_list *stack_a, t_list *stack_b, char **arr, int silent)
{
	if (stack_a)
		list_free(stack_a);
	if (stack_b)
		list_free(stack_b);
	if (arr)
		ft_free_split(arr);
	if (!silent)
		ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	check_errors(char **values)
{
	int	i;
	int	j;

	if (values[0] == NULL)
		handle_error(NULL, NULL, values, 0);
	i = 0;
	while (values[i])
	{
		if (!is_numeric(values[i])
			|| (ft_atoi(values[i]) != ft_atol(values[i])))
			handle_error(NULL, NULL, values, 0);
		j = i + 1;
		while (values[j])
		{
			if (atoi(values[i]) == atoi(values[j]))
				handle_error(NULL, NULL, values, 0);
			j++;
		}
		i++;
	}
}

/* Duplicates NULL-terminated array of strings */
char	**arr_duplicate(char **arr)
{
	int		i;
	char	**result;

	i = 0;
	while (arr[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		result[i] = ft_strdup(arr[i]);
		if (!result[i])
		{
			ft_free_split(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

t_list	*parse(int argc, char **argv)
{
	char	**values;
	t_list	*result;
	int		i;

	if (argc == 2 && !is_numeric(argv[1]))
		values = ft_split(argv[1], ' ');
	else
		values = arr_duplicate(&argv[1]);
	if (values == NULL)
		handle_error(NULL, NULL, values, 1);
	check_errors(values);
	i = 0;
	while (values[i])
		i++;
	result = list_init(i, values);
	ft_free_split(values);
	if (!result)
		handle_error(NULL, NULL, NULL, 1);
	return (result);
}

void	bubble_sort(int nums_len, int *arr)
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

	if (!src)
		return (NULL);
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
	bubble_sort(i, res);
	return (res);
}

void	stack_a_rotate_to_top(t_node *node, t_stacks *stacks)
{
	int	pos;

	pos = list_find_position(node, stacks->stack_a);
	if ((stacks->stack_a->length / 2) >= pos)
	{
		while (pos--)
			ra(stacks);
		return ;
	}
	pos = stacks->stack_a->length - pos;
	while (pos--)
		rra(stacks);
}

void	stack_b_rotate_to_top(t_node *node, t_stacks *stacks)
{
	int	pos;

	pos = list_find_position(node, stacks->stack_b);
	{
		while (pos--)
			rb(stacks);
		return ;
	}
	pos = stacks->stack_b->length - pos;
	while (pos--)
		rrb(stacks);
}

void	_sort_2(t_stacks *stacks)
{
	if (stacks->stack_a->head->value > stacks->stack_a->tail->value)
		sa(stacks);
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
		return (sa(stacks));
	if (stacks->stack_a->head != biggest && stacks->stack_a->tail == smallest)
		return (rra(stacks));
	if (stacks->stack_a->head == biggest && stacks->stack_a->tail != smallest)
		return (ra(stacks));
	if (stacks->stack_a->head == biggest && stacks->stack_a->tail == smallest)
		return (sa(stacks), rra(stacks));
}

void	simple_sort(int n, t_stacks *stacks)
{
	t_node	*smallest;

	while (stacks->stack_a->length > 3)
	{
		smallest = list_find_smallest(stacks->stack_a);
		stack_a_rotate_to_top(smallest, stacks);
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
t_node	*list_find_value(int lower, int upper, t_list *lst)
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
int	list_cl(int index, int n, int l, int *arr)
{
	return (arr[(l / n) * (index - 1)]);
}

int	list_cu(int index, int n, int l, int *arr)
{
	if (index == n)
		return (arr[l - 1]);
	return (arr[((l / n) * index) - 1]);
}

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

int	move_total(t_move *move)
{
	int	total_rx;
	int	total_rrx;

	if (move->ra > move->rb)
		total_rx = move->ra;
	else
		total_rx = move->rb;
	if (move->rra > move->rrb)
		total_rrx = move->rra;
	else
		total_rrx = move->rrb;
	move->total = total_rx + total_rrx;
	return (move->total);
}

t_move	*move_init(t_move *move)
{
	move->ra = 0;
	move->rb = 0;
	move->rra = 0;
	move->rrb = 0;
	move->total = INT_MAX;
	return (move);
}

t_move	*move_copy(t_move *dest, t_move *src)
{
	dest->ra = src->ra;
	dest->rb = src->rb;
	dest->rra = src->rra;
	dest->rrb = src->rrb;
	dest->total = src->total;
	return (dest);
}

void	move_calculate(t_node *node, t_stacks *stacks, t_move *move)
{
	t_node	*target;
	int		target_pos;
	int		curr_pos;

	target = list_find_target(node, stacks->stack_a);
	target_pos = list_find_position(target, stacks->stack_a);
	curr_pos = list_find_position(node, stacks->stack_b);
	if (target_pos <= (stacks->stack_a->length / 2))
		move->ra = target_pos;
	else
		move->rra = stacks->stack_a->length - target_pos;
	if (curr_pos <= (stacks->stack_b->length / 2))
		move->rb = curr_pos;
	else
		move->rrb = stacks->stack_b->length - curr_pos;
	move_total(move);
}

t_move	move_find_best(t_stacks *stacks)
{
	t_move	best_move;
	t_move	curr_move;
	t_node	*curr;

	move_init(&best_move);
	curr = stacks->stack_b->head;
	while (curr)
	{
		move_init(&curr_move);
		move_calculate(curr, stacks, &curr_move);
		if (best_move.total > curr_move.total)
			move_copy(&best_move, &curr_move);
		curr = curr->next;
		if (curr == stacks->stack_b->head || best_move.total < 2)
			break ;
	}
	return (best_move);
}

void	move_apply(t_move *move, t_stacks *stacks)
{
	while (move->ra && move->rb)
	{
		move->ra--;
		move->rb--;
		rr(stacks);
	}
	while (move->rra && move->rrb)
	{
		move->rra--;
		move->rrb--;
		rrr(stacks);
	}
	while (move->ra--)
		ra(stacks);
	while (move->rb--)
		rb(stacks);
	while (move->rra--)
		rra(stacks);
	while (move->rrb--)
		rrb(stacks);
}

/* Divides stack_a into n chunks and pushes them to stack_b,
 * leaving only 6 values in stack_a.
 * n / 2 - i     = lower chunk index
 * n / 2 + i + 1 = upper chunk index */
void	divide_in_chunks(int n, t_stacks *stacks)
{
	int		*sorted;
	int		i;
	int		l;
	t_node	*node;

	sorted = copy_as_sorted(stacks->stack_a);
	if (!sorted)
		handle_error(stacks->stack_a, stacks->stack_b, NULL, 1);
	i = 0;
	l = stacks->stack_a->length;
	while (i < (n / 2) && stacks->stack_a->length > 6)
	{
		node = list_find_value(list_cl(n / 2 - i, n, l, sorted),
				list_cu(n / 2 + i + 1, n, l, sorted), stacks->stack_a);
		if (!node)
		{
			i++;
			continue ;
		}
		stack_a_rotate_to_top(node, stacks);
		pb(stacks);
		if (stacks->stack_b->head->value < list_cl(n / 2 + i + 1, n, l, sorted))
			rb(stacks);
	}
	free(sorted);
}

void	optimal_sort(int num_of_chunks, t_stacks *stacks)
{
	t_move	best_move;

	divide_in_chunks(num_of_chunks, stacks);
	simple_sort(stacks->stack_a->length, stacks);
	while (stacks->stack_b->length)
	{
		best_move = move_find_best(stacks);
		move_apply(&best_move, stacks);
		pa(stacks);
	}
	stack_a_rotate_to_top(list_find_smallest(stacks->stack_a), stacks);
}

void	push_swap(t_stacks *stacks)
{
	if (stacks->stack_a->length == 1 || list_is_sorted(stacks->stack_a))
		return ;
	else if (stacks->stack_a->length == 2)
		return (_sort_2(stacks));
	else if (stacks->stack_a->length == 3)
		return (_sort_3(stacks));
	else if (stacks->stack_a->length <= 10)
		return (simple_sort(stacks->stack_a->length, stacks));
	else if (stacks->stack_a->length <= 200)
		return (optimal_sort(2, stacks));
	else
		return (optimal_sort(4, stacks));
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc == 1)
		return (EXIT_SUCCESS);
	stacks.stack_a = parse(argc, argv);
	stacks.stack_b = list_init(0, NULL);
	if (!stacks.stack_b)
		handle_error(stacks.stack_a, NULL, NULL, 1);
	push_swap(&stacks);
	list_free(stacks.stack_a);
	list_free(stacks.stack_b);
}
