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
#define SWITCH 2
#define UNIDADES A0
#define DECENAS A1
#define DELAY 10

// Estructura de datos
// Como una función sólo puede devolver un valor, se creará esta estructura que contiene 2 variables, 
// para así poder devolver ambos valores dentro de un único tipo de dato.
typedef struct {
  // Variable para decidir ejecutar o no una acción de acuerdo a su valor.
  bool ejecucion;
  // Variable para guardar en memoria el estado anterior de un botón.
  bool estadoAnterior;
}estructura;

/**
 * Detectar el cambio en el estado de una entrada digital.
 *
 * Esta función toma el estado actual de una entrada y la compara con su estado anterior
 * para ejecutar una acción por única vez en base a esos datos.
 *
 * @param estadoActual El estado actual de la entrada (activo/no activo).
 * @param estadoAnterior Estado inmediatamente anterior de la entrada.
 * @return Se devuelve el estado anterior de la entrada, y la ejecución (o no) de la acción.
 */
estructura detectarPulsacion(bool estadoActual, bool estadoAnterior);

/**
 * Muestra un número en los displays
 *
 * Se muestra el número ingresado por parámetro, y es mostrado
 * usando la función de multiplexación.
 *
 * @param num Número a ser mostrado.
 */
void mostrarNumero(int num);

/**
 * Multiplexación.
 *
 * Se enciende un display de las unidades/decenas con un número y se apaga el otro, 
 * luego se agrega un pequeño delay.
 *
 * @param posicion es el display que será encendido.
 */
void encenderDisplays(int posicion);

/**
 * Muestra un número en un display
 *
 * Se encienden los LED del display para mostrar un número.
 *
 * @param numero Número a ser mostrado.
 */
void encenderNumero(int numero);

/**
 * Cambia un número por si se sale del límite establecido.
 *
 * Esta función toma un número y lo compara con el límite superior, y con cero.
 * Si es mayor que el límite superior, se reinicia en 0.
 * Si es menor que 0, pasa al límite superior.
 * Si está dentro de los límites, lo deja como está.
 *
 * @param contador El número a ser comparado.
 * @param limiteSuperior El valor máximo que puede tener el número.
 * @return Se devuelve el número ingresado con las modificaciones necesarias.
 */
int normalizarContador(int contador, int limiteSuperior);

/**
 * Comprueba si un número es primo.
 *
 * Esta función toma un número y busca sus divisores (sin contar a 1 y a sí mismo), 
 * si encuentra uno, devuelve un false. Si no encuentra ninguno, devuelve true.
 *
 * @param numero El número que será comprobado.
 * @return Se devuelve un true o false, dependiendo de si el número es primo o no.
 */
bool esPrimo(int numero);

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
  Serial.begin(9600);
}

// Número que será mostrado en el display.
int numero;
// Contador de números primos.
int numeroPrimo = 2;
// Contador de números naturales.
int numeroContador = 0;

// Variables para detectar la pulsación de los botones.
bool btnSumarEstadoActual;
bool btnRestarrEstadoActual;
bool btnResetEstadoActual;

/* 
 * Variables para obtener el estado anterior de los botones, y así poder
 * ejecutar una acción por única vez, de acuerdo al cambio de estado del botón.
 * Se inicializan en false, ya que al principio del programa no estarán siendo presionados.
 */
bool btnSumarEstadoAnterior = false;
bool btnRestarrEstadoAnterior = false;
bool btnResetEstadoAnterior = false;

// Posición del interruptor deslizante.
bool estadoSwitch;

// Estructruras de datos para obtener el cambio de estado en un botón
// y actualizar su estado anterior
estructura deteccionSuma;
estructura deteccionResta;
estructura deteccionReset;

void loop()
{

  //numero = normalizarContador(numero, 99);

  btnSumarEstadoActual = !(digitalRead(AUMENTAR));
  btnRestarrEstadoActual = !(digitalRead(DISMINUIR));
  btnResetEstadoActual = !(digitalRead(RESET));
  estadoSwitch = !(digitalRead(SWITCH));

  deteccionSuma = detectarPulsacion(btnSumarEstadoActual, btnSumarEstadoAnterior);
  btnSumarEstadoAnterior = deteccionSuma.estadoAnterior;

  deteccionResta = detectarPulsacion(btnRestarrEstadoActual, btnRestarrEstadoAnterior);
  btnRestarrEstadoAnterior = deteccionResta.estadoAnterior;

  deteccionReset = detectarPulsacion(btnResetEstadoActual, btnResetEstadoAnterior);
  btnResetEstadoAnterior = deteccionReset.estadoAnterior;

  if (estadoSwitch == LOW){
    if (deteccionSuma.ejecucion){
    numeroContador++;
    }
    if (deteccionResta.ejecucion){
    numeroContador--;
    }
    if (deteccionReset.ejecucion){
    numeroContador = 0;
    }
    numeroContador = normalizarContador(numeroContador, 99);
    numero = numeroContador;
  }
  else{
    if (deteccionSuma.ejecucion){
      numeroPrimo++;
      while (!esPrimo(numeroPrimo)){
        if (numeroPrimo > 99){
            numeroPrimo = 2;
            break;
        }
        numeroPrimo++;
        Serial.println(numeroPrimo);
      }
    }
    if (deteccionResta.ejecucion){
      numeroPrimo--;
      while (!esPrimo(numeroPrimo)){
        if (numeroPrimo < 2){
            numeroPrimo = 97;
            break;
        }
        numeroPrimo--;
      }
    }
    if (deteccionReset.ejecucion){
      numeroPrimo = 2;
    }
    numero = numeroPrimo;  
  }
  Serial.println(numero);
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

estructura detectarPulsacion(bool estadoActual, bool estadoAnterior){
  // Declaración de la variable principal.
  estructura devolucion;
  // Asignación del estado anterior de la variable que será devuelta, 
  //en base al parámetro.
  devolucion.estadoAnterior = estadoAnterior;
  
  /* 
   * En caso de haber un cambio en el estado, el estado anterior
   * pasa a ser igual al estado actual.
   * La ejecución toma el valor del estado actual de la entrada.
   */
  if (estadoActual != estadoAnterior){
    devolucion.estadoAnterior = estadoActual;
    devolucion.ejecucion = estadoActual;
  }
  // Si no hay un cambio en el estado, la acción no será ejecutada.
  else{
    devolucion.ejecucion = false;
  }
      
  return devolucion;
}

int normalizarContador(int contador, int limiteSuperior){

  if (contador > limiteSuperior){
    contador = contador - (limiteSuperior + 1);
  }
  if (contador < 0){
    contador = (limiteSuperior + 1) + contador;
  }

  return contador;
}

bool esPrimo(int numero) {
  // No existen números primos menores a 2.
  if (numero < 2) {
    return false;
  }
  /*
   * Se buscan divisores del número, entre 2 (el número primo más pequeño), 
   * y la mitad del número (los números superiores a su mitad no pueden ser divisores).
   * Si encuentra un divisor, se devuelve false.
   */
  for (int i = 2; i <= (numero / 2); i++) {
    if (numero % i == 0) {
    return false;
    }
}
  return true;
}