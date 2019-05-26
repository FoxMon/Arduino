/* 가변 저항으로 서보 모터의 각도를 제어합니다. */

#include <Servo.h> // 서보모터 라이브러리 사용을 위해, 헤더파일 추가

int Potent = 3; // 가변 저항 연결핀 3번
int sensorValue = 0; // 센서 값
Servo s; // 클래스개념

void setup() {
  s.attach(2); // 서보모터에 펄스를 공급해줄 포트 2번으로 설정

  pinMode(Potent, INPUT); // 가변저항 핀을 입력
}

void loop() {
  sensorValue = analogRead(Potent); // 가변저항값을 읽어들임
  // 가변저항의 입력되니 값을 0~1023 범위의 값을 읽어서, 0~179 범위의 출력
  // 값으로 서보모터를 제어함.
  s.write(map(sensorValue, 0, 1023, 0, 179));
  delay(200);
}
