/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:57:53 by avella            #+#    #+#             */
/*   Updated: 2016/05/27 16:35:30 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double		inter_sphere(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
	a = mult(&(ray_dir), &(ray_dir));
	b = mult(&eo, &(ray_dir));
	c = mult(&eo, &eo) - obj->size * obj->size;
	e->det = b * b - a * c;
	if (e->det < 0.0001)
		return (-1);
	return (ret_val(a, b, e->det));
}

double		inter_plan(t_obj *obj, t_env *e)
{
	double value;

	value = -((mult(&obj->rot, &(e->ray_origin)) - mult(&obj->rot, &obj->pos)) \
			/ mult(&obj->rot, &(e->ray_dir)));
	if (value < 0.0001)
		return (-1);
	return (value);
}

double		inter_cyl(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		ray_dir;
	double t0;
	double t1;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
	a = ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z;
        b =  (2 * (ray_dir.x * eo.x)) + (2 * (ray_dir.z * eo.z));
        c = eo.x * eo.x + eo.z * eo.z - obj->size * obj->size;
        e->det = b *b - 4*a*c;
        if (e->det < 0.0001)
	  return (-1);
	t0 = (-b + sqrt(e->det)) / (2 * a);
	t1 = (-b - sqrt(e->det)) / (2 * a);
	if(t0 > t1)
	  {
	    float tmp = t0;
	    t0 = t1;
	    t1 = tmp;
	  }
	float y0 = eo.y + t0 * ray_dir.y;
	float y1 = eo.y + t1 * ray_dir.y;
	if (y0<-2)
	  {
	    if (y1<-2)
	      return (-1);
	    else
	      {
		// hit the cap
		float th = t0 + (t1-t0) * (y0+1) / (y0-y1);
		if (th<=0) return (-1);
		return ((-b - sqrt(e->det)) / (2 * a));
	      }
	  }
	else if (y0>=-2 && y0<=2)
	  {
	    // hit the cylinder bit
	    if (t0<=0) return (-2);
	    return ((-b - sqrt(e->det)) / (2 * a));
	  }
	else if (y0>2)
	  {
	    if (y1>2)
	      return (-1);
	    else
	      {
		// hit the cap
		float th = t0 + (t1-t0) * (y0-1) / (y0-y1);
		if (th<=0) return (-2);

		return ((-b - sqrt(e->det)) / (2 * a));
	      }
	  }
	return (-1);
}

double		inter_cone(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
	a = ray_dir.x * ray_dir.x - ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	b = ray_dir.x * eo.x - ray_dir.y * eo.y + ray_dir.z * eo.z;
	c = eo.x * eo.x + eo.z * eo.z - eo.y * eo.y;
	e->det = b * b - a * c;
	if (e->det < 0.0001)
		return (-1);
	return (ret_val(a, b, e->det));
}

t_obj		*all_inter(t_env *e)
{
	t_obj		*my_obj;
	t_obj		*obj;
	double		value;

	obj = NULL;
	my_obj = e->obj;
	value = e->value;
	while (my_obj)
	{
		if (my_obj->type == 0)
			value = inter_plan(my_obj, e);
		else if (my_obj->type == 1)
			value = inter_sphere(my_obj, e);
		else if (my_obj->type == 3)
			value = inter_cyl(my_obj, e);
		else if (my_obj->type == 2)
			value = inter_cone(my_obj, e);
		if (value > 0.0001 && value < e->value)
		{
			obj = my_obj;
			e->value = value;
		}
		my_obj = my_obj->next;
	}
	return (obj);
}
