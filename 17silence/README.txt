file video.avi
Para ver que tiene 10fp.

ffmpeg -i video.avi -r 10 -f image2 image/image-%07d.png
para generar imagenes de cada fotograma 3424

cropper.sh
para recortar solo los pixeles de los LEDs (pasa de >2GB a 18MB).
Adjuntada la version comprimida en images.7z.

(images.7z debe extraerse al directorio /image si no se han realizado los pasos anteriores)
silence.py
lee los pixeles de las imagenes y en funcion del color, a cada fotograma asigna los 3 bits.

Convierto los bits del primer led a caracteres, y me sale un HTTP header.
silence.php Al poner la cookie adecuada tengo acceso al enunciado del problema.
Tambien podria hacerlo modificando la cookie del navegador con alguna extension.

For each input N return the sum of digits of N!:
digits.py hace lo pedido!

- Enric Cusell