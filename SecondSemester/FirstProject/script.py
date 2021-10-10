import os
import subprocess
import time
import datetime

BED = input("Path BED (pasta de testes do e-vandro):") 
# BED = '/mnt/hgfs/PROGRAMACAO/C/EstruturaDados1/PROJETO2/1paths/BED/testcase/t2'
#BED = input("Diretorio BED")

BSD = input("Path de saída:")
# BSD = '/mnt/hgfs/PROGRAMACAO/C/EstruturaDados1/PROJETO2/1paths/BSD'
#BSD = input("Diretorio B")

src = input("Path da pasta SRC:")
# src = '/mnt/hgfs/PROGRAMACAO/C/EstruturaDados1/PROJETO2/MateusKomar/src'
#src = '/media/devgod/Instalacoes/Usuários/Komarchewski/Google Drive/UEL/PROGRAMACAO/C/EstruturaDados2/T1/tentativa1/src'


ini = datetime.datetime.now()

os.chdir(src)
subprocess.call(["make", "t1"])
print("\n")

geo = [] 
pm = []
files = []
subdir = []
for (dirpath, dirnames, filenames) in os.walk(BED):
    #geo.extend(filenames)
    files.extend(filenames)
    subdir.extend(dirnames)
    break

geo = [ fi for fi in files if fi.endswith(".geo") ]
pm = [ fi for fi in files if fi.endswith(".pm") ]

subqry = []
for i in subdir:
    subsubqry = []
    for (dirpath, dirnames, filenames) in os.walk(BED + "/" + i):
        subsubqry.extend(filenames)
        subqry.append(subsubqry)
        break

geo.sort()
pm.sort()
subdir.sort()

count = 0
for files_in_subqry in subqry:
    for j in files_in_subqry:
        print(f"./t1 -e {BED} -o {BSD} -f {geo[count]} -pm {pm[count]} -q {subdir[count] + '/' + j}")
        print("\n")
        subprocess.call(["./t1", "-e", BED, "-o", BSD, "-f", geo[count], "-pm", pm[count], "-q", subdir[count] + "/" + j])
        

    count += 1 


fin = datetime.datetime.now()

print(f"Tempo para rodar:\n{str(fin - ini)}")