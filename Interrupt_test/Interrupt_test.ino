/* 버튼을 누를때(인터럽트발생시) Led에 불을 들어오게 합니다. */

int led1 = 3; // LedPin1 -> 3
int led2 = 4; // LedPin2 -> 4
int button1 = 1; // ButtonPin1 -> 1
int button2 = 2; // ButtonPin2 -> 2
int cnt1, cnt2; // I.H를 카운트해줄 변수

int callback1(uint32_t ulPin){ // Interrupt Handler 1
  cnt1++;
}

int callback2(uint32_t ulPin){ // Interrupt Handler 2
  cnt2++;
}

void setup(){
  Serial.begin(9600); // Serial통신속도
  Serial.println("Hello!!"); // Serial모니터에 Hello출력

  pinMode(led1, OUTPUT); // LED1핀 출력
  digitalWrite(led1, LOW);

  pinMode(led2, OUTPUT); // LED2핀 출력
  digitalWrite(led2, LOW);

  pinMode(button1, INPUT); // Button1핀 입력
  attachPinInterrupt(1, callback1, HIGH);
  pinMode(button2, INPUT); // Button2핀 입력
  attachPinInterrupt(2, callback2, HIGH);
}

void loop(){
  int i = 0, j = 0;
  cnt1 = 0;
  cnt2 = 0;

/* 버튼이 눌릴때마다, 각 버튼에 해당하는 cnt값을 증가시키고,
 놓치는 인터럽트가 발생하지 않도록 합니다. */
  while(true){
    if(i<cnt1){
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
    }
    else{
      break;
    }
    cnt1--; // 해당 이벤트를 완수하면 cnt값을 1씩 내립니다.
  }

  while(true){ // 위와 마찬가지.
    if(j<cnt2){
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);  
      delay(500);    
    }
    else{
      break;
    }
    cnt2--;
  }
}
