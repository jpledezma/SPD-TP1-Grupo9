// Enlazar los pines de arduino a las entradas del display 7 segmentos
#define A 13
#define B 12
#define C 11
#define D 10
#define E 9
#define F 8
#define G 7

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
}

// Encender el display con el número correspondiente
void encenderNumero(int numero){
  
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

// Apagar el display
void apagarDisplay(){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

// Estructura con 2 tipos de datos: el estado anterior de la entrada digital, y la ejecución de la acción que efectúa esa entrada
typedef struct {
  bool ejecucion;
  bool estado_anterior;
}estructura;


// función para ejecutar una acción por única vez en base a una entrada digital (por ejemplo, un pulsador)
estructura detectarPulsacion(bool estado_actual, bool estado_anterior){
  estructura devolucion;
  devolucion.estado_anterior = estado_anterior;
  
  if (estado_actual != estado_anterior){
    devolucion.estado_anterior = estado_actual;
    devolucion.ejecucion = estado_actual;
  }
  else{
    devolucion.ejecucion = false;
  }
      
  return devolucion;
}

// función para evitar que el contador tome valores fuera de los límites establecidos (entre 0 y 99)
int normalizarContador(int contador){

  if (contador > 99){
    contador = contador - 100;
  }
  if (contador < 0){
    contador = 100 + contador;
  }

  return contador;
}
// Idem al anterior, pero permite seleccionar el límite superior (el límite inferior siempre es 0)
int normalizarContador2(int contador, int limite_superior){

  if (contador > limite_superior ){
    contador = contador - limite_superior - 1;
  }
  if (contador < 0){
    contador = limite_superior + 1 + contador;
  }

  return contador;
}