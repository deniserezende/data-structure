import os
import subprocess
import time
import datetime
import random

# BED = input("Path BED (pasta de testes do e-vandro):") 
BED = '/home/pjr/Downloads/t2'

# BSD = input("Path de saída:")
BSD = '/home/pjr/Downloads/output'

# src = input("Path da pasta SRC:")
src = '/home/pjr/Downloads/SecondProject'

valgrind = '/home/pjr/Downloads/valgrind'


ini = datetime.datetime.now()

random.seed(ini)
print(f"time={ini}")

os.chdir(src)
subprocess.call(["make", "clean"])
subprocess.call(["make", "t2"])
print("\n")

geo = [] 
via = []
files = []
subdir = []
for (dirpath, dirnames, filenames) in os.walk(BED):
    #geo.extend(filenames)
    files.extend(filenames)
    subdir.extend(dirnames)
    break

geo = [ fi for fi in files if fi.endswith(".geo") ]
via = [ fi for fi in files if fi.endswith(".via") ]

subqry = []
for i in subdir:
    subsubqry = []
    for (dirpath, dirnames, filenames) in os.walk(BED + "/" + i):
        subsubqry.extend(filenames)
        subqry.append(subsubqry)
        break

geo.sort()
via.sort()
subdir.sort()

count = 0
for files_in_subqry in subqry:
    for j in files_in_subqry:
        valgrind_filename = random.randrange(200000)
        valgrind_fullpath = f"{valgrind}/{valgrind_filename}.txt"
        print(f"./t2 -e {BED} -o {BSD} -f {geo[count]} -v {via[count]} -q {subdir[count] + '/' + j}")
        print("\n")
        subprocess.call(["valgrind", f"--log-file={valgrind_fullpath}", "./t2", "-e", BED, "-o", BSD, "-f", geo[count], "-v", via[count], "-q", subdir[count] + "/" + j])
        

    count += 1 


fin = datetime.datetime.now()

print(f"time={ini}")
print(f"Tempo para rodar:\n{str(fin - ini)}")
