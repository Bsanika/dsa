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

# Client code for Bob
def diffie_hellman_client():
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

    # Input Bob's private key
    private_key_b = int(input("Enter Bob's private key: "))
    public_key_b = modular_exponentiation(g, private_key_b, p)
    print(f"Bob's Public Key: {public_key_b}")

    # Connect to Alice's server
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(('localhost', 8081))

    # Receive Alice's public key
    public_key_a = int(client.recv(1024).decode())
    print(f"Received Alice's Public Key: {public_key_a}")

    # Send Bob's public key to Alice
    client.send(str(public_key_b).encode())

    # Calculate shared secret
    shared_secret_b = modular_exponentiation(public_key_a, private_key_b, p)
    print(f"Bob's Calculated Shared Secret: {shared_secret_b}")

    client.close()

if __name__ == "__main__":
    diffie_hellman_client()



# Enter a prime number (p): 7
# Enter a primitive root (g): 3
# Enter Bob's private key: 4
# Bob's Public Key: 4
# Received Alice's Public Key: 6
# Bob's Calculated Shared Secret: 1