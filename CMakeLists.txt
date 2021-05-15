cmake_minimum_required(VERSION 3.19)
project(cub C)

set(CMAKE_C_STANDARD 99)

add_executable(cub main.c parser/wall_check.c mlx_drawer/open_window.c parser/check_arguments.c parser/errors.c parser/flag_parser_utils.c parser/flag_parser.c parser/map_to_mass_utils.c parser/map_to_mass.c parser/parser.c mlx_drawer/bmp.c mlx_drawer/draw_sprite.c mlx_drawer/draw_walls.c mlx_drawer/exit.c mlx_drawer/mlx_utils.c mlx_drawer/move_player_utils.c mlx_drawer/move_player.c mlx_drawer/raycast.c mlx_drawer/sprite_utils.c mlx_drawer/window_creation.c)
TARGET_LINK_LIBRARIES(cub /Users/kgale/Desktop/my_cub/mlx_mac/libmlx.a)
TARGET_LINK_LIBRARIES(cub /Users/kgale/Desktop/my_cub/libft/libft.a)
TARGET_LINK_LIBRARIES(cub "-framework OpenGL" "-framework Appkit")