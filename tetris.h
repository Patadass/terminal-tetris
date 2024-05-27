#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

#include "draw.h"

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#define CONTAINER_WIDTH 10
#define CONTAINER_HEIGHT 20


class Tetris{
private:
    static int container_width, container_height;
    static int starting_x,staring_y;
    static WORD container_color;
    static short map[CONTAINER_HEIGHT][CONTAINER_WIDTH];
public:
    static void queue_start_sequence();
    static void generate_map();
    static void draw_container();
    static void draw_on_container(int i,int j);
    static void draw_np_container();
    static void draw_on_np_container(int piece);
    static void draw_from_map();
    static void map_put(int i,int j,int n = 1);
    static short map_pull(int i,int j);
    static void map_zero(int i,int j);
    static bool is_out_of_bounds(int i,int j);
    //o
    static void map_put_o_block(int starting_i,int starting_j,int state = 0);
    static void map_zero_o_block(int starting_i,int starting_j,int state = 0);
    static int map_check_collision_o_block(int starting_i,int starting_j,int state = 0);
    //

    //i
    static void map_put_i_block(int starting_i,int starting_j,int state = 0);
    static void map_zero_i_block(int starting_i,int starting_j,int state = 0);
    static int map_check_collision_i_block(int starting_i,int starting_j,int state = 0);
    //

    //t
    static void map_put_t_block(int starting_i,int starting_j,int state = 0);//state is the rotation of the block
    static void map_zero_t_block(int starting_i,int starting_j,int state = 0);//state is the rotation of the block
    static int map_check_collision_t_block(int starting_i,int starting_j,int state = 0);
    //

    //j
    static void map_put_j_block(int starting_i,int starting_j,int state = 0);
    static void map_zero_j_block(int starting_i,int starting_j,int state = 0);
    static int map_check_collision_j_block(int starting_i,int starting_j,int state = 0);
    //

    //l
    static void map_put_l_block(int starting_i,int starting_j,int state = 0);
    static void map_zero_l_block(int starting_i,int starting_j,int state = 0);
    static int map_check_collision_l_block(int starting_i,int starting_j,int state = 0);
    //

    //s
    static void map_put_s_block(int starting_i,int starting_j,int state = 0);
    static void map_zero_s_block(int starting_i,int starting_j,int state = 0);
    static int map_check_collision_s_block(int starting_i,int starting_j,int state = 0);
    //

    //z
    static void map_put_z_block(int starting_i,int starting_j,int state = 0);
    static void map_zero_z_block(int starting_i,int starting_j,int state = 0);
    static int map_check_collision_z_block(int starting_i,int starting_j,int state = 0);
    //

    static void line_manager();

    static int get_height();
    static int get_width();
    static int get_starting_x();
    static int get_starting_y();
};


#endif //TETRIS_TETRIS_H
