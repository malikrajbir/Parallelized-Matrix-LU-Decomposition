
#include "include.h"

#include "commons.h"


/*
 * Swapping double pointed values.
 * @param _1, _2 (double *)
 */
void swap_d(double * _1, double * _2) {
    double _t = *_1;
    *_1 = *_2; 
    *_2 = _t;
}

/*
 * Swapping int pointed values.
 * @param _1, _2 (double *)
 */
void swap_i(int * _1, int * _2) {
    int _t = *_1;
    *_1 = *_2; 
    *_2 = _t;
}


/*
 * Swapping double pointed rows.
 * @param _1, _2 (double **)
 */
void swap_d_r(double ** _1, double ** _2) {
    double* _t = *_1;
    *_1 = *_2; 
    *_2 = _t;
}


/*
 * Ordered printing of a square-matrix.
 * @param _mat (double **): matrix
 * @param _sze (int): size of the matrix
 * @param _fd (file directory no.)
 */
void _print_sq(double **_mat, int _sze, int _fd) {
    char *s = (char *)malloc(10);
    for(int i=0; i<_sze; i++) {
        for(int j=0; j<_sze; j++) {
            sprintf(s, "%16.12lf", _mat[i][j]);
            write(_fd, s, 10);
        }
        write(_fd, "\n", 1);
    }
}


/*
 * Ordered printing of a square-matrix, keeping in mind the permutation.
 * @param _mat (vector<vector<double>>): matrix
 */
void __print_permute(double ** _mat, int * _p, int sze, int _fd) {
    int r;
    char *s = (char *)malloc(10);
    for(int i=0; i<sze; i++) {
        r = _p[i];
        for(int j=0; j<sze; j++) {
            sprintf(s, "%16.12lf", _mat[r][j]);
            write(_fd, s, 10);
        }
        write(_fd, "\n", 1);
    }
}

/*
 * Standard Matrix Multiplication.
 * @param (std::vector<std::vector<double>>&, std::vector<std::vector<double>>&): matrices involved
 * 
 * NOTE: Both matrices are assumed to be square and of the same order.
 */
void __matmul(double ** _1, double ** _2, double ** result, int size) {
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++){

            if(isnan(_1[i][j]))
                printf("L matrix %d %d \n",i,j);
            if(isnan(_2[i][j]))
                printf("U matrix %d %d \n",i,j);
            
            double temp = 0.0;
            for(int k=0; k<size; k++){
                temp += (_1[i][k] * _2[k][j]);
            }
            result[i][j] = temp;
        }
}

double checker(double **original, double ** result, int *p, int size, int _fd){
    double error = 0.0;
    int r;
    char *s = (char *)malloc(10);
    for(int i=0; i<size; i++){
        r=p[i];
        for(int j=0; j<size; j++){

            // sprintf(s, "%16.12lf",(original[r][j] - result[i][j]));
            // write(_fd, s, 10);
            int y = 0;
            if(isnan(original[r][j])){
                printf("original matrix %d %d \n",r,j);
                y=1;
            }
            
            if(isnan(result[i][j])){
                printf("Result %d %d \n",i,j);
                y=1;
            }
            if(y!=1)
            error += (original[r][j] - result[i][j]);
        }

        // write(_fd, "\n", 1);
    }
    return error;

}