/* 
 * 시리얼 통신으로 DC모터의 방향과 속도를 컨트롤함
 * 이때 주의할 점은, 방향이 갑자기 바뀌는 경우 stop 했다가 다시 돌아감
*/ 

int enable = 4; // 동작스위친 핀
int in1 = 3; // 순방향 모터핀
int in2 = 2; // 역방향 모터핀
int spdnum; // 속도제어
char dir; // 방향제어
char tempDir; // 방향전환 확인

void setup() {
  Serial.begin(9600); // 시리얼통신속도 9600으로 설정
  pinMode(in1, OUTPUT); // 순방향 핀 출력 설정
  pinMode(in2, OUTPUT); // 역방향 핀 출력 설정
}

void loop() {
  if(Serial.available() != 0){
    tempDir = dir; // 입력받기 전 방향을 임시로 저장해 둠
    dir = Serial.read(); // char형으로 시리얼 모니터에서 방향을 읽어들임
    spdnum = Serial.parseInt(); // int형으로 시리얼 모니터에서 속도를 읽어들임

    if(dir == 'L'){
      if(tempDir != dir){ // 만약에 방향을 전환했다면 
      analogWrite(enable, 0); // 속도를 0으로 멈추고
      delay(800); // 0.8초의 딜레이를 줌 (방향 바꾸기 전 약간의 여지를 줌)
      }
      
      Serial.print("방향은 : ");
      Serial.println(dir);
      Serial.print("속도는 : ");
      Serial.println(spdnum);

      analogWrite(enable, spdnum); // 스피드값 출력
      digitalWrite(in1, HIGH); // 순방향 HIGH
      digitalWrite(in2, LOW); // 역방향 LOW
    }
    else if(dir == 'R'){ // 방향이 바뀌었는지 확인
      if(tempDir != dir){
      analogWrite(enable, 0);
      delay(800);
      }
      
      Serial.print("방향은 : ");
      Serial.println(dir);
      Serial.print("속도는 : ");
      Serial.println(spdnum);

      analogWrite(enable, spdnum); // 스피드값 출력
      digitalWrite(in1, LOW); // 순방향 LOW
      digitalWrite(in2, HIGH); // 역방향 HIGH
    }
  }
}
