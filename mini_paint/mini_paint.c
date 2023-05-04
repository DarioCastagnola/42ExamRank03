#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	float	radius;
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
	float	dist;

	if (argc != 2)
		return (write(1, "Error: argument\n", 16) - 15);
	file = fopen(argv[1], "r");
	if (!file)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
	if (fscanf(file, "%d %d %c\n", &bg.width, &bg.height, &bg.sign) != 3)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
	if (bg.width < 1 && bg.width > 300 && bg.height < 1 && bg.height > 300)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
	y = -1;
	while (++y < bg.height)
	{
		x = -1;
		while (++x < bg.width)
			mat[y][x] = bg.sign;
	}
	check = -1;
	while ((check = fscanf(file, "%c %f %f %f %c\n", &shape.type, &shape.x,
		&shape.y, &shape.radius, &shape.sign)) == 5)
	{
		if (shape.radius <= 0 || (shape.type != 'c' && shape.type != 'C'))
			return (write(1, "Error: Operation file corrupted\n", 32) - 31);
		y = -1;
		while (++y < bg.height)
		{
			x = -1;
			while (++x < bg.width)
			{
				dist = sqrtf((x - shape.x) * (x - shape.x) + (y - shape.y) * (y - shape.y));
				if ((shape.radius - dist) < 1 && (shape.radius - dist) >= 0 && shape.type == 'c')
					mat[y][x] = shape.sign;
				else if (shape.type == 'C' && dist <= shape.radius)
					mat[y][x] = shape.sign;
			}
		}
	}
	if (check != 5 && check != -1)
		return (write(1, "Error: Operation file corrupted\n", 32) - 31);
		y = -1;
		while (++y < bg.height)
		{
			x = -1;
			while (++x < bg.width)
				write(1, &mat[y][x], 1);
			write(1, "\n", 1);
		}
		return (0);
}
