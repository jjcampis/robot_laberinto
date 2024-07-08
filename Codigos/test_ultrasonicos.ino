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

void setup() {
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

  delay(100); // Espera 100 ms entre lecturas
}
