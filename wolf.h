#ifndef     WOLF_H
#define     WOLF_H
#include    "./libft/libft.h"
#include    <mlx.h>
#include    <math.h>


#define map_width 24
#define map_height 24
#define k_esc 53
#define k_up 126
#define k_down 125
#define k_right 124
#define k_left 123

typedef struct  s_data
{
    void    *mlx;
    void    *window;
    double  pos_x;
    double  pos_y;
    double  plane_x;
    double  plane_y;
    double  dir_x;
    double  dir_y;
    int     x;
    double  camera_x;
    double  ray_pos_x;
    double  ray_pos_y;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    int     line_height;
    int     draw_start;
    int     draw_end;
    double  frame_time;
    double  move_speed;
    double  rot_speed;
    double  old_dir_x;
    double  old_plane_x;
    int     arc;
}               t_data;

int     ft_abs(int x);
void    draw_line(t_data *data);
int    hook_keydown(int key, t_data *data);
void    move_up(t_data *data);
void    move_down(t_data *data);
void    move_left(t_data *data);
void    move_right(t_data *data);

#endif