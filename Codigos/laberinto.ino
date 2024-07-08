#include <NewPing.h>

// Definición de pines
#define TRIGGER_PIN_LEFT  2
#define ECHO_PIN_LEFT     3
#define TRIGGER_PIN_FRONT 4
#define ECHO_PIN_FRONT    5
#define TRIGGER_PIN_RIGHT 6
#define ECHO_PIN_RIGHT    7

#define MAX_DISTANCE_LEFT 100  // Distancia máxima a medir para el sensor izquierdo (en cm)
#define MAX_DISTANCE_FRONT 200 // Distancia máxima a medir para el sensor frontal (en cm)
#define MAX_DISTANCE_RIGHT 100 // Distancia máxima a medir para el sensor derecho (en cm)
#define DEFAULT_DISTANCE 300   // Distancia predeterminada cuando se lee 0

NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE_LEFT);
NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE_FRONT);
NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE_RIGHT);

const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 10;
const int motorPin4 = 11;

void setup() {
  // Configurar los pines de los motores
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int distanceLeft = sonarLeft.ping_cm();
  int distanceFront = sonarFront.ping_cm();
  int distanceRight = sonarRight.ping_cm();

  // Manejo de lecturas de 0
  if (distanceLeft == 0) {
    distanceLeft = DEFAULT_DISTANCE;
  }
  if (distanceFront == 0) {
    distanceFront = DEFAULT_DISTANCE;
  }
  if (distanceRight == 0) {
    distanceRight = DEFAULT_DISTANCE;
  }

  Serial.print("Left: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Front: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Right: ");
  Serial.print(distanceRight);
  Serial.println(" cm");

  if (distanceFront < 9 && distanceLeft < 9 && distanceRight < 9) {
    // Callejón sin salida
    turn180();
  } else if (distanceFront < 9) {
    // Obstáculo al frente
    if (distanceLeft > distanceRight) {
      turnLeftDynamic();
    } else {
      turnRightDynamic();
    }
  } else {
    // Seguir derecho ajustando
    adjustDirection(distanceLeft, distanceRight);
    forward();
  }
  delay(100); // Espera 100 ms entre lecturas y movimientos
}

void forward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void backward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void turnLeft(int tiempo) {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(tiempo); // Ajusta el tiempo de giro según tu robot
  stopMotors();
}

void turnRight(int tiempo) {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(tiempo); // Ajusta el tiempo de giro según tu robot
  stopMotors();
}

void turn180() {
  turnLeftDynamic();  // Realiza un giro de 180 grados
  turnLeftDynamic();  // Realiza un giro de 180 grados
}

void adjustDirection(int left, int right) {
  if (left > right) {
    // Pequeña corrección hacia la izquierda
    turnLeft(50);
  } else if (right > left) {
    // Pequeña corrección hacia la derecha
    turnRight(50);
  }
}

void stopMotors() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void turnLeftDynamic() {
  int initialLeft = sonarLeft.ping_cm();
  int initialRight = sonarRight.ping_cm();
  int newLeft, newRight;
  
  while (true) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    delay(50); // Pequeño giro incremental
    stopMotors();
    
    newLeft = sonarLeft.ping_cm();
    newRight = sonarRight.ping_cm();
    
    if (newLeft < initialLeft || newRight > initialRight) {
      // Si el sensor izquierdo mide menos o el sensor derecho mide más, el giro es suficiente
      break;
    }
  }
}

void turnRightDynamic() {
  int initialLeft = sonarLeft.ping_cm();
  int initialRight = sonarRight.ping_cm();
  int newLeft, newRight;
  
  while (true) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    delay(50); // Pequeño giro incremental
    stopMotors();
    
    newLeft = sonarLeft.ping_cm();
    newRight = sonarRight.ping_cm();
    
    if (newRight < initialRight || newLeft > initialLeft) {
      // Si el sensor derecho mide menos o el sensor izquierdo mide más, el giro es suficiente
      break;
    }
  }
}
