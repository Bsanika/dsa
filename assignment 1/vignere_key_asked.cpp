#include <bits/stdc++.h>
using namespace std;

// Function to generate the key in a cyclic manner
string generateKey(string str, string key) {
    int x = str.size();
    for (int i = 0;; i++) {
        if (key.size() == str.size())
            break;
        key.push_back(key[i % x]);
    }
    return key;
}

// Function to encrypt the plaintext using the key
string cipherText(string str, string key) {
    string cipher_text;
    for (int i = 0; i < str.size(); i++) {
        // converting in range 0-25
        char x = (str[i] + key[i]) % 26;
        // convert into alphabets(ASCII)
        x += 'A';
        cipher_text.push_back(x);
    }
    return cipher_text;
}

// Function to decrypt the ciphertext using the key
string originalText(string cipher_text, string key) {
    string orig_text;
    for (int i = 0; i < cipher_text.size(); i++) {
        // converting in range 0-25
        char x = (cipher_text[i] - key[i] + 26) % 26;
        // convert into alphabets(ASCII)
        x += 'A';
        orig_text.push_back(x);
    }
    return orig_text;
}

// Function to check if input contains only alphabetic characters
bool isValidInput(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

// Driver program to test the above function
int main() {
    string str, keyword;
    int choice;

    // Asking user if they want to encrypt or decrypt
    cout << "Enter 1 to encrypt or 0 to decrypt: ";
    cin >> choice;

    if (choice != 1 && choice != 0) {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    // Taking user input for text and keyword
    cout << "Enter the text: ";
    cin >> str;

    cout << "Enter the keyword: ";
    cin >> keyword;

    // Check if input is valid
    if (!isValidInput(str) || !isValidInput(keyword)) {
        cout << "Invalid input! Text and keyword should contain only alphabetic characters." << endl;
        return 0;
    }

    // Convert both text and keyword to uppercase
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);

    // Generate the key based on the length of the input text
    string key = generateKey(str, keyword);

    if (choice == 1) {
        // Encrypt the plaintext
        string cipher_text = cipherText(str, key);
        cout << "Ciphertext: " << cipher_text << "\n";
    } else {
        // Decrypt the ciphertext
        string decrypted_text = originalText(str, key);
        cout << "Decrypted Text: " << decrypted_text << "\n";
    }

    return 0;
}

/*Enter 1 to encrypt or 0 to decrypt: 1
Enter the text: sanika
Enter the keyword: ram
Ciphertext: JAZZKM*/