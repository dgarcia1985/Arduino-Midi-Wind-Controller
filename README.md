# Controlador de viento Midi   
<a href="README.en.md">English</a>   

Aquí está el <a href="Code/midiWindController.ino">código</a> y los recursos para construir un controlador de viento Midi basado en Arduino.   
Mi objetivo era construir un controlador barato con una dinámica mejor que un teclado para tocar trompetas, saxofones, flautas y otros instrumentos de viento.   
He montado el prototipo con piezas impresas en 3D (Los archivos están Disponibles en la carpeta Parts), piezas desmontadas de mandos de videojuegos rotos, cables de distintos dispositivos USB estropeados, sensores y botones.

Las características del instrumento son las siguientes:

* 12 botones para seleccionar que nota se va a tocar, pueden accionarse de forma simultánea.  
* 1 sensor de presión GY-68 BMP180.   
* 1 Joystick de un mando viejo de GameCube para controlar la rueda de Pitch/Modulación.
* 1 potenciómetro lineal del gatillo de un mando de GameCube para controlar el ataque mordiendo la boquilla.
* 8 botones que permiten cambiar configuraciones del dispositivo y calibrarlo.   

Abajo podemos ver el esquema de conexiones del dispositivo:

![esquema](https://user-images.githubusercontent.com/103361813/162631641-c1413340-165d-418e-a282-0f6627521640.svg)  

Para poder utilizarlo como un dispositivo MIDI USB normal es necesario reprogramar el firmware de Arduino con <a href="https://github.com/ddiakopoulos/hiduino">Hiduino</a> o similar.   
Para realizar pruebas hasta reprogramar la placa de Arduino como dispositivo MIDI he utilizado <a href="https://projectgus.github.io/hairless-midiserial/">Hairless Midi</a>, ten en cuenta que la tasa de Baudios del dispositivo MIDI es distinta si lo utilizamos eon esta aplicación. Se detallará en las instrucciones.   
Las piezas 3D están modeladas con <a href="https://www.freecadweb.org/">FreeCAD</a>   
Muchas de las piezas utilizadas son demasiado grandes para mi impresora 3D, por lo que algunas piezas han sido impresas partidas en dos para luego unirlas, algunas piezas van atornilladas pero otras han sido unidas utilizando un soldador para fundir el plástico.   
He impreso las piezas en PETG, pero casi todas las piezas deberían poder hacerse en cualquier plástico. La lengüeta que transmite la fuerza de mordida debería estar impresa en un plástico bastante resistente (ABS o PETG).   

Los planos de las piezas los puedes consultar <a href="#">aquí</a>.

La lista completa de componentes es la siguiente:

* Placa Arduino Uno o compatible (Asegurate de que puede reprogramarse o sólo lo podrás usar mediante un programa Serial a Midi)   
* 12 Botones de interruptor para Arduino   
* 1 Joystick (Sólo utilizaremos un eje así que puede valer cualquier potenciómetro rotatorio con un sistema de retorno a la posición central)   
* 1 potenciómetro deslizante (Utilice el de el gatillo de un mando de GameCube, pero se estropeó y lo cambié por uno A20K que es lo que encontré que me entrará en la pieza que ya tenía diseñada) que recibirá la fuerza de la mordida.
* 1 Muelle para crear el efecto de autoretorno en el potenciómetro deslizante (También utilice uno de un mando de GameCube roto).
* 4 resistencias de 1k, 2 de 2k, 2 de 5.1k y 2 de 10k. Los valores en realidad pueden ser distintos. <a href="#">Aquí se detalla que hacen</a>.   
* 1 sensor GY-68 BMP180.
* Conectores JST para organizar los cables de manera más sencilla.
* Piezas impresas en 3D, los modelos los puedes bajar aquí en formatos FCSTD y STL.
