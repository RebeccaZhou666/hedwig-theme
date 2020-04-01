#include <pitchToFrequency.h>
#include <pitchToNote.h>
#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>

#define NOTE_B0  23
#define NOTE_C1  24
#define NOTE_CS1 25
#define NOTE_D1  26
#define NOTE_DS1 27
#define NOTE_E1  28
#define NOTE_F1  29
#define NOTE_FS1 30
#define NOTE_G1  31
#define NOTE_GS1 32
#define NOTE_A1  33
#define NOTE_AS1 34
#define NOTE_B1  35
#define NOTE_C2  36
#define NOTE_CS2 37
#define NOTE_D2  38
#define NOTE_DS2 39
#define NOTE_E2  40
#define NOTE_F2  41
#define NOTE_FS2 42
#define NOTE_G2  43
#define NOTE_GS2 44
#define NOTE_A2  45
#define NOTE_AS2 46
#define NOTE_B2  47
#define NOTE_C3  48
#define NOTE_CS3 49
#define NOTE_D3  50
#define NOTE_DS3 51
#define NOTE_E3  52
#define NOTE_F3  53
#define NOTE_FS3 54
#define NOTE_G3  55
#define NOTE_GS3 56
#define NOTE_A3  57
#define NOTE_AS3 58
#define NOTE_B3  59
#define NOTE_C4  60
#define NOTE_CS4 61
#define NOTE_D4  62
#define NOTE_DS4 63
#define NOTE_E4  64
#define NOTE_F4  65
#define NOTE_FS4 66
#define NOTE_G4  67
#define NOTE_GS4 68
#define NOTE_A4  69
#define NOTE_AS4 70
#define NOTE_B4  71
#define NOTE_C5  72
#define NOTE_CS5 73
#define NOTE_D5  74
#define NOTE_DS5 75
#define NOTE_E5  76
#define NOTE_F5  77
#define NOTE_FS5 78
#define NOTE_G5  79
#define NOTE_GS5 80
#define NOTE_A5  81
#define NOTE_AS5 82
#define NOTE_B5  83
#define NOTE_C6  84
#define NOTE_CS6 85
#define NOTE_D6  86
#define NOTE_DS6 87
#define NOTE_E6  88
#define NOTE_F6  89
#define NOTE_FS6 90
#define NOTE_G6  91
#define NOTE_GS6 92
#define NOTE_A6  93
#define NOTE_AS6 94
#define NOTE_B6  95
#define NOTE_C7  96
#define NOTE_CS7 97
#define NOTE_D7  98
#define NOTE_DS7 99
#define NOTE_E7  100
#define NOTE_F7  101
#define NOTE_FS7 102
#define NOTE_G7  103
#define NOTE_GS7 104
#define NOTE_A7  105
#define NOTE_AS7 106
#define NOTE_B7  107
#define NOTE_C8  108

#define REST 0

int tempo = 144;
int wholenote = (60000*4)/tempo;

int lastButtonState = HIGH;
byte note = 0;

//int bpm = 72;  // beats per minute
// duration of a beat in ms
//float beatDuration = 60.0 / bpm * 1000;

// the melody sequence:
//int melody[] = {64, 66, 71, 73, 74, 66, 64, 73, 71, 66, 74, 73};
//int melody2[] = { 71, 66, 74, 73,64, 66, 71, 73, 74, 66, 64, 73};
// which note of the melody to play:
int noteCounter = 0;
//int noteCounter2 = 0;


int melody[] = {


  // Hedwig's theme fromn the Harry Potter Movies
  // Socre from https://musescore.com/user/3811306/scores/4906610
  
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,//18
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST,4, NOTE_AS4,4,  

  NOTE_D5, 2, NOTE_AS4, 4,//26
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
  
};


void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT_PULLUP);
//  pinMode(5, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(2);
  int speedSong = analogRead(A1);
  tempo = map(speedSong, 0,1023, 100,250);
  wholenote = (60000*4)/tempo;
  Serial.println(speedSong);
  
  if(buttonState != lastButtonState){
    if(buttonState == LOW){
      midiCmd(0x90, melody[noteCounter], 127);
      midiCmd(0x91, melody[noteCounter], 127);
      // all the notes in this are sixteenth notes,
      int noteDuration = (wholenote)/abs(melody[noteCounter+1]);
      // keep it on for the appropriate duration:
      delay(noteDuration);
      
      // turn the note off:
      midiCmd(0x80, melody[noteCounter], 127);
      midiCmd(0x81, melody[noteCounter], 127);
      // increment the note number for next time through the loop:
      noteCounter+=2;
      // keep the note in the range from 0 - 11 using modulo:
      noteCounter = noteCounter % sizeof(melody);
    }else{
      midiCmd(0x80, melody[noteCounter], 0x00);
      midiCmd(0x81, melody[noteCounter], 0x00);
      // all the notes in this are sixteenth notes,
      // which is 1/4 of a beat, so:
      int noteDuration = (wholenote)/abs(melody[noteCounter+1]);
      // keep it on for the appropriate duration:
      delay(noteDuration);
      
      // turn the note off:
      midiCmd(0x80, melody[noteCounter], 127);
      midiCmd(0x81, melody[noteCounter], 127);
      // increment the note number for next time through the loop:
      noteCounter+=2;
      // keep the note in the range from 0 - 11 using modulo:
      noteCounter = noteCounter % sizeof(melody);
    }
  }

}

void midiCmd(byte cmd, byte data1, byte data2){
  midiEventPacket_t midiMsg = {cmd >>4, cmd, data1, data2};
  MidiUSB.sendMIDI(midiMsg);
}
