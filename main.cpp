#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

#include "draw.h"

using namespace std;

const int CONTAINER_WIDTH = 10;
const int CONTAINER_HEIGHT = 20;

class Container{
private:
    static int container_width;
    static int container_height;
    static int starting_x,staring_y;
    static WORD container_color;
    static short map[CONTAINER_HEIGHT][CONTAINER_WIDTH];
public:
    static void generate_map() {
        for(int i = 0;i < CONTAINER_HEIGHT;i++){
            for(int j = 0;j < CONTAINER_WIDTH;j++){
                map_zero(i,j);
            }
        }
    }
    static void draw_container() {
        Draw::set_color(container_color);
        Draw::draw_rect(starting_x,staring_y,container_width,container_height);
        Draw::reset_color();
    }

    static void map_put(int i,int j,int n = 1) {
        Container::map[i][j] = short(n);
    }
    static short map_pull(int i,int j) {
        return Container::map[i][j];
    }
    static void map_zero(int i,int j) {
        Container::map[i][j] = 0;
    }
    static bool is_out_of_bounds(int i,int j){
        if(i >= CONTAINER_HEIGHT || i < 0){
            return true;
        }
        if(j >= CONTAINER_WIDTH || j < 0){
            return true;
        }
        return false;
    }

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

    static int get_height(){return Container::container_height;}
    static int get_width(){return Container::container_width;}
    static int get_starting_x(){return Container::starting_x;}
    static int get_starting_y(){return Container::staring_y;}
};
short Container::map[CONTAINER_HEIGHT][CONTAINER_WIDTH];
int Container::container_height = CONTAINER_HEIGHT + 2, Container::container_width = CONTAINER_WIDTH + 2;
int Container::starting_x = 0,Container::staring_y = 0;
WORD Container::container_color = BACKGROUND_WHITE;

//   put
// 1 = O block
// 2 = I block
// 3 = T block
// 4 = J block
// 5 = L block
// 6 = S block
// 7 = Z block

void Container::map_put_o_block(int starting_i,int starting_j,int state) {
    int i = starting_i,j = starting_j;
    map_put(i,j,1);
    map_put(i,j+1,1);
    map_put(i+1,j),1;
    map_put(i+1,j+1,1);
}
void Container::map_zero_o_block(int starting_i,int starting_j,int state) {
    int i = starting_i,j = starting_j;
    map_zero(i,j);
    map_zero(i,j+1);
    map_zero(i+1,j);
    map_zero(i+1,j+1);
}
int Container::map_check_collision_o_block(int starting_i, int starting_j, int state) {
    //0 means block cant go down
    //1 means block cant go left
    //2 means block cant go right
    //4 means block can go anywhere
    //5 means block has hit another block below
    int i = starting_i,j = starting_j;
    int code = 0;
    if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
    if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+2) >= 1|| is_out_of_bounds(i,j+2)){code+=2;}
    if(map_pull(i+2,j) >= 1 || map_pull(i+2,j+1) >= 1){return 0;}
    if(is_out_of_bounds(i+2,0)){return 0;}
    if(code == 0){code = 4;}
    return code;
}

