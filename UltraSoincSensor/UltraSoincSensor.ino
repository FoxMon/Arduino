int trigPin = 2; // trigPin 2번핀
int echoPin = 3; // echoPin 3번핀

void setup(){
  Serial.begin(9600); // 시리얼 시작과 속도

  pinMode(trigPin, OUTPUT); // tirgPin을 출력
  pinMode(echoPin, INPUT); // echoPin을 입력
}

void loop(){
  float duration, distance; // duration, distance를 실수 변수

  digitalWrite(trigPin, HIGH);
  delay(10); // 0.01초 대기
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // echoPin이 유지한 시간 저장
  // High 였을 때 시간(초음파를 보냈다가 다시 돌아온 시간)을 가지고 계산

  distance = ((float)(340*duration)/10000)/2; // 왕복이니까 나누기 2
  // 음파의 속도 340, ms -> s로

  //Serial모니터에 Echo가 HIGH인 시간 및 거리를 표시
  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println("cm\n");
  delay(500);
}
