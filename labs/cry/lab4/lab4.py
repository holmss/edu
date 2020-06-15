import random
import string

LENGTH = 13000

'''биография Г.Ф.Лавкрафта (13 435 символов) VS "Показания Рэндольфа Картера" (13 907 символов)'''

def match (t1, t2):
    count = 0
    for i,j in zip(t1, t2):
        if i == j:
            count+=1
    return count

#2 осмысленных текста (английский)

def match_text_text ():
    text1 = open("bio.txt").read()
    text2 = open("book.txt").read()
    length = min(len(text1), len(text2))
    print("text-text match: ", match(text1[:length], text2[:length])/length)

#осмысленный текст и текст из случайных букв

'''генерим текст'''
def random_letter_text_gen ():
    text = ""
    while len(text) < LENGTH:
        word_length = random.randint(2,10)
        word = ''.join(random.choice(string.ascii_letters) for _ in range(word_length))
        text += " " + word
    text = text[:LENGTH]
    return text

'''считаем совпадения'''

def match_text_letters ():
    text1 = (open("book.txt").read())[:LENGTH]
    text2 = random_letter_text_gen()
    print("text-letters match: ", match(text1, text2)/LENGTH)


#осмысленный текст и текст из случайных слов

'''генерим текст'''
'''source: https://github.com/dwyl/english-words/blob/master/words.txt'''
def random_words_text_gen ():
    text = ""
    words = open("words.txt").read()
    words = words.splitlines()
    while len(text) < LENGTH:
        text += " " + random.choice(words)
    text = text[:LENGTH]
    return text

'''считаем совпадения'''

def match_text_words ():
    text1 = (open("book.txt").read())[:LENGTH]
    text2 = random_words_text_gen()
    print("text-words match: ", match(text1, text2)/LENGTH)

#2 текста из случайных букв

def match_letters_letters ():
    text1 = random_letter_text_gen()
    text2 = random_letter_text_gen()
    print("letters-letters match: ", match(text1, text2)/LENGTH)

#2 текста из случайных слов

def match_words_words ():
    text1 = random_words_text_gen()
    text2 = random_words_text_gen()
    print("words-words match: ", match(text1, text2)/LENGTH)

match_text_text()
match_text_letters()
match_text_words()
match_letters_letters()
match_words_words()