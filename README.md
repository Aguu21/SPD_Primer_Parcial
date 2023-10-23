# SPD_Primer_Parcial 

## Integrante
Agustín Román Pineda 1°D

## Primera instancia del parcial:
![alt text](https://github.com/Aguu21/SPD_Primer_Parcial/blob/main/imagenes/esquema_primera_parte.png?raw=true)

## Descripción:
La primera parte consta de tres botones que controlan un contador interno, este contador se muestra en dos display de 7 segmentos.
Uno de los contadores aumenta el número, otro lo disminuye y otro lo reincia en 00.

## Funciones prinicipales:
Esta función se encarga de detectar que una única acción del contador al momento de apretar cualquier botón.
~~~ C++
int boton_apretado(void){
  valor_aumentar = digitalRead(AUMENTAR);
  valor_disminuir = digitalRead(DISMINUIR);
  valor_reiniciar = digitalRead(REINICIAR);

  if (valor_aumentar){
  	aumentaPrevia = 1;
  }
  if (valor_disminuir){
  	disminuyePrevia = 1;
  }
  if (valor_reiniciar){
  	reiniciaPrevia = 1;
  }

  if(valor_aumentar == 0 && valor_aumentar != aumentaPrevia){
    aumentaPrevia = 0;
    return AUMENTAR;
  }
  if(valor_disminuir == 0 && valor_disminuir != disminuyePrevia){
    disminuyePrevia = 0;
    return DISMINUIR;
  }
  if(valor_reiniciar == 0 && valor_reiniciar != reiniciaPrevia){
    reiniciaPrevia = 0;
    return REINICIAR;
  }
  return 0;
}
~~~
Esta función se encarga de aplicar la multiplexación, las funciones llamadas encienden los leds correspondientes a los números.
Está acortada porque aplica lo mismo para cada número, los encendidos y apagados están en cada caso ya que la lógica del switch demora
lo suficiente como para que no sean visible los dos a la vez y se pierde la ilusión de números diferentes.

~~~ C++
void select_num(int numero, int display){
  switch (numero){
    case 0:
    	//Se encienden ambos
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
    	//Se muestra el digito en ambos
        display_cero();
    	//Se apaga el que no corresponde
    	digitalWrite(display, LOW);
    	break;
    case 1:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_uno();
    	digitalWrite(display, LOW);
        break;
    ...
    default:
        break;
}
}
~~~

## Link del proyecto:
- [proyecto](https://www.tinkercad.com/things/gE38rFH0yCa)


## Segunda instancia del parcial:
![alt text](https://github.com/Aguu21/SPD_Primer_Parcial/blob/main/imagenes/esquema_primera_parte.png?raw=true)

## Descripción:
La segunda parte consta de un switch que determina si el contador se mueve entre números primos o no.
Se debe integrar un motor que mejore el proyecto. Se debe agregar otro componente, un sensor entre tres opciones.

## Funciones prinicipales:
Se determina si el número del contador es o no primo, de no serlo se suma o disminuye hasta que lo sea.
~~~ C++
int determinar_primo(int contador, int modo){
  bool flag = true;
  while (flag){
    contador = contador + modo;
    if(contador == 1){
      break;
    }
    else if (contador > 99){
      contador = 0;
    }
    else if (contador < 0){
      contador = 99;
    }
    for(int i = 2; i < contador + 1; i++){
      if(contador % i == 0){
        if(contador == i){
          flag = false;
        }
        else{
          break;
        }
      }
    }
  }
  return contador;
}
~~~
En el loop se agrega el cambio del switch y se implementa el uso del motor y del sensor de temperatura.
El motor CC tiene revoluciones proporcionales al contador y el motor AF se enciende en calor o frio extremo segun el modo del contador.
~~~ C++
void loop()
{
  int apretado = boton_apretado();
  int lecturaSensor = map(analogRead(SENSOR_TEMP),\
                          20, 358 ,-40 ,125);
  if(digitalRead(SWITCH)){
    if(lecturaSensor > 40){
      analogWrite(MOTORAF, 500);
    }
    else{
      analogWrite(MOTORAF, 0);
    }
    analogWrite(MOTORCC, map(contador, 0, 500, 0, 255));
    if (apretado == AUMENTAR){
      contador ++;
      if (contador > 99){
        contador = 0;	
      }
    }
    else if (apretado == DISMINUIR){
      contador --;
      if (contador < 0){
        contador = 99;
      }
    }
  }
  else{
    if(lecturaSensor < 0){
      analogWrite(MOTORAF, 500);
    }
    else{
      analogWrite(MOTORAF, 0);
    }
    analogWrite(MOTORCC, map(contador, 0, 500, 0, 255));
    //Logica contador con numeros primos
  	if (apretado == AUMENTAR){
      contador = determinar_primo(contador, 1);
    }
    else if (apretado == DISMINUIR){
      contador = determinar_primo(contador, -1);
    }
  }
  mostrar_display((contador / 10) % 10 , contador % 10);
}
~~~

## Link del proyecto:
- [proyecto](https://www.tinkercad.com/things/0psbEUwSERk)