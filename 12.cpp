#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

std::pair<int, int> findMin(const std::vector<int>& vec){
    if (vec.empty()) return {std::numeric_limits<int>::max(), -1};
    int mmin = vec[0];
    int index = 0;
    for(int i = 1; i < vec.size(); ++i){
        if (vec[i] < mmin){
            mmin = vec[i];
            index = i;
        }
    }
    return {mmin, index};
}

void bubbleSort(std::vector<int>& vec){
    for(int i = 0; i < vec.size() - 1; ++i){
        for(int j = vec.size() - 1; j > i; --j){
            if (vec[j] < vec[j-1]) {
                int temp = vec[j];
                vec[j] = vec[j-1];
                vec[j-1] = temp;
            }
        }
    }
}

int binarySearch(const std::vector<int>& vec, int target){
    int l = 0;
    int r = vec.size()-1;
    while(l <= r){
        int mid = (l+r)/2;
        if (vec[mid] == target) return mid;
        if (vec[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

std::tuple<int, int, int> findMin(const std::vector<std::vector<int>>& vec){
    if (vec.empty() || vec[0].empty()) return {std::numeric_limits<int>::max(), -1, -1};
    int mmin = vec[0][0];
    int indexi = 0;
    int indexj = 0;
    for(int i = 0; i < vec.size(); ++i){
        for(int j = 0; j < vec[i].size(); ++j){
            if (vec[i][j] < mmin){
                mmin = vec[i][j];
                indexi = i;
                indexj = j;
            }
        }
    }
    return {mmin, indexi, indexj};
}

void reverseVector(std::vector<int>& vec) {
    for(int i = 0, j = vec.size()-1; i <= j; ++i, --j){
        int temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }
}

void cyclicShift(std::vector<int>& vec, int positions) {
    positions %= vec.size();

    if (positions == 0) return;

    std::vector<int> temp(vec.size());

    for (int i = 0; i < vec.size(); ++i) {
        temp[i] = vec[(i + positions) % vec.size()];
    }

    vec = temp;
}

void replaceValue(std::vector<int>& arr, int oldValue, int newValue) {
    for (auto& value : arr) {
        if (value == oldValue) {
            value = newValue;
        }
    }
}

void calc(double udot, double u1, double u2, double N1, double N2 ){
    int S = 10;
    double V = (N1+N2)*log2(u1+u2);
    double Vdot = (2 + udot) * log2(2+udot);
    double Lgalka = (2/u1)*(u2/N2);
    std::cout << u1 * log2(u1) + u2*log2(u2) << std::endl;
    std::cout << Vdot << std::endl;
    std::cout << V << std::endl;
    std::cout << Vdot/V << std::endl;
    std::cout << Lgalka << std::endl;
    std::cout << (2/u1)*(u2/N2)*(N1+N2)*log2(u1+u2) << std::endl;
    std::cout << V*V/(S*Vdot) << std::endl;
    std::cout << (u1*N2*(u1*log2(u1)+u2*log2(u2))*log2(u1+u2))/(2*S*u2) << std::endl;
    std::cout << (u1*N2*(N1+N2)*log2(u1+u2))/(2*S*u2) << std::endl;
    std::cout << Lgalka*Lgalka*V << std::endl;
    std::cout << Vdot*Vdot/V << std::endl;

}

int main(){
    calc(3, 6, 4, 6, 6);
    return 0;
}