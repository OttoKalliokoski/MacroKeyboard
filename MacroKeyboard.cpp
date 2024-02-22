//Asenna kirjasto menemällä valikkoon Sketch->Include-library->Manage-libraries ja hae "hid-project" ja paina install

#include "HID-Project.h"

const int button_pins[] = {2,3,4,5,6,7,8,9,10,16};
int button_states[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int last_button_states[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
unsigned long button_debounce_time[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
unsigned long debounceDelay = 50;
void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<10; i++)
  {
    pinMode(button_pins[i],INPUT_PULLUP);
    
    button_debounce_time[i] = 0.0;
  }

  Consumer.begin();
  BootKeyboard.begin();
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<10; i++)
  {
    int pressed = digitalRead(button_pins[i]);
    if(pressed!=last_button_states[i])
    {
      button_debounce_time[i] = millis();
    }

    if((millis() - button_debounce_time[i]) > debounceDelay)
    {
      if(pressed != button_states[i])
      {
        button_states[i] = pressed;

        if(button_states[i] == LOW)
        {
          
          switch(i) //Tietoja näppäimistökomennoista: https://github.com/NicoHood/HID/wiki/API-Documentation
          {
            case 0:
              Consumer.write(MEDIA_PLAY_PAUSE);   //Media näppäimille: https://github.com/NicoHood/HID/wiki/Consumer-API
              break;
            case 1:
              BootKeyboard.println("Hello world");
              break;
            case 2:
              break;
            case 3:
              break;
            case 4:
              break;
            case 5:
              break;
            case 6:
              break;
            case 7:
              break;
            case 8:
              break;
            case 9:
              break;
          }
        }
      }
    }
    last_button_states[i] = pressed;
  }
  delay(1);
}