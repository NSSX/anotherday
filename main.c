/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:10:06 by avella            #+#    #+#             */
/*   Updated: 2016/05/27 17:38:27 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void	give_effect(t_env *e)
{
	e->effect.vec = give_vec(e->obj_tmp, e);
	e->effect.shadow = give_shadow(e);
	e->effect.light = my_light(e);
	e->effect.bri = light_effect(e);
	e->effect.light = mult_value(&(e->effect.light), e->effect.shadow);
	e->effect.bri = a_x_b(&(e->effect.bri), &(e->effect.light));
}

void	all_effect(t_env *e)
{
	give_effect(e);
	e->color = plus(&(e->color), &(e->effect.bri));
	limit_for_vec(&(e->color), 0, 1);
	e->color = a_x_b(&(e->color), &(e->effect.light));
}

void	move_cam(t_env *e, int keycode)
{
	double a;
	double b;
	double val1;
	double val2;

	a = cos(e->v);
	b = sin(e->v);
	val1 = a * 5;
	val2 = b * 5;
	if (keycode == 13)
	{
		e->eye_pos.z -= val1;
		e->eye_pos.x += val2;
	}
	if (keycode == 1)
	{
		e->eye_pos.z += val1;
		e->eye_pos.x -= val2;
	}
}

int		event_mlx(int keycode, t_env *e)
{
	static int etat;

	if (!etat)
		etat = 0;
	another_keycode(keycode, e);
	move_cam(e, keycode);
	if (keycode == 49)
	{
		if (etat == 3)
			etat = 0;
		else
			etat++;
		ft_putstr("Etat Numero : ");
		ft_putnbr(etat);
		print_obj(etat);
	}
	movable(keycode, e, etat);
	ray_tracer(e);
	return (1);
}

int		main(int ac, char **av)
{
	t_env e;

	give(&e);
	parsing(&e, ac, av[1]);
	init_eye(&e);
	light_number(&e);
	pov(&e);
	e.v = 0;
	e.v2 = 0;
	e.nl = 1 / e.nl;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.width, e.height, e.name);
	ray_tracer(&e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, event_mlx, &e);
	mlx_loop(e.mlx);
	return (0);
}
