// C++ code
//
#define B 13
#define A 10
#define F 9
#define G 8
#define C 5
#define D 6
#define E 7

#define SWITCH 4  
#define AUMENTAR 12
#define DISMINUIR 2
#define MOTORCC 3
#define MOTORAF 11
#define SENSOR_TEMP A0

int contador = 0;
int valor_aumentar = 1;
int valor_disminuir = 1;
int aumentaPrevia = 1;
int disminuyePrevia = 1;

void setup()
{
  for(int i = 5; i < 11; i++){
  	pinMode(i, OUTPUT);
  }
  pinMode(B, OUTPUT);
  
  pinMode(MOTORCC, OUTPUT);
  
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  
  pinMode(SWITCH, INPUT);
  pinMode(AUMENTAR, INPUT_PULLUP);
  pinMode(DISMINUIR, INPUT_PULLUP);
  Serial.begin(9600);
}

//Cada numero del display
void display_cero(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void display_uno(){
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void display_dos(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void display_tres(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void display_cuatro(){
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void display_cinco(){
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(F, HIGH);
}

void display_seis(){
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(F, HIGH);
}

void display_siete(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void display_ocho(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void display_nueve(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

//Muestra los dos numeros en cada display respectivamente

void mostrar_display(int decimal, int unidad){
  select_num(decimal, A5);
  select_num(unidad, A4);

}

//Recibe el numero a mostrar y el display que corresponde 
//apagar. La multiplexacion se logra dando la orden de encender
//ambos displays, mostrando el numero en ambos, pero apagando
//uno de ellos. Al hacerse tan rapido se da la ilusion de que
//se muestran dos numeros distintos a la vez.
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
    case 2:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_dos();
    	digitalWrite(display, LOW);
        break;
    case 3:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_tres();
    	digitalWrite(display, LOW);
        break;
    case 4:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_cuatro();
    	digitalWrite(display, LOW);
        break;
    case 5:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_cinco();
    	digitalWrite(display, LOW);
        break;
    case 6:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_seis();
    	digitalWrite(display, LOW);
        break;
    case 7:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_siete();
    	digitalWrite(display, LOW);
        break;
    case 8:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_ocho();
    	digitalWrite(display, LOW);
        break;
    case 9:
        digitalWrite(A5, HIGH);
        digitalWrite(A4, HIGH);
        display_nueve();
    	digitalWrite(display, LOW);
        break;
    default:
        break;
}
}

//Detecta cuando se presiona un boton, generando un unico cambio.
int boton_apretado(void){
	
  valor_aumentar = digitalRead(AUMENTAR);
  valor_disminuir = digitalRead(DISMINUIR);

  if (valor_aumentar){
  	aumentaPrevia = 1;
  }
  if (valor_disminuir){
  	disminuyePrevia = 1;
  }
  
  //Se requiere saber si previamente estaba presionado el boton
  //para no ejecutar demasiadas veces la misma orden.
  if(valor_aumentar == 0 && valor_aumentar != aumentaPrevia){
    aumentaPrevia = 0;
    return AUMENTAR;
  }
  if(valor_disminuir == 0 && valor_disminuir != disminuyePrevia){
    disminuyePrevia = 0;
    return DISMINUIR;
  }
  return 0;
  
}

//Determina cual es el siguiente numero primo del contador
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

void loop()
{
  int apretado = boton_apretado();
  int lecturaSensor = map(analogRead(SENSOR_TEMP),\
                          20, 358 ,-40 ,125);

  //Integrar el motor cc consta de agregar un high o low segun
  //corresponda basandose en el switch.
  if(digitalRead(SWITCH)){
    //Si la temperatura es extrema se alerta con 
    //el motor encendido y debe estar en modo uno a uno.
    if(lecturaSensor > 40){
      analogWrite(MOTORAF, 500);
    }
    else{
      analogWrite(MOTORAF, 0);
    }
    analogWrite(MOTORCC, map(contador, 0, 500, 0, 255));
    //Logica contador sin numeros primos
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
    //Si la temperatura es extrema negativa se alerta con 
    //el motor encendido y debe estar en modo primo a primo.
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