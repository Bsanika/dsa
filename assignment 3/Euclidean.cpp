#include <bits/stdc++.h>
using namespace std;
// Function to return
// gcd of a and b
int gcd(int a, int b){
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
// Driver Code
int main(){
    int a,b;
    cout<<"enter a and b:";
    cin>>a>>b;
      // Function call
    cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << endl;
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