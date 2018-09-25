#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

#define w 1280
#define h 720


t_data *make_struct()
{
    t_data *e;

    e = (t_data *)malloc(sizeof(t_data));
    e->pos_x = 22.0;
    e->pos_y = 12.0;
    e->dir_x = -1.0;
    e->dir_y = 0.0;
    e->plane_x = 0.0;
    e->plane_y = 0.66;
    e->move_speed = 1.0;
	e->rot_speed = 1.0;
    return (e);
}

int worldMap[(int)map_width][(int)map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_data	*data_init(t_data *data)
{
	data->ray_pos_x = data->pos_x;
	data->ray_pos_y = data->pos_y;
	data->camera_x = 2 * data->x / (double)(w) - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = (int)(data->ray_pos_x);
	data->map_y = (int)(data->ray_pos_y);
	data->delta_dist_x = sqrt(1 + (data->ray_dir_y * data->ray_dir_y) / (data->ray_dir_x * data->ray_dir_x));
	data->delta_dist_y = sqrt(1 + (data->ray_dir_x * data->ray_dir_x) / (data->ray_dir_y * data->ray_dir_y));
	data->hit = 0;
	return (data);
}

//initialize player start
t_data	*player_init(t_data *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
			data->side_dist_x = (data->ray_pos_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->ray_pos_x) * data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->ray_pos_y - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->ray_pos_y) * data->delta_dist_y;
	}
	return (data);		
}

t_data	*dda_engine(t_data *data)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (worldMap[data->map_x][data->map_y] > 0) data->hit = 1;
	}
	return (data);			
}

t_data	*camera_dist(t_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = fabs((data->map_x - data->ray_pos_x + (1 - data->step_x) / 2) / data->ray_dir_x);
	else
		data->perp_wall_dist = fabs((data->map_y - data->ray_pos_y + (1 - data->step_y) / 2) / data->ray_dir_y);
	return (data);
}

t_data	*fill_line_calc(t_data *data)
{
	data->line_height = fabs((h / data->perp_wall_dist));
	data->draw_start = -(data->line_height) / 2 + h / 2;
	if (data->draw_start < 0) data->draw_start = 0;
		data->draw_end = data->line_height / 2 + h / 2;
	if (data->draw_end >= h) data->draw_end = h - 1;
	return (data);
}

t_data	*draw_verline(t_data *data)
{
	while (data->draw_start < data->draw_end)
	{
        mlx_pixel_put(data->mlx, data->window, data->x, data->draw_start, 0x00123456);
        data->draw_start++;
	}
	return (data);
}

void    make_screen(t_data *data)
{
    data->x = 0;

    while (data->x < 1280)
    {
		mlx_clear_window(data->mlx, data->window);
		data_init(data);
		player_init(data);
		dda_engine(data);
		camera_dist(data);
		fill_line_calc(data);
			//choose wall color
		draw_verline(data);
        data->x++;
    }
}

int	key_down(int key, t_data *data)
{
	if (key == k_esc)
	{
		exit(EXIT_SUCCESS);
	}
	if (key == k_up)
	{
		move_up(data);
	}
	if (key == k_down)
	{
		move_down(data);
	}
	if (key == k_left)
	{
		move_left(data);
	}
	if (key == k_right)
	{
		move_right(data);
	}
    return (0);
}

void move_up(t_data *data)
{
    write(1, "1", 1);
 	if(!(worldMap[(int)(data->pos_x + data->dir_x * data->move_speed)][(int)(data->pos_y)]))
	  data->pos_x += data->dir_x * data->move_speed;
	if(!(worldMap[(int)(data->pos_x)][(int)(data->pos_y + data->dir_y * data->move_speed)]))
	 data->pos_y += data->dir_y * data->move_speed;
	make_screen(data);
}

void	move_down(t_data *data)
{
	if(!(worldMap[(int)(data->pos_x - data->dir_x * data->move_speed)][(int)(data->pos_y)]))
		data->pos_x -= data->dir_x * data->move_speed;
	if(!(worldMap[(int)(data->pos_x)][(int)(data->pos_y - data->dir_y * data->move_speed)]))
		data->pos_y -= data->dir_y * data->move_speed;
	make_screen(data);
}

void move_right(t_data *data)
{
  //both camera direction and camera plane must be rotated
  data->old_dir_x = data->dir_x;
  data->dir_x = data->dir_x * cos(-(data->rot_speed) - data->dir_y * sin(-(data->rot_speed)));
  data->dir_y = data->old_dir_x * sin(-(data->rot_speed)) + data->dir_y * cos(-(data->rot_speed));
  data->old_plane_x = data->plane_x;
  data->plane_x = data->plane_x * cos(-(data->rot_speed)) - data->plane_y * sin(-(data->rot_speed));
  data->plane_y = data->old_plane_x * sin(-(data->rot_speed) + data->plane_y * cos(-(data->rot_speed)));
  make_screen(data);
}
		
		
//rotate to the left
void	move_left(t_data *data)
{
  //both camera direction and camera plane must be rotated
  data->old_dir_x = data->dir_x;
  data->dir_x = data->dir_x * cos(data->rot_speed) - data->dir_y * sin(data->rot_speed);
  data->dir_y = data->old_dir_x * sin(data->rot_speed) + data->dir_y * cos(data->rot_speed);
  data->old_plane_x = data->plane_x;
  data->plane_x = data->plane_x * cos(data->rot_speed) - data->plane_y * sin(data->rot_speed);
  data->plane_y = data->old_plane_x * sin(data->rot_speed) + data->plane_y * cos(data->rot_speed);
  make_screen(data);
}

int main()
{ 
    t_data *data;

    data = make_struct();
    data->mlx = mlx_init();
    data->window =  mlx_new_window(data->mlx, 1280, 720, "wolf3D");
    make_screen(data);
	mlx_key_hook(data->window, key_down, data);
    mlx_loop(data->mlx);
}