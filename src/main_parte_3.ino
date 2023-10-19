// UTN FRA - Sistema de Procesamiento de Datos
// Iván Laurito

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
#define SWITCH_NUMEROS 2
#define SWITCH_INGRESO 1
#define UNIDADES A0
#define DECENAS A1
#define SENSOR_TEMPERATURA A3
#define SENSOR_LUZ A4
#define MOTOR 6
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
  pinMode(SWITCH_NUMEROS, INPUT_PULLUP);
  pinMode(SWITCH_INGRESO, INPUT_PULLUP);
  pinMode(UNIDADES, OUTPUT);
  pinMode(DECENAS, OUTPUT);
  pinMode(SENSOR_TEMPERATURA, INPUT);
  pinMode(SENSOR_LUZ, INPUT);
  digitalWrite(UNIDADES, 0);
  digitalWrite(DECENAS, 0);
  encenderNumero(0);
  Serial.begin(9600);
}

int numero;
int numeroTemperatura;
int numeroLuz;
int numeroPrimo = 2;
int numeroContador = 0;
int numeroMotor;
int lecturaTemperatura;
int lecturaLuz;

bool btnSumarEstadoActual;
bool btnRestarrEstadoActual;
bool btnResetEstadoActual;

bool btnSumarEstadoAnterior = false;
bool btnRestarrEstadoAnterior = false;
bool btnResetEstadoAnterior = false;
bool estadoSwitchNumeros;
bool estadoSwitchIngreso;

estructura deteccionSuma;
estructura deteccionResta;
estructura deteccionReset;



/**
*
*  Primero obtengo el valor devuelto por el sensor y
*  y luego uso la función map() para que devuelva un
*  valor entre 0 y 99 según la intensidad de la luz
*  que el sensor capte.
*
*  Uso las mismas funciones que en las partes 1 y 2
*  para mostrar los números en el display usando el
*  método de la multiplexación.
*
*  Nótese que para el sensor de luz ambiental, tanto
*  el cable de 5 voltios como la entrada analógica
*  van conectados al colector. El cable de 5 voltios
*  presenta en su recorrido una resistencia de 100
*  ohmios y es con base en este valor que se toman
*  los valores máximos y mínimos obtenidos desde el
*  sensor antes de la función map(). Si la magnitud
*  de la resistencia fuese otra, la función map() con
*  los valores presentes en este código quedaría
*  obsoleta y habría que cambiar algunos de sus
*  parámetros para que el programa siga funcionando
*  correctamente.
*
*/
void loop()
{
  btnSumarEstadoActual = !(digitalRead(AUMENTAR));
  btnRestarrEstadoActual = !(digitalRead(DISMINUIR));
  btnResetEstadoActual = !(digitalRead(RESET));
  estadoSwitchNumeros = !(digitalRead(SWITCH_NUMEROS));
  estadoSwitchIngreso = !(digitalRead(SWITCH_INGRESO));

  deteccionSuma = detectarPulsacion(btnSumarEstadoActual, btnSumarEstadoAnterior);
  btnSumarEstadoAnterior = deteccionSuma.estadoAnterior;

  deteccionResta = detectarPulsacion(btnRestarrEstadoActual, btnRestarrEstadoAnterior);
  btnRestarrEstadoAnterior = deteccionResta.estadoAnterior;

  deteccionReset = detectarPulsacion(btnResetEstadoActual, btnResetEstadoAnterior);
  btnResetEstadoAnterior = deteccionReset.estadoAnterior;
  
  
  
  if (estadoSwitchIngreso == HIGH) {

    if (estadoSwitchNumeros == HIGH){
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
  }
  else
  {
    
    lecturaTemperatura = analogRead(SENSOR_TEMPERATURA);
    lecturaLuz = analogRead(SENSOR_LUZ);
    numeroTemperatura = map(lecturaTemperatura, 20, 358, 0, 49);
    numeroLuz = map(lecturaLuz, 1023, 976, -1, 49);
    numero = numeroTemperatura + numeroLuz;
    numeroMotor = map(numero, 0, 99, 0, 255);
    analogWrite(MOTOR, numeroMotor);
    
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
  if (numero < 2) {
    return false;
  }
  for (int i = 2; i <= (numero / 2); i++) {
    if (numero % i == 0) {
    return false;
    }
}
  return true;
}