import secrets
import json
from pathlib import Path

def random_key(L):
    key = secrets.token_bytes(L)
    intkey = int.from_bytes(key, 'big')
    return intkey

def encrypt(string):
    byte = string.encode('utf8')
    byte = int.from_bytes(byte, 'big')
    random_number = random_key( len( str(byte) ) )
    encryption = byte ^ random_number
    return random_number, encryption

def decrypt(key, encryption):
    decryption = key ^ encryption
    length = len(str(encryption))
    print(length)
    decryption_bytes = int.to_bytes(decryption, len(str(decryption)), 'big')
    message = decryption_bytes.decode('utf8')
    return message

def encrypt_by_json(encryption):
    encryption_by_json = json.dumps(encryption)
    file_dirctory = Path('/Users/jerryw/Desktop/code/python/json_encryption.txt')
    with open(file_dirctory, 'w', encoding = 'utf8') as fp_of_json_encryption:
        fp_of_json_encryption.write(encryption_by_json)
    fp_of_json_encryption.close()

def decrypt_by_json():
    file_dirctory = Path('/Users/jerryw/Desktop/code/python/json_encryption.txt')
    with open(file_dirctory, 'r', encoding = 'utf8') as fp_of_json_encryption:
        encryption_by_json = fp_of_json_encryption.read()
    fp_of_json_encryption.close()
    decryption_by_json = json.loads(encryption_by_json)
    return decryption_by_json


directory = Path('/Users/jerryw/Desktop/code/python/message.txt')
with open(directory) as fp:
    string = fp.read()
a = encrypt(string)
encryption = a[1]
encrypt_by_json(encryption)
b = decrypt(a[0], decrypt_by_json())
directory = Path('/Users/jerryw/Desktop/code/python/recovered_message.txt')
with open(directory, 'w', encoding = 'utf8') as fp_of_recovered_message:
    fp_of_recovered_message.write(b)
print(b)