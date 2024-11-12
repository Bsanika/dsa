
#include <bits/stdc++.h>
using namespace std;
#define SIZE 30

// Convert all characters of a string to lowercase
void toLowerCase(char plain[], int ps) {
    for (int i = 0; i < ps; i++) {
        if (plain[i] > 64 && plain[i] < 91)
            plain[i] += 32;
    }
}

// Remove all spaces in a string
int removeSpaces(char* plain, int ps) {
    int count = 0;
    for (int i = 0; i < ps; i++)
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    plain[count] = '\0';
    return count;
}

// Generate the 5x5 key square
void generateKeyTable(char key[], int ks, char keyT[5][5]) {
    int dicty[26] = { 0 };

    for (int i = 0; i < ks; i++) {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }
    dicty['j' - 97] = 1;

    int i = 0, j = 0;
    for (int k = 0; k < ks; k++) {
        if (dicty[key[k] - 97] == 2) {
            dicty[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
    for (int k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    // Print the key table in matrix format
    cout << "Key Table (5x5):" << endl;
    for (int m = 0; m < 5; m++) {
        for (int n = 0; n < 5; n++) {
            cout << keyT[m][n] << " ";
        }
        cout << endl;
    }
}

// Search for the characters of a digraph in the key square and return their position
void search(char keyT[5][5], char a, char b, int arr[]) {
    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            } else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// Function to find the modulus with 5
int mod5(int a) {
    return (a < 0) ? (a + 5) % 5 : a % 5;
}

// Function to encrypt the plaintext
void encrypt(char str[], char keyT[5][5], int ps) {
    int a[4];
    cout << "Digraph pairs during encryption:" << endl;

    // Create digraphs and handle duplicates
    for (int i = 0; i < ps; i += 2) {
        // Handle duplicates by inserting 'x'
        if (i + 1 < ps && str[i] == str[i + 1]) {
            cout << str[i] << "x "; // Print the digraph pair
            str[i + 1] = 'x'; // Replace the duplicate with 'x'
            ps++; // Increase the size as we added 'x'
            i--; // Decrement i to stay at the current index
        } else if (i + 1 < ps) {
            cout << str[i] << str[i + 1] << " "; // Print the digraph pair
        } else {
            cout << str[i] << " "; // Handle the last single letter
        }

        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[2]][mod5(a[3] + 1)];
        } else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
    cout << endl; // New line after pairs
}

// Function to decrypt the ciphertext
void decrypt(char str[], char keyT[5][5], int ps) {
    int a[4];
    cout << "Digraph pairs during decryption:" << endl;
    for (int i = 0; i < ps; i += 2) {
        cout << str[i] << str[i + 1] << " "; // Print the digraph pair
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] - 1)];
            str[i + 1] = keyT[a[2]][mod5(a[3] - 1)];
        } else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] - 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] - 1)][a[1]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
    cout << endl; // New line after pairs
}

// Function to call encryption
void encryptByPlayfairCipher(char str[], char key[]) {
    char keyT[5][5];
    int ps = strlen(str);
    int ks = strlen(key);

    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);

    // Create digraphs, adding 'x' for odd length
    if (ps % 2 != 0) {
        str[ps++] = 'x'; // Add 'x' to handle odd length
        str[ps] = '\0';
    }

    generateKeyTable(key, ks, keyT);
    encrypt(str, keyT, ps);
}

// Function to call decryption
void decryptByPlayfairCipher(char str[], char key[]) {
    char keyT[5][5];
    int ps = strlen(str);
    int ks = strlen(key);

    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);

    generateKeyTable(key, ks, keyT);
    decrypt(str, keyT, ps);

    // Remove the padding 'x' if it was added during encryption
    if (ps > 1 && str[ps - 1] == 'x') {
        str[ps - 1] = '\0';
    }
}

// Function to create digraphs from plaintext
void createDigraphs(char str[], int& ps) {
    int i = 0;
    char temp[SIZE];
    int j = 0;

    while (i < ps) {
        // Check for identical consecutive letters
        if (i + 1 < ps && str[i] == str[i + 1]) {
            temp[j++] = str[i];   // Add first letter
            temp[j++] = 'x';      // Insert 'x'
            i++;                  // Skip to next letter
        } else if (i + 1 < ps) {
            temp[j++] = str[i];   // Add first letter
            temp[j++] = str[i + 1]; // Add second letter
            i += 2;               // Move past both letters
        } else {
            temp[j++] = str[i];   // Add last single letter
            i++;
        }
    }

    // Update original string
    for (int k = 0; k < j; k++) {
        str[k] = temp[k];
    }
    str[j] = '\0'; // Null terminate the new string
    ps = j; // Update size
}

int main() {
    char str[SIZE], key[SIZE];
    int choice;

    cout << "Playfair Cipher - Encrypt/Decrypt\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice (1/2): ";
    cin >> choice;

    cout << "Enter the key: ";
    cin.ignore(); // Clear newline from input buffer
    cin.getline(key, SIZE);

    cout << "Enter the plaintext/ciphertext: ";
    cin.getline(str, SIZE);

    int ps = strlen(str);
    
    if (choice == 1) {
        createDigraphs(str, ps);
        encryptByPlayfairCipher(str, key);
        cout << "Ciphertext: " << str << endl;
    } else if (choice == 2) {
        decryptByPlayfairCipher(str, key);
        cout << "Decrypted text: " << str << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}


/*Playfair Cipher - Encrypt/Decrypt
1. Encrypt
2. Decrypt
Enter your choice (1/2): 1
Enter the key: sanika
Enter the plaintext/ciphertext: tree is good
Key Table (5x5):
s a n i k
b c d e f
g h l m o
p q r t u
v w x y z
Digraph pairs during encryption:
tr ex ei sg ox od
Ciphertext: utdymebplzlf*/