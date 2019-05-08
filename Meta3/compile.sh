if [ $# -eq 1 ]; then
    if [ "$1" = "debug" ]; then
        lex gocompiler.l && yacc -d --debug --verbose gocompiler.y && cc -o gocompiler lex.yy.c y.tab.c ast.c semantic.c -lm -Wall -Wno-unused-function
    fi
else
    lex gocompiler.l && yacc -d gocompiler.y && cc -o gocompiler lex.yy.c y.tab.c ast.c semantic.c -lm -Wall -Wno-unused-function
fi