//int berat;
//char xx;
//
//int ab;
//char a;
//char c;

char a, c, e, g, i, k;
int b, d, f, h, j, l;

void setup() {
  Serial2.begin(9600);  //
  Serial.begin(115200);
  Serial.print("mulai");
 }

void loop() {
  while (Serial2.available() > 0) {
    a = Serial2.read();
    b = Serial2.parseInt();
    c = Serial2.read();
    d = Serial2.parseInt();
    e = Serial2.read();
    f = Serial2.parseInt();
    g = Serial2.read();
    h = Serial2.parseInt();
    i = Serial2.read();
    j = Serial2.parseInt();
    k = Serial2.read();
    l = Serial2.parseInt();
  if(d==4) d=0;
  Serial.println("RPM");
  Serial.println(b);    //status alat
  Serial.println("RPS");
  Serial.println(d);  //Slift
  Serial.println(e);
  Serial.println(f);    //UPorDOWN
  Serial.println(g);
  Serial.println(h);    //statustombol
  Serial.println(i);
  Serial.println(j);    //statuspsu
  Serial.println(k);
  Serial.println(l);    //statuspsu
  Serial.println("");
  Serial.println("");
  b=0;
  }
  delay(1000);
}
