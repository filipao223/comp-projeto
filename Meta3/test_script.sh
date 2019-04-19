#!/usr/bin/env bash

same=0
lexsame=0
different=0
lexdiff=0

project_dir=$(xdg-user-dir DOCUMENTS)/COMP/Projeto/comp-projeto/Meta3

cd $project_dir

lex gocompiler.l 
yacc -d gocompiler.y
cc -o gocompiler lex.yy.c y.tab.c -lm
cp gocompiler $project_dir/CasosTeste/GitLab

cd $project_dir/CasosTeste/GitLab

#Remove previous _ours files
rm *_ours.out
rm Lex/*_ours.out

shopt -s nullglob # enable null glob

#Test Lex only first

echo "=============TESTING LEX================"

for filename in Lex/*.{dgo,go}; do
    echo "Testing "$filename"...."

    if [ "$filename" = "Lex/errors.go" ]; then
        ./gocompiler -l -d < $filename > Lex/output.txt
    else
        ./gocompiler -l < $filename > Lex/output.txt
    fi

    if cmp -s "${filename%.*}.out" "Lex/output.txt"; then
        echo "Files are the same"
        ((lexsame++))
    else
        echo "Files are different"
        mv Lex/output.txt ${filename%.*}_ours.out
        ((lexdiff++))
    fi
done

echo "$lexsame files are equal"
echo "$lexdiff files are different"

#Test yacc stuff

echo "=============TESTING YACC================"

for filename in ./*.{dgo,go}; do
    echo "Testing "$filename"...."

    if [ "$filename" = "./errors.dgo" ] || [ "$filename" = "./syntax_errors_stmt.dgo" ] || [ "$filename" = "./testeErros.dgo" ]; then
        ./gocompiler < $filename > output.txt
    else
        ./gocompiler -t < $filename > output.txt
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

shopt -u nullglob # disable null glob

rm output.txt
rm Lex/output.txt
rm gocompiler

#Move the .l and .y file to the desktop, rename it and zip it
cp $project_dir/gocompiler.* $(xdg-user-dir DESKTOP)/.
cd $(xdg-user-dir DESKTOP)
zip gocompiler.zip gocompiler.l gocompiler.y
cd -

echo "$same files are equal"
echo "$different files are different"