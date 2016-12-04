#include <Servo.h>
int LINEA=0;
int NOLINEA=1;

// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
int enableA = 2;
int pinA1 = 3;
int pinA2 = 4;

//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableB = 7;
int pinB1 = 5;
int pinB2 = 6;

//This lets you run the loop a single time for testing
//boolean run = true;
boolean tiempoAlSuelo = true;

//Servo Sonar variables
Servo servoSonar;
int pinServoSonar = 8;

//Sonar variables
long distanciaSonar;
long tiempoRespuestaSonar;

int pinTrigSonar = 13;
int pinEchoSonar = 12;




void setup() {
 // Serial.begin(9600);
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
 
  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);

  servoSonar.attach(pinServoSonar);
  
  pinMode(pinTrigSonar , OUTPUT); /* trig envía el pulso ultrasónico */
  pinMode(pinEchoSonar, INPUT); /* Echo capta el rebote del pulso ultrasónico*/
}

void loop() {
  if (tiempoAlSuelo) {
     
    leerSonar();
    servoSonar.write(90);
    tiempoAlSuelo = false;
    delay(1000);
  }
    enableMotors();
    
    
    //Leemos sonar para saber si podemos ir forward
    //Si la distancia es de mas de 30 cm podemos seguir adelante
    
    leerSonar();
    if(distanciaSonar > 20){
        //Go forward
        forward(500);
    }else{
      //Si hay un obstaculo a menos de 10 cm habra que girar.
      //Comprobamos obtáculos a derecha
      comprobarObstaculoSonarDcha();
      //Si no hay obstáculos en 10 cm, vamos a la derecha
      if(distanciaSonar > 10){
        turnRight(500);
      } else{
        comprobarObstaculoSonarIzq();
        if(distanciaSonar > 10){
          turnLeft(500);
        } else{
          //Camino bloqueado en frente, izq y dcha. Vamos hacia atras.
          backward(500);
        }
      }
    }
    /*
    
    
    //Go backward
    backward(800);
    //Go forward
    forward(400);
    //Turn left
    turnLeft(400);
    coast(200);
    forward(800);
    backward(800);
    //Turn right
    turnRight(800);
    coast(200);
    //This stops the loop
    //run = false; 
*/

    //servoSonar.write(0);
    //delay(500);
    
    //delay(5000);
    //servoSonar.write(180);
    //delay(500);    
}


void comprobarObstaculoSonarDcha(){
 // Serial.println("Comprobando a Dcha");
  servoSonar.write(0);
  delay(500);
  leerSonar();
}

void comprobarObstaculoSonarIzq(){
 // Serial.println("Comprobando a Izq");
  servoSonar.write(180);
  delay(500);
  leerSonar();
}

void leerSonar(){
  digitalWrite(pinTrigSonar,LOW); /* Por seguridad volvemos a poner el Trig a LOW*/
  delayMicroseconds(5);

  digitalWrite(pinTrigSonar, HIGH); /* Emitimos el pulso ultrasónico */
  delayMicroseconds(10);

  tiempoRespuestaSonar = pulseIn(pinEchoSonar, HIGH); /* Medimos la longitud del pulso entrante Cuanto tiempo tarda la entrada en pasar de HIGH a LOW retorna microsegundos */
 // Serial.println("Tiempo "+ String(tiempoRespuestaSonar)+" microsegundos");

  distanciaSonar = int(0.017*tiempoRespuestaSonar); /* Calcular la distancia conociendo la velocidad */
 // Serial.println("Distancia "+ String(distanciaSonar)+"cm");
  
  //delay(100);
}

//Define high-level H-bridge commands
 
void enableMotors()
{
 motorAOn();
 motorBOn();
}
 
void disableMotors()
{
 motorAOff();
 motorBOff();
}
 
void forward(int time)
{
 servoSonar.write(90);
 motorAForward();
 motorBForward();
 delay(time);
}
 
void backward(int time)
{
 servoSonar.write(90);
 motorABackward();
 motorBBackward();
 delay(time);
}
 
void turnLeft(int time)
{
 motorABackward();
 motorBForward();
 delay(time);
}
 
void turnRight(int time)
{
 motorAForward();
 motorBBackward();
 delay(time);
}
 
void coast(int time)
{
 motorACoast();
 motorBCoast();
 delay(time);
}
 
void brake(int time)
{
 motorABrake();
 motorBBrake();
 delay(time);
}
//Define low-level H-bridge commands
 
//enable motors
void motorAOn()
{
 digitalWrite(enableA, HIGH);
}
 
void motorBOn()
{
 digitalWrite(enableB, HIGH);
}
 
 //disable motors
void motorAOff()
{
 digitalWrite(enableB, LOW);
}
 
void motorBOff()
{
 digitalWrite(enableA, LOW);
}
 
 //motor A controls
void motorAForward()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, LOW);
}
 
void motorABackward()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, HIGH);
}
 
//motor B controls
void motorBForward()
{
 digitalWrite(pinB1, HIGH);
 digitalWrite(pinB2, LOW);
}
 
void motorBBackward()
{
 digitalWrite(pinB1, LOW);
 digitalWrite(pinB2, HIGH);
}
 
//coasting and braking
void motorACoast()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, LOW);
}
 
void motorABrake()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, HIGH);
}
 
void motorBCoast()
{
 digitalWrite(pinB1, LOW);
 digitalWrite(pinB2, LOW);
}
 
void motorBBrake()
{
 digitalWrite(pinB1, HIGH);
 digitalWrite(pinB2, HIGH);
}

