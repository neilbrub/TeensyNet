// New note to play or 'no note change' signal passed, flow state assumed to always be correct
void controller(int note_to_play) {
  static int channel = 1;

  // For use without breath sensor
  if (AUTOPLAY) current_volume = 105;
  
  if (current_volume <= 0) {
    usbMIDI.sendNoteOff(note_playing, current_volume, channel);
    if (note_to_play > 0){
      note_playing = note_to_play; 
    }
    else if (note_to_play == -1) {
      note_playing = squeak_note;
    }
  }
  else {
    if (note_to_play == -1) {
      usbMIDI.sendNoteOff(note_playing, current_volume, channel);
      usbMIDI.sendNoteOn(squeak_note, current_volume, channel);
      note_playing = squeak_note;
    }
    else if (note_to_play == 0) {
      usbMIDI.sendNoteOff(note_playing, current_volume, channel);
      usbMIDI.sendNoteOn(note_playing, current_volume, channel);
    }
    else {
      usbMIDI.sendNoteOff(note_playing, current_volume, channel);
      usbMIDI.sendNoteOn(note_to_play, current_volume, channel);
      note_playing = note_to_play; 
    }
  }
}
