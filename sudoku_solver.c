#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*VARIABLES VARIABLES VARIABLES VARIABLES VARIABLES VARIABLES VARIABLES*/
#define PUZZLE_SIZE 9
#define BLOCK_SIZE PUZZLE_SIZE/3
#define PUZZLE_SQUARES PUZZLE_SIZE*PUZZLE_SIZE

/*9x9 Matrix numbers 1-9 or "0" for empty*/
int puzzle[PUZZLE_SIZE][PUZZLE_SIZE] = 
    {
        {7, 2, 1,   0, 0, 0,   0, 0, 8},
        {5, 0, 0,   1, 0, 8,   0, 7, 0},
        {0, 8, 0,   0, 7, 5,   6, 0, 0},

        {0, 5, 0,   0, 1, 0,   0, 8, 6},
        {8, 0, 0,   7, 0, 6,   0, 0, 5},
        {4, 0, 0,   5, 8, 0,   0, 9, 0},

        {0, 0, 8,   4, 5, 0,   0, 6, 0},
        {0, 7, 0,   8, 0, 9,   0, 0, 2},
        {0, 0, 5,   0, 0, 0,   8, 3, 0}
    };
int puzzle_notes[PUZZLE_SIZE][PUZZLE_SIZE][PUZZLE_SIZE];
double solution_time;


