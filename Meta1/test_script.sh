#!/usr/bin/env bash

same=0
different=0

project_dir=$(xdg-user-dir DOCUMENTS)/COMP/Projeto/comp-projeto/Meta1

cd $project_dir

lex gocompiler.l 
clang-3.9 lex.yy.c -o gocompiler
cp gocompiler $project_dir/CasosTeste/GitLab

cd $project_dir/CasosTeste/GitLab

for filename in ./*.dgo; do
    echo "Testing "$filename"...."

    if [ "$filename" = "./errors.dgo" ]; then
        ./gocompiler < $filename > output.txt
    else
        ./gocompiler -l < $filename > output.txt
    fi
    

    if cmp -s "${filename%.*}.out" "output.txt"; then
        echo "Files are the same"
        ((same++))
    else
        echo "Files are different"
        mv output.txt ${filename%.*}_ours.out
        ((different++))
    fi
done

rm output.txt
rm gocompiler

#Move the .l file to the desktop, rename it and zip it
cp $project_dir/gocompiler.l $(xdg-user-dir DESKTOP)/gocompiler.l
cd $(xdg-user-dir DESKTOP)
zip gocompiler.zip gocompiler.l
cd -

echo "$same files are equal"
echo "$different files are different"