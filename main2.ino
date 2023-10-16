// UTN FRA - Sistema de Procesamiento de Datos
// Juan Pablo Ledezma - Iván Laurito

//https://www.tinkercad.com/things/f6Zv6YR02ac-parcial-domiciliario-parte-2/editel

// Enlazar los pines de arduino a las entradas del display 7 segmentos
// Definir DELAY, tiempo entre encendido de unidades y de decenas
#define A 13
#define B 12
#define C 11
#define D 10
#define E 9
#define F 8
#define G 7
#define RESET 5
#define AUMENTAR 4
#define DISMINUIR 3
#define SWITCH 2
#define UNIDADES A0
#define DECENAS A1
#define DELAY 10

// "Setear" los pines de arduino como salida
void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(RESET, INPUT_PULLUP);
  pinMode(AUMENTAR, INPUT_PULLUP);
  pinMode(DISMINUIR, INPUT_PULLUP);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(UNIDADES, OUTPUT);
  pinMode(DECENAS, OUTPUT);
  digitalWrite(UNIDADES, 0);
  digitalWrite(DECENAS, 0);
  encenderNumero(0);
  Serial.print(9600);
}

int contador_enteros = 0;
int contador_primos = 2;

int botonAumentar = 1;
int botonDisminuir = 1;
int botonReset = 1;

int aumentarAnterior = 1;
int disminuirAnterior = 1;
int resetAnterior = 1;

int modo_switch = 0;

void loop()
{
  modo_switch = digitalRead(SWITCH);
  
  int boton = botonPresionado();
  
  if (modo_switch == HIGH) {
  
  	if (boton == AUMENTAR) {
      if (contador_enteros < 100) {
        contador_enteros++;
      } else {
        contador_enteros = 0;
      }
    }
    if (boton == DISMINUIR) {
      if (contador_enteros > -1) {
        contador_enteros--;
      } else {
        contador_enteros = 99;
      }
    }
    if (boton == RESET) {
  	  contador_enteros = 0;
    }
    
    mostrarNumeroEntero();
    
  }
  
  //Contador de primos:
  
  //Cuando el switch está en modo 'Números primos', el contador de 
  //primos aumenta o disminuye según qué botón se presionó.
  //Si ese nuevo número no es primo, se repite la acción hasta
  //que el número cumpla con esa condición. Entonces, la función 
  //muestra el siguiente o el anterior número primo según corresponda.
  
  //Si el número primo mostrado es 97, al presionar el botón de 
  //'Aumentar' el contador pasa a ser 2.
  //Si el número primo mostrado es 2, al presionar el botón de 
  //'Disminuir' el contador pasa a ser 97.
  if (modo_switch == LOW) {  
    
    if (boton == AUMENTAR) {
      while(true) {
      	if (contador_primos < 100) {
          contador_primos++;
          if (esPrimo(contador_primos)) {
            break;
          }
        } else {
          contador_primos = 2;
          break;
      	}
      }
    }
    
    if (boton == DISMINUIR) {
      while(true) {
      	if (contador_primos > -1) {
          contador_primos--;
          if (esPrimo(contador_primos)) {
            break;
          }
      	} else {
        	contador_primos = 97;
        	break;
      	}
      }
    }
    if (boton == RESET) {
  	  contador_primos = 2;
    }
    
    mostrarNumeroPrimo();
    
  }
}

void mostrarNumeroEntero() {
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(contador_enteros - (contador_enteros / 10) * 10);  //UNIDADES
  encenderDisplays(UNIDADES);
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(contador_enteros / 10);  //DECENAS
  encenderDisplays(DECENAS);
}

void mostrarNumeroPrimo() {
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(contador_primos - (contador_primos / 10) * 10);  //UNIDADES
  encenderDisplays(UNIDADES);
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(contador_primos / 10);  //DECENAS
  encenderDisplays(DECENAS);
}

bool esPrimo(int numero) {
  if (numero < 2) {
    return false;
  }
  if (numero > 2) {
    for (int i = 2; i * 2 <= numero; i++) {
      if (numero % i == 0) {
        return false;
      }
    }
  }
  return true;
}

int botonPresionado() {
  botonAumentar = digitalRead(AUMENTAR);
  botonDisminuir = digitalRead(DISMINUIR);
  botonReset = digitalRead(RESET);
  if (botonAumentar) { 
    aumentarAnterior = 1;
  }
  if (botonDisminuir) {
    disminuirAnterior = 1;
  }
  if (botonReset) {
    resetAnterior = 1;
  }
  
  
  
  if (botonAumentar == 0 && botonAumentar != aumentarAnterior)
  {
    aumentarAnterior = botonAumentar;
    return AUMENTAR;
  } 
  else if (botonDisminuir == 0 && botonDisminuir != disminuirAnterior)
  {
   	disminuirAnterior = botonDisminuir;
    return DISMINUIR;
  }
  else if (botonReset == 0 && botonReset != resetAnterior)
  {
    resetAnterior = botonReset;
    return RESET;
  }
}

void encenderDisplays(int posicion)
{
  if (posicion == UNIDADES)
  {
    digitalWrite(UNIDADES, LOW);
    digitalWrite(DECENAS, HIGH);
    delay(DELAY);
  }
  else
  {
    digitalWrite(DECENAS, LOW);
    digitalWrite(UNIDADES, HIGH);
    delay(DELAY);
  }
}

// Encender el display con el número correspondiente
void encenderNumero(int numero){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  switch (numero){
    case 1:
  	  digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    case 2:
  	  digitalWrite(A, HIGH);
  	  digitalWrite(B, HIGH);
      digitalWrite(E, HIGH);
  	  digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 3:
      digitalWrite(A, HIGH);
  	  digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
  	  digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 4:
  	  digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
  	  digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 5:
  	  digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
  	  digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 6:
  	  digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
  	  digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 7:
  	  digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    case 8:
  	  digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
  	  digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 9:
  	  digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
  	  digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    default:
  	  digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
  	  digitalWrite(F, HIGH);
      break;
  }
}