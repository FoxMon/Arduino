// LCD 모니터 활용

#include <LiquidCrystal.h> // LCD라이브러리 활용을 위한 헤더파일
#define MAX_BUFFER_SIZE 50

// LCD (Rs, Enable, Data Bit 4, 5, 6, 7 )
LiquidCrystal lcd(1, 2, 3, 4, 5, 6); // LCD와 보드의 핀 번호
int thisChar = 'a';
int lcd_stInte = 0;
char serialInput[MAX_BUFFER_SIZE]; // serial input buffer
String inputData;
char *help[] = {"Help", "Exit", "Hello", "Timer", "Blink", "OnOff", "Direction", "UserInput", "Scroll"};

void init_lcd(){
  lcd.begin(16, 2); // 2rows 16columns, LCD를 초기화
  delay(200);
  lcd.clear(); // 화면을 지운 후, 커서 처음자리
  delay(200);
  lcd.home(); // 화면 그대로, 커서만(0, 0)으로
  delay(1000);
  lcd.print("Hello World!"); // 문자열이나 변수 값 출력
  delay(2000);
}

void user_help_menu(){
  for(int i = 0; i < sizeof(help) / sizeof(char *); i++){
    Serial.println(help[i]); // 메뉴 출력
  }
}

void setup(){
  init_lcd(); // 초기화면

  Serial.begin(9600); // 시리얼 통신 개통
}

void serial_user_input(){
  int count = 0;
  char data = 0;

  while(!Serial.available());
  while(Serial.available() > 0){
    delay(50);

    data = Serial.read(); // 시리얼 통신으로 문자를 읽어옴
    serialInput[count] = data; // 배열에 넣고

    if(data == '\r' || data == '\n' || data == '\a'){
      Serial.print("Blueino Received : ");
      serialInput[count] = 0;
      Serial.println(serialInput);
    }

    count = (count + 1) % MAX_BUFFER_SIZE;
  }
}

int input_interpret(char *cmd){
  for(int i = 0; i < sizeof(help) / sizeof(char *); i++){
    if(!strcmp(help[i], cmd)){ // 어떤 명령이 들어왔는가?
      return i;
    }
  }

  return 0;
}

void ex_exit_user_input(){
  Serial.println("normal node : ");
}

void display_hello(){
  init_lcd();

  lcd.clear(); // LCD 지우고
  delay(200);
  lcd.home(); //
  delay(200);
  lcd.setCursor(0,1);
  lcd.print("Hello Blueinno!!"); // Hello Blueinno!! 출력
  delay(1000);
  lcd.clear(); // LCD지움
  delay(1000); // 1초간 유지
}

void display_user_input(){
  init_lcd();

  // 문자 전송시

  while(1){
    lcd.setCursor(0,1);

    serial_user_input();

    if(!strcmp(serialInput, "Exit")){ // exit입력 시 함수 종료
      return;
    }

    for(int i = 0; serialInput[i] != '\0'; i++){ 
      lcd.write(serialInput[i]); // 문자 하나씩 출력
      delay(500);
    }
  }
}

void scroll(){
  init_lcd();

  for(int i = 0; i < 13; i++){
    lcd.scrollDisplayLeft(); // 왼쪽으로 스크롤
    delay(150);
  }

  for(int i = 0; i < 29; i++){
    lcd.scrollDisplayRight(); // 오른쪽으로 스크롤
    delay(150);
  }

  for(int i = 0; i < 16; i++){
    lcd.scrollDisplayLeft(); // 다시 왼쪽으로 돌려서 제자리
    delay(150);
  }

  delay(1000);
}

void display_direction(){
  init_lcd();

  for(int i = 0; i < 50; i++){
    if(thisChar == 'm'){
      lcd.rightToLeft(); // 'm' 표시 보면 방향 바꿈
    }

    if(thisChar == 's'){
      lcd.leftToRight(); // 's' 표시 방향 전환
    }

    if(thisChar > 'z'){
      lcd.clear(); // 'z' 발견 시 커서 처음자리로
      thisChar = 'a';
    }

    delay(200);
    lcd.print((char)thisChar); // char 출력
    delay(1000);
    thisChar++; // 계속 늘려줌 a~z까지
  }
}

void display_on_off(){
  init_lcd();

  lcd.display(); // On
  delay(3000);
  lcd.noDisplay(); // Off
  delay(3000);
}

void cursor_blink(){
  init_lcd();

  lcd.noBlink(); // 깜빡임 x
  delay(3000);
  lcd.blink(); // 깜빡임 o
  delay(3000);
}

void timer_display(){
  init_lcd();

  lcd.setCursor(0, 1); // 커서 위치 조정
  delay(1000);
  lcd.print(millis()/1000);
  delay(1000);
}

void loop(){
  long input;

  serial_user_input(); // 메뉴입력 받음
  input = input_interpret(serialInput); // 명령을 넣어줌

  switch(input){
    case 0:
      user_help_menu();
      break;
    case 1:
      ex_exit_user_input();
      break;
    case 2:
      display_hello();
      break;
    case 3:
      timer_display();
      break;
    case 4:
      cursor_blink();
      break;
    case 5:
      display_on_off();
      break;
    case 6:
      display_direction();
      break;
    case 7:
      display_user_input();
      break;
    case 8:
      scroll();
      break;
  }
}
