#include "pitches.h"
#include "PlayMelody.h"
/*
 * upButton이 눌리면 숫자가 올라갑니다.
 * 해당 state에 해당하는 event를 처리합니다.
 * downButton이 눌릴 경우에는 숫자가 내려갑니다.
 * SerialMonitor로 state를 처리할 수 있어야 합니다.
 * 스피커로 노래 출력하는거 추가하기.
 * 시리얼로 state 변화주기
*/

#define STATE_MAX 10
#define PIEZO_SPK 1
#define SEVEN_SEG 0

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
int numTones = 8;
unsigned int tones[] = {262, 294, 330, 349, 392, 440, 494, 523};
unsigned int melody[] = { // 멜로디를 위한 음표
   NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4,
   NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, 0
};
unsigned int noteDurations[] = { // 음표 길이들 : 4 = 4분(1/4) 음표, 8 = 8분(1/8) 음표, 
   4, 4, 4, 4, 4, 4, 2,
   4, 4, 4, 4, 2, 2
};
// int potent = 0; // 가변저항기 핀 14번
// int ledPin = 0; // LED핀
int speakerPin = 14; // 입력 핀의 상태를 읽기 위한 변수
// int DHpin = 0; // 온습도 핀
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
     dat[i] = Read_Data();
  }
  
  pinMode (DHpin, OUTPUT);
  digitalWrite (DHpin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
}
*/

// 음정 출력
/*
void Play_Doremi() {
  for(int i=0; i<numTones; i++){
    tone(speakerPin, tones[i]);
        // tone(pin, frquency, duration);
        delay(500);
      }
    noTone(speakerPin);
}
*/
//학교종이 땡땡땡
void Play_School_Bell(void)
{ 
  int noteDuration = 0, thisNote = 0, pauseBetweenNotes = 0;
  for (thisNote = 0; thisNote < sizeof(noteDurations) / sizeof(int); thisNote++) {

    // 음표 길이를 계산하기 위하여, 1초를 음표 타입으로 나눕니다. 
    // 예를 들어, 4분 음표 = 1000 / 4,  8분 음표 = 1000/8 등과 같이
    // 합니다.
    noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote]);
    delay(noteDuration);

    // 음표들을 구분하기 위하여, 음표 사이에 최소한의 지연 시간을
    // 음표 길이 + 30%가 잘 동작하는 것 같습니다:
    noTone(speakerPin);
    pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
     // 음 발생하는 것을 멈춤니다:
     noTone(speakerPin);
}

int Button_Int_Handler1(uint32_t ulPin){ // Button Interrupt Handler 1
  Serial.print("upButton_Interrupt");
  
  state_mode = (state_mode + 1) % STATE_MAX; // 현재 state에 +1
  
  Serial.print("STATE_MODE : ");
  Serial.println(state_mode);
}

int Button_Int_Handler2(uint32_t ulPin){ // Button Interrupt Handler 2
  Serial.print("downButton_Interrupt");
  
  state_mode = (state_mode - 1); // 현재 state에 -1

  if(state_mode < 0){ // state가 0인 상태에서 downButton이 눌려진다면
    state_mode = (STATE_MAX - 1); // state는 9인 상태로 돌아감
  }
  
  Serial.print("STATE_MODE : ");
  Serial.println(state_mode);
}

void Play_State_And_Change(void){
    switch(state_mode){ // state에 해당하는 event 실행
      case SEVEN_SEG:
        Serial.println("STATE 0.");
        break;
      case PIEZO_SPK:
        Serial.println("STATE 1.");
        break;
      /*case :
        Serial.println("2. ");
        break;
      case :
        Serial.println("3. ");
        break;
      case :
        Serial.println("4. ");
        break;
      */
      default :
        Serial.println("STATE ERROR");
        break;
    }
}

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도
  
  pinMode(upButton, INPUT); // up버튼 핀 인풋
  pinMode(downButton, INPUT);
  // pinMode(ledPin, OUTPUT);
  // pinMode(speakerPin, OUTPUT);

  attachPinInterrupt(upButton, Button_Int_Handler1, HIGH); // upButton I.H
  attachPinInterrupt(downButton, Button_Int_Handler2, HIGH); // downButton I.H

  for(int i = 0; i < segNum; i++){ // 7-Segment를 전부 OUTPUT으로..
    pinMode(segmentLEDsNum[i], OUTPUT);
    delay(10);
    digitalWrite(segmentLEDsNum[i], LOW);
  }
}

void loop() {
  char input = 0;

  Play_State_And_Change();
  
  if(Serial.available()) { // Serial Monitor로 state 입력을 받음
    input = Serial.read();

    if(input >= '0' && input <= '9'){
      input = input - '0';
      state_mode = input % STATE_MAX; // 현재 state의 상태를 유지
      Play_State_And_Change();
    }
    else{
      Serial.println("type 0 ~ 9 ");
    }
  }
}
