#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>

using namespace std;

using VV = vector<vector<int>>;
using V = vector<int>;

void print_matrix(VV matrix, string row_prefix = " ") {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << row_prefix << setw(3) << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

VV sum_matrix(VV matrix_x, VV matrix_y){
    int sz = matrix_x.size();
    VV new_matrix = VV(sz, V(sz,0));

    for(int i = 0; i < sz; ++i){
        for(int j = 0; j < sz; ++j){
            new_matrix[i][j] = (matrix_x[i][j] + matrix_y[i][j]);
        }
    }
    return new_matrix;
}

VV sub_matrix(VV matrix_x, VV matrix_y){
    int sz = matrix_x.size();
    VV new_matrix = VV(sz, V(sz,0));

    for(int i = 0; i < sz; ++i){
        for(int j = 0; j < sz; ++j){
            new_matrix[i][j] = (matrix_x[i][j] - matrix_y[i][j]);
        }
    }
    return new_matrix;
}


VV multiply_matrix(VV matrix_x, VV matrix_y){
    int sz = matrix_x.size();
    VV new_matrix = VV(sz, V(sz,0));

    for(int i = 0; i < sz; ++i){
        for(int j = 0; j < sz; ++j){
            for(int k = 0; k < sz; ++k){
                new_matrix[i][j] += (matrix_x[i][k] * matrix_y[k][j]);
            }
        }
    }
    return new_matrix;
}

VV matrix_2x2(VV matrix_x, int x = 1, int y = 1){
    int sz = matrix_x.size();
    int sz2 = sz/2;
    VV new_matrix_2x2 = VV(sz2, V(sz2,0));
    if(x == 1){
        if(y == 1){
            for(int i = 0; i < sz2; ++i){
                for(int j = 0; j < sz2; ++j){
                    new_matrix_2x2[i][j] = matrix_x[i][j];
                }
            }
        }else{
            for(int i = 0; i < sz2; ++i){
                for(int j = 0; j < sz2; ++j){
                    new_matrix_2x2[i][j] = matrix_x[i][j+sz2];
                }
            }
        }
    }else{
        if(y == 1){
            for(int i = 0; i < sz2; ++i){
                for(int j = 0; j < sz2; ++j){
                    new_matrix_2x2[i][j] = matrix_x[i+sz2][j];
                }
            }
        }else{
            for(int i = 0; i < sz2; ++i){
                for(int j = 0; j < sz2; ++j){
                    new_matrix_2x2[i][j] = matrix_x[i+sz2][j+sz2];
                }
            }
        }
    }
    return new_matrix_2x2;
}


int main(){
    int n = 0;
    ifstream in("input.txt");
    if(in.is_open()){
        in >> n;
    }
    VV matrix_A = VV(n, V(n, 0));
    VV matrix_B = VV(n, V(n, 0));


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> matrix_A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> matrix_B[i][j];
        }
    }
    VV matrix_A11 = matrix_2x2(matrix_A, 1, 1);
    VV matrix_A12 = matrix_2x2(matrix_A, 1, 2);
    VV matrix_A21 = matrix_2x2(matrix_A, 2, 1);
    VV matrix_A22 = matrix_2x2(matrix_A, 2, 2);

    VV matrix_B11 = matrix_2x2(matrix_B, 1, 1);
    VV matrix_B12 = matrix_2x2(matrix_B, 1, 2);
    VV matrix_B21 = matrix_2x2(matrix_B, 2, 1);
    VV matrix_B22 = matrix_2x2(matrix_B, 2, 2);

    VV matrix_D0 = multiply_matrix(sum_matrix(matrix_A11, matrix_A22),sum_matrix(matrix_B11,matrix_B22));
    VV matrix_D1 = multiply_matrix(sub_matrix(matrix_A12, matrix_A22),sum_matrix(matrix_B21,matrix_B22));
    VV matrix_D2 = multiply_matrix(sub_matrix(matrix_A21, matrix_A11),sum_matrix(matrix_B11,matrix_B12));
    VV matrix_D3 = multiply_matrix(sum_matrix(matrix_A11, matrix_A12), matrix_B22);
    VV matrix_D4 = multiply_matrix(matrix_A11, sub_matrix(matrix_B12, matrix_B22));
    VV matrix_D5 = multiply_matrix(matrix_A22, sub_matrix(matrix_B21, matrix_B11));
    VV matrix_D6 = multiply_matrix(sum_matrix(matrix_A21, matrix_A22), matrix_B11);

    VV first_quater = sum_matrix(sub_matrix(sum_matrix(matrix_D0, matrix_D1), matrix_D3), matrix_D5);
    VV second_quater = sum_matrix(matrix_D3, matrix_D4);
    VV third_quater = sum_matrix(matrix_D5, matrix_D6);
    VV fourth_quater = sum_matrix(matrix_D0, sum_matrix(matrix_D2, sub_matrix(matrix_D4, matrix_D6)));

    print_matrix(first_quater);
    print_matrix(second_quater);
    print_matrix(third_quater);
    print_matrix(fourth_quater);


    return 0;
}
