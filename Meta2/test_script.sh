#!/usr/bin/env bash

same=0
different=0

project_dir=$(xdg-user-dir DOCUMENTS)/COMP/Projeto/comp-projeto/Meta2

cd $project_dir

lex gocompiler.l 
yacc -d gocompiler.y
cc -o gocompiler lex.yy.c y.tab.c -lm
cp gocompiler $project_dir/CasosTeste/GitLab

cd $project_dir/CasosTeste/GitLab

#Remove previous _ours files
rm *_ours.out

shopt -s nullglob # enable null glob

for filename in ./*.{dgo,go}; do
    echo "Testing "$filename"...."

    ./gocompiler -l < $filename > output.txt

    if cmp -s "${filename%.*}.out" "output.txt"; then
        echo "Files are the same"
        ((same++))
    else
        echo "Files are different"
        mv output.txt ${filename%.*}_ours.out
        ((different++))
    fi
done

shopt -u nullglob # disable null glob

rm output.txt
rm gocompiler

#Move the .l and .y file to the desktop, rename it and zip it
cp $project_dir/gocompiler.* $(xdg-user-dir DESKTOP)/.
cd $(xdg-user-dir DESKTOP)
zip gocompiler.zip gocompiler.l gocompiler.y
cd -

echo "$same files are equal"
echo "$different files are different"