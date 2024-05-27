#include "tetris.h"


short Tetris::map[CONTAINER_HEIGHT][CONTAINER_WIDTH];
int Tetris::container_height = CONTAINER_HEIGHT + 2, Tetris::container_width = CONTAINER_WIDTH + 2;
int Tetris::starting_x = 0,Tetris::staring_y = 0;
WORD Tetris::container_color = BACKGROUND_WHITE;

void Tetris::queue_start_sequence() {
    int x = 16,y = 10;//t
    Draw::set_color(BACKGROUND_LIGHT_BLUE);
    Draw::draw_fill_rect(x,y,18,3);
    Draw::draw_fill_rect(x+6,y+3,6,8);
    x = x+20;//e
    Draw::set_color(BACKGROUND_RED);
    Draw::draw_fill_rect(x,y,5,11);
    Draw::draw_fill_rect(x+5,y,8,2);
    Draw::draw_fill_rect(x+5,y+4,6,3);
    Draw::draw_fill_rect(x+5,y+9,8,2);
    x = x+15;//t
    Draw::set_color(BACKGROUND_LIGHT_BLUE);
    Draw::draw_fill_rect(x,y,18,3);
    Draw::draw_fill_rect(x+6,y+3,6,8);
    x = x+20;//r
    Draw::set_color(BACKGROUND_YELLOW);
    Draw::draw_fill_rect(x,y,4,11);
    Draw::draw_rect(x+3,y,8,5);
    Draw::draw_rect(x+3,y+1,7,3);
    Draw::draw_fill_rect(x+3,y+5,4,2);
    Draw::draw_fill_rect(x+6,y+7,3,2);
    Draw::draw_fill_rect(x+8,y+9,3,2);
    x = x+13;//I
    Draw::set_color(BACKGROUND_GREEN);
    Draw::draw_fill_rect(x,y,6,11);
    x = x+8;//S
    Draw::set_color(BACKGROUND_PURPLE);
    Draw::draw_fill_rect(x,y,12,3);
    Draw::draw_fill_rect(x,y+2,6,4);
    Draw::draw_fill_rect(x,y+4,12,3);
    Draw::draw_fill_rect(x+6,y+6,6,3);
    Draw::draw_fill_rect(x,y+8,12,3);
    x = 14,y-=2;
    Draw::set_color(BACKGROUND_WHITE);
    for(int i = x;i < 106;i++){
        Draw::draw_rect(i,y,1,1);
        Draw::draw_rect(119-i,y+14,1,1);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    for(int j = y;j < 22;j++){
        Draw::draw_rect(x,30-j,1,1);
        Draw::draw_rect(x+91,j,1,1);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    Draw::reset_color();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    system("cls");
}

void Tetris::generate_map() {
    for(int i = 0;i < CONTAINER_HEIGHT;i++){
        for(int j = 0;j < CONTAINER_WIDTH;j++){
            Tetris::map_zero(i,j);
        }
    }
}

void Tetris::draw_container() {
    Draw::set_color(container_color);
    Draw::draw_rect(starting_x,staring_y,container_width,container_height);
    Draw::reset_color();
}

void Tetris::draw_on_container(int i,int j) {
    Draw::draw_rect(Tetris::get_starting_x()+j+1, Tetris::get_starting_y() + i + 1, 1, 1);
}

void Tetris::draw_np_container() {
    Draw::set_color(container_color);
    Draw::draw_rect(starting_x+14,0,7,6);
    Draw::reset_color();
}

void Tetris::draw_on_np_container(int piece) {
    int i = get_starting_x();
    int j = get_starting_y();
    Draw::set_color(BACKGROUND_BLACK);
    Draw::draw_fill_rect(i+15,j+1,5,4);
    if(piece == 1){
        i+=17;j+=2;
        Draw::set_color(BACKGROUND_LIGHT_YELLOW);
        Draw::draw_rect(i,j,2,2);
    }
    if(piece == 2){
        i+=17;j+=1;
        Draw::set_color(BACKGROUND_LIGHT_BLUE);
        Draw::draw_rect(i,j,1,4);
    }
    if(piece == 3){
        i+=17;j+=2;
        Draw::set_color(BACKGROUND_PURPLE);
        Draw::draw_rect(i,j,1,1);
        Draw::draw_rect(i-1,j+1,3,1);
    }
    if(piece == 4){
        i+=17;j+=1;
        Draw::set_color(BACKGROUND_BLUE);
        Draw::draw_rect(i,j,1,3);
        Draw::draw_rect(i-1,j+2,1,1);
    }
    if(piece == 5){
        i+=17;j+=1;
        Draw::set_color(BACKGROUND_YELLOW);
        Draw::draw_rect(i,j,1,3);
        Draw::draw_rect(i+1,j+2,1,1);
    }
    if(piece == 6){
        i+=17;j+=2;
        Draw::set_color(BACKGROUND_GREEN);
        Draw::draw_rect(i,j,2,1);
        Draw::draw_rect(i-1,j+1,2,1);
    }
    if(piece == 7){
        i+=16;j+=2;
        Draw::set_color(BACKGROUND_RED);
        Draw::draw_rect(i,j,2,1);
        Draw::draw_rect(i+1,j+1,2,1);
    }
}

void Tetris::draw_from_map() {
    for(int i = 0;i < CONTAINER_HEIGHT;i++){
        for(int j = 0;j < CONTAINER_WIDTH;j++){
            if(Tetris::map_pull(i,j) == 1){Draw::set_color(BACKGROUND_LIGHT_YELLOW);}
            if(Tetris::map_pull(i,j) == 2){Draw::set_color(BACKGROUND_LIGHT_BLUE);}
            if(Tetris::map_pull(i,j) == 3){Draw::set_color(BACKGROUND_PURPLE);}
            if(Tetris::map_pull(i,j) == 4){Draw::set_color(BACKGROUND_BLUE);}
            if(Tetris::map_pull(i,j) == 5){Draw::set_color(BACKGROUND_YELLOW);}
            if(Tetris::map_pull(i,j) == 6){Draw::set_color(BACKGROUND_GREEN);}
            if(Tetris::map_pull(i,j) == 7){Draw::set_color(BACKGROUND_RED);}
            if(Tetris::map_pull(i,j) == 0){
                Draw::set_color(BACKGROUND_BLACK);
            }
            Tetris::draw_on_container(i,j);
        }
    }
}

void Tetris::map_put(int i,int j,int n) {
    Tetris::map[i][j] = short(n);
}
short Tetris::map_pull(int i,int j) {
    return Tetris::map[i][j];
}
void Tetris::map_zero(int i,int j) {
    Tetris::map[i][j] = 0;
}
bool Tetris::is_out_of_bounds(int i,int j){
    if(i >= CONTAINER_HEIGHT || i < 0){
        return true;
    }
    if(j >= CONTAINER_WIDTH || j < 0){
        return true;
    }
    return false;
}

int Tetris::get_height(){return Tetris::container_height;}
int Tetris::get_width(){return Tetris::container_width;}
int Tetris::get_starting_x(){return Tetris::starting_x;}
int Tetris::get_starting_y(){return Tetris::staring_y;}

void Tetris::map_put_o_block(int starting_i,int starting_j,int state) {
    int i = starting_i,j = starting_j;
    map_put(i,j,1);
    map_put(i,j+1,1);
    map_put(i+1,j);
    map_put(i+1,j+1,1);
}
void Tetris::map_zero_o_block(int starting_i,int starting_j,int state) {
    int i = starting_i,j = starting_j;
    map_zero(i,j);
    map_zero(i,j+1);
    map_zero(i+1,j);
    map_zero(i+1,j+1);
}
int Tetris::map_check_collision_o_block(int starting_i, int starting_j, int state) {
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

void Tetris::map_put_i_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_put(i,j,2); map_put(i,j+1,2); map_put(i,j+2,2); map_put(i,j+3,2);}
    if(state == 1 || state == 3){map_put(i,j,2); map_put(i+1,j,2); map_put(i+2,j,2); map_put(i+3,j,2);}
}
void Tetris::map_zero_i_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i,j+2); map_zero(i,j+3);}
    if(state == 1 || state == 3){map_zero(i,j); map_zero(i+1,j); map_zero(i+2,j); map_zero(i+3,j);}
}
int Tetris::map_check_collision_i_block(int starting_i, int starting_j, int state) {
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

void Tetris::map_put_t_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_put(i,j+1,3); map_put(i+1,j,3); map_put(i+1,j+1,3); map_put(i+1,j+2,3);}
    if(state == 1){map_put(i,j+1,3); map_put(i+1,j+1,3); map_put(i+1,j+2,3); map_put(i+2,j+1,3);}
    if(state == 2){map_put(i+1,j,3); map_put(i+1,j+1,3); map_put(i+1,j+2,3); map_put(i+2,j+1,3);}
    if(state == 3){map_put(i,j+1,3); map_put(i+1,j,3); map_put(i+1,j+1,3); map_put(i+2,j+1,3);}
}

