#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_mac/mlx.h"
# include "../includes/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define CLOSE 17
# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define SHIFT 56
# define SIZE_CHUNK 4096
# define STEP 1000
# define FOV 60
# define TURN_LEFT 123
# define TURN_RIGHT 124
# define FOV2 30
# define PI 3.14
# define RADS 0.01745
# define SIZE_PLAYER 1

typedef struct s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct s_map
{
	char			*line;
	int				len;
	void			*next;
}					t_map;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_key
{
	int			keycode;
	int			run;
}				t_key;

typedef struct s_reycast
{
	int			width;
	double		dist_screen;
	double		ugl;
	int			step;
	double		hypotenuse;
	double		dist;
	double		dist_x;
	double		dist_y;
	double		l;
	double		*rey_len;
	int			check_sprite;
	int			count_sprite;
}				t_reycast;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
	int				size;
	int				start;
	int				y_start;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_maping_texture
{
	int				x_mass;
	int				y_mass;
	int				y_tmp;
	double			x;
	double			y;
}					t_map_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		angl;
}				t_player;

typedef struct s_length
{
	int			x;
	int			y;
	int			max_x;
	int			max_y;
}				t_length;

typedef struct s_scene
{
	int			x_rea;
	int			y_rea;
	char		*NO_texture;
	char		*SO_texture;
	char		*WE_texture;
	char		*EA_texture;
	char		*S_texture;
	int			floor;
	int			ceiling;
	char		**mass;
	int			mass_x;
	int			mass_y;
	int			save_option;
	t_map		*map;
	t_player	pl;
}				t_scene;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	double			color_x;
	double			color_y;
}					t_texture;

typedef struct s_all
{
	t_scene				*scene;
	t_vars				vars;
	t_data				data;
	t_key				key;
	t_length			map_length;
	t_length			pix_for_map;
	t_reycast			vis;
	t_texture			NO_texture;
	t_texture			SO_texture;
	t_texture			WE_texture;
	t_texture			EA_texture;
	t_texture			S_texture;
	t_sprite			*sprite;
}						t_all;

void			ft_check_argv(int argc, char **argv, t_scene **scene, int *fd);
int				create_trgb(int t, int r, int g, int b);
void			ft_parser(int fd, t_scene *scene);
void			line_parser(char *line, t_scene *scene, int fd);
void			map_to_mass(t_scene *scene);
void			error_with_map(t_scene *scene);
void			map_error(int fd, t_scene *scene, char *line);
void			free_scene(t_scene *scene);
void			free_split(char **split);
void			ft_exit(int fd, char **split, char *line);
void			handle_map(char *line, t_scene *scene, int fd);
void			free_map(t_scene *scene);
int				ft_check_path_to_texture(char *path, char **split, char *line);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	get_color_image(t_texture *texture, int x, int y);
int				ft_close_exit(t_all *all);
void			free_sprite(t_all *all);
void			print_error(t_all *all);
void			ft_reycast(t_all *all);
void			move(t_all *all);
void			draw(t_all *all, double x, double y, double l);
void			draw_sprite(t_all *all);
int				all_null(t_all *all);
void			create_bmp(t_all *all);
void			check_sprite(t_all *all, double step);
unsigned int	get_color(t_data *data, int x, int y);
void			init_scene(t_scene **scene);
void			move_utils(t_all *all, int i);
void			ft_check_walls(t_scene *scene);
int				ft_window(t_scene *scene);
void			save_sprite_list(t_all *all);
void			check_scene(t_scene *scene);

#endif
