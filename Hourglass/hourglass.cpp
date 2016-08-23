#include <vector>
#include <iostream>

using namespace std;


void extractHourGlasses(vector< vector<int> >& arr, int x, int y, int& oldSum) {
    vector< vector<int> > hourGlass(3, vector<int>(3));

    int start = 0, end = 2;

    if((x+2) >= 6)
        return;

    for(int arr_i = x, i = start; arr_i <= x+2; arr_i++, i++){
       for(int arr_j = y, j = start; arr_j <= y+2; arr_j++, j++){
            if(arr_i == x || arr_i == x+2)
                hourGlass[i][j] = arr[arr_i][arr_j];
            else if(arr_i == x+1 && arr_j == (y+1))
                hourGlass[i][j] = arr[arr_i][arr_j];
            else
                hourGlass[i][j] = 0;
        }
    }

    int sum = 0;
    for(int i = start; i <= end; i++){
       for(int j = start; j <= end; j++){
            sum += hourGlass[i][j];
        }
    }

    if(oldSum < sum) {
        oldSum = sum;
    }
}

int main(){
    vector< vector<int> > arr(6,vector<int>(6));
    for(int arr_i = 0;arr_i < 6;arr_i++) {
       for(int arr_j = 0;arr_j < 6;arr_j++) {
          cin >> arr[arr_i][arr_j];
       }
    }

    vector< vector<int> > hourGlass(3, vector<int>(3));
    int sum = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            extractHourGlasses(arr, i, j, sum);
        }
    }

    cout << sum;

    return 0;
}
