#include <bits/stdc++.h> 
using namespace std;

// Function for extended Euclidean Algorithm 
int gcdExtended(int a, int b, int *x, int *y) { 
    // Base Case 
    if (a == 0) 
    { 
        *x = 0; 
        *y = 1; 
        return b; 
    } 
    int x1, y1; // To store results of recursive call 
    int gcd = gcdExtended(b%a, a, &x1, &y1); 
    // Update x and y using results of 
    // recursive call 
    *x = y1 - (b/a) * x1; 
    *y = x1; 
    return gcd; 
} 

// Driver Code
int main() { 
    int x, y;
    // a = 35, b = 15; 
    int a,b;
    cout<<"enter a and b:";
    cin>>a>>b;
    int g = gcdExtended(a, b, &x, &y); 
    cout << "GCD(" << a << ", " << b << ") = " << g << endl;
    return 0; 
} 

/*Input:
enter a and b: 48 18
Output:
GCD(48, 18) = 6*/

/*Input:
enter a and b: 101 103
Output:
GCD(101, 103) = 1*/

/*Input:
enter a and b: 56 98
Output:
GCD(56, 98) = 14*/