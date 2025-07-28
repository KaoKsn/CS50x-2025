# A simple calculator using python

# Operator choice.
def choice(opr,a,b):
    list_opr = ['+','-','*','/','%']
    indicator = 0
    for operator in list_opr:
        if  operator == opr:
            indicator = 1
            break

    if indicator == 0:
        print("Invalid Operator!")
    else:
        if opr == '+':
            return a+b

        elif opr == '-':
            return a-b

        elif opr == '*':
            return a*b

        elif opr == '/':
            return a/b

        elif opr == '%':
            return a%b

def main():
    opr = input("Operator: ")
    while True:
        try:
            a = float(input("a: "))
            b = float(input("b: "))
        except ValueError:
            continue
        else:
            break
    # Perform the operation
    print(choice(opr,a,b))

if __name__ == "__main__":
    main()
