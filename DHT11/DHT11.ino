// 데이터 통신 이해하기
// 온습도 센서 ( DHT11 Temperature and humidity sensor)

int DHpin = 2; // 온습도 데이터 출력 핀을 2번
byte dat[5]; // dat 배열 길이 5, 정수형 변수 byte

byte read_data(){
  byte data;

  for(int i = 0; i < 8; i++){
    if(digitalRead(DHpin) == LOW){
      while(digitalRead(DHpin) == LOW); // 50us동안 기다림

      delayMicroseconds(30); // HIGH의 지속시간을 결정, 0또는1로 결정됨 파형에 따라서

      if(digitalRead(DHpin) == HIGH){
        data |= ( 1 << (7-i));
      }

      while(digitalRead(DHpin) == HIGH); // 1데이터, 다음 수신을 기다림
    }
  }

  return data;
}

void start_test(){
  digitalWrite(DHpin, LOW);
  delay(30); // LOW의 상태가 18ms보다 크면, DHT11의 신호를 감지하기 시작함

  digitalWrite(DHpin, HIGH);
  delayMicroseconds(40); // DHT11의 신호를 기다림

  pinMode(DHpin, INPUT);
  
  while(digitalRead(DHpin) == HIGH);
  delayMicroseconds(80);

  if(digitalRead(DHpin) == LOW){
    delayMicroseconds(80);
  }

  for(int i = 0; i < 4; i++){ // 온도와 습도의 데이터를 받음, 오류검출비트는 고려하지 않음
    dat[i] = read_data();
  }

  pinMode(DHpin, OUTPUT);
  
  digitalWrite(DHpin, HIGH);
}

void setup(){
  Serial.begin(9600);

  pinMode(DHpin, OUTPUT);
}

void loop(){
  start_test(); // 온습도 검사 시작

  Serial.print("Current Humidity = "); // 현재 습도 출력
  Serial.print(dat[0], DEC);
  Serial.print('.');
  Serial.print(dat[1], DEC);
  Serial.println('%');

  Serial.print("Current Temperature = "); // 현재 온도 출력
  Serial.print(dat[2], DEC);
  Serial.print('.');
  Serial.print(dat[3], DEC);
  Serial.println('C');

  delay(700);
}
