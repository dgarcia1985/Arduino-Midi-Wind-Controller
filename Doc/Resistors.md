# Using resistors in parallel for reading multiple switchs in a single analog input  

<a href="Resistencias.md">Español</a>

##Translation pending  

All wind controller digital inputs are occupied with switches for note selection.

I needed more buttons to do other tasks such as changing octaves, transposing notes, or modifying device configuration.


I connect the analog input with a resistor to the 5V power pin and four parallel resistors with switches connected to ground.

![Resistor wiring scheme](../Img/resistencias.svg)

This way we will read a value of 1023 in the input when none of the switches is connected, this value will be lowered by each switch is activated. The electric current will be distributed inversely proportional to the resistor value associated with each switch. 

To calculate the analog value we need to now the ratio between the resistance of the resistor without switch and the total resistance of the circuit. We can calculate total resistance with the next formula.
![Total resistance formula](../Img/formula-resistencias.svg)  
Being S binary values that will be 0 when the switch is off and 1 when it's on.

Once we have the total resistance we can calculate the ratio of current passing through R<sub>5</sub>. To know the theoretical value that we will be reading in the Arduino's analog input we must multiply this ratio by 1023(Máximum value of a 10 bits analog input).

This formula let us calculate this value.

![Analog input value formula](../Img/formula-resistencias2.svg)

If you use the same resistors than i did you get this formula.
![Analog input value formula 2](../Img/formula-resistencias3.svg)

With this we can calculate the analog read of any buttons configuration. There's no combination of higher value resistors that could output a lower value than pressing a switch attached to a lower value resistor. This allows us to detect that S<sub>1</sub> is pressed when the analog read is lower than 512 (theoretically).

As any resistor have a tolerance value, i have increased the theoretical values in the code.   

With the resistors i have used between 2 and 4 units of tolerance is enough. 


