#include <iostream>
#include <vector>
int main() {
    std::cout << "Hello, World!" << std::endl;
    int array[10] = {1,2,3,4,5,6,7,8,9};
    std::vector<int*> intPointerVector;
    for(int i=0;i<10;i++){
        intPointerVector.push_back(array+i);
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}