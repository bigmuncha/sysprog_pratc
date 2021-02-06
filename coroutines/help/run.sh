#!/usr/bin/env bash
set -euo pipefail

python3 help/generator.py -f test1.txt -c 10000 -m 10000
python3 help/generator.py -f test2.txt -c 10000 -m 10000
python3 help/generator.py -f test3.txt -c 10000 -m 10000
python3 help/generator.py -f test4.txt -c 10000 -m 10000
python3 help/generator.py -f test5.txt -c 10000 -m 10000
python3 help/generator.py -f test6.txt -c 100000 -m 10000

gcc -o main merge_sort.c
