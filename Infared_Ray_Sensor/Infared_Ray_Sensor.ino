
// 적외선 센서로 라인 인식하기

void setup() {
  pinMode(2, INPUT); // 2번 핀을 입력
  pinMode(13, OUTPUT); // 13번 핀을 출력으로 설정

  Serial.begin(9600); // 시리얼 데이터 속도 9600
}

void loop() {
  if(digitalRead(2)){ // 2번핀 읽었을 때, HIGH일 경우
    digitalWrite(13, HIGH); // 13번 핀 HIGH

    Serial.println("White"); // 시리얼 모니터에 White 출력

    delay(100);

    digitalWrite(13, LOW); // 13번 핀 LOW

    delay(100);
  }
  else{ // LOW일 경우
    Serial.println("Black"); // Black

    delay(100);
  }
}