void Container::map_put_i_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_put(i,j,2); map_put(i,j+1,2); map_put(i,j+2,2); map_put(i,j+3,2);}
    if(state == 1 || state == 3){map_put(i,j,2); map_put(i+1,j,2); map_put(i+2,j,2); map_put(i+3,j,2);}
}
void Container::map_zero_i_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i,j+2); map_zero(i,j+3);}
    if(state == 1 || state == 3){map_zero(i,j); map_zero(i+1,j); map_zero(i+2,j); map_zero(i+3,j);}
}
int Container::map_check_collision_i_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    int code = 0;
    if(state == 0 || state == 2){
        if(map_pull(i,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+4) >= 1 || is_out_of_bounds(i,j+4)){code+=2;}
        if(map_pull(i+1,j) >= 1 || map_pull(i+1,j+1) >= 1 || map_pull(i+1,j+2) >= 1 || map_pull(i+1,j+3) >= 1 ||
                is_out_of_bounds(i+1,j)){return 0;}
        if(is_out_of_bounds(i+1,j)){return 0;}
    }
    if(state == 1 || state == 3){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || map_pull(i+2,j-1) >= 1 || map_pull(i+3,j-1) >= 1 ||
                is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+1) >= 1 || map_pull(i+1,j+1) >= 1 || map_pull(i+2,j+1) >= 1 || map_pull(i+3,j+1) >= 1 ||
           is_out_of_bounds(i,j+1)){code+=2;}
        if(map_pull(i+4,j) >= 1){return 0;}
        if(is_out_of_bounds(i+4,j) == 1){return 0;}
    }
    if(code == 0){code = 4;}
    return code;
}

void Container::map_put_t_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_put(i,j+1,3); map_put(i+1,j,3); map_put(i+1,j+1,3); map_put(i+1,j+2,3);}
    if(state == 1){map_put(i,j+1,3); map_put(i+1,j+1,3); map_put(i+1,j+2,3); map_put(i+2,j+1,3);}
    if(state == 2){map_put(i+1,j,3); map_put(i+1,j+1,3); map_put(i+1,j+2,3); map_put(i+2,j+1,3);}
    if(state == 3){map_put(i,j+1,3); map_put(i+1,j,3); map_put(i+1,j+1,3); map_put(i+2,j+1,3);}
}

void Container::map_zero_t_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_zero(i,j+1); map_zero(i+1, j); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1){map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+1,j+2); map_zero(i+2,j+1);}
    if(state == 2){map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+1,j+2); map_zero(i+2,j+1);}
    if(state == 3){map_zero(i,j+1); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+2,j+1);}
}

int Container::map_check_collision_t_block(int starting_i, int starting_j, int state) {
    //0 means block cant go down
    //1 means block cant go left
    //2 means block cant go right
    //4 means block can go anywhere
    //5 means block has hit another block below
    int i = starting_i,j = starting_j;
    int code = 0;
    if(state == 0){
        if(map_pull(i,j) >= 1 || map_pull(i+1,j-1) >= 1 || is_out_of_bounds(i+1,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+3) >= 1 || is_out_of_bounds(i+1,j+3)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+2,j+1) >= 1 || map_pull(i+2,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+2,0)){return 0;}
    }
    if(state == 1){
        if(map_pull(i,j) >= 1 || map_pull(i+1,j) >= 1 || map_pull(i+2,j) >= 1 || is_out_of_bounds(0,j)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+3) >= 1 || map_pull(i+2,j+2) >= 1 || is_out_of_bounds(i+1,j+3)){code+=2;}
        if(map_pull(i+3,j+1) >= 1 || map_pull(i+2,j+2)){return 0;}
        if(is_out_of_bounds(i+3,0)){return 0;}
    }
    if(state == 2){
        if(map_pull(i+1,j-1) >= 1 || map_pull(i+2,j) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i+1,j+3) >= 1 || map_pull(i+2,j+2) >= 1|| is_out_of_bounds(i+1,j+3)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+3,j+1) >= 1 || map_pull(i+2,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+3,0)){return 0;}
    }
    if(state == 3){
        if(map_pull(i,j) >= 1 || map_pull(i+1,j-1) >= 1 || map_pull(i+2,j) >= 1 || is_out_of_bounds(i+1,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+2) >= 1 || map_pull(i+2,j+2) >= 1 || is_out_of_bounds(i,j+2)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+3,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,0)){return 0;}
    }
    if(code == 0){code = 4;}
    return code;
}

