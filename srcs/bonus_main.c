/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:25:58 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 17:56:13 by emuminov         ###   ########.fr       */
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

int	main(void)
{
	char	buf[5];
	int		sz;

	// parse the input

	// receive operations
	sz = 1;
	buf[4] = '\0';
	while (sz > 0)
	{
		sz = read(1, buf, 4);
		buf[sz] = '\0';
		if (is_operation(buf))
			// do operation on the stack
			printf("It's an operation!\n");
		else if (sz != 0)
		{
			printf("It's NOT an operation!\n");
			exit(1);
		}
	}

	// check if ordered
	printf("Heh!\n");
}
