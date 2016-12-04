#include <Servo.h>
Servo servoIzq;
Servo servoDer;

int pinServoIzq = 8;
int pinServoDer = 9;

int pinIrDer = 3;
int pinIrIzq = 2;

struct Salida {
  boolean activo = false;
  int servoIzq = -1;
  int servoDer = -1;
};

Salida sComp1 ;
Salida sComp2 ;
Salida sComp3 ;
int x, contador = 0;

void setup() {
  Serial.begin(9600);
  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);

  pinMode( pinIrDer , INPUT);
  pinMode( pinIrIzq , INPUT);
}

void loop() {
 
  int valorSensorIzq =digitalRead(pinIrIzq);
  int valorSensorDer = digitalRead(pinIrDer);



  comp1_EntratEnPista(valorSensorIzq, valorSensorDer);
  if ( sComp1.activo ) {

   contador++;
  if (contador == 10000)
  {
    if(x<90){
      x++;
    }
    contador = 0;
  }
     servoIzq.write(sComp1.servoIzq); 
     servoDer.write(sComp1.servoDer);
  
    return;
  }

  comp2_CorregirTrayectoria(valorSensorIzq, valorSensorDer);
  if ( sComp2.activo ) {
    x=0;
     servoIzq.write(sComp2.servoIzq); 
     servoDer.write(sComp2.servoDer);
    return;
  }

  comp3_Avanzar(valorSensorIzq, valorSensorDer);
  if ( sComp3.activo ) {
    x=0;
   servoIzq.write(sComp3.servoIzq); 
   servoDer.write(sComp3.servoDer);
    return;
  }


}

void comp1_EntratEnPista(int valorSensorIzq, int valorSensorDer) {
  sComp1.activo = false;
  if ( valorSensorIzq == 1 && valorSensorDer == 1 ) {
    sComp1.activo = true;
    sComp1.servoIzq = 90-x; // Valores inventados
    sComp1.servoDer = 180; // Valores inventados
  }
}

void comp2_CorregirTrayectoria(int valorSensorIzq, int valorSensorDer) {
  sComp2.activo = false;
  if ( valorSensorIzq == 0 && valorSensorDer == 1 ) {
    sComp2.activo = true;
    sComp2.servoIzq = 90; // Valores inventados
    sComp2.servoDer = 180; // Valores inventados
  }
  if ( valorSensorIzq == 1 && valorSensorDer == 0 ) {
    sComp2.activo = true;
    sComp2.servoIzq = 0; // Valores inventados
    sComp2.servoDer = 90; // Valores inventados
  }
}

void comp3_Avanzar(int valorSensorIzq, int valorSensorDer) {
  sComp3.activo = false;
  if ( valorSensorIzq == 0 && valorSensorDer == 0) {
    sComp3.activo = true;
    sComp3.servoIzq = 0; // Valores inventados
    sComp3.servoDer = 180; // Valores inventados
  }
}