void Container::map_put_j_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_put(i,j,4); map_put(i+1,j,4); map_put(i+1,j+1,4); map_put(i+1,j+2,4);}
    if(state == 1){map_put(i,j,4); map_put(i,j+1,4); map_put(i+1,j,4); map_put(i+2,j,4);}
    if(state == 2){map_put(i,j); map_put(i,j+1); map_put(i,j+2); map_put(i+1,j+2);}
    if(state == 3){map_put(i,j+1,4); map_put(i+1,j+1,4); map_put(i+2,j); map_put(i+2,j+1,4);}
}
void Container::map_zero_j_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_zero(i,j); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1){map_zero(i,j); map_zero(i,j+1); map_zero(i+1,j); map_zero(i+2,j);}
    if(state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i,j+2); map_zero(i+1,j+2);}
    if(state == 3){map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+2,j); map_zero(i+2,j+1);}
}
int Container::map_check_collision_j_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    int code = 0;
    if(state == 0){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i+1,j+3) >= 1 || map_pull(i,j+1) >= 1 || is_out_of_bounds(i+1,j+3)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+2,j+1) >= 1 || map_pull(i+2,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+2,j)){return 0;}

    }
    if(state == 1){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || map_pull(i+2,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+1) >= 1 || map_pull(i+2,j+1) >= 1 || is_out_of_bounds(i,j+2)){code+=2;}
        if(map_pull(i+3,j) >= 1 || map_pull(i+1,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,j)){return 0;}
    }
    if(state == 2){
        if(map_pull(i,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+3) >= 1 || map_pull(i+1,j+3) >= 1 || is_out_of_bounds(i,j+3)){code+=2;}
        if(map_pull(i+1,j) >= 1 || map_pull(i+1,j+1) >= 1 || map_pull(i+2,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+2,j+2)){return 0;}
    }
    if(state == 3){
        if(map_pull(i,j) >= 1 || map_pull(i+1,j) >= 1 || map_pull(i+2,j-1) >= 1 || is_out_of_bounds(i+2,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+2) >= 1 || map_pull(i+2,j+2) >= 1 || is_out_of_bounds(i,j+2)){code+=2;}
        if(map_pull(i+3,j) >= 1 || map_pull(i+3,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,j)){return 0;}
    }
    if(code == 0){code = 4;}
    return code;
}

void Container::map_put_l_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_put(i,j+2,5); map_put(i+1,j,5); map_put(i+1,j+1,5); map_put(i+1,j+2,5);}
    if(state == 1){map_put(i,j,5); map_put(i+1,j,5); map_put(i+2,j,5); map_put(i+2,j+1,5);}
    if(state == 2){map_put(i,j,5); map_put(i,j+1,5); map_put(i,j+2,5); map_put(i+1,j,5);}
    if(state == 3){map_put(i,j,5); map_put(i,j+1,5); map_put(i+1,j+1,5); map_put(i+2,j+1,5);}
}
void Container::map_zero_l_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_zero(i,j+2); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1){map_zero(i,j); map_zero(i+1,j); map_zero(i+2,j); map_zero(i+2,j+1);}
    if(state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i,j+2); map_zero(i+1,j);}
    if(state == 3){map_zero(i,j); map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+2,j+1);}
}
int Container::map_check_collision_l_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    int code = 0;
    if(state == 0){
        if(map_pull(i+1,j-1) >= 1 || map_pull(i,j+1) >= 1 || is_out_of_bounds(i+1,j-1)){code++;}
        if(map_pull(i,j+3) >= 1 || map_pull(i+1,j+3) >= 1 || is_out_of_bounds(i,j+3)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+2,j+1) >= 1 || map_pull(i+2,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+2,j)){return 0;}
    }
    if(state == 1){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || map_pull(i+2,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+1) >= 1 || map_pull(i+1,j+1) >= 1 || map_pull(i+2,j+2) >= 1 || is_out_of_bounds(i+2,j+2)){code+=2;}
        if(map_pull(i+3,j) >= 1 || map_pull(i+3,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,j)){return 0;}
    }
    if(state == 2){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+3) >= 1 || map_pull(i+1,j+1) >= 1 || is_out_of_bounds(i,j+3)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+1,j+1) >= 1 || map_pull(i+1,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i,j+2)){return 0;}
    }
    if(state == 3){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j) >= 1 || map_pull(i+2,j) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+2) >= 1 || map_pull(i+2,j+2) >= 1 || is_out_of_bounds(i,j+2)){code+=2;}
        if(map_pull(i+1,j) >= 1 || map_pull(i+3,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,j+1)){return 0;}
    }
    if(code == 0){code = 4;}
    return code;
}

