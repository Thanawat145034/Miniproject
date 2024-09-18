const int LED = 2;            // ขาเชื่อมต่อของ LED
const int sensorPin = 18;     // ขาเชื่อมต่อของเซ็นเซอร์สั่นสะเทือน
const int sound_sensor = 19;  // ขาเชื่อมต่อของเซ็นเซอร์เสียง

bool ledState = false;        // สถานะของ LED (เปิดหรือปิด)
unsigned long lastToggleTime = 0; // เวลาที่ LED ถูกเปิดหรือปิดล่าสุด
const unsigned long interval = 10000; // กำหนดเวลา 10 วินาที (10000 มิลลิวินาที)

void setup() {
  pinMode(LED, OUTPUT);       // กำหนดขา LED เป็นขาเอาท์พุต
  pinMode(sensorPin, INPUT);   // กำหนดขาเซ็นเซอร์เป็นขาอินพุต
  pinMode(sound_sensor, INPUT);
  digitalWrite(LED, LOW);     // เริ่มต้นด้วยการปิดไฟ LED
  Serial.begin(115200);       // เริ่มต้นการสื่อสารกับคอมพิวเตอร์
}

void loop() {
  int status_sensor = digitalRead(sound_sensor);
  int sensorValue = digitalRead(sensorPin); // อ่านค่าจากเซ็นเซอร์สั่นสะเทือน
  unsigned long currentTime = millis(); // อ่านเวลาปัจจุบัน
  Serial.println(sensorValue);
  
  if (status_sensor == HIGH) { // ตรวจจับการตบมือ
    if (!ledState) {
      // ถ้าไฟ LED ดับอยู่ให้เปิดไฟ LED
      ledState = true;
      digitalWrite(LED, HIGH);
    }
    // ตั้งค่าให้หยุดการตรวจจับการตบมือชั่วคราว
    delay(2000); // ป้องกันการตรวจจับซ้ำเร็วเกินไป
  }

  if (!ledState && sensorValue == HIGH) { // ตรวจจับการสั่นสะเทือนเมื่อไฟ LED ดับ
    ledState = true; // เปิดไฟ LED
    digitalWrite(LED, HIGH);
    lastToggleTime = currentTime; // บันทึกเวลาที่เปิดไฟ
  }

  // ตรวจสอบหากไฟ LED เปิดอยู่และครบ 10 วินาทีหลังการตรวจจับครั้งแรก
  if (ledState && (currentTime - lastToggleTime >= interval)) {
    ledState = false; // ปิดไฟ LED
    digitalWrite(LED, LOW);
  }
}
