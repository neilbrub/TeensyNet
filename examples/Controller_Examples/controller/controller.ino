int vol = 0;
int note_playing = 0;

void setup(){
}

// To test controller function
// Cycles through a few notes at different volumes
void loop(){
  vol = 100;
  controller(67);
  delay(1000);
  vol = 100;
  controller(55);
  delay(1000);
  vol = 25;
  controller(40);
  delay(1000);
  vol = 0;
  controller(40);
  delay(1000);
  vol = 120;
  controller(40);
  delay(1000);
  vol = 100;
  controller(60);
  delay(1000);
  vol = 25;
  controller(60);
  delay(1000);
  vol = 15;
  controller(60);
  delay(1000);
  vol = 120;
  controller(0);
  delay(1000);
  controller(-1);
  delay(1000);
}

void controller(int note_to_play) {
  static int channel = 1;
  if (vol <= 0) {
    usbMIDI.sendNoteOff(note_playing, vol, channel);
    if (note_to_play > 0){
      note_playing = note_to_play; 
    }
    else if (note_to_play == -1) {
      note_playing = squeak_note;
    }
  }
  else{
    if (note_to_play == -1){
      usbMIDI.sendNoteOff(note_playing, vol, channel);
      usbMIDI.sendNoteOn(85, vol, channel);
      note_playing = 85;
    }
    else if (note_to_play == 0) {
      usbMIDI.sendNoteOff(note_playing, vol, channel);
      usbMIDI.sendNoteOn(note_playing, vol, channel);
    }
    else{
      usbMIDI.sendNoteOff(note_playing, vol, channel);
      usbMIDI.sendNoteOn(note_to_play, vol, channel);
      note_playing = note_to_play; 
    }
  }
}
