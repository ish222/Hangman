import random

def main():
    words_list = getWords()
    rand_num = random.randint(0, 200)
    guess_num = 0
    w_copy_str = words_list[rand_num]
    w_copy = [_ for _ in w_copy_str]
    word_str = "_" * len(w_copy_str)
    word = [_ for _ in word_str]
    max_guess = len(w_copy_str) * 2
    guess_list = []
    print(word)
    while (guess_num < max_guess) and (word != w_copy):
        guess_char = guess()
        print(guess_char)
        if guess_char not in w_copy:
            print("Wrong guess, try again!")
            guess_list.append(guess_char)
            guess_num += 1
        else:
            index = findIndex(guess_char, w_copy)
            for i in index:
                word[i] = guess_char
        print(word)
        print(f"Wrong guesses so far: {guess_list}")
    if word == w_copy:
        print("You've won!")
        print(f"The word was: {w_copy_str}")
    else:
        print("Sorry, you've lost, please try again!")
        print(w_copy_str)


def guess():
    guess_letter = input("Please input your guess character: ")
    if len(guess_letter) > 1:
        print("Please input 1 character only!")
        guess()
    elif str.isdigit(guess_letter):
        print("Please only input letters not numbers!")
        guess()
    return guess_letter


def findIndex(char, w_copy):
    w_copy2 = w_copy.copy()
    index = []
    while w_copy2.count(char) > 0:
        ind = w_copy2.index(char)
        index.append(ind)
        w_copy2[ind] = None
    return index


def getWords():
    with open("words.txt", 'r') as f:
        word_list_nl = f.readlines()
    word_list = [i[:-1] for i in word_list_nl]
    return word_list

if __name__ == '__main__':
    main()
