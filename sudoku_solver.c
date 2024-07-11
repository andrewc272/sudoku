#import <stdio.h>

/*VARIABLES*/
/*9x9 Matrix numbers 1-9 or "0" for empty*/
int puzzle[9][9] = 
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
    for(int row = 0; row < sizeof(puzzle), row++){
        for( int col = 0; col < sizeof(puzzle[row])){
            if(puzzle[row][col] != 0) printf(" %d |", puzzle[row][col]);
            else printf("   |");
        }
        printf("\n------------------------------------\n");
    }
}

int is_puzzle_solved(){
    /*if the number is in the row, col, or square mark it by 0, 1 if not*/
    int all_nine_there[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    /*marks the current square we are looking at*/
    int current_numebr = 0;
    int square_bottom_right[2] = {0, 0}; /* {ROW, COL}*/

    /*check rows*/
    for( int row = 0; row < sizeof(puzzle), row++ ) {
        all_nine_there = {1, 1, 1, 1, 1, 1, 1, 1, 1}; 
        for( int col = 0; col < sizeof(puzzle[row]); col++ ){
            current_number = puzzle[row, col];
            if(current_number == 0) return 1;
            elif(all_nine_there[current_number - 1] != 0){
                all_nine_there[current_number - 1] = 0;
            }
            else return 1; 
        }
        for( int i = 0; i < sizeof(all_nine_there); i++ ){
            if ( all_nine_there[i] != 0 ) return 1;
        }
    }
    /*check cols*/
    for( int col = 0; col < sizeof(puzzle), col++ ) {
        all_nine_there = {1, 1, 1, 1, 1, 1, 1, 1, 1}; 
        for( int row = 0; row < sizeof(puzzle[col]); row++ ){
            current_number = puzzle[row, col];
            if(current_number == 0) return 1;
            elif(all_nine_there[current_number - 1] != 0){
                all_nine_there[current_number - 1] = 0;
            }
            else return 1; 
        }
        for( int i = 0; i < sizeof(all_nine_there); i++ ){
            if ( all_nine_there[i] != 0 ) return 1;
        }
    }


    /*check squares*/
    /*mark the bottom row*/
    for ( square_bottom_right[0] = 3; 
            square_bottom_right[0] <= 9; 
            square_bottom_right[0] = square_bottom_right[0] + 3 ){
        
        /*mark the far right row*/
        for (square_bottom_right[1] = 3; 
            square_bottom_right[1] <= 9; 
            square_bottom_right[1] = square_bottom_right[1] + 3 ){

            /*iterate through the last three rows*/
            for( int row = square_bottom_right[0] - 3; 
                    row < square_bottom_right[0], row++ ) {

                all_nine_there = {1, 1, 1, 1, 1, 1, 1, 1, 1};

                /*iterate through the last three columbs and check them*/ 
                for(int col = square_bottom_right[1] - 3; 
                    col < square_bottom_right[1], col++ ){

                    current_number = puzzle[row, col];
                    if(current_number == 0) return 1;
                    elif(all_nine_there[current_number - 1] != 0){
                        all_nine_there[current_number - 1] = 0;
                    }
                    return 1; 
                }
            }

            /*checking the square before moving*/
            for( int i = 0; i < sizeof(all_nine_there); i++ ){
                    if ( all_nine_there[i] != 0 ) return 1;
            }
        }
    }

    /*all clear*/
    return 0;
}

/*MAIN*/
int main(){
    /*INTRODUCTION*/
    printf("***SUDOKU SOLVER***");

    /*Get Puzzle*/
    for( int row = 1; row < (sizeof(puzzle)+1); row++ ){
        for( int col = 1; col < (sizeof(puzzle[row])+1); col++ ){
            print_puzzle();
            printf("Enter a number (1-9 or 0 for none) in box... \n");
            printf("\t Row: %d | Column: %d \nHERE: ", row, col);
            scanf("%d", &puzzle[row-1][col-1]);
        }
    }

    /*Solutions*/

    /*CONCLUSION*/
    printf("***RESULTS***\n");
    if ( is_puzzle_solved() == 0 ){
        print_puzzle();
        printf("Puzzle Solved!!!\n");
        printf("Solved in: %f", solution_time);
    }
    return 0;
}