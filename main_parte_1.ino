
// Segunda versión
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

typedef struct {
  bool ejecucion;
  bool estadoAnterior;
}estructura;

estructura detectarPulsacion(bool estadoActual, bool estadoAnterior);
void mostrarNumero(int num);
void encenderDisplays(int posicion);
void encenderNumero(int numero);
int normalizarContador(int contador, int limiteSuperior);

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
  pinMode(UNIDADES, OUTPUT);
  pinMode(DECENAS, OUTPUT);
  digitalWrite(UNIDADES, 0);
  digitalWrite(DECENAS, 0);
  encenderNumero(0);
  Serial.print(9600);
}

int numero = 0;
bool btnSumarEstadoActual;
bool btnRestarrEstadoActual;
bool btnResetEstadoActual;

bool btnSumarEstadoAnterior = false;
bool btnRestarrEstadoAnterior = false;
bool btnResetEstadoAnterior = false;

estructura deteccionSuma;
estructura deteccionResta;
estructura deteccionReset;

void loop()
{

  numero = normalizarContador(numero, 99);

  btnSumarEstadoActual = !(digitalRead(AUMENTAR));
  btnRestarrEstadoActual = !(digitalRead(DISMINUIR));
  btnResetEstadoActual = !(digitalRead(RESET));
  
  deteccionSuma = detectarPulsacion(btnSumarEstadoActual, btnSumarEstadoAnterior);
  btnSumarEstadoAnterior = deteccionSuma.estadoAnterior;

  deteccionResta = detectarPulsacion(btnRestarrEstadoActual, btnRestarrEstadoAnterior);
  btnRestarrEstadoAnterior = deteccionResta.estadoAnterior;

  deteccionReset = detectarPulsacion(btnResetEstadoActual, btnResetEstadoAnterior);
  btnResetEstadoAnterior = deteccionReset.estadoAnterior;

  if (deteccionSuma.ejecucion){
    numero++;
  }
  if (deteccionResta.ejecucion){
    numero--;
  }

  if (deteccionReset.ejecucion){
    numero = 0;
  }
  
  mostrarNumero(numero);
}

void mostrarNumero(int num) {
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(num % 10);
  encenderDisplays(UNIDADES);
  digitalWrite(UNIDADES, HIGH);
  digitalWrite(DECENAS, HIGH);
  encenderNumero(num / 10);
  encenderDisplays(DECENAS);
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

// función para ejecutar una acción por única vez en base a una entrada digital (por ejemplo, un pulsador)
estructura detectarPulsacion(bool estadoActual, bool estadoAnterior){
  estructura devolucion;
  devolucion.estadoAnterior = estadoAnterior;
  
  if (estadoActual != estadoAnterior){
    devolucion.estadoAnterior = estadoActual;
    devolucion.ejecucion = estadoActual;
  }
  else{
    devolucion.ejecucion = false;
  }
      
  return devolucion;
}

// función para evitar que el contador tome valores fuera de los límites establecidos (entre 0 y 99)
int normalizarContador(int contador, int limiteSuperior){

  if (contador > limiteSuperior){
    contador = contador - (limiteSuperior + 1);
  }
  if (contador < 0){
    contador = (limiteSuperior + 1) + contador;
  }

  return contador;
}
