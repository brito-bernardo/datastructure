#include <iostream>

void bubbleSort(int a[], int t)
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < (5-i-1); ++j)
        {
            if (t == 1)
            {
                if (a[j] > a[j+1])
                {
                    int temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }
            else
            {
                if (a[j] < a[j+1])
                {
                    int temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }

        }
    }
}


int main()
{
    int myarr[5];
    int type;
    std::cout << "Enter 5 integers in any order: " << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cin >> myarr[i];
    }

    std::cout << "Choose how you want to order" << std::endl;
    std::cout << "1. Ascending" << std::endl;
    std::cout << "2. Descending" << std::endl;
    std::cin >> type;


    std::cout << "Before sorting" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << myarr[i] << " ";
    }
    bubbleSort(myarr, type);

    std::cout << std::endl << "After sorting" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << myarr[i] << " ";
    }
    return 0;
}
