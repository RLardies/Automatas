make clean
make
./main 
dot -Tpng af11.dot > ejs_prueba/ej_main_nodet.png
dot -Tpng AFD.dot > ejs_prueba/ej_main_det.png

./ejercicio_prueba1
dot -Tpng afd_prueba1.dot > ejs_prueba/ej_prueba1_nodet.png
dot -Tpng AFD.dot > ejs_prueba/ej_prueba1_det.png

./ejercicio_prueba2
dot -Tpng afd_prueba2.dot > ejs_prueba/ej_prueba2_nodet.png
dot -Tpng AFD.dot > ejs_prueba/ej_prueba2_det.png

./ejercicio_prueba3
dot -Tpng afd_prueba3.dot > ejs_prueba/ej_prueba3_nodet.png
dot -Tpng AFD.dot > ejs_prueba/ej_prueba3_det.png

./ejercicio_prueba4
dot -Tpng afd_prueba4.dot > ejs_prueba/ej_prueba4_nodet.png
dot -Tpng AFD.dot > ejs_prueba/ej_prueba4_det.png
make clean
