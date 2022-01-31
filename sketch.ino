#include <Adafruit_MPU6050.h>;
#include <Servo.h>;
#include <Wire.h>;

Adafruit_MPU6050 adaf;
//niebieskie servo
Servo servX;
//czerwone servo
Servo servY;
//zielone servo
Servo servZ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if(!adaf.begin()){

    Serial.println("nie dziala");
    while(1)delay(200);
  }

  adaf.setAccelerometerRange(MPU6050_RANGE_2_G);
  servX.attach(3);
  servY.attach(5);
  servZ.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(0x68, 6);
  while(Wire.available() == 0){}
  byte b1 = Wire.read();
  byte b2 = Wire.read();
  byte b3 = Wire.read();
  byte b4 = Wire.read();
  byte b5 = Wire.read();
  byte b6 = Wire.read();
  //zakres -3276 3276
  float x = b1 << 8 | b2;
  float y = b3 << 8 | b4;
  float z = b5 << 8 | b6;
  
  

 
 

  //mapuje wartosci odwrotnie, ujemne wychylenie na prawo, dodanie wychylenie na lewo. 
  // uzywam surowych wartosc, nie przeliczonich na G, bo przy skali -2 2 serva nie wychylą się do końca
  x = map(x,-32768.0,32768.0,180.0,0);
  y = map(y,-32768.0,32768.0,180.0,0.0);
  z = map(z,-32768.0,32768.0,180.0,0.0);


  servX.write(x);
  
  servY.write(y);
  
  servZ.write(z);

   float x_g = x/16384.0;
  float y_g = y/16384.0;
  float z_g = z/16384.0;

  Serial.println("Przyspieszenie w osi x: " + String(x_g));
  Serial.println("Przyspieszenie w osi y: " + String(y_g));
  Serial.println("Przyspieszenie w osi z: " + String(z_g));
  delay(2000);
}
