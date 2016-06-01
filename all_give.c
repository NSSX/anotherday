/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_give.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:45:33 by avella            #+#    #+#             */
/*   Updated: 2016/05/26 16:55:36 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void	give(t_env *e)
{
	t_vec3d	give;

	e->obj = NULL;
	e->obj_tmp = NULL;
	e->nl = 0;
	e->name = "RayTracer V1";
	e->width = WIDTH;
	e->height = HEIGHT;
	give = (t_vec3d){0, 0, 0};
	e->eye_pos = give;
	give = (t_vec3d){0, 0, 0};
	e->eye_dir = give;
}

void	light_number(t_env *e)
{
	t_obj *tmp;

	tmp = e->obj;
	while (tmp)
	{
		if (tmp->type == 8)
			e->nl += 1.0;
		tmp = tmp->next;
	}
}

void	init_eye(t_env *e)
{
	e->eye_pos.x = 0;
	e->eye_pos.y = 1;
	e->eye_pos.z = 0;
	e->eye_dir.x = 0;
	e->eye_dir.y = 1;
	e->eye_dir.z = 0;
}

void	pov(t_env *e)
{
	t_obj *pov;

	pov = e->obj;
	while (pov)
	{
		if (pov->type == 9)
		{
			e->eye_pos.x = pov->pos.x;
			e->eye_pos.y = pov->pos.y;
			e->eye_pos.z = pov->pos.z;
			e->eye_dir.x = pov->rot.x;
			e->eye_dir.y = pov->rot.y;
			e->eye_dir.z = pov->rot.z;
		}
		pov = pov->next;
	}
}
