import struct
import os

def read(path:str):
    f = open(path, "rb")
    arr = []
    for i in range(1000):
        byte = struct.unpack('f', f.read(4))
        arr.append(byte[0])

    return arr

def convert(path:str):
    new_path = path.split('.')[0] + '.txt'
    f = open("../files/" + new_path, 'w')
    arr = read(path)
    for line in arr:
        f.write(str(line) + "\n")

def listdir(path:str):
    return [str(f) for f in os.listdir(path)]

def convertAll(path:str):
    arr = listdir(path)
    #print(arr)
    for f in arr:
        convert(path+f)

def indexfile(path:str):
    arr = []
    for f in listdir(path):
        try:
            if f.split('.')[1] == 'txt':
                arr.append(f)
        except:
            continue
    return arr
def createIndexFile(arr):
    f = open('./indexfile.txt', 'w')
    for l in arr:
        f.write(l+'\n')
try:        
    convertAll('orig/')
except:
    pass
createIndexFile(indexfile('./'))
