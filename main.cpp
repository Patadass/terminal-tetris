#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <random>

#include "draw.h"
#include "tetris.h"

using namespace std;

class Piece{
private:
    int i,j,prev_i,state,keyCode,piece_num;
    bool is_done = false;
public:
    Piece() = default;
    Piece(int _i,int _j,int _prev_i,int _state,int _keyCode,int _piece_num){
        i = _i;
        j = _j;
        prev_i = _prev_i;
        state = _state;
        keyCode = _keyCode;
        piece_num = _piece_num;
    }
    void set(int _i,int _prev_i,int _key_code){
        i = _i;
        prev_i = _prev_i;
        keyCode = _key_code;
    }
    void reset(int _i,int _j,int _prev_i,int _state,int _keyCode,int _piece_num){
        i = _i;
        j = _j;
        prev_i = _prev_i;
        state = _state;
        keyCode = _keyCode;
        piece_num = _piece_num;
        is_done = false;
    }
    void change_piece(int _piece_num){
        piece_num = _piece_num;
    }
    void set_done(bool _is_done){is_done = _is_done;}
    bool get_is_done(){return is_done;}
    friend Piece game_event(Piece piece);
};

int random(int from, int to){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(from, to);
    return distribution(generator);
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

Piece game_event(Piece piece){
    // 1 = O block
    // 2 = I block
    // 3 = T block
    // 4 = J block
    // 5 = L block
    // 6 = S block
    // 7 = Z block
    bool can_right = false, can_left = false;
    if(piece.piece_num == 1){
        Tetris::map_zero_o_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_o_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_o_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_o_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_o_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_o_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_o_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_o_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_o_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    if(piece.piece_num == 2){
        Tetris::map_zero_i_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_i_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_i_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_i_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_i_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_i_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_i_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_i_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_i_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    if(piece.piece_num == 3){
        Tetris::map_zero_t_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_t_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_t_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_t_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_t_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_t_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_t_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_t_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_t_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    if(piece.piece_num == 4){
        Tetris::map_zero_j_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_j_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_j_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_j_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_j_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_j_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_j_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_j_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_j_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    if(piece.piece_num == 5){
        Tetris::map_zero_l_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_l_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_l_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_l_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_l_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_l_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_l_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_l_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_l_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    if(piece.piece_num == 6){
        Tetris::map_zero_s_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_s_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_s_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_s_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_s_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_s_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_s_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_s_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_s_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    if(piece.piece_num == 7){
        Tetris::map_zero_z_block(piece.prev_i,piece.j,piece.state);
        if (Tetris::map_check_collision_z_block(piece.i,piece.j,piece.state) != 1 &&
            Tetris::map_check_collision_z_block(piece.i,piece.j,piece.state) != 3 &&
            Tetris::map_check_collision_z_block(piece.i,piece.j,piece.state) != 0) {
            can_left = true;
        }
        if (Tetris::map_check_collision_z_block(piece.i, piece.j, piece.state) != 2 &&
            Tetris::map_check_collision_z_block(piece.i, piece.j, piece.state) != 3 &&
            Tetris::map_check_collision_z_block(piece.i, piece.j, piece.state) != 0) {
            can_right = true;
        }
        if(can_left && piece.keyCode == 1){piece.j--;}
        if(can_right && piece.keyCode == 2){piece.j++;}
        if(piece.keyCode == 3){
            if(piece.state == 3){piece.state = 0;}
            else{piece.state++;}
        }
        piece.keyCode = 0;
        Tetris::map_put_z_block(piece.i,piece.j,piece.state);
        if(Tetris::map_check_collision_z_block(piece.i,piece.j,piece.state) == 0){
            piece.set_done(true);
        }
    }
    Tetris::draw_from_map();
    return piece;
}

void event() {//testing
    int j = 4;
    int prev_i = 0;
    int state = 0;
    int piece_num = random(1,7);

    int keyCode = 0;

    auto *t1 = new thread(keyHandle,&keyCode);
    Piece piece(0,j,prev_i,state,keyCode,piece_num);
    for(int i = 0;;i++){
        t1->join();
        piece.set(i,prev_i,keyCode);
        keyCode = 0;
        piece = game_event(piece);
        if(piece.get_is_done()){
            Tetris::line_manager();
            piece_num = random(1,7);
            i = -1;j = 4;prev_i = -1;state = 0;keyCode = 0;
            piece.reset(i,j,prev_i,state,keyCode,piece_num);
        }
        prev_i = i;
        Draw::setxy(13,1);
        for(int k = 0;k < 20;k++){
            for(int m = 0;m < 10;m++){
                Draw::reset_color();
                cout<<Tetris::map_pull(k,m);
            }
            Draw::setxy(13,k+2);
        }
        Draw::setxy(13,21);
        cout<<i<<" "<<j<<" "<<Tetris::map_check_collision_z_block(i,j,state)<<" "<<state;
        t1 = new thread(keyHandle,&keyCode);
    }
}

int main() {
    Tetris::draw_container();
    Tetris::generate_map();
    event();
    Draw::setxy(0,Tetris::get_height()+ Tetris::get_starting_y());
    system("pause");
    return 0;
}
