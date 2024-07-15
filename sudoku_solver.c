#include <stdio.h>
#include <time.h>

/*VARIABLES VARIABLES VARIABLES VARIABLES VARIABLES VARIABLES VARIABLES*/
#define PUZZLE_SIZE 9

/*9x9 Matrix numbers 1-9 or "0" for empty*/
int puzzle[PUZZLE_SIZE][PUZZLE_SIZE] = 
    {
        {6, 0, 3,   4, 0, 1,   8, 9, 7},
        {7, 0, 5,   2, 9, 6,   3, 0, 1},
        {9, 0, 4,   0, 8, 0,   0, 0, 0},

        {8, 6, 0,   0, 0, 0,   1, 0, 4},
        {0, 3, 0,   6, 0, 0,   0, 5, 9},
        {1, 0, 0,   0, 2, 0,   0, 0, 0},

        {0, 9, 0,   0, 0, 0,   5, 0, 0},
        {0, 0, 0,   0, 3, 2,   0, 1, 8},
        {3, 0, 0,   1, 0, 5,   0, 0, 0}
    };
int puzzle_notes[PUZZLE_SIZE][PUZZLE_SIZE][PUZZLE_SIZE];
double solution_time;


/*METHOD DECLARATIONS*/
void print_puzzle();
int is_puzzle_solved();
void solution1_basic(int count);
void solution2_complex(int count);
void take_notes();
int contains_locked_canidate_n(int x, int y, int n);
void locked_canidate(int block);


/*METHODS METHODS METHODS METHODS METHODS METHODS METHODS METHODS METHODS*/
void print_puzzle(){
    printf("\n***************************************\n");
    for(int row = 0; row < PUZZLE_SIZE; row++){ /*LOOP1*/
        for( int col = 0; col < PUZZLE_SIZE; col++){ /*LOOP2*/
            if(puzzle[row][col] != 0) printf(" %d |", puzzle[row][col]);
            else printf("   |");
            if( (col % 3) == 2 ) printf("|");
        }/*END LOOP2*/
        if( (row % 3) == 2 ) printf("\n---------------------------------------");
        printf("\n---------------------------------------\n");
    }/*END LOOP1*/
}/*END void print_puzzle()*/

