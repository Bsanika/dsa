// C++ program to illustrate Rail Fence Cipher
// Encryption and Decryption
#include <bits/stdc++.h>
using namespace std;

// function to encrypt a message
string encryptRailFence(string text, int key)
{
	// create the matrix to cipher plain text
	// key = rows , length(text) = columns
	char rail[key][(text.length())];
	// filling the rail matrix to distinguish filled
	// spaces from blank ones
	for (int i=0; i < key; i++)
		for (int j = 0; j < text.length(); j++)
			rail[i][j] = '\n';
	// to find the direction
	bool dir_down = false;
	int row = 0, col = 0;
	for (int i=0; i < text.length(); i++)
	{
		// check the direction of flow
		// reverse the direction if we've just
		// filled the top or bottom rail
		if (row == 0 || row == key-1)
			dir_down = !dir_down;
		// fill the corresponding alphabet
		rail[row][col++] = text[i];
		// find the next row using direction flag
		dir_down?row++ : row--;
	}
	//now we can construct the cipher using the rail matrix
	string result;
	for (int i=0; i < key; i++)
		for (int j=0; j < text.length(); j++)
			if (rail[i][j]!='\n')
				result.push_back(rail[i][j]);

	return result;
}

// This function receives cipher-text and key
// and returns the original text after decryption
string decryptRailFence(string cipher, int key){
	// create the matrix to cipher plain text. key = rows , length(text) = columns
	char rail[key][cipher.length()];
	// filling the rail matrix to distinguish filled spaces from blank ones
	for (int i=0; i < key; i++)
		for (int j=0; j < cipher.length(); j++)
			rail[i][j] = '\n';
	// to find the direction
	bool dir_down;
	int row = 0, col = 0;
	// mark the places with '*'
	for (int i=0; i < cipher.length(); i++){
		// check the direction of flow
		if (row == 0)
			dir_down = true;
		if (row == key-1)
			dir_down = false;
		// place the marker
		rail[row][col++] = '*';
		dir_down?row++ : row--; // find the next row using direction flag
	}
	// now we can construct the fill the rail matrix
	int index = 0;
	for (int i=0; i<key; i++)
		for (int j=0; j<cipher.length(); j++)
			if (rail[i][j] == '*' && index<cipher.length())
				rail[i][j] = cipher[index++];
	// now read the matrix in zig-zag manner to construct the resultant text
	string result;
	row = 0, col = 0;
	for (int i=0; i< cipher.length(); i++){
		// check the direction of flow
		if (row == 0)
			dir_down = true;
		if (row == key-1)
			dir_down = false;
		// place the marker
		if (rail[row][col] != '*')
			result.push_back(rail[row][col++]);
		dir_down?row++: row--; // find the next row using direction flag
	}
	return result;
}
bool isValidInput(string str, bool allowUnderscore = false) {
    for (char c : str) {
        if (allowUnderscore && c == '_') {
            continue;
        }
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}
int main() {
    string msg;
    int choice, key;

    // Ask user if they want to encrypt or decrypt
    cout << "Enter 1 to encrypt or 0 to decrypt: ";
    cin >> choice;

    if (choice != 1 && choice != 0) {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    // Taking user input for message and key
    cout << "Enter the message: ";
    cin.ignore();
    getline(cin, msg); // to handle spaces in the message

    cout << "Enter the key (number of rails): ";
    cin >> key;

    // Check if the message is valid (allow spaces as they are part of Rail Fence cipher)
    if (!isValidInput(msg)) {
        cout << "Invalid input! The message should contain only alphabetic characters." << endl;
        return 0;
    }

    // Convert message to uppercase
    transform(msg.begin(), msg.end(), msg.begin(), ::toupper);

    if (choice == 1) {
        // Encrypt the message
        string cipher_text = encryptRailFence(msg, key);
        cout << "Encrypted Message: " << cipher_text << endl;
    } else {
        // Decrypt the message
        string original_msg = decryptRailFence(msg, key);
        cout << "Decrypted Message: " << original_msg << endl;
    }

    return 0;
}

