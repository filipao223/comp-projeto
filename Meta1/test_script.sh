#!/usr/bin/env bash

same=0
different=0

lex ~/Documents/COMP/Projeto/comp-projeto/Meta1/projeto.l && clang-3.9 ~/Documents/COMP/Projeto/comp-projeto/Meta1/lex.yy.c -o analisador1
rm lex.yy.c

for filename in ./*.dgo; do
    echo "Testing "$filename"...."

    if [ "$filename" = "./errors.dgo" ]; then
        ./analisador1 < $filename > output.txt
    else
        ./analisador1 -l < $filename > output.txt
    fi
    

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

#Move the .l file to the desktop, rename it and zip it
project_dir=$(xdg-user-dir DOCUMENTS)/COMP/Projeto/comp-projeto/Meta1
cp $project_dir/projeto.l $(xdg-user-dir DESKTOP)/gocompiler.l
cd $(xdg-user-dir DESKTOP)
zip gocompiler.zip gocompiler.l
cd -

echo "$same files are equal"
echo "$different files are different"