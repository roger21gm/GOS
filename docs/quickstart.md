## Nonogram

Nonograms, also known as Picross or Griddlers, are image logic puzzles in which cells in a grid must be colored or blank according to the numbers on the side of the grid to reveal a hidden image. In this type of puzzle, numbers are a form of discrete tomography that measures the number of continuous lines of filled-in squares there are in any given row or column. For example, a track of "4 8 3" would mean that there are sets of four, eight, and three filled squares, in that order, with at least one blank square between successive groups.

![](https://i.imgur.com/QRd1Rre.png)

We can encode *nonograms* with ***BUP*** using the following parameters and variables defined in the `viewpoint` block:
```
viewpoint:
    param int rowSize;
    param int colSize;
    param int maxNonos;

    param int rowNonos[rowSize][maxNonos];
    param int colNonos[colSize][maxNonos];

    var x[rowSize][colSize];
    var hasStartedRow[rowSize][maxNonos][colSize];
    var hasStartedCol[colSize][maxNonos][rowSize];
```

- `rowSize` is the grid row size. 
- `colSize` is the grid column size.
- `maxNonos` is the maximum number of blocks that a column or a row could have
- `rowNonos` indicates the number of blocks and its sizes in each row.
- `colNonos` indicates the number of blocks and its sizes in each column. 
- `x` is the result board: `x[i][j]` will be true if and only if row `i`, column `j` is coloured and false otherwise.
- `hasStartedRow[i][b][j]` will be true if and only if block `b` of row `i` has already started in the column `j`.
- `hasStartedCol[j][b][i]` will be true if block `b` of column `j` has already started in the row `i`.

The constraints are the same applied over columns and over rows. The following constrains are those applied over rows:

- If a block of a row has started at column `i`, it also must have started in column `i+1`. 
```
//Order encoding
forall(i in 0..rowSize-1, b in 0..maxNonos-1){
    if(rowNonos[i][b] != 0){
        forall(j in 0..colSize-2){
            hasStartedRow[i][b][j] -> hasStartedRow[i][b][j+1];
        };
    }
    else{
        &&( [!hasStartedRow[i][b][j] | j in 0..colSize-1] );
    };
};
```
- A block mush have started soon enough to fit in the row.
```
forall(i in 0..rowSize-1, b in 0..maxNonos-1){
    if(rowNonos[i][b] != 0){
        hasStartedRow[i][b][colSize-rowNonos[i][b]];
    };
};
```
- `x[i][j]` must be `true` if it is colored.
```
//Channelling between hasStarted and x
forall(i in 0..rowSize-1, b in 0..maxNonos-1){
    if(rowNonos[i][b] != 0){
        forall(j in 0..colSize-1){
            if(j >= rowNonos[i][b]){
                x[i][j] <- hasStartedRow[i][b][j] & !hasStartedRow[i][b][j-rowNonos[i][b]]; 
            }
            else {
                x[i][j] <- hasStartedRow[i][b][j];
            };
        };
    };
};	
```
- The number of cells true in the row `i` must be the sum of the length of the blocks in row `i`.
```
forall(i in 0..rowSize-1){
    EK(x[i], sum(rowNonos[i]));
};	
```
- Block `b` must start before block `b+1`
```
forall(i in 0..rowSize-1, b in 0..maxNonos-2){
    if(rowNonos[i][b+1] != 0){
        forall(j in 0..colSize-1){
            if(j-rowNonos[i][b]-1 >= 0){
                hasStartedRow[i][b+1][j] -> hasStartedRow[i][b][j-rowNonos[i][b]-1];
            }
            else {
                !hasStartedRow[i][b+1][j];
            };
        };
    };
};	
```

![](https://i.imgur.com/yuXQwEG.png)



## Sudoku

Sudoku is a popular Japanese puzzle that is based on the logical placement of numbers. The goal of Sudoku is to fill in a 9×9 grid with digits so that each column, row, and 3×3 section contain the numbers between 1 to 9. At the beginning of the game, the 9×9 grid will have some of the squares filled in. Your job is to use logic to fill in the missing digits and complete the grid.

The mathematical model of the sudoku is the following:

##### Sets
***G** = Set of already placed numbers*
##### Variables
![](https://latex.codecogs.com/png.latex?%5Cdpi%7B120%7D%20%5Cfn_phv%20%5Clarge%20y_%7Bijk%7D%20%3D%20%5Cbegin%7Bcases%7D%201%2C%20%26%20%5Cmbox%7Bif%20%7D%5Cmbox%7B%20element%20%5Ctextit%7B%28i%2Cj%29%7D%20of%20the%20%5Ctextit%7Bn%7Dx%5Ctextit%7Bn%7D%20sudoku%20matrix%20contains%20the%20integer%20%5Ctextit%7Bk%7D%7D%20%5C%5C%200%2C%20%26%20%5Cmbox%7Belse%20%7D%5Cend%7Bcases%7D)
##### Constraints
- Only one *k* in each column  
![](https://latex.codecogs.com/png.latex?%5Cdpi%7B120%7D%20%5Cfn_phv%20%5Clarge%20%5Csum_%7Bi%3D1%7D%5E%7Bn%7Dy_%7Bijk%7D%20%3D%201%20%5Cqquad%20%5Cforall_%7Bi%2Cj%7D%20%5Cin%201..n)
- Only one *k* in each row  
![](https://latex.codecogs.com/png.latex?%5Cfn_phv%20%5Clarge%20%5Csum_%7Bj%3D1%7D%5E%7Bn%7Dy_%7Bijk%7D%20%3D%201%20%5Cqquad%20%5Cforall_%7Bi%2Cj%7D%20%5Cin%201..n)
- Only one *k* in each sub-matrix  
![](https://latex.codecogs.com/png.latex?%5Cfn_phv%20%5Clarge%20%5Csum_%7Bj%3Dmq-m&plus;1%7D%5E%7Bmq%7Dy_%7Bijk%7D%20%5Csum_%7Bi%3Dmq-m&plus;1%7D%5E%7Bmq%7Dy_%7Bijk%7D%20%3D%201%20%5Cqquad%20%5Cforall_%7Bk%7D%20%5Cin%201..n%20%5C%2C%2C%5C%2C%5Cforall_%7Bp%2Cq%7D%20%5Cin%201..m)
- Every poistion in the matrix must be filled once  
![](https://latex.codecogs.com/png.latex?%5Cfn_phv%20%5Clarge%20%5Csum_%7Bk%3D1%7D%5E%7Bn%7Dy_%7Bijk%7D%20%3D%201%20%5Cqquad%20%5Cforall_%7Bi%2Cj%7D%20%5Cin%201..n)
- Given elements G in matrix are set “on”  
![](https://latex.codecogs.com/png.latex?%5Cfn_phv%20%5Clarge%20y_%7Bijk%7D%20%3D%201%20%5Cqquad%20%5Cforall_%7Bi%2Cj%2Ck%7D%20%5Cin%20G)



A 9x9 sudoku can be modelled using **BUP** as:
```
viewpoint:
    var p[9][9][9];
    param int iniSudoku[9][9];

constraints:
    forall(i in 0..8, j in 0..8){
        EO(p[i][j][_]); // One value per cell
        AMO(p[i][_][j]); // Each value one time per row
        AMO(p[_][i][j]); // Each value one time per column
    };
    //Each value one time per block
    forall(i in [0,3,6], j in [0,3,6], k in 0..8){
        AMK([p[i+l][j+g][k] | l in 0..2, g in 0..2], 1);
    };
    //Initialize input fixed sudoku values.
    forall(i in 0..8, j in 0..8){
        if(iniSudoku[i][j] != 0){
            p[i][j][iniSudoku[i][j]-1];
        };
    };
    
output:
    "Sudoku solution: \n";
    [ k+1 ++ " " ++ ((j+1) % 3 == 0 ? " " : "") ++ (j==8 ? (i+1) % 3 == 0 ? "\n\n": "\n" : "") | i in 0..8, j in 0..8, k in 0..8 where p[i][j][k]];
```

And the following input parameters:
```
{
    "iniSudoku" : [
        [8, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 3, 6, 0, 0, 0, 0, 0],
        [0, 7, 0, 0, 9, 0, 2, 0, 0],
        [0, 5, 0, 0, 0, 7, 0, 0, 0],
        [0, 0, 0, 0, 4, 5, 7, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 3, 0],
        [0, 0, 1, 0, 0, 0, 0, 6, 8],
        [0, 0, 8, 5, 0, 0, 0, 1, 0],
        [0, 9, 0, 0, 0, 0, 4, 0, 0]
    ]
}
```

The solution obtained is:
```
c restarts 3
c decisions 490
c propagations 108196
c conflics 291
c stats 0;0;0.043765;-1;4536;11361;3;-1;-1;490;108196;291;-1;-1;
v 
s SATISFIABLE
Solució sudoku: 

8 1 2  7 5 3  6 4 9  
9 4 3  6 8 2  1 7 5  
6 7 5  4 9 1  2 8 3  

1 5 4  2 3 7  8 9 6  
3 6 9  8 4 5  7 2 1  
2 8 7  1 6 9  5 3 4  

5 2 1  9 7 4  3 6 8  
4 3 8  5 2 6  9 1 7  
7 9 6  3 1 8  4 5 2 
```


