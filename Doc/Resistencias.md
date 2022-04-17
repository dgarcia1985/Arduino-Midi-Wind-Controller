# Uso de resistencias en paralelo para leer varios pulsadores en una entrada analógica.

El controlador de viento ocupa todas las entradas digitales de la placa con botones para seleccionar que nota va a sonar.

Necesitaba añadir más botones para poder realizar distintas tareas (cambiar de octavas, transponer notas, alternar distintas configuraciones, etc ...)

Para ello conecto la entrada analógica a utilizar con la toma de 5V de la placa con una resistencia.

![Esquema Resistencias](../Img/resistencias.svg)

De esta forma leeremos un valor de 1023 en la entrada cuando ningún botón esté pulsado y el valor descenderá a medida que pulsemos botones ya que la circulación de la corriente se repartirá de forma inversamente proporcional a la resistencia de cada ramal del circuito.

Para calcular los valores, necesitamos saber que relación hay entre la resistencia que atraviesa cada uno de los interruptores y la resistencia total del circuito.

![Cálculo de la resistencia total](../Img/formula-resistencias.svg)  
Siendo S valores binarios que serán 0 cuando el interruptor este desconectado (por lo que la resistencia asociada no se tendrá en cuenta) y 1 cuando se presione.

Una vez hemos calculado la resistencia total podemos calcular el coeficiente de corriente que pasa por la Resistencia 5 dividiendo la resistencia total entre el valor de la resistencia 5. Para saber el valor teórico que devolverá la lectura analógica en Arduino multiplicamos el coeficiente por 1023 (valor máximo de una entrada analógica de 10 bits).

Por lo tanto podríamos calcular el valor teórico de entrada en Arduino con la siguiente fórmula.

![Cálculo del valor de entrada analógica](../Img/formula-resistencias2.svg)

Si utilizas los mismos valores de resistencias que yo tendrías la siguiente fórmula.
![Cálculo del valor de entrada analógica 2](../Img/formula-resistencias3.svg)

A partir de esta fórmula podemos calcular los valores que leeremos en función de que interruptores estén pulsados. Ninguna combinación de resistencias de mayor valor dará una lectura analógica menor que pulsar el interruptor con una resistencia de mayor valor. Esto nos permite en el código detectar primero si el botón S1 está pulsado e ir filtrando cada uno de los casos posibles de menor a mayor resistencia.

Además debemos tener en cuenta que las resistencias tienen unas tolerancias que harán variar el valor real que leamos en el Arduino.

Con las resistencias que he utilizado me ha bastado con aumentar en el código entre dos y cuatro unidades los valores teóricos obtenidos.


