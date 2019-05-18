int button = 1; // button핀
int segmentLEDsNum[] = {2,3,4,5,6,7,8,9}; // 세그먼트핀
int digitLEDs[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //0
  {0, 1, 1, 0, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1, 0}, //2
  {1, 1, 1, 1, 0, 0, 1, 0}, //3
  {0, 1, 1, 0, 0, 1, 1, 0}, //4
  {1, 0, 1, 1, 0, 1, 1, 0}, //5
  {1, 0, 1, 1, 1, 1, 1, 0}, //6
  {1, 1, 1, 0, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1, 0}, //8
  {1, 1, 1, 1, 0, 1, 1, 0}, //9
};
int segNum = 8; // 세그먼트 핀 숫자개수
int buttonState = 0; // 버튼입력상태
int cnt = 0; // 카운트

void setup() {
  for(int i = 0; i < segNum; i++){
    pinMode(segmentLEDsNum[i], OUTPUT);
  }
  pinMode(button, INPUT);
}

void loop() {
  buttonState = digitalRead(button);

  if(buttonState == HIGH){
    for(int i = 0; i < segNum; i++){
      digitalWrite(segmentLEDsNum[i], digitLEDs[cnt][i]);
    }
    delay(1000);
    cnt++;
  }
  if(cnt == 10){
    cnt = 0;
  }
}
