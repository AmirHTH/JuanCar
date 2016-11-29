#include <Servo.h>
int LINEA=0;
int NOLINEA=1;

Servo servoIzq;
Servo servoDer;

int pinServoIzq = 8;
int pinServoDer = 9;

int pinIrDer = 3;
int pinIrIzq = 2;



void setup() {
  servoIzq.attach(pinServoIzq);
  servoDer.attach(pinServoDer);

  pinMode( pinIrDer , INPUT);
  pinMode( pinIrIzq , INPUT);



}

void loop() {
  // salir por IZQ
  if (digitalRead(pinIrDer) == LINEA && digitalRead(pinIrIzq) == NOLINEA){
  
    giraDerecha(0);
  }

  // salir por DER
  if (digitalRead(pinIrDer) == NOLINEA && digitalRead(pinIrIzq) == LINEA){
  
    giraIzquierda(0);
  }

  //seguir
  if (digitalRead(pinIrDer) == LINEA && digitalRead(pinIrIzq) == LINEA){
  
    avanzar(0);
  }

  // No detecto nada
   if (digitalRead(pinIrDer) == NOLINEA && digitalRead(pinIrIzq) == NOLINEA){
  
    parar();
  }
 

}


void giraDerecha (int relentizar)
{
  servoIzq.write(0+relentizar); 
  servoDer.write(90);

  
}

void giraIzquierda (int relentizar)
{
  servoIzq.write(90); 
  servoDer.write(180-relentizar);

}


void rotaDerecha (int relentizar)
{
  servoIzq.write(0+relentizar); 
  servoDer.write(180-relentizar);
 
}

void rotaIzquierda (int relentizar)
{
  servoIzq.write(0+relentizar); 
  servoDer.write(180-relentizar);

}

void parar()
{
  servoIzq.write(90); 
  servoDer.write(90);

}

void avanzar(int relentizar)
{

  servoIzq.write(0+relentizar); 
  servoDer.write(180-relentizar);
}

void retroceder(int relentizar)
{
  servoIzq.write(0+relentizar); 
  servoDer.write(0+relentizar);

}


