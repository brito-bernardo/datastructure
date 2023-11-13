#include <iostream>

int binarySearch(int arr[],int left, int right, int x)
{
    while(left <= right){
        int mid = left + (right-left)/2;
        if(arr[mid] == x)
        {
            return mid;
        }
        else if (arr[mid] < x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int num;
    int myarr[10];
    int output;

    std::cout << "Enter 10 integers in ASCENDING order" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cin >> myarr[i]  ;
    }

    std::cout << "Enter one number that you want to search in the array: " << std::endl;
    std::cin >> num;
    output = binarySearch(myarr,0,9,num);

    if(output == -1)
    {
        std::cout << "No match found" << std::endl;
    }
    else
    {
        std::cout << "Match found at index position: " << output << std::endl;
    }

    return 0;
}
