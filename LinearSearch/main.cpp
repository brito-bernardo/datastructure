#include <iostream>


void linearSearch(int array[], int n)
{
    int temp = -1;

    for (int i = 0; i < 5; ++i) {
        if (array[i] == n)
        {
            std::cout << "Element has been found at position: " << i << std::endl;
            temp = 0;
            break;
        }
    }
    if (temp == -1)
    {
        std::cout << "Element has not been found" << std::endl;
    }


}


int main() {

    int arr[5] = {1,5,6,7,2,};
    std::cout << "Please enter an element to search" << std::endl;
    int num;
    std::cin >> num;
    linearSearch(arr, num);



    return 0;
}
