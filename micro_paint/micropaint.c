/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micropaint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:05:23 by dcastagn          #+#    #+#             */
/*   Updated: 2023/05/03 15:14:08 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_bg
{
	int		width;
	int		height;
	char	sign;
}	t_bg;

typedef struct s_shape
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	sign;
}	t_shape;

int	main(int argc, char **argv)
{
	FILE	*file;
	t_bg	bg;
	t_shape	shape;
	int		x;
	int		y;
	char	mat[300][300];
	int		check;

	if (argc != 2)
		return (write(1, "Error: argument\n", 16) - 15);
	file = fopen(argv[1], "r");
	if (!file)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
	if (fscanf(file, "%d %d %c\n", &bg.width, &bg.height, &bg.sign) != 3)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
	if (!(bg.width > 0 && bg.width <= 300 && bg.height > 0 && bg.height <= 300))
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
	y = 0;
	while (y < bg.height)
	{
		x = 0;
		while (x < bg.width)
		{
			mat[y][x] = bg.sign;
			x++;
		}
		y++;
	}
	check = -1;
	while ((check = fscanf(file, "%c %f %f %f %f %c\n", &shape.type, &shape.x,
		&shape.y, &shape.width, &shape.height, &shape.sign)) == 6)
	{
		if (shape.width <= 0 || shape.height <= 0 || (shape.type != 'r' && shape.type != 'R'))
			return (write(1, "Error: Operation file corrupted\n", 32) - 31);
		y = 0;
		while (y < bg.height)
		{
			x = 0;
			while (x < bg.width)
			{
				if (shape.x <= x && x <= shape.width + shape.x && shape.y <= y && y <= shape.height + shape.y)
				{
					if (y - shape.y < 1 || x - shape.x < 1 || (shape.x + shape.width) - x < 1 || (shape.height + shape.y) - y < 1)
						mat[y][x] = shape.sign;
					else if (shape.type == 'R')
						mat[y][x] = shape.sign;
				}
				x++;
			}
			y++;
		}
	}
	if (check != 6 && check != -1)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
		y = 0;
		while (y < bg.height)
		{
			x = 0;
			while (x < bg.width)
			{
				write(1, &mat[y][x], 1);
				x++;
			}
			y++;
			write(1, "\n", 1);
		}
		return (0);
}
