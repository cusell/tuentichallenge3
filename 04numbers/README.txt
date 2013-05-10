g++ numbers.cpp -o numbers -O2
./numbers > numbers.txt
Se lee el fichero y muestra el progreso hasta 1.0 por la salida stderr.
Por stdout se imprime el array de los 100 numeros que faltan en el archivo.

Este array es el que uso en el siguiente codigo missing.cpp
g++ missing.cpp -o missing -O2

