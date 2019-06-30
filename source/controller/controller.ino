int vol = 0;
int note_in_play = 0;
int channel = 1;

void setup(){
}

void loop(){
    vol = 100;
    controller(1,40);
    delay(1000);
    vol = 25;
    controller(0,40);
    delay(1000);
    vol = 15;
    controller(0,40);
    delay(1000);
    vol = 120;
    controller(0,40);
    delay(1000);
    vol = 100;
    controller(1,60);
    delay(1000);
    vol = 25;
    controller(0,60);
    delay(1000);
    vol = 15;
    controller(0,60);
    delay(1000);
    vol = 120;
    controller(0,60);
    delay(1000);
}

void controller(int action_id, int note_to_play) {
    if (action_id == 0) {
        if (vol <= 0) {
            usbMIDI.sendNoteOff(note_in_play, vol, channel);
            note_in_play = 0;
        }
        else if (note_in_play) {
            usbMIDI.sendNoteOff(note_in_play, vol, channel);
            usbMIDI.sendNoteOn(note_in_play, vol, channel);
        }
    }
    else if (action_id == 1) {
        if (vol <= 0) {
            usbMIDI.sendNoteOff(note_in_play, vol, channel);
            note_in_play = 0;
        }
        else if (note_in_play != note_to_play) {
            usbMIDI.sendNoteOff(note_in_play, vol, channel);
            usbMIDI.sendNoteOn(note_to_play, vol, channel);
            note_in_play = note_to_play;
        }
        else {
            usbMIDI.sendNoteOff(note_in_play, vol, channel);
            usbMIDI.sendNoteOn(note_in_play, vol, channel);
        }
    }
}
