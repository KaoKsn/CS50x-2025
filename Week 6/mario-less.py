# Height of the pyramid
def pyramid_height():
    while True:
        height = input("Height: ")
        if height.isnumeric() and int(height) >= 1 and int(height) <= 8:
            break
    height = int(height)
    return height

# Printing the pyramid.


def print_pyramid(height):
    for i in range(height):
        for j in range(height):
            if j >= height-i-1:
                print("#", end='')
            else:
                print(end=' ')
        print()


def main():
    print_pyramid(pyramid_height())


if __name__ == "__main__":
    main()
