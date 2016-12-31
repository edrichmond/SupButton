// This #include statement was automatically added by the Particle IDE.
#include "InternetButton/InternetButton.h"

InternetButton b = InternetButton();
int published = 0;
uint32_t notificationTimeOut = 300000; //five minutes
uint32_t notificationTime;
int notificationOn = 0;

void setup() {
    Serial.begin(9600);
    Particle.subscribe("SupRecipe", runRecipe);
    b.begin();
    b.setBrightness(128);
}

void clearAll() {
    for (int i=1; i<=12; i++) {
        b.ledOn(i, 0, 0, 0);
    }
}

void clearNotification() {
    notificationOn = 0;
    clearAll(); //clear LEDs
}

void runRecipe(const char *event, const char *data)
{
    if (String(data) == "Recipe 1") {
        // do nothing
    } else if (String(data) == "Recipe 2") {
        // do nothing
    } else if (String(data) == "Recipe 3") {
        if (notificationOn) {
            clearNotification();
        }
        else {
            notificationTime = millis();
            notificationOn = 1;
        }
    } else if (String(data) == "Recipe 4") {
        // do nothing
    }
}

void loop() {
    // if notification is on, check for timeout
    if (notificationOn && ((millis() - notificationTime) > notificationTimeOut)) {
        clearNotification();
    }
    
    if (notificationOn) {
        b.advanceRainbow(1, 11);
    }
    
    //check for button presses
    if(b.buttonOn(1)) {
        if(!published) {
            Particle.publish("SupRecipe", "Recipe 1");
            published = 1;                                  
        }
    } else if (b.buttonOn(2)) {
        if(!published) {
            Particle.publish("SupRecipe", "Recipe 2");
            published = 1;                                  
        }   
    } else if (b.buttonOn(3)) {
        if(!published) {
            Particle.publish("SupRecipe", "Recipe 3");
            published = 1;                                  
        }   
    } else if (b.buttonOn(4)) {
         if(!published) {
            Particle.publish("SupRecipe", "Recipe 4");
            published = 1;                                  
        }      
    }
    else {published = 0;} 
}
