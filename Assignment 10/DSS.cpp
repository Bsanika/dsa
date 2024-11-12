//23
//11
//5
//6
//walchand -valid
//23 11 2 6
//Hello -valid
//Test - invalid
#include <iostream>
#include <random>
#include <cassert>

using namespace std;

// Function to compute (base^exponent) % mod
int mod_exp(int base, int exponent, int mod) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) // If exponent is odd
            result = (result * base) % mod;
        base = (base * base) % mod; // Square the base
        exponent /= 2; // Divide the exponent by 2
    }
    return result;
}

// Function to compute gcd
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to compute modular inverse
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // If no modular inverse exists
}

// Main function for signing and verification
int main() {
    // DSA Parameters
    int p, q, g, x;

    // Taking inputs for DSA parameters and private key
    cout << "Enter the prime number p: ";
    cin >> p;
    cout << "Enter the prime divisor q: ";
    cin >> q;
    cout << "Enter the generator g: ";
    cin >> g;
    cout << "Enter your private key x: ";
    cin >> x;

    // Taking user input for the message
    string message;
    cout << "Enter the message to sign: ";
    cin.ignore(); // Clear the newline character from the buffer
    getline(cin, message);
    
    // Hash the message (simplified here, use a real hash in practice)
    int Hm = message.length(); // Example hash value (replace with a real hash function)

    // Generate random k
    int k;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, q - 1);
    do {
        k = dis(gen);
    } while (gcd(k, q) != 1); // Ensure k is coprime to q

    // Compute r
    int r = mod_exp(g, k, p) % q;

    // Check for r = 0
    if (r == 0) {
        cout << "Signature computation failed: r = 0" << endl;
        return 1; // If r = 0, fail
    }

    // Compute k inverse
    int k_inv = mod_inverse(k, q);
    if (k_inv == -1) {
        cout << "Signature computation failed: No modular inverse of k" << endl;
        return 1; // If no modular inverse exists, fail
    }

    // Compute s
    int s = (k_inv * (Hm + x * r)) % q;
    if (s == 0) {
        cout << "Signature computation failed: s = 0" << endl;
        return 1; // If s = 0, fail
    }

    // Print values for debugging
    cout << "k = " << k << ", r = " << r << ", s = " << s << endl;

    // Signature
    cout << "Signature: (r = " << r << ", s = " << s << ")" << endl;

    // Now, let's verify the signature
    // Check validity of r and s
    if (r <= 0 || r >= q || s <= 0 || s >= q) {
        cout << "The signature is invalid." << endl;
        return 1;
    }

    // Compute w
    int w = mod_inverse(s, q);
    if (w == -1) {
        cout << "Verification failed: No modular inverse of s" << endl;
        return 1; // If no modular inverse exists, fail
    }

    // Compute u1 and u2
    int u1 = (Hm * w) % q;
    int u2 = (r * w) % q;

    // Compute v
    int v = (mod_exp(g, u1, p) * mod_exp(mod_exp(g, x, p), u2, p)) % p; // where y = g^x mod p
    v = v % q;

    // Print intermediate values for debugging
    cout << "u1 = " << u1 << ", u2 = " << u2 << ", v = " << v << endl;

    // Compare v with r
    if (v == r) {
        cout << "The signature is valid" << endl;
    } else {
        cout << "The signature is Invalid." << endl;
    }

    return 0;
}


/*Enter the prime number p: 23
Enter the prime divisor q: 11
Enter the generator g: 5
Enter your private key x: 6
Enter the message to sign: walchand
k = 6, r = 8, s = 2
Signature: (r = 8, s = 2)
u1 = 4, u2 = 4, v = 8
The signature is valid*/