#include <Bridge.h>
//#include <Console.h>

#include <HttpClient.h>

/*#include <Adafruit_LEDBackpack.h>
  #include <Adafruit_GFX.h>
  #include <Wire.h>
*/
#define LED_KO        12
#define LED_OK        13
#define FLOW_METER    7

//Adafruit_7segment matrix = Adafruit_7segment();

double _totalQuantity = 0.0;
double debit = 0.00225;

void setup() {
  pinMode(LED_KO, OUTPUT);
  pinMode(LED_OK, OUTPUT);
  pinMode(FLOW_METER, INPUT);

  _setKO();

  Bridge.begin(); //Yun Bridge
  Serial.begin(9600);
  while (!Serial);

  /*matrix.begin(0x70);
    matrix.setBrightness(2);
    displayQuantity(_totalQuantity);
  */
  Serial.println("Application Up !!!");
  _setOK();
}

void loop() {
  int flow = digitalRead(FLOW_METER);


  if (flow > 0) {
    _totalQuantity += debit;

    displayQuantity(_totalQuantity);

    Serial.println(_totalQuantity);

    sendQuantity(debit);
  }

  delay(50);
}

/**
   Display total quantity drunk on Adafruit_7segment
*/
void displayQuantity(double quantity) {
  //  matrix.println(quantity, 2);
  //  matrix.writeDisplay();
}

void sendQuantity(double quantity) {
  // Initialize the client library
  HttpClient client;

  // Make a HTTP request:
  String req = "http://192.168.43.91:8090/drink?name=Marcel&quantity=" + String(quantity * 1000);
  Serial.println(req);
  client.get(req);
}



void _setOK() {
  digitalWrite(LED_KO, LOW);
  digitalWrite(LED_OK, HIGH);
}

void _setKO() {
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_KO, HIGH);
}
