import string
import random
from pathlib import Path
from zipfile import ZipFile

def random_secret(L):
    secret = str()
    for i in range(L):
        letter = random.choice(string.ascii_letters + string.digits)
        secret = secret + letter
    return secret

def qualified(secret):
    count = 0
    for i in range(len(secret)):
        if secret[i] in string.ascii_lowercase:
            count += 1
            break
    for i in range(len(secret)):
        if secret[i] in string.ascii_uppercase:
            count += 1
            break
    for i in range(len(secret)):    
        if secret[i] in string.digits:
            count += 1
            break
    if count == 3:
        return True
    else:
        return False

def Extract(dirctory, password):
    zfile = ZipFile('/Users/jerryw/Desktop/code/python/experience.zip')
    zfile.extractall(members = zfile.namelist(), path = dirctory, pwd = password.encode('utf-8'))
    my_file = Path('/Users/jerryw/Desktop/code/python/experience')
    if my_file.is_dir():
        return True
    else:
        return False


length = random.randint(8, 20)
print(length)
secret = random_secret(length)
print(secret)
verify = qualified(secret)
print(verify)


dirctory = Path('/Users/jerryw/Desktop/code/python')
password = input("please input your password:")
verify_of_extract = Extract(dirctory, password)
print(verify_of_extract)
# RSLE0btD7xNJE6j