void Container::map_put_s_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_put(i,j+1,6); map_put(i,j+2,6); map_put(i+1,j,6); map_put(i+1,j+1,6);}
    if(state == 1 || state == 3){map_put(i,j,6); map_put(i+1,j,6); map_put(i+1,j+1,6); map_put(i+2,j+1,6);}
}
void Container::map_zero_s_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_zero(i,j+1); map_zero(i,j+2); map_zero(i+1,j); map_zero(i+1,j+1);}
    if(state == 1 || state == 3){map_zero(i,j); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+2,j+1);}
}
int Container::map_check_collision_s_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    int code = 0;
    if(state == 0 || state == 2){
        if(map_pull(i,j) >= 1 || map_pull(i+1,j-1) >= 1 || is_out_of_bounds(i+1,j-1)){code++;}
        if(map_pull(i,j+3) >= 1 || map_pull(i+1,j+2) >= 1 || is_out_of_bounds(i,j+3)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+2,j+1) >= 1 || map_pull(i+1,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+2,j)){return 0;}
    }
    if(state == 1 || state == 3){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j-1) >= 1 || map_pull(i+2,j) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+1) >= 1 || map_pull(i+1,j+2) >= 1 || map_pull(i+2,j+2) >= 1 || is_out_of_bounds(i+1,j+2)){code+=2;}
        if(map_pull(i+2,j) >= 1 || map_pull(i+3,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,j+1)){return 0;}
    }
    if(code == 0){code = 4;}
    return code;
}

void Container::map_put_z_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_put(i,j,7); map_put(i,j+1,7); map_put(i+1,j+1,7); map_put(i+1,j+2,7);}
    if(state == 1 || state == 3){map_put(i,j+1,7); map_put(i+1,j,7); map_put(i+1,j+1,7); map_put(i+2,j,7);}
}
void Container::map_zero_z_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1 || state == 3){map_zero(i,j+1); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+2,j);}
}
int Container::map_check_collision_z_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    int code = 0;
    if(state == 0 || state == 2){
        if(map_pull(i,j-1) >= 1 || map_pull(i+1,j) >= 1 || is_out_of_bounds(i,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+3) >= 1 || is_out_of_bounds(i+1,j+3)){code+=2;}
        if(map_pull(i+1,j) >= 1 || map_pull(i+2,j+1) >= 1 || map_pull(i+2,j+2) >= 1){return 0;}
        if(is_out_of_bounds(i+2,j+1)){return 0;}
    }
    if(state == 1 || state == 3){
        if(map_pull(i,j) >= 1 || map_pull(i+1,j-1) >= 1 || map_pull(i+2,j-1) >= 1 || is_out_of_bounds(i+1,j-1)){code++;}
        if(map_pull(i,j+2) >= 1 || map_pull(i+1,j+2) >= 1 || map_pull(i+2,j+1) >= 1 || is_out_of_bounds(i,j+2)){code+=2;}
        if(map_pull(i+3,j) >= 1 || map_pull(i+2,j+1) >= 1){return 0;}
        if(is_out_of_bounds(i+3,j)){return 0;}
    }
    if(code == 0){code = 4;}
    return code;
}

void draw_on_container(int i,int j) {
    Draw::draw_rect(Container::get_starting_x()+j+1, Container::get_starting_y() + i + 1, 1, 1);
}

