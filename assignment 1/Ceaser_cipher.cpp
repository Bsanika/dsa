#include <iostream>
using namespace std;
// Function to encrypt the plaintext
string encrypt(string text, int s) {
    string result = "";
    // Traverse the text
    for (int i = 0; i < text.length(); i++) {
        // Encrypt uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i] + s - 65) % 26 + 65);
        // Encrypt lowercase letters
        else if (islower(text[i]))
            result += char(int(text[i] + s - 97) % 26 + 97);
        else
            result += text[i]; // Leave non-alphabet characters as is
    }

    return result;
}
// Function to decrypt the ciphertext
string decrypt(string text, int s) {
    string result = "";
    // Traverse the text
    for (int i = 0; i < text.length(); i++) {
        // Decrypt uppercase letters
        if (isupper(text[i]))
            result += char((int(text[i] - s - 65) + 26) % 26 + 65);
        // Decrypt lowercase letters
        else if (islower(text[i]))
            result += char((int(text[i] - s - 97) + 26) % 26 + 97);
        else
            result += text[i]; // Leave non-alphabet characters as is
    }

    return result;
}

// Driver program to test the above functions
int main() {

    cout<<"Enter 1 to encrypt and 0 to dycrypt: "<<endl;
    int a;
    cin>>a;
    if(a == 1){
        string text;
        cout<<"enter text: ";
        cin>>text;
        int s;
        cout<<"enter shifting num: ";
        cin>>s;
        char ch = 'a';
        string encrypted = encrypt(text, s);
        cout << "Text: " << text << endl;
        cout << "Shift: " << s << endl;
        cout << "Encrypted: " << encrypted << endl;
    }else if(a == 0){
        string text;
        cout<<"enter text: ";
        cin>>text;
        int s;
        cout<<"enter shifting num: ";
        cin>>s;

        string decrypted = decrypt(text, s);
        cout << "Decrypted: " << decrypted << endl;
    }else{
        cout<<"Invalid input."<<endl;
    }

    return 0;
}

/*Enter 1 to encrypt and 0 to dycrypt: 
1
enter text: sanika
enter shifting num: 1
Text: sanika
Shift: 1
Encrypted: tbojlb*/