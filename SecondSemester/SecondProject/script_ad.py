import os
import subprocess
import time
import datetime

# BED = input("Path BED (pasta de testes do e-vandro):") 
BED = '/Users/Denise/Downloads/t2'

# BSD = input("Path de saída:")
BSD = '/Users/Denise/Downloads/output'

# src = input("Path da pasta SRC:")
src = '/Users/Denise/Dropbox/UEL/UniversitySubjectsGitHub/DataStructureGitHub/DataStructure/SecondSemester/SecondProject'


ini = datetime.datetime.now()

os.chdir(src)
subprocess.call(["make", "clean"])
subprocess.call(["make", "t2"])
print("\n")

report_path = "/Users/Denise/Dropbox/UEL/UniversitySubjectsGitHub/DataStructureGitHub/DataStructure/SecondSemester/SecondProject/output_python.txt"
report = open(report_path, 'w')

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
        data = f"./t2 -e {BED} -o {BSD} -f {geo[count]} -v {via[count]} -q {subdir[count] + '/' + j}\n"
        report.write(data)
        subprocess_ini = datetime.datetime.now()
        subprocess.call(["time", "./t2", "-e", BED, "-o", BSD, "-f", geo[count], "-v", via[count], "-q", subdir[count] + "/" + j])
        subprocess_end = datetime.datetime.now()
        time_report = f"time={str(subprocess_end - subprocess_ini)}\n\n"
        report.write(time_report)

        print(data)         
        print(time_report)          

    count += 1 


fin = datetime.datetime.now()

total_time_report = f"Tempo para rodar:\n{str(fin - ini)}"
report.write(total_time_report)
report.close()
print(total_time_report)


