import sys
import re

#git log --graph --decorate --pretty="%H %an - %s" c2a6c5caeab8a106f37bc996ae5d9f8a0b8c91b9...HEAD > ../chibios.log

with open(sys.argv[1]) as f:
    lines = f.readlines()

for line in reversed(lines):
    m = re.match(r"([|/\\ *+]+)([[0-9A-Fa-f]*).*", line)
    if m.group(1).find("+")!=-1 and m.group(2)!="":
        sys.stdout.write(m.group(2))
        sys.stdout.write(" ")
