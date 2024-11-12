#include<bits/stdc++.h>
using namespace std;

// k is size of num[] and rem[].  Returns the smallest
// number x such that:
//  x % num[0] = rem[0], 
//  x % num[1] = rem[1], 
//  ..................
//  x % num[k-2] = rem[k-1]
// Assumption: Numbers in num[] are pairwise coprime 
// (gcd for every pair is 1)
int findMinX(int num[], int rem[], int k)
{
    int x = 1; // Initialize result

    // As per the Chinese remainder theorem,
    // this loop will always break.
    while (true)
    {
        // Check if remainder of x % num[j] is 
        // rem[j] or not (for all j from 0 to k-1)
        int j;
        for (j=0; j<k; j++ )
            if (x%num[j] != rem[j])
               break;

        // If all remainders matched, we found x
        if (j == k)
            return x;

        // Else try next number
        x++;
    }

    return x;
}

// Driver method
// int main(void)
// {
//     int num[] = {3, 4, 5};
//     int rem[] = {2, 3, 1};
//     int k = sizeof(num)/sizeof(num[0]);
//     cout << "x is " << findMinX(num, rem, k);
//     return 0;
// }

int main(void)
{
    int k;
    
    // Get input for the number of equations
    cout << "Enter the number of equations: ";
    cin >> k;

    int num[k], rem[k];

    // Input the divisors (num[]) and the remainders (rem[])
    cout << "Enter the divisors (space-separated): ";
    for (int i = 0; i < k; i++) {
        cin >> num[i];
    }

    cout << "Enter the remainders (space-separated): ";
    for (int i = 0; i < k; i++) {
        cin >> rem[i];
    }

    // Calculate and display the result using the findMinX function
    cout << "x is " << findMinX(num, rem, k) << endl;

    return 0;
}
/*Enter the number of equations: 2
Enter the divisors (space-separated): 7 5
Enter the remainders (space-separated): 6 4
x is 34*/

/*Enter the number of equations: 3
Enter the divisors (space-separated): 3 4 5
Enter the remainders (space-separated): 2 3 1
x is 11*/