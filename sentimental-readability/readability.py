# Libraries or functions to add
from cs50 import get_string


def main():
    # Obtain text from user
    text = get_string("Please submit text to analyze: ")
    # Define variables to use with declared functions
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    final_index = coleman_liau(letters, words, sentences)

    # Print index results
    if final_index < 1:
        print("Before Grade 1")

    elif final_index > 16:
        print("Grade 16+")

    else:
        print(f"Grade {final_index}")


def count_letters(text):

    # set variable to 0
    letters = int(0)

    # Repeat action for the length of the string text
    for i in range(len(text)):
        # if it's a letter, add a point
        if text[i].isalpha():
            letters += 1
        # If it's not a letter, do not add points
    # Return the total
    return letters


def count_words(text):
    # set variable to 0
    words = int(0)

    # a. If first character is alphabetical, add one
    if text[0].isalpha():
        words += 1

    # If it's not, do not add points

    # b. Repeat following action for the length of the string text
    for i in range(len(text)):
        # if it's a space, add a point
        if text[i].isspace():
            words += 1

        # If it's not a space, do not add points

    # return the total
    return words


def count_sentences(text):
    # set variable to 0
    sentences = 0

    # Repeat following action for the length of the string text:
    for i in range(len(text)):
        # if it's a question mark or an exclamation point or a period, add one to counter
        if text[i] == '!' or text[i] == '?' or text[i] == '.':
            sentences += 1
        # If it's not, do not add points

    # return the total
    return sentences


def coleman_liau(letters, words, sentences):
    # Calculate index, this time without floats
    index = ((letters * 100 / words) * 0.0588) - ((sentences * 100 / words) * 0.296) - 15.8

    # round index
    round_index = round(index)

    return round_index


main()