void draw_from_map() {
    for(int i = 0;i < CONTAINER_HEIGHT;i++){
        for(int j = 0;j < CONTAINER_WIDTH;j++){
            if(Container::map_pull(i,j) == 1){Draw::set_color(BACKGROUND_LIGHT_YELLOW);}
            if(Container::map_pull(i,j) == 2){Draw::set_color(BACKGROUND_LIGHT_BLUE);}
            if(Container::map_pull(i,j) == 3){Draw::set_color(BACKGROUND_PURPLE);}
            if(Container::map_pull(i,j) == 4){Draw::set_color(BACKGROUND_BLUE);}
            if(Container::map_pull(i,j) == 5){Draw::set_color(BACKGROUND_YELLOW);}
            if(Container::map_pull(i,j) == 6){Draw::set_color(BACKGROUND_GREEN);}
            if(Container::map_pull(i,j) == 7){Draw::set_color(BACKGROUND_RED);}
            if(Container::map_pull(i,j) == 0){
                Draw::set_color(BACKGROUND_BLACK);
            }
            draw_on_container(i,j);
        }
    }
}

void tick(){this_thread::sleep_for(chrono::milliseconds(10));}

void keyHandle(int *keyCode){
    for(int i = 0;i < 40;i++){
        thread t1(tick);
        if(GetKeyState(0x41) & 0x8000){// 0x41 = A
            *keyCode = 1;
        }
        if(GetKeyState(0x44) & 0x8000){// 0x44 = D
            *keyCode = 2;
        }
        if(GetKeyState(0x57) & 0x8000){
            *keyCode = 3;
        }
        t1.join();
    }
}

void event() {//testing
    int j = 4;
    int prev_i = 0;
    int state = 0;

    int keyCode = 0;

    auto *t1 = new thread(keyHandle,&keyCode);

    for(int i = 0;;i++){
        t1->join();
        Container::map_zero_z_block(prev_i,j,state);
        if(keyCode == 1) {
            if (Container::map_check_collision_z_block(i, j, state) != 1 &&
                Container::map_check_collision_z_block(i, j, state) != 3 &&
                Container::map_check_collision_z_block(i, j, state) != 0) {
                j--;
            }
            keyCode = 0;
        }
        if(keyCode == 2) {
            if (Container::map_check_collision_z_block(i, j, state) != 2 &&
                Container::map_check_collision_z_block(i, j, state) != 3 &&
                Container::map_check_collision_z_block(i, j, state) != 0) {
                j++;
            }
            keyCode = 0;
        }
        if(keyCode == 3){
            if(state == 3){
                state = 0;
            }else{
                state++;
            }
            keyCode = 0;
        }
        Container::map_put_z_block(i,j,state);
        draw_from_map();
        Draw::setxy(13,1);
        for(int k = 0;k < 20;k++){
            for(int m = 0;m < 10;m++){
                cout<<Container::map_pull(k,m);
            }
            Draw::setxy(13,k+2);
        }

        Draw::setxy(13,21);
        cout<<i<<" "<<j<<" "<<Container::map_check_collision_z_block(i,j,state)<<" "<<state;
        //Draw::setxy(0,Container::get_height()+ Container::get_starting_y());
        //system("pause");
        t1 = new thread(keyHandle,&keyCode);
        //this_thread::sleep_for(chrono::milliseconds(200));
        if(Container::map_check_collision_z_block(i,j,state) == 0){
            break;
        }
        prev_i = i;
    }
}

int main() {
    Container::draw_container();
    Container::generate_map();
    for(int i = 0;i < 20;i++){
        if(i > 9 && i < 13){
            continue;
        }
        Container::map_put(i,0);
        Container::map_put(i,9);
    }
    Container::map_put_t_block(18,4,0);
    event();
    Draw::setxy(0,Container::get_height()+ Container::get_starting_y());
    system("pause");
    return 0;
}
