import random
import string

MAX_KEY_LEN = 32
MAX_VALUE_LEN = 2

def generate_random_key():
    return "".join([random.choice(list(string.hexdigits.lower())) for _ in range(1, MAX_KEY_LEN + 1)])

def generate_random_value():
    return "".join([random.choice(list(string.digits)) for _ in range(1, MAX_VALUE_LEN + 1)])

if __name__ == "__main__":
    for num in range(1, 2):
        values = list()
        output_filename = "{:02d}.t".format(num)
        print(output_filename)
        with open(output_filename, 'w') as output:
            for _ in range(1, 1000000):
                key = generate_random_key()
                value = generate_random_value()
                values.append((key,value))
                output.write("{} {}\n".format(key, value))
        
        output_filename = "{:02d}.a".format(num)
        with open (output_filename, 'w') as output:
            values = sorted(values, key=lambda x: x[0])
            for value in values:
                output.write("{}\t{}\n".format(value[0], value[1]))
