
/* 초음파센서로 사람이 들어오면 LED에 불을 켭니다. */

#define trigPin  2 // trigPin
#define echoPin  3 // echoPin
#define B_LED  4 // BlueColor LED

int cnt = 0; // 카운트 저장할 변수
float duration, distance; // 시간과 거리 

void setup(){
  Serial.begin(9600); // Serial통신 속도

  pinMode(trigPin, OUTPUT); // tirgPin을 출력으로
  pinMode(echoPin, INPUT); // echoPin을 입력으로
  pinMode(B_LED, OUTPUT); // B_LED를 출력으로 설정합니다.
}

void loop(){
  /* trig와 echo로 거리를 결정짓습니다. */

  digitalWrite(trigPin, HIGH);
  delay(10); // 0.01 동안 대기.
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // echoPin에 저장된 시간
  distance = ((float)(340*duration) / 10000) / 2; // cm로 계산

  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println("cm\n");
  delay(500);
  
  if(distance <= 50) // 50cm를 기준으로 합니다.
  {                  // 이 범위 안에 들어오면 증가시킵니다.
    cnt++; // 1 증가시킵니다.
    Serial.println(cnt);
    Serial.println("LED가 켜집니다.");
    delay(1000);

    digitalWrite(B_LED, HIGH);
  }
}
