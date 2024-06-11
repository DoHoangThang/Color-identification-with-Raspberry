// #define LED_7 8 //Orange
// #define LED_6 7 //Black
// #define LED_5 6  //Purple
// #define LED_4 5  //Yellow
// #define LED_3 4  //Blue
// #define LED_2 3  //Red
// #define LED_1 2  //Green

// String data;

// void setup() {
//   Serial.begin(9600);
//   pinMode(LED_1, OUTPUT);
//   pinMode(LED_2, OUTPUT);
//   pinMode(LED_3, OUTPUT);
//   pinMode(LED_4, OUTPUT);
//   pinMode(LED_5, OUTPUT);
//   pinMode(LED_6, OUTPUT);
//   pinMode(LED_7, OUTPUT);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     data = Serial.readStringUntil('\n');
//     Serial.println(data);
//     delay(100);
    
//     if (data == "0")           //Bật đèn Yellow, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, HIGH);
//       digitalWrite(LED_2, LOW);
//       digitalWrite(LED_3, LOW);
//       digitalWrite(LED_4, LOW);
//       digitalWrite(LED_5, LOW);
//       digitalWrite(LED_6, LOW);
//       digitalWrite(LED_7, LOW);
//     } else if (data == "1")   //Bật đèn Green, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, LOW);
//       digitalWrite(LED_2, HIGH);
//       digitalWrite(LED_3, LOW);
//       digitalWrite(LED_4, LOW);
//       digitalWrite(LED_5, LOW);
//       digitalWrite(LED_6, LOW);
//       digitalWrite(LED_7, LOW);
//     } else if (data == "2")   //Bật đèn Red, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, LOW);
//       digitalWrite(LED_2, LOW);
//       digitalWrite(LED_3, HIGH);
//       digitalWrite(LED_4, LOW);
//       digitalWrite(LED_5, LOW);
//       digitalWrite(LED_6, LOW);
//       digitalWrite(LED_7, LOW);
//     } else if (data == "3")   //Bật đèn Blue, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, LOW);
//       digitalWrite(LED_2, LOW);
//       digitalWrite(LED_3, LOW);
//       digitalWrite(LED_4, HIGH);
//       digitalWrite(LED_5, LOW);
//       digitalWrite(LED_6, LOW);
//       digitalWrite(LED_7, LOW);
//     } else if (data == "4")   //Bật đèn Purple, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, LOW);
//       digitalWrite(LED_2, LOW);
//       digitalWrite(LED_3, LOW);
//       digitalWrite(LED_4, LOW);
//       digitalWrite(LED_5, HIGH);
//       digitalWrite(LED_6, LOW);
//       digitalWrite(LED_7, LOW);
//     } else if (data == "5")   //Bật đèn Black, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, LOW);
//       digitalWrite(LED_2, LOW);
//       digitalWrite(LED_3, LOW);
//       digitalWrite(LED_4, LOW);
//       digitalWrite(LED_5, LOW);
//       digitalWrite(LED_6, HIGH);
//       digitalWrite(LED_7, LOW);
//     } else if (data == "6")   //Bật đèn Orange, tắt các đèn còn lại
//     {
//       digitalWrite(LED_1, LOW);
//       digitalWrite(LED_2, LOW);
//       digitalWrite(LED_3, LOW);
//       digitalWrite(LED_4, LOW);
//       digitalWrite(LED_5, LOW);
//       digitalWrite(LED_6, LOW);
//       digitalWrite(LED_7, HIGH);
//     }
//   } 
//   delay(20);
// }

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 8 // Thay đổi số lượng LED thành 2
#define LED_PIN   6 // Chọn chân kết nối cho NeoPixel

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();           // Khởi tạo đối tượng NeoPixel
  strip.show();            // Tắt tất cả các LED NeoPixel
  strip.setBrightness(30); // Đặt độ sáng của NeoPixel
  
  // Mảng lưu trữ các màu cho từng lần chớp tắt
  uint32_t colors[] = {strip.Color(255, 0, 0), strip.Color(0, 255, 0), strip.Color(0, 0, 255)};
  
  // Lặp lại quá trình chớp tắt 3 lần
  for (int j = 0; j < 3; j++) {
    // Chọn màu cho lần chớp tắt
    uint32_t color = colors[j];
    
    // Bật tất cả các LED với màu tương ứng
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, color); // Đặt màu cho LED
    }
    strip.show(); // Hiển thị màu đã đặt
    delay(1000); // Delay để tạo hiệu ứng chớp tắt
    
    // Tắt tất cả các LED
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); // Tắt LED
    }
    strip.show(); // Hiển thị màu đã đặt
    delay(500); // Delay để tạo hiệu ứng chớp tắt
  }
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    delay(100);
    
    if (data == "0") {
      setColor(strip.Color(255, 255, 0)); // Màu Yellow
    } 
    else if (data == "1") {
      setColor(strip.Color(0, 255, 0));   // Màu Green
    } else if (data == "2") {
      setColor(strip.Color(255, 0, 0));   // Màu Red
    } else if (data == "3") {
      setColor(strip.Color(0, 0, 255));   // Màu Blue
    } else if (data == "4") {
      setColor(strip.Color(128, 0, 128)); // Màu Purple
    } else if (data == "5") {
      setColor(strip.Color(255, 255, 255));     // Màu Black
    } else if (data == "6") {
      setColor(strip.Color(255, 165, 0)); // Màu Orange
    }
  } 
  delay(20);
}

void setColor(uint32_t color) {
  for (int i = 0; i < LED_COUNT; i++) { // Lặp qua tất cả các LED
    strip.setPixelColor(i, color); // Đặt màu cho từng LED
  }
  strip.show();                  // Hiển thị màu đã đặt
}
// void setColor(uint32_t color) { 
//   strip.setPixelColor(0, color); // Đặt màu cho LED NeoPixel đầu tiên
//   strip.show();                  // Hiển thị màu đã đặt
// }