/*METHOD DECLARATIONS*/
void print_puzzle();
int is_puzzle_solved();
void strat1();
void strat2();
void strat3();
void take_notes();
void print_notes();
void fill_notes();


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
    for ( square_bottom_right[0] = BLOCK_SIZE; 
            square_bottom_right[0] <= PUZZLE_SIZE; 
            square_bottom_right[0] = square_bottom_right[0] + BLOCK_SIZE ){ 
        
        /*LOOP2 mark the far right row*/
        for (square_bottom_right[1] = BLOCK_SIZE; 
            square_bottom_right[1] <= PUZZLE_SIZE; 
            square_bottom_right[1] = square_bottom_right[1] + BLOCK_SIZE ){

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
void strat1(){ 
    int row, col;

    take_notes();

    for( int square = 0; square < PUZZLE_SQUARES; square++ ){
        //go to each sqaure
        row = square/PUZZLE_SIZE;
        col = square%PUZZLE_SIZE;

        int count = 0;

        //see how many notes there are
        for( int i = 0; i < PUZZLE_SIZE; i++){
            if ( puzzle_notes[row][col][i] != 0) count++;
        }

        if(count != 1);
        else{ //if there is just one mark it in!!
            for( int i = 0; i < PUZZLE_SIZE; i++){
                if ( puzzle_notes[row][col][i] != 0){
                    puzzle[row][col] = i+1;
                }
            }
        }
    }
} /* END strat1() */


void strat2(){
    int row, row_block, col, col_block;

    take_notes();

    for( int square = 0; square < PUZZLE_SQUARES; square++ ) {
        //go to each sqaure
        row = square/PUZZLE_SIZE;
        row_block = (row/3) * 3;

        col = square%PUZZLE_SIZE;
        col_block = (col/3) * 3;


        if( puzzle[row][col] != 0 );
        else{
        
            for ( int i = 0; i < PUZZLE_SIZE; i++ ){
                if( puzzle_notes[row][col][i] == 1 ){

                    int count = 0;

                    /*rows*/
                    for ( int j = 0; j < PUZZLE_SIZE; j++ ){
                        if ( j != row && puzzle_notes[j][col][i] != 0 ){
                            count++;
                        }
                    }

                    if( count == 0) puzzle[row][col] = i+1;
                    count = 0;

                    /*cols*/
                    for ( int j = 0; j < PUZZLE_SIZE; j++ ){
                        if ( j != col && puzzle_notes[row][j][i] != 0 ){
                            count++;
                        }
                    } 

                    if( count == 0) puzzle[row][col] = i+1;
                    count = 0;

                    /*blocks*/ 
                    for ( int j = 0; j < PUZZLE_SIZE; j++ ){
                        int j_row = (j/3) + row_block;
                        int j_col = (j%3) + col_block;

                        if ( j_row != row && j_col != col != 
                            puzzle_notes[row][j][i] != 0 ){

                            count++;
                        }
                    } 

                    if( count == 0) puzzle[row][col] = i+1;
                    count = 0;
                }
            }
        }
    }

    
} /* END strat2*/


/* Locked Canidate */
/*  1) is a certain number n noted in the cell
    2) is n noted elsewhere in adjacent cells
    3) if it is all other squares in the original cell's block
            cannot be n
    Cell - three horizontal or vertical squares that are within
            the same block and row/col*/
void strat3(){
    int block_row, cell_row, block_col, cell_col;

    take_notes();
    print_notes();

    for( int i = 0; i < PUZZLE_SIZE; i++){
        for (int j = 0; j < PUZZLE_SIZE*(BLOCK_SIZE); j++){
            /*horizontal cells*/
            cell_row = j%9;
            block_row = (cell_row/3) * 3;
            cell_col = (j%3) * 3;

            int count = 0;

            // Step 1
            for ( int k = 0; k < BLOCK_SIZE; k++ ){
                if ( puzzle_notes[cell_row][cell_col+k][i] != 0 ){
                    count = 1;
                    k = BLOCK_SIZE;
                    printf("1: (%d, %d) contains %d\n", cell_row, cell_col+k, i+1);
                }   
            }

            // Step 2
            if ( count == 1 ){
                for( int k = 0; k < PUZZLE_SIZE; k++ ){
                    if( (k < cell_col || k >= (cell_col+3) )
                        && puzzle_notes[cell_row][k][i] != 0 ){
                            count = 0;
                            k = PUZZLE_SIZE;
                        printf("2: (%d, %d) contains %d\n", cell_row, k, i+1);
                    }
                }
            }

            // Step 3
            if ( count == 1 ){
                printf("step 3 hit\n");
                for( int k = 0; k < PUZZLE_SIZE; k++ ){
                    int note_row = (k/3) + block_row;
                    int note_col = (k%3) + cell_col;

                    if( note_row != cell_row ){
                        puzzle_notes[note_row][note_col][i] = 0;
                    }
                }
            }

            printf("\n");

            /*vertical cells*/
            cell_row = (j/9) * 3;
            cell_col = j%9;
            block_col = (cell_col/3) * 3;

            count = 0;

            // Step 1
            for( int k = 0; k < BLOCK_SIZE; k++ ){
                if ( puzzle_notes[cell_row+k][cell_col][i] != 0 ){
                    count = 1;
                    k = BLOCK_SIZE;
                }
            }

            // Step 2
            if ( count == 1 ){
                for ( int k = 0; k < PUZZLE_SIZE; k++ ){
                    if ( ( k < cell_row || k >= cell_row+3 )
                        && puzzle_notes[k][cell_col][i] != 0 ){
                        
                        count = 0;
                        k = PUZZLE_SIZE;
                    }
                }
            }

            // Step 3
            if ( count == 1 ){
                for( int k = 0; k < PUZZLE_SIZE; k++){
                    int note_row = (k/3) + cell_row;
                    int note_col = (k%3) + block_col;

                    if( note_col != cell_col ){
                        puzzle_notes[note_row][note_col][i] = 0;
                    }
                }
            }            
        }
    }
} /* END strat3 */


void take_notes(){
    int row, row_block, col, col_block;
    
    for( int square = 0; square < PUZZLE_SQUARES; square++ )
    {/* Go through all of the squares*/
        /* get the row and col */
        row = square/PUZZLE_SIZE;
        row_block = (row/3) * 3;
        col = square%PUZZLE_SIZE;
        col_block = (col/3) * 3;


        if( puzzle[row][col] != 0 ){
            for ( int i = 0; i < PUZZLE_SIZE; i++ ){
                if ( i != puzzle[row][col]-1){
                    puzzle_notes[row][col][i] = 0;
                }
            }
        }
        else{

            /* for each square check its... */
            /* ...row */
            for ( int i = 0; i < PUZZLE_SIZE; i++ ){
                if ( i == col );
                else if ( puzzle[row][i] != 0 ){
                    puzzle_notes[row][col][puzzle[row][i]-1] = 0;
                }
            }

            /* ...col */
            for ( int i = 0; i < PUZZLE_SIZE; i++ ){
                if ( i == row );
                else if ( puzzle[i][col] != 0 ){
                    puzzle_notes[row][col][puzzle[i][col]-1] = 0;
                }
            }

            /* ...block*/
            for ( int i = 0; i < PUZZLE_SIZE; i++ ){
                
                int i_row = (i/3) + row_block;
                int i_col = (i%3) + col_block;

                if ( i_row == row && i_col == col);
                else if ( puzzle[i_row][i_col] != 0 ){
                    puzzle_notes[row][col][puzzle[i_row][i_col]-1] = 0;
                }
            }

        }
    }
}/* END take_notes() */

void print_notes(){
        /*print notes*/
    for(int i = 0; i < 73; i++) printf("-");
    printf("\n");
    for ( int row = 0; row < PUZZLE_SIZE; row++ ){
        printf("| ");
        /*notes 1-3*/
        for ( int col = 0; col < PUZZLE_SIZE; col++ ){
            for ( int i = 0; i < 3; i++){
                if ( puzzle_notes[row][col][i] != 0 ) printf("%d ", i+1);
                else printf("- ");
            }
            if( col%3 == 2 ) printf("| ");
            else printf("  ");
        }

        printf("\n| ");

        /*notes 4-6*/
        for ( int col = 0; col < PUZZLE_SIZE; col++ ){
            for ( int i = 3; i < 6; i++){
                if ( puzzle_notes[row][col][i] != 0 ) printf("%d ", i+1);
                else printf("- ");
            }
            if( col%3 == 2 ) printf("| ");
            else printf("  ");
        }

        printf("\n| ");

        /*notes 7-9*/
        for ( int col = 0; col < PUZZLE_SIZE; col++ ){
            for ( int i = 6; i < 9; i++){
                if ( puzzle_notes[row][col][i] != 0 ) printf("%d ", i+1);
                else printf("- ");
            }
            if( col%3 == 2 ) printf("| ");
            else printf("  ");
        }
        printf("\n| ");
        if( row%3 == 2 ){
            for(int i = 0; i < 71; i++) printf("-");
        } 
        printf("\n");
    }
}

void fill_notes(){
    for( int row = 0; row < PUZZLE_SIZE; row++ ){
        for( int col = 0; col < PUZZLE_SIZE; col++ ){
            for( int i = 0; i < PUZZLE_SIZE; i++ ){
                puzzle_notes[row][col][i] = 1;
            }
        }
    }
}


/*MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN*/
int main(){
    /*VARIABLES*/
    time_t start, end;
    int tries = 0;

    /*fill notes*/
    fill_notes();

    /*INTRODUCTION*/
    printf("***SUDOKU SOLVER***");
    print_puzzle();
    

    /*Timer Start*/
    start = clock();

    /*Solutions*/
    strat3();
    // while( is_puzzle_solved() != 0 && tries < 50 ){
    //     strat2();
    //     tries++;
    // }

    /*Timer End*/
    end = clock();
    solution_time = (double)(end-start)/CLOCKS_PER_SEC;

    print_notes();

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