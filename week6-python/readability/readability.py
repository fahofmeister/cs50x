from cs50 import get_string


# Global variables
nLetters = 0
nWords = 0
nSentences = 0


def main():
    # Main routine

    text = get_string("Text: ")
    checkText(text)
    index = round(calcIndex())

    if index < 1:
        print("Before Grade 1")

    elif index >= 16:
        print("Grade 16+")

    else:
        print(f"Grade {index}")


def checkText(text):
    # Counts words, letters and sentences
    import re

    global nLetters
    global nWords
    global nSentences

    nWords = len(text.split())
    nSentences = len(re.split(r'[.!?] ', text))
    # Inspired by Stack Overflow
    # https://stackoverflow.com/questions/19669001/using-len-for-text-but-discarding-spaces-in-the-count
    nLetters = len(text) - len(re.findall('[;.!?,\' ]', text))

    # print(f"{nLetters} letter(s)")
    # print(f"{nWords} word(s)")
    # print(f"{nSentences} sentence(s)")


def calcIndex():
    # Calculates the Coleman-Liau index
    global nLetters
    global nWords
    global nSentences

    L = nLetters / nWords * 100
    S = nSentences / nWords * 100

    return 0.0588 * L - 0.296 * S - 15.8


if __name__ == '__main__':
    main()
