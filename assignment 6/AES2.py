
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from secrets import token_bytes

# Function to generate a random key for AES encryption
def generate_key():
    key = token_bytes(32)  # AES-256 uses a 32-byte key
    print(f"Generated AES Key (hex): {key.hex()}")
    return key

# Encrypt function
def encrypt(message, key):
    print("Starting encryption process...")
    cipher = AES.new(key, AES.MODE_CBC)  # Using CBC mode
    iv = cipher.iv  # Get the IV used for encryption
    print(f"Generated IV (Initialization Vector): {iv.hex()}")
    
    padded_text = pad(message.encode('utf-8'), AES.block_size)  # Padding the message
    print(f"Padded Message: {padded_text.hex()}")  # Print padded message in hex for clarity

    encrypted_text = cipher.encrypt(padded_text)  # Encrypt the padded message
    print(f"Encrypted Block (hex): {encrypted_text.hex()}")

    # Combine IV and encrypted text for the final output
    final_output = iv + encrypted_text
    return final_output

# Main interactive function
if __name__ == "__main__":
    print("Do you want to (1) Encrypt or (2) Decrypt?")
    choice = input("Enter 1 for Encrypt, 2 for Decrypt: ")

    if choice == "1":
        # Encrypt option
        key = generate_key()
        message = input("Enter the message to encrypt: ")
        final_encrypted_message = encrypt(message, key)
        print(f"\nFinal Encrypted Message (hex): {final_encrypted_message.hex()}")

    # Decryption code can be added here if needed
