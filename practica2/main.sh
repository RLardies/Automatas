make clean
make
./main
dot -Tpng afd_main.dot > ejs_prueba/main.png
dot -Tpng AFD_MIN.dot > ejs_prueba/main_min.png
./prueba1
dot -Tpng afd_prueba1.dot > ejs_prueba/afd_prueba1.png
dot -Tpng AFD_MIN.dot > ejs_prueba/afd_prueba1_min.png
./prueba2
dot -Tpng afd_prueba2.dot > ejs_prueba/afd_prueba2.png
dot -Tpng AFD_MIN.dot > ejs_prueba/afd_prueba2_min.png
./prueba3
dot -Tpng afd_prueba3.dot > ejs_prueba/afd_prueba3.png
dot -Tpng AFD_MIN.dot > ejs_prueba/afd_prueba3_min.png
make clean

