
 /*     "학교 종이" 한 소절을 멜로디로 출력하기   
     Copyright (c) 2016 Blueinno.cc  All right reserved.
 */ 
  
#include "pitches.h"

int button =1;  // 버튼에 연결된 핀을 1번으로 설정
int buttonState = 0; // 버튼 핀의 상태를 저장하기 위함

// 멜로디를 위한 음표들:

int melody[] = {
   NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4,
   NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
};
 
// 음표 길이들 : 4 = 4분(1/4) 음표, 8 = 8분(1/8) 음표, 
int noteDurations[] = {
   4, 4, 4, 4, 4, 4, 2,
   4, 4, 4, 4, 2, 2,
};

void setup() { 
  pinMode(button, INPUT); // 버튼을 입력으로 설정
}


void loop() {
buttonState = digitalRead(button); // 버튼이 눌려 졌는지를 읽음
if(buttonState  == HIGH) {  // 조건; 버튼의 상태가 HIGH 이면
   
// melody[] 배열(array)에 있는 모든 음표들을 연주합니다:
   for (int thisNote = 0; thisNote < sizeof(noteDurations)/sizeof(int); thisNote++) {
 
   // 음표 길이를 계산하기 위하여, 1초를 음표 타입으로 나눕니다. 
   // 예를 들어, 4분 음표 = 1000 / 4,  8분 음표 = 1000/8 등과 같이
   // 합니다.
     int noteDuration = 1000/noteDurations[thisNote];
     tone(2, melody[thisNote],noteDuration);
 
     int pauseBetweenNotes = noteDuration * 1.30;
     delay(pauseBetweenNotes);
     // 음 발생하는 것을 멈춤:
     noTone(2);
   }
  }
}
