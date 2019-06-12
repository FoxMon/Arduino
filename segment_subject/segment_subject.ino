// SegmentLEDs PinMode 
int segmentLEDs[] = { 2, 3, 4, 5, 6, 7, 8, 9};
// LED 개수
int segmentLEDsNum = 8;
// Common Cathode
int digitForNum[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //0
  {0, 1, 1, 0, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1, 0}, //2
  {1, 1, 1, 1, 0, 0, 1, 0}, //3
  {0, 1, 1, 0, 0, 1, 1, 0}, //4
  {1, 0, 1, 1, 0, 1, 1, 0}, //5
  {1, 0, 1, 1, 1, 1, 1, 0}, //6
  {1, 1, 1, 0, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1, 0}, //8
  {1, 1, 1, 1, 0, 1, 1, 0}  //9
};
// 입력받은 숫자 저장할 int형 변수
int segNum;

void setup() {
  Serial.begin(9600);
  // 7세그먼트 각각 LED에 연결된 핀 OUTPIT 설정
  for(int i = 0; i < segmentLEDsNum; i++){
    pinMode(segmentLEDs[i], OUTPUT);
  }
}

void loop() {
  if(Serial.available()){ // Serial모니터로 숫자를 입력받고 해당 숫자가 출력되도록 합니다.
    segNum = Serial.parseInt(); // int형으로 숫자입력 받음
    
    for(int i = 0; i < segmentLEDsNum; i++){
      digitalWrite(segmentLEDs[i], digitForNum[segNum][i]);
    }
  }
}
