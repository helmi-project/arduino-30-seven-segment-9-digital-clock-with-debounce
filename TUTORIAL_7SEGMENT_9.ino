/*
   TUTORIAL SEVEN SEGMENT PADA ARDUINO
   MENGGUNAKAN CHIP TM1637
   MEMBUAT JAM - TANPA MENGGUNAKAN DELAY()
   GABUNG PENGGUNAAN DEBOUNCE PADA TOMBOL

   Pinout :
   CLK -> D10
   DIO -> D11

   Tombol 1 -> D9
   Tombol 2 -> D8

   D4 -> Led Merah
   D5 -> Led Hijau
   D6 -> Led Biru
   D7 -> Led Kuning

*/

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 10
#define DIO 11
#define merah 4
#define hijau 5
#define biru 6
#define kuning 7
#define TOMBOL1 9
#define TOMBOL2 8

//inisiasi TM1637
TM1637Display display(CLK, DIO);

int jam = 10;
int menit = 30;
int detik = 0;
int waktu;

int statusTitik = 0;

unsigned long millisSebelumnya1 = 0;
unsigned long millisSebelumnya2 = 0;

unsigned long waktuDebounceTerakhir1 = 0;
unsigned long waktuDebounceTerakhir2 = 0;
unsigned long delayDebounce = 50;
int statusTombol1;
int statusTombol2;
int statusTerakhirTombol1 = HIGH;
int statusTerakhirTombol2 = HIGH;

void setup()
{
  display.setBrightness(0x0f);
  pinMode(kuning, OUTPUT);
  pinMode(biru, OUTPUT);
  pinMode(hijau, OUTPUT);
  pinMode(merah, OUTPUT);
  pinMode(TOMBOL1, INPUT);
  pinMode(TOMBOL2, INPUT);
  digitalWrite(TOMBOL1, HIGH); //pull high sebagai default awal
  digitalWrite(TOMBOL2, HIGH); //pull high sebagai default awal

}

void loop()
{

  unsigned long millisSekarang1 = millis();
  if (millisSekarang1 - millisSebelumnya1 >= 1000) {
    millisSebelumnya1 = millisSekarang1;
    detik++;
  }
  if (detik == 60) {
    detik = 0;
    menit++;
  }
  if (menit == 60) {
    menit = 0;
    jam++;
  }
  if (jam == 24) {
    jam = 0;
  }
  waktu = (jam * 100) + menit;
  cekLed();

  unsigned long millisSekarang2 = millis();
  if (millisSekarang2 - millisSebelumnya2 >= 500) {
    millisSebelumnya2 = millisSekarang2;
    statusTitik = !statusTitik;
  }

  if (statusTitik == 0) {
    display.showNumberDecEx(waktu, (0x80 >> 1), true);
  } else {
    display.showNumberDec(waktu, true);
  }

  int a = digitalRead(TOMBOL1);
  if (a != statusTerakhirTombol1) {
    waktuDebounceTerakhir1 = millis();
  }
  if ((millis() - waktuDebounceTerakhir1) > delayDebounce) {
    if (a != statusTombol1) {
      statusTombol1 = a;
      if (statusTombol1 == LOW) {
        jam++;
        detik = 0;
      }
    }
  }
  statusTerakhirTombol1 = a; 

  int b = digitalRead(TOMBOL2);
  if (b != statusTerakhirTombol2) {
    waktuDebounceTerakhir2 = millis();
  }
  if ((millis() - waktuDebounceTerakhir2) > delayDebounce) {
    if (b != statusTombol2) {
      statusTombol2 = b;
      if (statusTombol2 == LOW) {
        menit++;
        detik = 0;
      }
    }
  }
  statusTerakhirTombol2 = b; 
}

void cekLed() {
  if (detik >= 0 && detik < 15) {
    digitalWrite(kuning, HIGH);
    digitalWrite(biru, LOW);
    digitalWrite(hijau, LOW);
    digitalWrite(merah, LOW);
  }
  if (detik >= 15 && detik < 30) {
    digitalWrite(kuning, HIGH);
    digitalWrite(biru, HIGH);
    digitalWrite(hijau, LOW);
    digitalWrite(merah, LOW);
  }
  if (detik >= 30 && detik < 45) {
    digitalWrite(kuning, HIGH);
    digitalWrite(biru, HIGH);
    digitalWrite(hijau, HIGH);
    digitalWrite(merah, LOW);
  }
  if (detik >= 45 && detik < 60) {
    digitalWrite(kuning, HIGH);
    digitalWrite(biru, HIGH);
    digitalWrite(hijau, HIGH);
    digitalWrite(merah, HIGH);
  }
}
