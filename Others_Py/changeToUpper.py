name = ["hello", "yes", "NoPe"]

index = 0
for string in name:
    print(f"{name[index]}:  {string.upper()}")
    index += 1
print()

# Check if the string is numeric

n = input("Input: ").isnumeric()

if n:
    print("Numeric!")
else:
    print("Not Numeric!")

