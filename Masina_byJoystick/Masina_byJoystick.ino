
int enA=9;
int in1=8;
int in2=7;
int enB=3;
int in3=5;
int in4=4;

int joyVert=A0;
int joyHorz=A1;

int MotorSpeed1=0;
int MotorSpeed2=0;
int becR=12;
int becG=13;
#define buzzerPin 2
int joyposVert=512;
int joyposHorz=512;
void setup() {
  // put your setup code here, to run once:
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(becR,OUTPUT);
  pinMode(becG,OUTPUT);
  digitalWrite(enA,LOW);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  digitalWrite(enB,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  joyposVert=analogRead(joyVert);
  joyposHorz=analogRead(joyHorz);

  if(joyposVert<460)
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    
    digitalWrite(becR,HIGH);
    digitalWrite(becG,LOW); //sens rosu-verde
    
    joyposVert=joyposVert-460;
    joyposVert=joyposVert*(-1);
    MotorSpeed1=map(joyposVert,0,460,0,255);
    MotorSpeed2=map(joyposVert,0,460,0,255);
  }
  else if(joyposVert>564)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    
    digitalWrite(becR,LOW);
    digitalWrite(becG,HIGH); //sens verde-rosu
    
    MotorSpeed1=map(joyposVert,564,1024,0,255);
    MotorSpeed2=map(joyposVert,564,1024,0,255);
  }
  else
  {
    MotorSpeed1=0;
    MotorSpeed2=0;
  }
if(joyposHorz<460)
{
  noTone(buzzerPin);
  joyposHorz=joyposHorz-460;
  joyposHorz=joyposHorz*(-1);
  joyposHorz=map(joyposHorz,0,460,0,255);
  if(joyposHorz>=250)
  {
    tone(buzzerPin,60);
  }
  MotorSpeed1=MotorSpeed1-joyposHorz;
  MotorSpeed2=MotorSpeed2+joyposHorz;

  if(MotorSpeed1 <0) MotorSpeed1=0;
  if(MotorSpeed2>255) MotorSpeed2=255;
}
else if(joyposHorz>564)
{
  noTone(buzzerPin);
  joyposHorz=map(joyposHorz,564,1024,0,255);
  if(joyposHorz>=250)
  {
    tone(buzzerPin,60);
  }
  MotorSpeed1=MotorSpeed1+joyposHorz;
  MotorSpeed2=MotorSpeed2-joyposHorz;
 
  if(MotorSpeed1>255) MotorSpeed1=255;
  if(MotorSpeed2<0) MotorSpeed2=0;
}
if(MotorSpeed1<8) MotorSpeed1=0;
if(MotorSpeed2<8) MotorSpeed2=0;

static unsigned long lastMillis=0;
if(millis() - lastMillis >=100)
{
    lastMillis=millis();
 // Serial.print(" joyposVert este: ");
 // Serial.print(joyposVert);
 // Serial.print(" joyposHorz este: ");
 // Serial.print(joyposHorz);
 // Serial.print(" MotorSpeed1 este: ");
    Serial.print(MotorSpeed1);
 // Serial.print(" MotorSpeed2 este: ");
    Serial.print(",");
    Serial.print(MotorSpeed2);
    Serial.println();
}
analogWrite(enA,MotorSpeed1);
analogWrite(enB,MotorSpeed2);
}
