import rsa
from Crypto.Hash import MD5
from pathlib import Path
from rsa import key

(pubkey, privkey) = rsa.newkeys(1000)
print("大素数:\np = %s\nq = %s" %(privkey.p, privkey.q))
print("公钥:\nn = %s\ne = %s" %(pubkey.n, pubkey.e))
print("私钥:\nn = %s\nd = %s" % (privkey.n, privkey.d))

dirctory_of_message = Path('/Users/jerryw/Desktop/code/python/message.txt')
with open(dirctory_of_message, 'r') as fp_of_message:
    message = fp_of_message.read()
fp_of_message.close()

message = message.encode('utf8')

dirctory_of_pubkey = Path('/Users/jerryw/Desktop/code/python/pubkey.txt')
with open(dirctory_of_pubkey, 'w') as fp_of_pubkey:
    fp_of_pubkey.write(str(pubkey.n))
    fp_of_pubkey.write('\n')
fp_of_pubkey.close()
with open(dirctory_of_pubkey, 'a') as fp_of_pubkey:
    fp_of_pubkey.write(str(pubkey.e))
fp_of_pubkey.close()
with open(dirctory_of_pubkey, 'r') as fp_of_pubkey:
    public_key = fp_of_pubkey.readlines()
fp_of_pubkey.close()

dirctory_of_privkey = Path('/Users/jerryw/Desktop/code/python/privkey.txt')
with open(dirctory_of_privkey, 'w') as fp_of_privkey:
    fp_of_privkey.write(str(privkey.n))
    fp_of_privkey.write('\n')
fp_of_privkey.close()
with open(dirctory_of_privkey, 'a') as fp_of_privkey:
    fp_of_privkey.write(str(privkey.e))
    fp_of_privkey.write('\n')
    fp_of_privkey.write(str(privkey.d))
    fp_of_privkey.write('\n')
    fp_of_privkey.write(str(privkey.p))
    fp_of_privkey.write('\n')
    fp_of_privkey.write(str(privkey.q))
fp_of_privkey.close()
with open(dirctory_of_privkey, 'r') as fp_of_privkey:
    private_key = fp_of_privkey.readlines()
fp_of_privkey.close()

pukey = key.PublicKey(int(public_key[0]), int(public_key[1]))
prkey = key.PrivateKey(int(private_key[0]), int(private_key[1]), int(private_key[2]), int(private_key[3]), int(private_key[4]))



sign = rsa.sign(message, prkey, "MD5") # 使用私钥进行'MD5'签名
print("签名:",sign)
try:
    verify = rsa.verify(message, sign, pukey)  # 使用公钥验证签名
except:
    print("验证失败")
else:
    print("验证成功")