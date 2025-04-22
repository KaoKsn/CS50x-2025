# Reading Height
def pyramid_height():
    while True:
        try:
            height = int(input("Height: "))
        except ValueError:  # To handle inputs that are not integers.
            continue
        if height >= 1 and height <= 8:
            break
    return height


# Printing the structure.
def print_pyramid(height):
    for i in range(height):
        for j in range(height):
            if j >= height-i-1:
                print("#", end='')
            else:
                print(end=' ')
        print(end='  ')
    # Printing the symmetric element.
        # for k in range(i+1):
        print("#" * (i+1), end='')
        print()


def main():
    print_pyramid(pyramid_height())


# Call the main() method.
if __name__ == "__main__":
    main()
