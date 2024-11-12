//input two prime numbers which are in range of 50 to 100
//61 67
//53 59
//walchand

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to calculate GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular inverse
int modInverse(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;
    while (new_r != 0) {
        int quotient = r / new_r;
        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
    if (r > 1) return -1;  // Inverse doesn't exist
    if (t < 0) t += phi;
    return t;
}

// Function to perform modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to generate RSA key pairs
pair<pair<int, int>, pair<int, int>> generate_keypair(int p, int q) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    srand(time(0));
    int e = rand() % (phi - 1) + 1;
    while (gcd(e, phi) != 1) {
        e = rand() % (phi - 1) + 1;
    }

    // Calculate d (modular inverse of e)
    int d = modInverse(e, phi);

    // Public key (e, n) and private key (d, n)
    return {{e, n}, {d, n}};
}

// Function to encrypt the message
vector<long long> encrypt(pair<int, int> public_key, string plaintext) {
    int e = public_key.first;
    int n = public_key.second;
    vector<long long> ciphertext;
    for (char ch : plaintext) {
        ciphertext.push_back(modExp((int)ch, e, n));
    }
    return ciphertext;
}

// Function to decrypt the message
string decrypt(pair<int, int> private_key, vector<long long> ciphertext) {
    int d = private_key.first;
    int n = private_key.second;
    string plaintext;
    for (long long ch : ciphertext) {
        plaintext += (char)modExp(ch, d, n);
    }
    return plaintext;
}

int main() {
    // Input two prime numbers
    int p, q;
    cout << "Enter the first prime number (p): ";
    cin >> p;
    cout << "Enter the second prime number (q): ";
    cin >> q;

    // Generate public and private keys
    auto keypair = generate_keypair(p, q);
    pair<int, int> public_key = keypair.first;
    pair<int, int> private_key = keypair.second;

    // Display the keys
    cout << "Public key: (" << public_key.first << ", " << public_key.second << ")" << endl;
    cout << "Private key: (" << private_key.first << ", " << private_key.second << ")" << endl;

    // Input plaintext message from user
    string message;
    cout << "Enter the message to encrypt: ";
    cin.ignore();  // To ignore any leftover newline characters in the buffer
    getline(cin, message);

    // Encrypt the message
    vector<long long> encrypted_message = encrypt(public_key, message);
    cout << "Encrypted message: ";
    for (long long ch : encrypted_message) {
        cout << ch << " ";
    }
    cout << endl;

    // Decrypt the message
    string decrypted_message = decrypt(private_key, encrypted_message);
    cout << "Decrypted message: " << decrypted_message << endl;

    return 0;
}

/*Enter the first prime number (p): 61
Enter the second prime number (q): 67
Public key: (1663, 4087)
Private key: (2767, 4087)
Enter the message to encrypt: walchand
Encrypted message: 1986 1102 3463 704 3789 1102 2171 2974
Decrypted message: walchand*/