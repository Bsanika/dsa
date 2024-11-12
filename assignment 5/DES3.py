

from Crypto.Cipher import DES
from secrets import token_bytes

# Function to generate a random key for DES encryption
def generate_key():
    key = token_bytes(8)  # DES uses 8-byte (64-bit) keys
    print(f"Generated Key (in bytes): {key.hex()}")
    return key

# Function to pad the text to a multiple of 8 bytes (since DES works on 64-bit blocks)
def pad(text):
    print(f"Original message before padding: '{text}'")
    while len(text) % 8 != 0:
        text += '\x08'  # PKCS#7 padding
    print(f"Padded Message: {text.encode('utf-8')}")
    return text

# Encrypt function with roundwise output
def encrypt(message, key):
    print("Starting encryption process...")
    cipher = DES.new(key, DES.MODE_ECB)  # Using ECB mode for simplicity
    padded_text = pad(message)
    
    # Split the message into 8-byte (64-bit) blocks and encrypt each block
    encrypted_text = b''
    for i in range(0, len(padded_text), 8):
        block = padded_text[i:i + 8]
        encrypted_block = cipher.encrypt(block.encode('utf-8'))
        encrypted_text += encrypted_block
        print(f"Round {i // 8 + 1}: Block '{block}' -> Encrypted Block (in bytes): {encrypted_block.hex()}")

    return encrypted_text

# Decrypt function with roundwise output
def decrypt(encrypted_message, key):
    print("Starting decryption process...")
    cipher = DES.new(key, DES.MODE_ECB)  # Using ECB mode for simplicity
    
    # Split the encrypted message into 8-byte (64-bit) blocks and decrypt each block
    decrypted_text = ''
    for i in range(0, len(encrypted_message), 8):
        block = encrypted_message[i:i + 8]
        decrypted_block = cipher.decrypt(block).decode('utf-8')
        decrypted_text += decrypted_block
        print(f"Round {i // 8 + 1}: Encrypted Block (in bytes): {block.hex()} -> Decrypted Block '{decrypted_block.strip()}'")
    
    return decrypted_text.rstrip()

# Main interactive function
if __name__ == "__main__":
    print("Do you want to (1) Encrypt or (2) Decrypt?")
    choice = input("Enter 1 for Encrypt, 2 for Decrypt: ")

    if choice == "1":
        # Encrypt option
        # Generate a random key
        key = generate_key()

        # Get message input from user
        message = input("Enter the message to encrypt: ")

        # Encrypt the message
        encrypted_message = encrypt(message, key)
        print(f"\nFinal Encrypted Message (in bytes): {encrypted_message.hex()}")

    elif choice == "2":
        # Decrypt option
        # Get the key from the user
        key_input = input("Enter the key (in hex) used for encryption: ")
        key = bytes.fromhex(key_input)  # Convert input to bytes

        # Get the encrypted message from user
        encrypted_input = input("Enter the encrypted message (in hex): ")
        encrypted_message = bytes.fromhex(encrypted_input)  # Convert input to bytes

        # Decrypt the message
        decrypted_message = decrypt(encrypted_message, key)
        print(f"\nFinal Decrypted Message: '{decrypted_message}'")

    else:
        print("Invalid option selected!")
