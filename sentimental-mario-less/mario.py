# TODO


def main():
    # refer to function below
    userInput = detHeight()
    for i in range(userInput):
        print(" " * (userInput - (i + 1)) + "#" * (i + 1))


def detHeight():
    # set the equivalence of a do while loop for validation
    while True:
        try:
            n = int(input("Enter the number of blocks: "))
            if n > 0 and n < 9:
                break
        # if input gives back an error, prompt again
        except ValueError:
            print("Next time, please enter a valid number between 1 and 8")
    return n


main()