int is_puzzle_solved(){
    //print_puzzle();
    /*if the number is in the row, col, or square mark it by 0, 1 if not*/
    int all_nine_there[PUZZLE_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    /*marks the current square we are looking at*/
    int current_number = 0;
    int square_bottom_right[2] = {0, 0}; /*where {ROW, COL}*/

    /*LOOP1 check rows*/
    for( int row = 0; row < PUZZLE_SIZE; row++ ) {

        /*reset all to 1 (false)*/
        for(int i = 0; i < PUZZLE_SIZE; i++)all_nine_there[i] = 1;

        /*LOOP2*/
        for( int col = 0; col < PUZZLE_SIZE; col++ ){
            current_number = puzzle[row][col];
            if(current_number == 0) return 1;/*empty square*/
            else if(all_nine_there[current_number - 1] != 0){/*hit!*/
                all_nine_there[current_number - 1] = 0;
            }
            else return 1; /*duplacate*/
        }/*END LOOP2*/
    }/*END LOOP1*/

    /*LOOP1 check cols*/
    for( int col = 0; col < PUZZLE_SIZE; col++ ) {

        /*reset all to 1 (false)*/
        for(int i = 0; i < PUZZLE_SIZE; i++)all_nine_there[i] = 1;

        /*LOOP2*/
        for( int row = 0; row < PUZZLE_SIZE; row++ ){
            current_number = puzzle[row][col];
            if(current_number == 0) return 1; /*empty square*/
            else if(all_nine_there[current_number - 1] != 0){ /*hit!*/
                all_nine_there[current_number - 1] = 0;
            }
        }/*END LOOP2*/
    }/*END LOOP1*/


    /*check squares*/
    /*LOOP1 mark the bottom row*/
    for ( square_bottom_right[0] = PUZZLE_SIZE/3; 
            square_bottom_right[0] <= PUZZLE_SIZE; 
            square_bottom_right[0] = square_bottom_right[0] + PUZZLE_SIZE/3 ){ 
        
        /*LOOP2 mark the far right row*/
        for (square_bottom_right[1] = PUZZLE_SIZE/3; 
            square_bottom_right[1] <= PUZZLE_SIZE; 
            square_bottom_right[1] = square_bottom_right[1] + PUZZLE_SIZE/3 ){

            /*reset all to 1 (false)*/
            for(int i = 0; i < PUZZLE_SIZE; i++)all_nine_there[i] = 1;

            /*LOOP3 iterate through the last three rows*/
            for( int row = square_bottom_right[0] - 3; 
                    row < square_bottom_right[0]; row++ ) {

                /*LOOP4 iterate through the last three columbs and check them*/
                for(int col = square_bottom_right[1] - 3; 
                    col < square_bottom_right[1]; col++ ){

                    current_number = puzzle[row][col];
                    if(current_number == 0) return 1; /*empty*/
                    else if(all_nine_there[current_number - 1] != 0){ /*hit!*/
                        all_nine_there[current_number - 1] = 0;
                    }
                    else return 1; /*duplacates*/
                }/*END LOOP4*/
            }/*END LOOP3*/
        }/*END LOOP2*/
    }/*END LOOP1*/

    /*puzzle solved!*/
    return 0;

}/*END int is_puzzle_solved()*/

/*SOLUTIONS SOLUTIONS SOLUTIONS SOLUTIONS SOLUTIONS SOLUTIONS SOLUTIONS*/
/*see "description.txt" for more details on solutions*/
void solution1_basic(int count){ 
    int square_row, square_col;
    int num_check[PUZZLE_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int number_filled = 0;

    while(is_puzzle_solved() != 0 && count > 0){ /*LOOP1*/
        for(int row = 0; row < PUZZLE_SIZE; row++){/*LOOP2*/
            for(int col = 0; col < PUZZLE_SIZE; col++){/*LOOP3*/
                /*for every square we need to check row, col and square*/
                /*check that it's empty*/
                if ( puzzle[row][col] == 0){
                    for(int i = 0; i < PUZZLE_SIZE; i++) num_check[i] = 1;

                    /*check its row*/
                    for ( int check_col = 0; check_col < PUZZLE_SIZE; 
                                                check_col++ ){/*LOOP4*/
                        if ( puzzle[row][check_col] != 0 ){
                            num_check[ puzzle[row][check_col]-1 ] = 0;
                        }
                    } /* END LOOP4 */

                    /*check its col*/
                    for ( int check_row = 0; check_row < PUZZLE_SIZE; 
                                                check_row++ ){ /*LOOP4*/
                        if ( puzzle[check_row][col] != 0 ){
                            num_check[ puzzle[check_row][col]-1 ] = 0;
                        }
                    } /* END LOOP4 */

                    /*check its square*/
                    square_row = row/3; /*0, 1 or 2*/
                    square_row = square_row*3; /*0, 3, 6*/

                    square_col = col/3; /*0, 1 or 2*/
                    square_col = square_col*3; /*0, 3, 6*/

                    for( int check_row = square_row;
                            check_row < square_row + 3; check_row++){ /*LOOP4*/
                        
                        for( int check_col = square_col;
                            check_col < square_col + 3; check_col++){ /*LOOP5*/

                            if ( puzzle[check_row][check_col] != 0 ){
                                num_check[ 
                                    puzzle[check_row][check_col]-1 ] = 0;
                            }
                        }/* END LOOP5 */
                    } /* END LOOP4 */

                    /*if num_check has only 1 false mark that number in!!*/
                    int c = 0;
                    for(int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP4*/
                        if ( num_check[i] != 0 && c < 1){
                            c++;
                        }else if ( num_check[i] != 0 && c >= 1 ){
                            c++;
                            i = PUZZLE_SIZE;
                        }
                    }/*END LOOP4*/

                    /*if there is 1 number left fill it into the square*/
                    if ( c == 1 ) {
                        for (int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP4*/
                            if ( num_check[i] != 0 ) { 
                                puzzle[row][col] = i+1;
                                number_filled =  i+1;
                            }
                        }/* END LOOP4*/
                    }/* END if */
                    else{
                        number_filled = 0;
                    }
                } /* END if */

                // printf("\n");
                // printf("(%d, %d) > { %d, %d } = %d:\t",
                //             row, col, square_row, square_col, number_filled);
                // for (int i = 0; i < PUZZLE_SIZE; i++){
                //     printf("%d = %s; ", i+1, num_check[i] ? " true" : "false");
                // } 

            } /* END LOOP3 */
        } /* END LOOP2 */
        count = count - 1; /*step*/
    } /* END LOOP1 */
} /* END solution1_basic() */

void solution2_complex(int count){
    while(is_puzzle_solved() != 0 && count > 0){
        solution1_basic(5);
        locked_canidate(0);

        count = count - 1;
    }
} /* END solution2_complex*/

void take_notes(){
    int square_row, square_col;
    int num_check[PUZZLE_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int number_filled = 0;
    
    for(int row = 0; row < PUZZLE_SIZE; row++){/*LOOP2*/
        for(int col = 0; col < PUZZLE_SIZE; col++){/*LOOP3*/
        /*for every square we need to check row, col and square*/
            /*check that it's empty*/
            if ( puzzle[row][col] == 0){
                for(int i = 0; i < PUZZLE_SIZE; i++) num_check[i] = 1;

                /*check its row*/
                for ( int check_col = 0; check_col < PUZZLE_SIZE; 
                                            check_col++ ){/*LOOP4*/
                    if ( puzzle[row][check_col] != 0 ){
                        num_check[ puzzle[row][check_col]-1 ] = 0;
                    }
                } /* END LOOP4 */

                /*check its col*/
                for ( int check_row = 0; check_row < PUZZLE_SIZE; 
                                            check_row++ ){ /*LOOP4*/
                    if ( puzzle[check_row][col] != 0 ){
                        num_check[ puzzle[check_row][col]-1 ] = 0;
                    }
                } /* END LOOP4 */

                /*check its square*/
                square_row = row/3; /*0, 1 or 2*/
                square_row = square_row*3; /*0, 3, 6*/

                square_col = col/3; /*0, 1 or 2*/
                square_col = square_col*3; /*0, 3, 6*/

                for( int check_row = square_row;
                        check_row < square_row + 3; check_row++){ /*LOOP4*/
                        
                    for( int check_col = square_col;
                        check_col < square_col + 3; check_col++){ /*LOOP5*/

                        if ( puzzle[check_row][check_col] != 0 ){
                            num_check[ 
                                puzzle[check_row][check_col]-1 ] = 0;
                        }
                    }/* END LOOP5 */
                } /* END LOOP4 */

                for(int i = 0; i < PUZZLE_SIZE; i++){
                    puzzle_notes[row][col][i] = num_check[i];
                }
            } /* END if */
            else{
                puzzle_notes[row][col][puzzle[row][col]-1] = 1;
            }

            // printf("\n");
            // printf("(%d, %d) > { %d, %d } = %d:\t",
            //         row, col, square_row, square_col, number_filled);
            // for (int i = 0; i < PUZZLE_SIZE; i++){
            //     printf("%d = %s; ", i+1, num_check[i] ? " true" : "false");
            // }
            // printf("\n");

        } /* END LOOP3 */
    } /* END LOOP2 */

    /*print notes*/
    // for ( int row = 0; row < PUZZLE_SIZE; row++ ){
    //     /*notes 1-3*/
    //     for ( int col = 0; col < PUZZLE_SIZE; col++ ){
    //         for ( int i = 0; i < 3; i++){
    //             if ( puzzle_notes[row][col][i] != 0 ) printf("%d ", i+1);
    //             else printf("- ");
    //         }
    //         printf("  ");
    //     }

    //     printf("\n");

    //     /*notes 4-6*/
    //     for ( int col = 0; col < PUZZLE_SIZE; col++ ){
    //         for ( int i = 3; i < 6; i++){
    //             if ( puzzle_notes[row][col][i] != 0 ) printf("%d ", i+1);
    //             else printf("- ");
    //         }
    //         printf("  ");
    //     }

    //     printf("\n");

    //     /*notes 7-9*/
    //     for ( int col = 0; col < PUZZLE_SIZE; col++ ){
    //         for ( int i = 6; i < 9; i++){
    //             if ( puzzle_notes[row][col][i] != 0 ) printf("%d ", i+1);
    //             else printf("- ");
    //         }
    //         printf("  ");
    //     }
    //     printf("\n\n");
    //     if( row%3 == 2 ) printf("\n");
    // }
}/* END take_notes() */

int contains_locked_canidate_n(int x, int y, int n){
    if( x%2 == 0){
        x = x/2;
        if( puzzle_notes[x][y][n] != 0){
            for( int j = 0; j < PUZZLE_SIZE; j++ ){
                if ( j < (y/3)*3 && j >= ((y/3)*3)+3 ){
                    if ( puzzle_notes[x][j][n] != 0){
                        return 1;
                    }
                }
            }
        }
    }
    else{
        x = (x-1)/2;
        if( puzzle_notes[y][x][n] != 0){
            for( int j = 0; j < PUZZLE_SIZE; j++ ){
                if ( j < (y/3)*3 && j >= ((y/3)*3)+3 ){
                    if ( puzzle_notes[j][x][n] != 0){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


void locked_canidate(int block){
    /*look for locked canidates then see if they are of use then move on*/
    if( block >= 9 ) return; //base

    int block_row = block/3;
    block_row = block_row*3;
    int block_col = (block%3)*3;

    take_notes();
    print_puzzle();

    /*check each row*/
    for( int row = block_row; row < block_row; row++ ){ /*LOOP1*/
        for( int col = block_col; col < block_col+3; col++){ /*LOOP2*/
            for(int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP3*/
                if(contains_locked_canidate_n(row*2, col, i) == 0){
                    for( int change_row = block_row; change_row < block_row+3;
                        change_row++){
                            if ( change_row != row){
                                for(int change_col = block_col;
                                        change_col < block_col+3; change_col++){
                                    
                                    puzzle_notes[change_row][change_col][i] = 0;
                                }
                            }
                        }
                }

            }/* END LOOP3 */
        }/* END LOOP2 */
    }/* END LOOP1 */
        
    /*check each col*/
    for( int col = block_col; col < block_col+3; col++ ){ /*LOOP1*/
        for( int row = block_row; row < block_row+3; row++){ /*LOOP2*/
            for(int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP3*/
                if(contains_locked_canidate_n((col*2)+1, row, i) == 0){
                    for( int change_col = block_col; change_col < block_col+3;
                        change_col++){
                            if ( change_col != col){
                                for(int change_row = block_row;
                                        change_row < block_row+3; change_row++){
                                    
                                    puzzle_notes[change_row][change_col][i] = 0;
                                }
                            }
                        }
                }

            }/* END LOOP3 */
        }/* END LOOP2 */
    }/* END LOOP1 */

    for( int row = block_row; row < block_row; row++ ){ /*LOOP1*/
        for( int col = block_col; col < block_col+3; col++){ /*LOOP2*/
            int count = 0;
            for(int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP3*/
                if( count < 1 && puzzle_notes[row][col][i] != 0 ) count++;
                else if (count >= 1 && puzzle_notes[row][col][i] != 0){
                    count++;
                    i = PUZZLE_SIZE;
                }
            }/* END LOOP3 */
            if ( count == 1 ){
                for( int i = 0; i < PUZZLE_SIZE; i++){
                    if( puzzle_notes[row][col][i] != 0) puzzle[row][col] = i+1;
                }
            } 
        }/* END LOOP2 */
    }/* END LOOP1 */

    /*if num_check has only 1 false mark that number in!!*/
    for ( int row = 0; row < PUZZLE_SIZE; row++ ){ /*LOOP1*/
        for ( int col = 0; col < PUZZLE_SIZE; col++ ){ /*LOOP2*/
            int c = 0;
            for (int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP3*/
                if (puzzle_notes[row][col][i] != 0 && c < 1){
                    c++;
                }
                else if (puzzle_notes[row][col][i] != 0 && c >= 1){
                    c++;
                    i = PUZZLE_SIZE;
                }
            } /*END LOOP3*/

            /*if there is 1 number left fill it into the square*/
            if (c == 1){
                for (int i = 0; i < PUZZLE_SIZE; i++){ /*LOOP3*/
                    if (puzzle_notes[row][col][i] != 0){
                        puzzle[row][col] = i + 1;
                    }
                } /* END LOOP3*/
            } /* END if */
        }/* END LOOP2*/
    }/* END LOOP1 */

    /*STEP*/
    locked_canidate(block+1); 
} /* END locked_canidate() */



/*MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN*/
int main(){
    /*VARIABLES*/
    time_t start, end;

    /*INTRODUCTION*/
    printf("***SUDOKU SOLVER***");

    /*Get Puzzle*/
    
    // for( int row = 1; row < (PUZZLE_SIZE+1); row++ ){ /*LOOP1*/
    //     for( int col = 1; col < (PUZZLE_SIZE+1); col++ ){ /*LOOP2*/
    //         print_puzzle();
    //         printf("Enter a number (1-9 or 0 for none) in box... \n");
    //         printf("\t Row: %d | Column: %d \nHERE: ", row, col);
    //         scanf("%d", &puzzle[row-1][col-1]);
    //     } /*END LOOP2*/
    // } /*END LOOP1*/
    print_puzzle();
    

    /*Timer Start*/
    start = clock();

    /*Solutions*/
    solution2_complex(50);

    /*Timer End*/
    end = clock();
    solution_time = (double)(end-start)/CLOCKS_PER_SEC;

    /*CONCLUSION*/
    printf("***RESULTS***\n");
    if ( is_puzzle_solved() == 0 ){
        print_puzzle();
        printf("Puzzle Solved!!!\n");
        printf("Solved in: %lf\n", solution_time);
    }
    else{
        print_puzzle();
        printf("Puzzle wasn't solved :(\n");
        printf("Timer: %lf\n", solution_time);
    }
    return 0;
} /* END int main() */