#include <iostream>
using namespace std;

bool go_back(int right_shift_space[], int col_offset[], int& piece_back, int& piece_idx, bool& back, int** map, int** map_temp, int w_map[], int h_map[], int& k);

int main(){
//num
    int number_of_pieces;
    int number_of_trucks;
//piece
    char in;
    int* w;
    int* h;
    int** piece;
//maps(trucks)
    int* w_map; //truck_length
    int* h_map;
    int** map;
    int** map_temp;
//array
    int piece_idx;
    int map_puzzle_idx;
//locaation
    int* row_offset;
    int* col_offset;
    int* right_shift_space;
//back
    int piece_back;
    bool back;
    bool end_case;
//result
    int* result;
    bool move_right;
    bool move_left;
    bool movable;

//pieces
    cin >> number_of_pieces;
    w = new int[number_of_pieces];
    h = new int[number_of_pieces];
    piece = new int *[number_of_pieces];
    for(int i=0; i<number_of_pieces; i++){
        cin >> w[i];
        cin >> h[i];
        piece[i] = new int[(w[i]*h[i])];
        for(int j=0; j<w[i]*h[i]; j++){
            cin >> in;
            if(in=='O')
                {piece[i][j] = i+1;}
            else if(in=='-')
                {piece[i][j] = 0;}
        }
    }
//trucks
    cin >> number_of_trucks;
    w_map = new int[number_of_trucks];
    for(int i=0; i<number_of_trucks; i++){
        cin >> w_map[i];
    }
//maps
    h_map = new int[number_of_trucks];
    map = new int *[number_of_trucks];
    
    for(int i=0; i<number_of_trucks; i++){
        h_map[i] = 8;
        map[i] = new int[(w_map[i]*h_map[i])];
        for(int j=0; j<w_map[i]*h_map[i]; j++){
            map[i][j] = 0;
        }
    }
//piece location record
    row_offset = new int[number_of_pieces];
    col_offset = new int[number_of_pieces];
    right_shift_space = new int[number_of_pieces];


//-----------------------main--------------------------
for(int k=0; k<number_of_trucks; k++){
        //row_offset
        for(int i=0; i<number_of_pieces; i++){
            row_offset[i] = h_map[k] - h[i];
        }
        // creat map_temp
        map_temp = new int *[number_of_pieces + 1];
        for(int i=0; i<number_of_pieces+1; i++){
            map_temp[i] = new int[(w_map[k]*h_map[k])];
        }
        //save the original map
        for(int j=0; j<w_map[k]*h_map[k]; j++){
            map_temp[0][j] = map[k][j];
        }
        //start at the first piece
        piece_idx = 0;
        back = false;
        move_left = true;
        move_right = true;
        movable = false;
        while(1){
            if(back==false){
                right_shift_space[piece_idx] = w_map[k]-w[piece_idx];
                col_offset[piece_idx] = 0;
            }
            back = false;
            for(int row=0; row<h[piece_idx]; row++){
                for(int col=0; col<w[piece_idx]; col++){
                    map_puzzle_idx = row*w_map[k]+col+row_offset[piece_idx]*w_map[k]+col_offset[piece_idx];
                    if(piece[piece_idx][row*w[piece_idx]+col]!=0 && map[k][map_puzzle_idx]!=0){
                        //go_back to next trial
                        end_case = go_back(right_shift_space, col_offset, piece_back, piece_idx, back, map, map_temp, w_map, h_map, k);
                        if(end_case==true){
                            goto end;
                        }
                        break;
                    }
                    else if((piece[piece_idx][row*w[piece_idx]+col]!=0) && (map[k][map_puzzle_idx]==0)){
                        map[k][map_puzzle_idx] = piece[piece_idx][row*w[piece_idx]+col];
                    }
                }
                //go to the next trial
                if(back==true){
                    break;
                }
            }

            //the last piece
            if(back==false && piece_idx==number_of_pieces-1){
            //check if the items can be transport
                //check movability
                for(int i=1; i<=number_of_pieces; i++){
                    for(int col=0; col<w_map[k]; col++){
                        for(int row=0; row<h_map[k]; row++){
                            if(col==0){
                                if(map[k][row*w_map[k]+col]==i){
                                    move_left = false;
                                }
                                if(map[k][row*w_map[k]+col]==i && map[k][row*w_map[k]+col+1]!=0 && map[k][row*w_map[k]+col+1]!=i){  //can't move
                                    move_right = false;
                                }
                            }
                            else if(col==w_map[k]-1){
                                if(map[k][row*w_map[k]+col]==i){
                                    move_right = false;
                                }
                                if(map[k][row*w_map[k]+col]==i && map[k][row*w_map[k]+col-1]!=0 && map[k][row*w_map[k]+col-1]!=i){  //can't move
                                    move_left = false;
                                }
                            }
                            else{
                                if(map[k][row*w_map[k]+col]==i && map[k][row*w_map[k]+col+1]!=0 && map[k][row*w_map[k]+col+1]!=i){  //can't move
                                    move_right = false;
                                }
                                if(map[k][row*w_map[k]+col]==i && map[k][row*w_map[k]+col-1]!=0 && map[k][row*w_map[k]+col-1]!=i){  //can't move
                                    move_left = false;
                                }
                            }
                        }
                    }
                    if(move_right==true || move_left==true){
                        move_right==true;
                        move_left==true;
                        movable = true;
                        break;
                    }
                    else{
                        move_right = true;
                        move_left = true;
                        movable = false;
                    }
                }
                //check length
                result = new int[w_map[k]];
                for(int row=0; row<h_map[k]; row++){
                    for(int col=0; col<w_map[k]; col++){
                        if(map[k][row*w_map[k]+col]!=0){
                            result[col] = 1;
                        }
                    }
                }
                for(int i=0; i<w_map[k]; i++){
                    if(result[i]!=1 || movable==true){
                        end_case = go_back(right_shift_space, col_offset, piece_back, piece_idx, back, map, map_temp, w_map, h_map, k);
                        if(end_case){
                            goto end;
                        }
                        break;
                    }
                }
                if(back==false){
                    cout << "Yes" << endl;
                    goto end;
                }
            }
            //not the last piece -> keep going
            else if(back==false){
                //move the piece to its next location
                if(right_shift_space[piece_idx] > 0){
                    col_offset[piece_idx] = col_offset[piece_idx] + 1;
                    right_shift_space[piece_idx] = right_shift_space[piece_idx] - 1;
                }
                else{  //the piece is at its last location
                    col_offset[piece_idx] = -1;
                    right_shift_space[piece_idx] = -1;
                }       
                //save the temp map
                for(int j=0; j<w_map[k]*h_map[k]; j++){
                    map_temp[piece_idx+1][j] = map[k][j];
                }
                //go to next piece
                piece_idx++;
            }

            //debug
            // for(int i=0; i<w_map[k]*h_map[k]; i++){
            //     if(i%11==10)
            //         cout << map[k][i] << endl;
            //     else
            //         cout << map[k][i];
            // }
            // cout << endl;
        }

        end:
        // delete map_temp
        for(int i=0; i<number_of_pieces+1; i++){
            delete[] map_temp[i];
        }
        delete[] map_temp;

}
    return 0;

}

bool go_back(int right_shift_space[], int col_offset[], int& piece_back, int& piece_idx, bool& back, int** map, int** map_temp, int w_map[], int h_map[], int& k){

    bool end;

    if(right_shift_space[piece_idx] > 0){  //move the piece to its next location and set piece_back to its next location
        col_offset[piece_idx] = col_offset[piece_idx] + 1;
        right_shift_space[piece_idx] = right_shift_space[piece_idx] - 1;
        piece_back = piece_idx;
        end = false;
    }
    else{  //the piece is at its last location
        for(int i=piece_idx-1; i>=0; i--){
            if(right_shift_space[i]!=-1){
                piece_back = i;
                end = false;
                break;
            }
            else if(i==0){  //terminate condition
                piece_back = -1;
                cout << "No" << endl;
                end = true;
                return end;
            }
        }
    }
    //set the next trial's piece_idx
    piece_idx = piece_back;
    back = true;
    //reset the map
    for(int j=0; j<w_map[k]*h_map[k]; j++){
        map[k][j] = map_temp[piece_idx][j];
    }
    return end;
}
