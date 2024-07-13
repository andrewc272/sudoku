#include <stdio.h>
#include <time.h>

/*VARIABLES*/
#define PUZZLE_SIZE 9

/*9x9 Matrix numbers 1-9 or "0" for empty*/
int puzzle[PUZZLE_SIZE][PUZZLE_SIZE] = 
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
float solution_time = 0.0;

/*METHOD DECLARATIONS*/
void print_puzzle();
int is_puzzle_solved();

/*METHODS*/
void print_puzzle(){
    printf("\n");
    for(int row = 0; row < PUZZLE_SIZE; row++){ /*LOOP1*/
        for( int col = 0; col < PUZZLE_SIZE; col++){ /*LOOP2*/
            if(puzzle[row][col] != 0) printf(" %d |", puzzle[row][col]);
            else printf("   |");
        }/*END LOOP2*/
        printf("\n------------------------------------\n");
    }/*END LOOP1*/
}/*END void print_puzzle()*/

int is_puzzle_solved(){
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

/*MAIN*/
int main(){
    /*VARIABLES*/
    time_t start, end;

    /*INTRODUCTION*/
    printf("***SUDOKU SOLVER***");

    /*Get Puzzle*/
    for( int row = 1; row < (PUZZLE_SIZE+1); row++ ){ /*LOOP1*/
        for( int col = 1; col < (PUZZLE_SIZE+1); col++ ){ /*LOOP2*/
            print_puzzle();
            printf("Enter a number (1-9 or 0 for none) in box... \n");
            printf("\t Row: %d | Column: %d \nHERE: ", row, col);
            scanf("%d", &puzzle[row-1][col-1]);
        } /*END LOOP2*/
    } /*END LOOP1*/

    /*Timer Start*/
    start = clock();

    /*Solutions*/
    

    /*Timer End*/
    end = clock();
    solution_time = (float)(end/CLOCKS_PER_SEC) - (start/CLOCKS_PER_SEC);

    /*CONCLUSION*/
    printf("***RESULTS***\n");
    if ( is_puzzle_solved() == 0 ){
        print_puzzle();
        printf("Puzzle Solved!!!\n");
        printf("Solved in: %f", solution_time);
    }
    else{
        printf("Puzzle wasn't solved :(\n");
        printf("Timer: %f\n", solution_time);
    }
    return 0;
} /* END int main() */