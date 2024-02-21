/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:15:33 by emuminov          #+#    #+#             */
/*   Updated: 2024/02/21 14:06:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc == 1)
		return (EXIT_SUCCESS);
	stacks.stack_a = parse(argc, argv);
	stacks.stack_b = list_create(0, NULL);
	if (!stacks.stack_b)
		handle_error(stacks.stack_a, NULL, NULL, 1);
	push_swap(&stacks);
	list_free(stacks.stack_a);
	list_free(stacks.stack_b);
}
