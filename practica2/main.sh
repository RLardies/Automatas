make clean
make
./main
dot -Tpng AFD_MIN.dot > ejs_prueba/main.png
./prueba1
dot -Tpng AFD_MIN.dot > ejs_prueba/prueba1.png
./prueba2
dot -Tpng AFD_MIN.dot > ejs_prueba/prueba2.png
./prueba3
dot -Tpng AFD_MIN.dot > ejs_prueba/prueba3.png
make clean

