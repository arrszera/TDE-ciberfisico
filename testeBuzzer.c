int buzzer = 8;
void setup(){
    pinMode(buzzer, OUTPUT);
}

void loop(){
    tone(buzzer, 261);
    delay(200);
    tone(buzzer, 293);
    delay(200);
    tone(buzzer, 329);
    delay(200);
    tone(buzzer, 349);
    delay(200);
    tone(buzzer, 392);
    delay(200);
    noTone(buzzer);
    delay(2000);
}