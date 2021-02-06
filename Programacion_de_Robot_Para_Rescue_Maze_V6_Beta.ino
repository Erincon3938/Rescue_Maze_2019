int Temperatura_de_Amb () ; 
int val ; 
int MotorDer1=2;//El pin 2 de arduino se conecta con el pin In1 del L298N
int MotorDer2=3;//El pin 3 de arduino se conecta con el pin In2 del L298N
int MotorIzq1=4;//El pin 7 de arduino se conecta con el pin In3 del L298N
int MotorIzq2=5;//El pin 4 de arduino se conecta con el pin In4 del L298N
int Sensor_Piso=6;
const int Sensor_de_Temp = A1;
int Led = 24 ;
int Valor ;
int Sensor_Piso= 22 ;
const int Trigger_Dela = 8;   //Pin digital 2 para el Trigger del sensor
const int Echo_Dela = 9;
const int Trigger_Der = 10;   //Pin digital 2 para el Trigger del sensor
const int Echo_Der = 11;
const int Trigger_Izq = 12;   //Pin digital 2 para el Trigger del sensor
const int Echo_Izq = 13;
int d1;
int t1;
int d2;
int t2;
int d3;
int t3;
int Distancia1; 
int Distancia2; 
int Distancia3; 
int Temp_C ;
int16_t mx, my, mz;
float declinacion= 54.10 ;
int ax, ay, az;
int gx, gy, gz;




void setup() { 

  pinMode(MotorDer1, OUTPUT); 
  pinMode(MotorDer2, OUTPUT);
  pinMode(MotorIzq1, OUTPUT); 
  pinMode(MotorIzq2, OUTPUT); 
  pinMode (Sensor_Piso, INPUT) ;
  Serial.begin(9600);
  pinMode(Trigger_Dela, OUTPUT); //pin como salida
  pinMode(Echo_Dela, INPUT);  //pin como entrada
  digitalWrite(Trigger_Dela, LOW);
  pinMode(Trigger_Der, OUTPUT); //pin como salida
  pinMode(Echo_Der, INPUT);  //pin como entrada
  digitalWrite(Trigger_Der, LOW);
  pinMode(Trigger_Izq, OUTPUT); //pin como salida
  pinMode(Echo_Izq, INPUT);  //pin como entrada
  digitalWrite(Trigger_Izq, LOW);

} 

void Temperatura (int & Temp_C) {
  
  int lectura = analogRead(Sensor_de_Temp);
  float voltaje = 5.0 /1024 * lectura ; 
  float temp = voltaje * 100 -50 ;
  Serial.println(temp) ;
  delay(60);
  Serial.println(" Grados Celsius"); 
  Temp_C == temp ; 

}

void Piso () { 

  Valor = digitalRead (Sensor_Piso);

  if ( Valor == LOW) {

    Retroceder () ; 
    delay (940);
    Izquierda ();
    delay (1014);
    Serial.print(Valor);
    Serial.println("Linea");

  }

  else {

    Avanzar ();

  }

}

void Retroceder(){ 

  digitalWrite(MotorDer1,HIGH);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,HIGH);
  digitalWrite(MotorIzq2,LOW);

}

void Avanzar(){ 

  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,HIGH);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,HIGH);

}

void Izquierda(){ // Tiempo de Giro de 555

  digitalWrite(MotorDer1,HIGH);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,HIGH);

}

void Derecha(){  // Tiempo de Giro de 500

  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,HIGH);
  digitalWrite(MotorIzq1,HIGH);
  digitalWrite(MotorIzq2,LOW);

}

void Parar() { 

  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,LOW);

}

void Ultra_Dela (int &Distancia1) {

  long t1; //timepo que demora en llegar el eco
  long d1; //distancia en centimetros

  digitalWrite(Trigger_Dela, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_Dela, LOW);
  t1 = pulseIn(Echo_Dela, HIGH); //obtenemos el ancho del pulso
  Distancia1 = t1/59;             //escalamos el tiempo a una distancia en cm
  Serial.print("Distancia Delantera: ");
  Serial.print(Distancia1);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(10);          //Hacemos una pausa de 100ms

}

void Ultra_Der (int &Distancia2) {

  long t2; //timepo que demora en llegar el eco
  long d2; //distancia en centimetros

  digitalWrite(Trigger_Der, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_Der, LOW);
  t2 = pulseIn(Echo_Der, HIGH); //obtenemos el ancho del pulso
  Distancia2 = t2/59;             //escalamos el tiempo a una distancia en cm
  Serial.print("Distancia Derecha: ");
  Serial.print(Distancia2);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(10);          //Hacemos una pausa de 100ms

}

void Ultra_Izq (int &Distancia3) {
  long t3; //timepo que demora en llegar el eco
  long d3; //distancia en centimetros

  digitalWrite(Trigger_Izq, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_Izq, LOW);
  t3 = pulseIn(Echo_Izq, HIGH); //obtenemos el ancho del pulso
  Distancia3 = t3/59;             //escalamos el tiempo a una distancia en cm
  Serial.print("Distancia Izquierda: ");
  Serial.print(Distancia3);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(10);          //Hacemos una pausa de 100ms

}

void Laberinto () { 
  
  Ultra_Dela(Distancia1);
  Ultra_Der(Distancia2); 
  Ultra_Izq (Distancia3);
  
  if ((Distancia1 > 6) ) {

    Avanzar () ;  
    
  }
  
  else if (Distancia2 > 8) {
    
    Derecha () ; 
    delay (400) ;
    
  }
  
  else if (Distancia3 > 8 ) { 
    
    Izquierda () ;   
    delay (555) ; 
    
  } 
  
}


void loop () { 

  Laberinto () ;

} 
