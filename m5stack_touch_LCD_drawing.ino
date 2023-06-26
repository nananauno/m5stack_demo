#include <M5Core2.h>

uint8_t r = 255;
uint8_t g = 0;
uint8_t b = 0;
int penSize = 5;  // ペンのサイズ
float accelerationThreshold = 150;  // 振ったことを検出するための閾値

char outStr[40];

void setup() {
  M5.begin();
  // Init IMU
  M5.IMU.Init();

  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.update();

  if(M5.Touch.ispressed()) {
    TouchPoint_t coordinate;
    coordinate = M5.Touch.getPressPoint();
    //M5.Lcd.drawPixel(coordinate.x, coordinate.y, M5.Lcd.color565(r, g, b));
    M5.Lcd.fillCircle(coordinate.x, coordinate.y, penSize, M5.Lcd.color565(r, g, b));

    // カーソル位置を画面に表示
    //sprintf(outStr, "x=%03d\ny=%03d", coordinate.x, coordinate.y);
    //M5.Lcd.setCursor(0,0);
    //M5.Lcd.print(outStr);
  }
  
  // RGBで色をグラデーションさせます。
  if(r > 0 && b == 0){
    r--;
    g++;
  }
  if(g > 0 && r == 0){
    g--;
    b++;
  }
  if(b > 0 && g == 0){
    r++;
    b--;
  }

  float gyrX, gyrY, gyrZ;
  M5.IMU.getGyroData(&gyrX, &gyrY, &gyrZ);

  // 加速度の値を画面に表示
  //sprintf(outStr, "gyrX=%5.1f\ngyrY=%5.1f\ngyrZ=%5.1f", gyrX, gyrY, gyrZ);
  //M5.Lcd.setCursor(0,0);
  //M5.Lcd.print(outStr);

  // 加速度が閾値を超えた場合に画面をクリア
  if(abs(gyrZ) > accelerationThreshold) {
    M5.Lcd.fillScreen(BLACK);
  }

  delay(20);  // 画面の更新頻度を制御します。必要に応じて調整してください。
}