/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:00:45 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/19 14:12:34 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

int choose_bloc()
{
	int nbr;
	
	srand(time(NULL));
	nbr = rand();
	nbr = nbr % 10;
	if (nbr == 0)
		return (4);
	else
		return (2);	
}

int choose_place()
{
	int nbr;
	
	srand(time(NULL));
	nbr = rand();
	nbr = nbr % 4;
	return (nbr);
}

void init_tab(int **tab)
{
	int x;
	int y;
	int i;
	
	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			tab[x][y] = 0;
			y++;
		}
		x++;
	}
	i = 0;
	while (i < 2)
	{
		tab[choose_place()][choose_place()] = choose_bloc();
		i++;
	}
}

void	join_up(int **tab)
{
	int x1;
	int x2;
	int y;
	
	y = 0;
	while (y < 4)
	{
		x1 = 0;
		x2 = 1;
		while (x2 < 4 || x1 < 4)
		{
			while (tab[x1][y] == 0 && x1 < 4)
				x1++;
			x2 = x1 + 1;
			if (x1 < 4 || x2 < 4)
				break;
			while (tab[x2][y] == 0 && x2 < 4)
				x2++;
			if (x1 < 4 || x2 < 4)
				break;
			if (tab[x2][y] == tab[x1][y] && tab[x2][y] != 0)
			{
				tab[x1][y] = 2 * tab[x1][y];
				tab[x2][y] = 0;
			}
			x1 = x2;
		}
		y++;
	}	
}

void	deplace_up(int **tab)
{
	int stock[4];
	int y;
	int x;
	int i;

	y = 0;
	while (y < 4)
	{
		ft_bzero(stock, 4 * sizeof(int));
		x = 0;
		i = 0;
		while (x < 4)
		{
			if (tab[x][y] != 0)
			{
				stock[i] = tab[x][y];
				i++;
			}
			x++;
		}
		x = 0;
		i = 0;
		while (x < 4)
		{
			tab[x][y] = stock[i];
			i++;
			x++;
		}
		y++;
	}
	
}

void	do_action(int **tab, int action)
{
	if (action == KEY_UP)
		join_up(tab);
	else if (action == KEY_DOWN)
		join_down(tab);
	else if (action == KEY_LEFT)
		join_left(tab);
	else if (action == KEY_RIGHT)
		join_right(tab);
	if (action == KEY_UP)
		deplace_up(tab);
	else if (action == KEY_DOWN)
		deplace_down(tab);
	else if (action == KEY_LEFT)
		deplace_left(tab);
	else if (action == KEY_RIGHT)
		deplace_right(tab);
} 