/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:25:58 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/22 10:17:11 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdio.h>
#include <string.h>

int	is_operation(char *str)
{
	return (strcmp(str, "sa\n") == 0
		|| strcmp(str, "sb\n") == 0
		|| strcmp(str, "ss\n") == 0
		|| strcmp(str, "ra\n") == 0
		|| strcmp(str, "rb\n") == 0
		|| strcmp(str, "rr\n") == 0
		|| strcmp(str, "rra\n") == 0
		|| strcmp(str, "rrb\n") == 0
		|| strcmp(str, "rrr\n") == 0
		|| strcmp(str, "pb\n") == 0
		|| strcmp(str, "pa\n") == 0
	);
}

void	do_operation(char *op, t_stacks *stacks)
{
	if (strcmp(op, "sa\n") == 0)
		sa(1, stacks);
	else if (strcmp(op, "sb\n") == 0)
		sb(1, stacks);
	else if (strcmp(op, "ss\n") == 0)
		ss(1, stacks);
	else if (strcmp(op, "ra\n") == 0)
		ra(1, stacks);
	else if (strcmp(op, "rb\n") == 0)
		rb(1, stacks);
	else if (strcmp(op, "rr\n") == 0)
		rr(1, stacks);
	else if (strcmp(op, "rra\n") == 0)
		rra(1, stacks);
	else if (strcmp(op, "rrb\n") == 0)
		rrb(1, stacks);
	else if (strcmp(op, "rrr\n") == 0)
		rrr(1, stacks);
	else if (strcmp(op, "pa\n") == 0)
		pa(1, stacks);
	else if (strcmp(op, "pb\n") == 0)
		pb(1, stacks);
}

void	receive_operations(t_stacks *stacks)
{
	char		buf[5];
	int			sz;

	sz = 1;
	buf[4] = '\0';
	while (sz > 0)
	{
		sz = read(0, buf, 4);
		buf[sz] = '\0';
		if (is_operation(buf))
			do_operation(buf, stacks);
		else if (sz > 0)
			handle_error(stacks->stack_a, stacks->stack_b, NULL, 0);
	}
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	stacks.stack_a = parse(argc, argv);
	stacks.stack_b = list_create(0, NULL);
	if (!stacks.stack_b)
		handle_error(stacks.stack_a, NULL, NULL, 1);
	receive_operations(&stacks);
	if (list_is_sorted(stacks.stack_a))
		printf("KO\n");
	else
		printf("KO\n");
}
