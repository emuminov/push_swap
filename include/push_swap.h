/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:38:07 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 08:22:35 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "../libft/libft.h"

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

char	**arr_duplicate(int l, char **arr);
int		arr_cl(int i, int n, int l, int *arr);
int		arr_cu(int i, int n, int l, int *arr);
int		*list_copy_as_sorted_arr(t_list *lst);
int		list_find_position(t_node *node, t_list *lst);
int		list_is_sorted(t_list *lst);
t_list	*list_append_value(int value, t_list *lst);
t_list	*list_create(int l, char **values);
t_list	*parse(int argc, char **argv);
t_move	move_find_best(t_stacks *stacks);
t_node	*list_find_biggest(t_list *lst);
t_node	*list_find_smallest(t_list *lst);
t_node	*list_find_target(t_node *node, t_list *lst);
t_node	*list_find_value_in_range(int lower, int upper, t_list *lst);
t_node	*list_unlink_head(t_list *lst);
void	arr_bubble_sort(int l, int *arr);
void	arr_free_split(char **strs);
void	divide_in_chunks(int n, t_stacks *stacks);
void	handle_error(t_list *stack_a, t_list *stack_b, char **arr, int silent);
void	list_free(t_list *lst);
void	list_prepend_node(t_node *node, t_list *lst);
void	move_apply(t_move *move, t_stacks *stacks);
void	pa(int silent, t_stacks *stacks);
void	pb(int silent, t_stacks *stacks);
void	push_swap(t_stacks *stacks);
void	ra(int silent, t_stacks *stacks);
void	rb(int silent, t_stacks *stacks);
void	rra(int silent, t_stacks *stacks);
void	rrb(int silent, t_stacks *stacks);
void	rrr(int silent, t_stacks *stacks);
void	rr(int silent, t_stacks *stacks);
void	sa(int silent, t_stacks *stacks);
void	sb(int silent, t_stacks *stacks);
void	ss(int silent, t_stacks *stacks);
void	stack_a_rotate_to_top(t_node *node, t_stacks *stacks);
void	stack_b_rotate_to_top(t_node *node, t_stacks *stacks);

#endif
