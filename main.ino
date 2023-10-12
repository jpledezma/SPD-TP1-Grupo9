<<<<<<< HEAD
// C++ code
// Juan Pablo Ledezma - Iván Laurito

// Enlazar los pines de arduino a las entradas del display 7 segmentos
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
#define UNIDADES A0
#define DECENAS A1
#define DELAY 10

// "Setear" los pines de arduino como salida
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(UNIDADES, OUTPUT);
  pinMode(DECENAS, OUTPUT);
  digitalWrite(UNIDADES, 0);
  digitalWrite(DECENAS, 0);
  encenderNumero(0);
  Serial.print(9600);
}

int numero = 0;
int botonAumentar = 1;
int botonDisminuir = 1;
int botonReset = 1;
int aumentarAnterior = 1;
int disminuirAnterior = 1;
int resetAnterior = 1;

void loop()
{
  int boton = botonPresionado();
  
  if (boton == AUMENTAR) {
    if (numero < 100) {
      numero++;
    } else {
      numero = 0;
    }
  }
  if (boton == DISMINUIR) {
    if (numero > -1) {
      numero--;
    } else {
      numero = 99;
    }
  }
  if (boton == RESET) {
  	numero = 0;
  }
  
  mostrarNumero();
}

void mostrarNumero() {
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(numero - (numero / 10) * 10);
  encenderDisplays(UNIDADES);
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(numero / 10);
  encenderDisplays(DECENAS);
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
=======
// Intentá modificar este archivo y hacer un commit para verificar que funcione
>>>>>>> e01ec2d200f486d3bbf711d10c67e24251bcab03
