int berat;
char xx;

int ab;
char a;
char c;
void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
 }

void loop() {
  while (Serial2.available() > 0) {
    ab = Serial2.parseInt();
    a = Serial2.read();
    berat = Serial2.parseInt();
    c = Serial2.read();
  }
  Serial.println(ab);
  Serial.println(a);
  Serial.println(berat);
  Serial.println(c);
  Serial.println("");
  
  delay(100);
}
