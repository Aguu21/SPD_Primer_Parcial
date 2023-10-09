// C++ code
//
#define B 11
#define A 10
#define F 9
#define G 8
#define C 5
#define D 6
#define E 7

#define REINICIAR 4  
#define AUMENTAR 3
#define DISMINUIR 2
int contador = 0;
int valor_aumentar = 1;
int valor_disminuir = 1;
int valor_reiniciar = 1;
int aumentaPrevia = 1;
int disminuyePrevia = 1;
int reiniciaPrevia = 1;

void setup()
{
  for(int i = 5; i < 12; i++){
  	pinMode(i, OUTPUT);
  }
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(REINICIAR, INPUT_PULLUP);
  pinMode(AUMENTAR, INPUT_PULLUP);
  pinMode(DISMINUIR, INPUT_PULLUP);
  Serial.begin(9600);
}


void display_cero(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

//Cada numero del display
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
  digitalWrite(A5, HIGH);
  digitalWrite(A4, HIGH);
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
  if(valor_reiniciar == 0 && valor_reiniciar != reiniciaPrevia){
    reiniciaPrevia = 0;
    return REINICIAR;
  }
  return 0;
  
}

void loop()
{
  int apretado = boton_apretado();
  
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
  else if (apretado == REINICIAR){
  	contador = 0;
  }
  mostrar_display((contador / 10) % 10 , contador % 10);
}