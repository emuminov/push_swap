/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:25:58 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/29 12:58:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	is_operation(char *str)
{
	return (ft_strcmp(str, "sa\n") == 0
		|| ft_strcmp(str, "sb\n") == 0
		|| ft_strcmp(str, "ss\n") == 0
		|| ft_strcmp(str, "ra\n") == 0
		|| ft_strcmp(str, "rb\n") == 0
		|| ft_strcmp(str, "rr\n") == 0
		|| ft_strcmp(str, "rra\n") == 0
		|| ft_strcmp(str, "rrb\n") == 0
		|| ft_strcmp(str, "rrr\n") == 0
		|| ft_strcmp(str, "pb\n") == 0
		|| ft_strcmp(str, "pa\n") == 0
	);
}

void	do_operation(char *op, t_stacks *stacks)
{
	if (ft_strcmp(op, "sa\n") == 0)
		sa(1, stacks);
	else if (ft_strcmp(op, "sb\n") == 0)
		sb(1, stacks);
	else if (ft_strcmp(op, "ss\n") == 0)
		ss(1, stacks);
	else if (ft_strcmp(op, "rra\n") == 0)
		rra(1, stacks);
	else if (ft_strcmp(op, "rrb\n") == 0)
		rrb(1, stacks);
	else if (ft_strcmp(op, "rrr\n") == 0)
		rrr(1, stacks);
	else if (ft_strcmp(op, "ra\n") == 0)
		ra(1, stacks);
	else if (ft_strcmp(op, "rb\n") == 0)
		rb(1, stacks);
	else if (ft_strcmp(op, "rr\n") == 0)
		rr(1, stacks);
	else if (ft_strcmp(op, "pa\n") == 0)
		pa(1, stacks);
	else if (ft_strcmp(op, "pb\n") == 0)
		pb(1, stacks);
}

void	receive_operations(t_stacks *stacks)
{
	char	*op;

	op = get_next_line(STDIN_FILENO);
	while (op)
	{
		if (is_operation(op))
			do_operation(op, stacks);
		else
		{
			free(op);
			get_next_line(-1);
			handle_error(stacks->stack_a, stacks->stack_b, NULL, 0);
		}
		free(op);
		op = get_next_line(STDIN_FILENO);
	}
	free(op);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			l;

	if (argc == 1)
		return (EXIT_SUCCESS);
	stacks.stack_a = parse(argc, argv);
	stacks.stack_b = list_create(0, NULL);
	l = stacks.stack_a->length;
	if (!stacks.stack_b)
		handle_error(stacks.stack_a, NULL, NULL, 1);
	receive_operations(&stacks);
	if (list_is_sorted(stacks.stack_a) && l == stacks.stack_a->length)
		ft_putstr_fd("OK\n", STDOUT_FILENO);
	else
		ft_putstr_fd("KO\n", STDOUT_FILENO);
	list_free(stacks.stack_a);
	list_free(stacks.stack_b);
}
