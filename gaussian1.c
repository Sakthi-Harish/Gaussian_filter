#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define smooth_kernel_size 5
#define sigma 1.0
#define K  1

#define WIDTH1 480
#define WIDTH2 360

using namespace std;


void convolution_2D(int N[WIDTH1][WIDTH2], double M[smooth_kernel_size][smooth_kernel_size], int P[WIDTH1][WIDTH2]) {

    // find center position of kernel (half of kernel size)
    int kCenterX = smooth_kernel_size / 2;
    int kCenterY = smooth_kernel_size / 2;

    for (int i = 0; i < WIDTH1; ++i)              // rows
    {
        for (int j = 0; j < WIDTH2; ++j)          // columns
        {
            for (int m = 0; m < smooth_kernel_size; ++m)     // kernel rows
            {
                //int mm = MASK_WIDTH1 - 1 - m;      // row index

                for (int n = 0; n < smooth_kernel_size; ++n) // kernel columns
                {
                    //int nn = MASK_WIDTH2 - 1 - n;  // column index

                    // index of input signal, used for checking boundary
                    int ii = i + (m - kCenterY);
                    int jj = j + (n - kCenterX);

                    // ignore input samples which are out of bound
                    if (ii >= 0 && ii < WIDTH1 && jj >= 0 && jj < WIDTH2)
                        P[i][j] += N[ii][jj] * M[m][n];
                }
            }
        }
    }
}
int main() {

    int image[WIDTH1][WIDTH2]; // have to get some image
    int output[WIDTH1][WIDTH2]; //have to get some outtput
    double gauss[smooth_kernel_size][smooth_kernel_size];
    double sum = 0;
    int i, j;

    ifstream fp("img.txt");
    if (! fp) {
        cout << "Error, file couldn't be opened" << endl; 
        return 1; 
    }    
    for(int row = 0; row < WIDTH1; row++) {  // stop loops if nothing to read
        for(int column = 0; column < WIDTH2; column++){
                fp >> image[row][column];
                output[row][column] = 0;
                if ( ! fp ) {
                cout << "Error reading file for element " << row << "," << column << endl; 
                return 1; 
                }
            }
    }

    for (i = 0; i < smooth_kernel_size; i++) {
        for (j = 0; j < smooth_kernel_size; j++) {
            double x = i - (smooth_kernel_size - 1) / 2.0;
            double y = j - (smooth_kernel_size - 1) / 2.0;
            gauss[i][j] = K * exp(((pow(x, 2) + pow(y, 2)) / ((2 * pow(sigma, 2)))) * (-1));
            sum += gauss[i][j];
        }
    }
    for (i = 0; i < smooth_kernel_size; i++) {
        for (j = 0; j < smooth_kernel_size; j++) {
            gauss[i][j] /= sum;
        }
    }
    for (i = 0; i < smooth_kernel_size; i++) {
        for (j = 0; j < smooth_kernel_size; j++) {
            //printf("%f ", gauss[i][j]);
        }
        //printf("\n");
    }


    convolution_2D(image,gauss, output);

    for(int row = 0; row < WIDTH1; row++) {  // stop loops if nothing to read
        for(int column = 0; column < WIDTH2; column++){
                cout<<output[row][column]<<" ";
            }
            cout<<"\n";
    }
    return 0;
}