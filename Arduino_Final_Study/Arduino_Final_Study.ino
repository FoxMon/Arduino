/*
 * upButton이 눌리면 숫자가 올라갑니다.
 * 해당 state에 해당하는 event를 처리합니다.
 * downButton이 눌릴 경우에는 숫자가 내려갑니다.
 * SerialMonitor로 state를 처리할 수 있어야 합니다.
*/

#define STATE_MAX 5

int state_mode = 0;
int upButton = 1; // up버튼 핀 1
int downButton = 2; // down 버튼 핀 2
int buttonState = 0; // 버튼입력상태
int segmentLEDsNum[] = { 3, 4, 5, 6, 7, 8, 9, 10 }; // 세그먼트 핀 3 ~ 10
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
// int potent = 14; // 가변저항기 핀 14번
// int in1 = 11; // 순방향
// int in2 = 12; // 역방향 둘 중 하나만 쓸 듯??
// int enable = 13; // 모터속도속도 고정이라면??
// int ledPin = 14; // LED핀
// int speakerPin = 2; // 입력 핀의 상태를 읽기 위한 변수
// int DHpin = 4; // 온습도 핀
// byte dat [5]; // 온습도 받기 위한 byte 배열

// 온습도 데이타를 읽기
/*byte Read_Data() {
   byte data = 0;
   for (int i = 0; i < 8; i ++) {
     if (digitalRead (DHpin) == LOW) {
       while (digitalRead (DHpin) == LOW); // wait for 50us
       delayMicroseconds (30); // determine the duration of the high level to determine the data is '0 'or '1'
       if (digitalRead (DHpin) == HIGH)
         data |= (1 << (7-i)); // high front and low in the post
       while (digitalRead (DHpin) == HIGH); // data '1 ', wait for the next one receiver
      }
   }
 return data;
}
 */

// 온습도 Signal 받기 위함
/*void Signal_Test () {
//   pinMode(DHpin, OUTPUT); // bus down, send start signal
//   delay (30); // delay greater than 18ms, so DHT11 start signal can be detected
  
  digitalWrite (DHpin, LOW);
  delay(30);
  digitalWrite (DHpin, HIGH);
  delayMicroseconds (20); // Wait for DHT11 response
  
  pinMode (DHpin, INPUT);
  while (digitalRead (DHpin) == HIGH);
  delayMicroseconds (80); // DHT11 response, pulled the bus 80us
  while(digitalRead (DHpin) == LOW);
  delayMicroseconds (80); // DHT11 80us after the bus pulled to start sending data
  while(digitalRead (DHpin) == HIGH);

  for (int i = 0; i < 4; i ++){// receive temperature and humidity data, the parity bit is not considered
     dat[i] = read_data ();
  }
  
  pinMode (DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
}
*/

int Button_Int_Handler1(uint32_t ulPin){ // Button Interrupt Handler 1
  Serial.print("upButton_Interrupt");
  
  state_mode = (state_mode + 1) % STATE_MAX; // 현재 state에 +1
  
  Serial.print("STATE_MODE : ");
  Serial.println(state_mode);
}

int Button_Int_Handler2(uint32_t ulPin){ // Button Interrupt Handler 2
  Serial.print("downButton_Interrupt");
  
  state_mode = (state_mode - 1) % STATE_MAX; // 현재 state에 -1
  
  Serial.print("STATE_MODE : ");
  Serial.println(state_mode);
}

void State_Change(void){
    
}

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도
  
  pinMode(upButton, INPUT); // up버튼 핀 인풋
  pinMode(downButton, INPUT);
  // pinMode(ledPin, OUTPUT);

  attachPinInterrupt(upButton, Button_Int_Handler1, HIGH); // upButton I.H
  attachPinInterrupt(downButton, Button_Int_Handler2, HIGH); // downButton I.H

  for(int i = 0; i < segNum; i++){ // 7-Segment를 전부 OUTPUT으로..
    pinMode(segmentLEDsNum[i], OUTPUT);
    delay(10);
    digitalWrite(segmentLEDsNum[i], LOW);
  }
}

void loop() {
}
