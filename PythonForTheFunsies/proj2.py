#!/usr/bin/env python3
import sys
from memory  import Memory
from chunk import *
from random import randint


def main():
    if len(sys.argv) != 2:
        print("USAGE: python3 proj2.py input_file.txt")
        exit()
    f = open(sys.argv[1], "r")
    num_procs = ""
    while len(num_procs.strip()) == 0:
        num_procs = f.readline()
    num_procs = int(num_procs)
    procs = []
    for line in f:
        if len(line.strip()) != 0:
            p = Proc(line.strip())
            procs.append(p)
    print(str(len(procs)) + "/" + str(num_procs))

    memory = Memory()
    print(str(memory) + "\n\n")
    print("Inserting " + procs[0].val + " at next location")
    #memory.place_proc(procs[0], memory.next_fit)
    memory.insert_proc(procs[0], 0)
    print(str(memory) + "\n\n")
    memory.remove_proc(procs[0])
    for p in procs[1:]:
        print("Inserting " + str(len(p)) + " of " + p.val + " at next location")
        memory.place_proc(p, memory.next_fit)
        print(str(memory) + "\n\n")
        memory.remove_proc(p)

if __name__ == "__main__":
    main()
	
