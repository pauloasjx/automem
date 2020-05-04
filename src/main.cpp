#include <Arduino.h>

//#include <Wire.h>

#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

#include "ui/loading.h"
#include "ui/result.h"
#include "ui/menu.h"
#include "ui/ui.h"
#include "misc/radio.h"

#include <string.h>

LiquidCrystal_I2C *lcd;
Ui *ui;

uint8_t currentCursor = 0;
uint8_t offset = 0;

// void debug_eeprom(int address)
// {
//   uint8_t data = e.read(address);
//   char buf[128];
//   sprintf(buf, " 0x%02X ", data);
//   Serial.print(buf);
// }

void setup()
{
  Serial.begin(9600);
  Wire.begin(0x50);

  E24cxx *e = new E24cxx(512);
  uint16_t *v = new uint16_t(0);
  char result[10];
  char a18[2];
  char a19[2];
  char a1a[2];
  char a1b[2];

  Serial.print(e->read(0x18));
  Serial.print(e->read(0x19));
  Serial.print(e->read(0x1a));
  Serial.print(e->read(0x1b));

  sprintf(a18, "%02X", e->read(0x18));
  sprintf(a19, "%02X", e->read(0x19));
  sprintf(a1a, "%02X", e->read(0x1a));
  sprintf(a1b, "%02X", e->read(0x1b));
  sprintf(result, "%c%c%c%c", a18[1], a19[0], a1a[1], a1b[0]);
  
  Serial.print(result);

  delay(10);

  // lcd = new LiquidCrystal_I2C(0x27, 20, 4);
  // lcd->init();
  // lcd->backlight();
  
  // List<MenuItem> items3 = List<MenuItem>();
  // items3.add(new MenuItem("Carro 1", new Loading(lcd)));
  // items3.add(new MenuItem("Carro 2", nullptr));
  // items3.add(new MenuItem("Carro 3", nullptr));
  // items3.add(new MenuItem("Carro 4", nullptr));

  // List<MenuItem> items2 = List<MenuItem>();
  // items2.add(new MenuItem("Chevrolet", new Menu(lcd, &items3)));
  // items2.add(new MenuItem("Volkswagen", nullptr));
  // items2.add(new MenuItem("Test", nullptr));
  // items2.add(new MenuItem("Test", nullptr));

  // List<MenuItem> itemsRR = List<MenuItem>();
  // itemsRR.add(new MenuItem("CD5404 (24c32)", new Result(lcd, result)));

  // List<MenuItem> itemsR = List<MenuItem>();
  // itemsR.add(new MenuItem("Fiat", new Menu(lcd, &itemsRR)));

  // List<MenuItem> items = List<MenuItem>();
  // items.add(new MenuItem("Imobilizador", new Loading(lcd)));
  // items.add(new MenuItem("Airbag", new Menu(lcd, &items2)));
  // items.add(new MenuItem("Odometro", nullptr));
  // items.add(new MenuItem("Radio", new Menu(lcd, &itemsR)));
  // items.add(new MenuItem("Teste 5", nullptr));
  // items.add(new MenuItem("Teste 6", nullptr));
  // items.add(new MenuItem("Teste 7", nullptr));
  // items.add(new MenuItem("Teste 8", nullptr));
  // items.add(new MenuItem("Teste 9", nullptr));
  // items.add(new MenuItem("Teste 10", nullptr));
  // items.add(new MenuItem("Teste 11", nullptr));
  // items.add(new MenuItem("Teste 12", nullptr));
  
  // Menu m = Menu(lcd, &items);
  // ui = new Ui(&m);
  // ui->render(lcd);
  
  //e->setup();
}

char state = 'W';
char option;
char address[8];
char data[8];
int current = 0;
uint16_t code;
void loop()
{
  // if (Serial.available())
  // {

    if(lcd != nullptr) ui->render(lcd);

    // char value = Serial.read();

    // if (state == 'W')
    // {

    //   for (int i = 0; i < 8; i++)
    //     address[i] = 0;
    //   for (int i = 0; i < 8; i++)
    //     data[i] = 0;
    //   current = 0;

    //   option = value;
    //   state = 'A';
    // }
    // else
    // {

    //   if (value == '#')
    //   {
    //     switch (option)
    //     {
    //     case 'R':
    //       // e.read_all();
    //       debug_eeprom((int)strtol(address, NULL, 16));
    //       //Serial.println(Radio::getCode(&e));
    //       break;
    //     case 'P':
    //       e.print();
    //       break;
    //     case 'W':
    //       e.write((int)strtol(address, NULL, 16), (int)strtol(data, NULL, 16));
    //       break;
    //     default:
    //       Serial.println("Opção inválida");
    //     }

    //     state = 'W';
    //   }
    //   else if (value == '$')
    //   {
    //     current = 0;
    //     state = 'D';
    //   }
    //   else
    //   {
    //     switch (state)
    //     {
    //     case 'A':
    //       if (current < 7)
    //       {
    //         address[current] = value;
    //         current++;
    //       }
    //       break;
    //     case 'D':
    //       if (current < 7)
    //       {
    //         data[current] = value;
    //         current++;
    //       }
    //       break;
    //     }
    //   }
    // }
  // }
}
