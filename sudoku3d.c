#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int***);
// Declare solveSudoku function
int solveSudoku(int***);

//Helper functions. You can define any functions that can help your solve the problem
int checkBox(int***, int);
int checkFull(int***, int);

/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!
*/
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

	// Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
	
	// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

	// Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}


void printSudoku(int*** arr){
	// This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions. 	
	
	// Your implementation here
	
	for(int l = 0; l < 3; l++){				//Sorry for using a lot of loops, but now I don't make the extra loops 3 times.
		for(int j = 0; j < 3; j++){			//J is row, I is Block, K is cell
			for(int i = 0; i < 3; i++){
				for(int k = 0; k < 3; k++){
					printf("%d ", *(*(*(arr+(i + ( l*3 )))+j)+k));
					//printf("%p ", (*(*(arr+(i + ( l*3 )))+j)+k));
				}
				if( i != 2){
					printf("| ");
				}
			}
			printf("\n");
		}
		if( l != 2){
			for(int z = 0; z < 21; z++){
				printf("-");
			}
			printf("\n");
		}
	}
	
	
}



int solveSudoku(int*** blocks){
	// This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
	// YOU MUST NOT USE ANY ARRAY NOTATION ([])!
	
	//Your implementation here
	int t = 0;
	t = findSpot(blocks);
	
	
	if(t >= 81){		//If t goes larger than scope, then it is solved.
		return 1;
	}
	
	int b = t / 9;
	int r = (t % 9) / 3;
	int c = (t % 9) % 3;
	
	
		for(int i = 1; i <= 9; i++){
			*(*(*(blocks + b)+r)+c) = i;
			if(checkFull(blocks, t)){
				*(*(*(blocks + b)+r)+c) = 0;
			}else{
				if(solveSudoku(blocks)){
					return 1;
				} else{
					*(*(*(blocks + b)+r)+c) = 0;
				}
			}
		}
		
	
	return 0;
}

int checkFull(int*** blocks, int t){
	int b = t / 9;
	int r = (t % 9) / 3;
	int c = (t % 9) % 3;
	int ht = b / 3;
	int vt = b % 3;
	
	for(int i = 0; i < 3; i++){				//Check block		
		for(int j = 0; j < 3; j++){			//I = Row, J = Cell
			if((*(*(*(blocks + b)+r)+c) == *(*(*(blocks + b)+i)+j)) && !(i== r && j== c)){ 	//If two different cells in a block == each other, 
				return 1;																	//and cell_check != cell_checking
			}
		}
	}
	
	for(int i = 0; i < 3; i++){				//Horizontal check
		for(int j = 0; j < 3; j++){			//I (after calculations) = block offset, j = cell
			if(!(b == (ht * 3 + i))){
				if( 	(*(*(*(blocks + b)+r)+c) == (*(*(*(blocks + (ht * 3 + i))+r)+j)))	&& !((ht * 3 + i) == b && j == c) 	){	//If two numbers horizonally are the same
					return 1;																										//And not == itself then return 1
				}
			}
		}
		
	}
	
	for(int i = 0; i < 3; i++){				//Vertical Check
		for(int j = 0; j < 3; j++){			//I (After calculations)= Block offset, j = row
			if(!(b == (vt + 3 * i))){
				if(		(*(*(*(blocks + b)+r)+c) == (*(*(*(blocks + (vt + 3 * i))+j)+c)))	&& !((vt + 3 * i) == b && j == r) ){	//If two numbers vertically are =
					return 1;																										//And not == itself
				}
			}
		}
	}
	
	
	
	return 0;
}

int findSpot(int*** blocks){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				if(*(*(*(blocks + i)+j)+k) == 0){
					return (i*9) + (j*3) + (k);
				}
			}
		}
	}
	return 81;
}