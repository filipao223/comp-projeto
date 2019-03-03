#!/usr/bin/env bash

same=0
different=0

lex ~/Documents/COMP/Projeto/comp-projeto/Meta1/projeto.l && clang-3.9 ~/Documents/COMP/Projeto/comp-projeto/Meta1/lex.yy.c -o analisador1
rm lex.yy.c

for filename in ./*.dgo; do
    echo "Testing "$filename"...."
    ./analisador1 -l < $filename > output.txt
    #echo "${filename%.*}.out"
    if cmp -s "${filename%.*}.out" "output.txt"; then
        echo "Files are the same"
        ((same++))
    else
        echo "Files are different"
        ((different++))
    fi
done

rm output.txt
rm analisador1

echo "$same files are equal"
echo "$different files are different"