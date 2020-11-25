from cs50 import get_int

# Ask the user to enter a height
while True:
    height = get_int("Height: ")

    if height in range(1, 9):
        break

# Prints the pyramid until the specified height
for i in range(1, height + 1):

    # For loop to add spaces
    for k in range(height - i):
        print(" ", end="")

    # For loop to print the hashes
    for j in range(i):
        print("#", end="")

    print()
