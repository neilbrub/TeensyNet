// New note to play or 'no note change' signal passed, flow state assumed to always be correct
void controller(int note_to_play) {
  static int channel = 1;
  if (current_volume <= 0) {
    usbMIDI.sendNoteOff(note_playing, current_volume, channel);
    note_playing = note_to_play;
  }
  else{
    if (note_to_play == -1){
      usbMIDI.sendNoteOff(note_playing, current_volume, channel);
      usbMIDI.sendNoteOn(85, current_volume, channel);
      note_playing = 85;
    }
    else if (note_to_play == 0) {
      usbMIDI.sendNoteOff(note_playing, current_volume, channel);
      usbMIDI.sendNoteOn(note_playing, current_volume, channel);
    }
    else{
      usbMIDI.sendNoteOff(note_playing, current_volume, channel);
      usbMIDI.sendNoteOn(note_to_play, current_volume, channel);
      note_playing = note_to_play; 
    }
  }
}
