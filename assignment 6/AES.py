from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

# Function to encrypt a message using AES
def aes_encrypt(message, key):
    cipher = AES.new(key, AES.MODE_CBC)  # CBC mode requires an IV (Initialization Vector)
    iv = cipher.iv  # Generate random IV
    padded_message = pad(message.encode('utf-8'), AES.block_size)  # Pad the message to a multiple of 16 bytes
    encrypted_message = cipher.encrypt(padded_message)
    return iv + encrypted_message  # Return IV concatenated with encrypted message

# Function to decrypt a message using AES
def aes_decrypt(encrypted_message, key):
    iv = encrypted_message[:16]  # Extract the IV (first 16 bytes)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    decrypted_message = unpad(cipher.decrypt(encrypted_message[16:]), AES.block_size)  # Decrypt and unpad the message
    return decrypted_message.decode('utf-8')

# Example usage
if __name__ == "__main__":
    # AES uses 16, 24, or 32 byte keys (128, 192, or 256 bits)
    key = get_random_bytes(16)  # Generate a random 16-byte key (128-bit)
    message = "This is a secret message."
    # Encrypt the message
    encrypted_message = aes_encrypt(message, key)
    print(f"Encrypted Message: {encrypted_message}")
    # Decrypt the message
    decrypted_message = aes_decrypt(encrypted_message, key)
    print(f"Decrypted Message: {decrypted_message}")
