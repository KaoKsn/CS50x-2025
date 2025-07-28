# Find the Coleman-Liau Index for the text.
def get_level(text):

    total_letters = 0
    total_words = 0
    total_sentences = 0

    # Parsing the input text based on the following definitions.
    # 1. Letter -> An english alphabet.
    # 2. Word -> A sequence of letters seperated by a whitespace.
    # 3. Sentence -> A sequence of words that ends with either of '!','?' or '.'
    for letter in text:
        if letter.isspace():
            total_words += 1
        elif letter.isalpha():
            total_letters += 1
        elif letter in ['?', '!', '.']:
            total_sentences += 1
    total_words += 1

    # Coleman-Liau Index:
    # index = 0.0588 * L - 0.296 * S - 15.8
    # L - Number of letters per 100 words
    # S - Number of sentences per 100 words.
    coleman_L = (total_letters / total_words) * 100
    coleman_S = (total_sentences / total_words) * 100
    level = round(0.0588 * coleman_L - 0.296 * coleman_S - 15.8)

    return level


# Print the reading level of the input text.
def print_level(level):
    if level < 1:
        print("Before Grade 1")
    elif level >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {level}")


def main():
    # Read text.
    text = input("Text: ")

    # Infere the reading level based on Coleman-Liau Index.
    level = get_level(text)

    # Print the reading level.
    print_level(level)


if __name__ == "__main__":
    main()