void Tetris::map_zero_t_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_zero(i,j+1); map_zero(i+1, j); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1){map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+1,j+2); map_zero(i+2,j+1);}
    if(state == 2){map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+1,j+2); map_zero(i+2,j+1);}
    if(state == 3){map_zero(i,j+1); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+2,j+1);}
}

int Tetris::map_check_collision_t_block(int starting_i, int starting_j, int state) {
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

void Tetris::map_put_j_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_put(i,j,4); map_put(i+1,j,4); map_put(i+1,j+1,4); map_put(i+1,j+2,4);}
    if(state == 1){map_put(i,j,4); map_put(i,j+1,4); map_put(i+1,j,4); map_put(i+2,j,4);}
    if(state == 2){map_put(i,j,4); map_put(i,j+1,4); map_put(i,j+2,4); map_put(i+1,j+2,4);}
    if(state == 3){map_put(i,j+1,4); map_put(i+1,j+1,4); map_put(i+2,j,4); map_put(i+2,j+1,4);}
}
void Tetris::map_zero_j_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_zero(i,j); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1){map_zero(i,j); map_zero(i,j+1); map_zero(i+1,j); map_zero(i+2,j);}
    if(state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i,j+2); map_zero(i+1,j+2);}
    if(state == 3){map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+2,j); map_zero(i+2,j+1);}
}
int Tetris::map_check_collision_j_block(int starting_i, int starting_j, int state) {
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

void Tetris::map_put_l_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_put(i,j+2,5); map_put(i+1,j,5); map_put(i+1,j+1,5); map_put(i+1,j+2,5);}
    if(state == 1){map_put(i,j,5); map_put(i+1,j,5); map_put(i+2,j,5); map_put(i+2,j+1,5);}
    if(state == 2){map_put(i,j,5); map_put(i,j+1,5); map_put(i,j+2,5); map_put(i+1,j,5);}
    if(state == 3){map_put(i,j,5); map_put(i,j+1,5); map_put(i+1,j+1,5); map_put(i+2,j+1,5);}
}
void Tetris::map_zero_l_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0){map_zero(i,j+2); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1){map_zero(i,j); map_zero(i+1,j); map_zero(i+2,j); map_zero(i+2,j+1);}
    if(state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i,j+2); map_zero(i+1,j);}
    if(state == 3){map_zero(i,j); map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+2,j+1);}
}
int Tetris::map_check_collision_l_block(int starting_i, int starting_j, int state) {
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

void Tetris::map_put_s_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_put(i,j+1,6); map_put(i,j+2,6); map_put(i+1,j,6); map_put(i+1,j+1,6);}
    if(state == 1 || state == 3){map_put(i,j,6); map_put(i+1,j,6); map_put(i+1,j+1,6); map_put(i+2,j+1,6);}
}
void Tetris::map_zero_s_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_zero(i,j+1); map_zero(i,j+2); map_zero(i+1,j); map_zero(i+1,j+1);}
    if(state == 1 || state == 3){map_zero(i,j); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+2,j+1);}
}
int Tetris::map_check_collision_s_block(int starting_i, int starting_j, int state) {
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

void Tetris::map_put_z_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_put(i,j,7); map_put(i,j+1,7); map_put(i+1,j+1,7); map_put(i+1,j+2,7);}
    if(state == 1 || state == 3){map_put(i,j+1,7); map_put(i+1,j,7); map_put(i+1,j+1,7); map_put(i+2,j,7);}
}
void Tetris::map_zero_z_block(int starting_i, int starting_j, int state) {
    int i = starting_i,j = starting_j;
    if(state == 0 || state == 2){map_zero(i,j); map_zero(i,j+1); map_zero(i+1,j+1); map_zero(i+1,j+2);}
    if(state == 1 || state == 3){map_zero(i,j+1); map_zero(i+1,j); map_zero(i+1,j+1); map_zero(i+2,j);}
}
int Tetris::map_check_collision_z_block(int starting_i, int starting_j, int state) {
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

void Tetris::line_manager() {
    bool clear = true;
    int level = 0;
    for(int i = 0;i < CONTAINER_HEIGHT;i++){
        for(int j = 0; j < CONTAINER_WIDTH;j++){
            if(Tetris::map_pull(i,j) == 0){
                clear = false;
                break;
            }
        }
        if(clear){
            for(int k = i;k >= 0;k--){
                for(int l = 0;l < CONTAINER_WIDTH;l++){
                    if(k == i){
                        Tetris::map_zero(k,l);
                        continue;
                    }
                    if(Tetris::map_pull(k,l) != 0){
                        Tetris::map_put(k+1,l,Tetris::map_pull(k,l));
                        Tetris::map_zero(k,l);
                    }
                }
            }
        }
        clear = true;
        level = 0;
    }
}