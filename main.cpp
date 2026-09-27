#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>

using namespace std;

using VV = vector<vector<int>>;
using V = vector<int>;
int On = 0;

void print_matrix(VV matrix, string row_prefix = " ") {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            cout << row_prefix << setw(3) << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void print_4quater(VV matrix_a, VV matrix_b, VV matrix_c, VV matrix_d){
    int sz = matrix_a.size();
    for(int i = 0; i < sz * 2; ++i){
        for(int j = 0; j < sz * 2; ++j){
            int v;
            if      (i <  sz && j <  sz) v = matrix_a[i][j];
            else if (i <  sz && j >= sz) v = matrix_b[i][j - sz];
            else if (i >= sz && j <  sz) v = matrix_c[i - sz][j];
            else                         v = matrix_d[i - sz][j - sz];

            cout << ' ' << setw(3) << v << ' ';
        }
        cout << '\n';
    }
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

bool is_pow10(int x) {
    if (x <= 0) return false;
    while (x % 10 == 0) x /= 10;
    return x == 1;
}

VV multiply_matrix(VV matrix_x, VV matrix_y){
    int sz = matrix_x.size();
    VV new_matrix = VV(sz, V(sz,0));

    for(int i = 0; i < sz; ++i){
        for(int j = 0; j < sz; ++j){
            for(int k = 0; k < sz; ++k){
                int a = matrix_x[i][k];
                int b = matrix_y[k][j];
                new_matrix[i][j] += (a * b);
                if(!is_pow10(a) && !is_pow10(b)){
                    ++On;
                }
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
    cout << "Matrix  D0:\n";
    print_matrix(matrix_D0);
    VV matrix_D1 = multiply_matrix(sub_matrix(matrix_A12, matrix_A22),sum_matrix(matrix_B21,matrix_B22));
    cout << "Matrix  D1:\n";
    print_matrix(matrix_D1);
    VV matrix_D2 = multiply_matrix(sub_matrix(matrix_A21, matrix_A11),sum_matrix(matrix_B11,matrix_B12));
    cout << "Matrix  D2:\n";
    print_matrix(matrix_D2);
    VV matrix_D3 = multiply_matrix(sum_matrix(matrix_A11, matrix_A12), matrix_B22);
    cout << "Matrix  D3:\n";
    print_matrix(matrix_D3);
    VV matrix_D4 = multiply_matrix(matrix_A11, sub_matrix(matrix_B12, matrix_B22));
    cout << "Matrix  D4:\n";
    print_matrix(matrix_D4);
    VV matrix_D5 = multiply_matrix(matrix_A22, sub_matrix(matrix_B21, matrix_B11));
    cout << "Matrix  D5:\n";
    print_matrix(matrix_D5);
    VV matrix_D6 = multiply_matrix(sum_matrix(matrix_A21, matrix_A22), matrix_B11);
    cout << "Matrix  D6:\n";
    print_matrix(matrix_D6);

    VV first_quater = sum_matrix(sub_matrix(sum_matrix(matrix_D0, matrix_D1), matrix_D3), matrix_D5);
    VV second_quater = sum_matrix(matrix_D3, matrix_D4);
    VV third_quater = sum_matrix(matrix_D5, matrix_D6);
    VV fourth_quater = sum_matrix(matrix_D0, sum_matrix(matrix_D2, sub_matrix(matrix_D4, matrix_D6)));

    print_4quater(first_quater, second_quater, third_quater, fourth_quater);

    cout << "L(4) = 7 * " << On << " + 40\n";
    cout << "L(4) = " << 7 * On + 40 << '\n';


    return 0;
}

