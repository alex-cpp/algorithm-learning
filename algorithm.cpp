// algorithm.cpp

#include <iostream>   /// for IO operations

// find the common in the 2 sorted array
void FindCommon(int* a, int* b, int n)
{
    int i = 0;
    int j = 0;

    while (i < n && j < n)
    {
        if (a[i] < b[j])
            ++i;
        else if (a[i] == b[j])
        {
            std::cout << a[i] << std::endl;
            ++i;
            ++j;
        }
        else// a[i] > b[j]
            ++j;
    }
}


void testFindCommon() {
    int N = 5;
    int a[] = { 0, 1, 2, 3, 4 };
    //int b[] = { 1, 3, 5, 7, 9 };
    int b[] = { 1, 3, 5, 7, 9 };

    std::cout << "\n The common is : ";
    FindCommon(a, b, N);

}