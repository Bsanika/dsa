#include <iostream>
#include <vector>

using namespace std;

// Function to get the key matrix from the key string
void getKeyMatrix(string key, int keyMatrix[][3]) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

// Function to perform matrix multiplication
void matrixMultiplication(int a[3][3], int b[3][1], int result[3][1]) {
    for (int i = 0; i < 3; i++) {
        result[i][0] = 0;
        for (int j = 0; j < 3; j++) {
            result[i][0] += a[i][j] * b[j][0];
        }
        result[i][0] = result[i][0] % 26;
    }
}

// Function to find the inverse of a 3x3 matrix modulo 26
void findInverseMatrix(int keyMatrix[3][3], int inverseMatrix[3][3]) {
    int determinant = 0;
    for (int i = 0; i < 3; i++) {
        determinant += (keyMatrix[0][i] * (keyMatrix[1][(i + 1) % 3] * keyMatrix[2][(i + 2) % 3] - keyMatrix[1][(i + 2) % 3] * keyMatrix[2][(i + 1) % 3]));
    }
    determinant = determinant % 26;
    if (determinant < 0) determinant += 26;

    int multiplicativeInverse = 0;
    for (int i = 1; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            multiplicativeInverse = i;
            break;
        }
    }

    int adj[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adj[i][j] = ((keyMatrix[(j + 1) % 3][(i + 1) % 3] * keyMatrix[(j + 2) % 3][(i + 2) % 3]) - (keyMatrix[(j + 1) % 3][(i + 2) % 3] * keyMatrix[(j + 2) % 3][(i + 1) % 3]));
            adj[i][j] = (adj[i][j] % 26 + 26) % 26;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverseMatrix[i][j] = (multiplicativeInverse * adj[i][j]) % 26;
        }
    }
}

// Function to encrypt the message
void encrypt(string message, string key) {
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);
    int messageVector[3][1];
    for (int i = 0; i < 3; i++) {
        messageVector[i][0] = (message[i]) % 65;
    }
    int cipherMatrix[3][1];
    matrixMultiplication(keyMatrix, messageVector, cipherMatrix);
    string CipherText;
    for (int i = 0; i < 3; i++) {
        CipherText += cipherMatrix[i][0] + 65;
    }
    cout << "Encrypted Text: " << CipherText << endl;
}

// Function to decrypt the message
void decrypt(string cipherText, string key) {
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);
    int inverseMatrix[3][3];
    findInverseMatrix(keyMatrix, inverseMatrix);
    int cipherVector[3][1];
    for (int i = 0; i < 3; i++) {
        cipherVector[i][0] = (cipherText[i]) % 65;
    }
    int messageMatrix[3][1];
    matrixMultiplication(inverseMatrix, cipherVector, messageMatrix);
    string PlainText;
    for (int i = 0; i < 3; i++) {
        PlainText += messageMatrix[i][0] + 65;
    }
    cout << "Decrypted Text: " << PlainText << endl;
}

int main() {
    // string message = "ACT";
    // string key = "GYBNQKURP";

    // encrypt(message, key);

    // string cipherText = "POH";
    // decrypt(cipherText, key);

    cout<<"Enter 1 to encrypt and 0 to dycrypt: "<<endl;
    int a;
    cin>>a;
    if(a == 1){
        string text;
        cout<<"enter text of size 3: ";
        cin>>text;
        string s;
        cout<<"enter key of size 9: ";
        cin>>s;
        encrypt(text, s);
    }else if(a == 0){
        string text;
        cout<<"enter text of size 3: ";
        cin>>text;
        string s;
        cout<<"enter key of size 9: ";
        cin>>s;
        decrypt(text, s);
    }else{
        cout<<"Invalid input."<<endl;
    }


    return 0;
}

/*Enter 1 to encrypt and 0 to dycrypt: 
1
enter text of size 3: bat
enter key of size 9: walchands
Encrypted Text: HYH*/