from math import gcd

# Check if a number is prime
def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

# Find all prime factors of n
def prime_factors(n):
    factors = set()
    while n % 2 == 0:
        factors.add(2)
        n //= 2
    for i in range(3, int(n ** 0.5) + 1, 2):
        while n % i == 0:
            factors.add(i)
            n //= i
    if n > 2:
        factors.add(n)
    return factors

# Check if g is a primitive root modulo p
def is_primitive_root(g, p):
    if gcd(g, p) != 1:
        return False  # g must be coprime with p
    required_set = set(range(1, p))
    actual_set = {pow(g, k, p) for k in range(1, p)}
    return required_set == actual_set


import socket
import random

# Function to perform modular exponentiation
def modular_exponentiation(base, exp, mod):
    result = 1
    base = base % mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp = exp >> 1
        base = (base * base) % mod
    return result

# Server code for Alice
def diffie_hellman_server():
    # Input and validate prime number (p)
    while True:
        p = int(input("Enter a prime number (p): "))
        if is_prime(p):
            break
        print("Invalid input! Please enter a valid prime number.")

    # Input and validate primitive root (g)
    while True:
        g = int(input("Enter a primitive root (g): "))
        if is_primitive_root(g, p):
            break
        print(f"{g} is not a valid primitive root of {p}. Please try again.")

    # Input Alice's private key
    private_key_a = int(input("Enter Alice's private key: "))
    public_key_a = modular_exponentiation(g, private_key_a, p)
    print(f"Alice's Public Key: {public_key_a}")

    # Set up server to communicate with Bob
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('localhost', 8081))
    server.listen(1)
    print("Waiting for Bob to connect...")

    conn, addr = server.accept()
    print(f"Connected to Bob: {addr}")

    # Send Alice's public key to Bob
    conn.send(str(public_key_a).encode())

    # Receive Bob's public key
    public_key_b = int(conn.recv(1024).decode())
    print(f"Received Bob's Public Key: {public_key_b}")

    # Calculate shared secret
    shared_secret_a = modular_exponentiation(public_key_b, private_key_a, p)
    print(f"Alice's Calculated Shared Secret: {shared_secret_a}")

    conn.close()

if __name__ == "__main__":
    diffie_hellman_server()




# Enter a prime number (p): 7
# Enter a primitive root (g): 3
# Enter Alice's private key: 3
# Alice's Public Key: 6
# Waiting for Bob to connect...
# Connected to Bob: ('127.0.0.1', 9060)
# Received Bob's Public Key: 4
# Alice's Calculated Shared Secret: 1
