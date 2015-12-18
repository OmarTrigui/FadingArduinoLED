/**
 * @updated by Omar Trigui
 * @updated by Rahma Rekik
 * @updated by Amina Abdelkefi
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Output
int redPin = 6;   // Red LED
int grnPin = 10;  // Green LED
int bluPin = 9;  // Blue LED

// Tableau des couleurs ( échelle max 100)
int black[3] = { 0, 0, 0 };
int red[3] = { 100, 0, 0 };
int green[3] = { 0, 100, 0 };
int blue[3] = { 0, 0, 100 };
int yellow[3] = { 40, 95, 0 };

// Initialisation des couleurs  ( 0 , 0 , 0 )
int redVal = black[0];
int grnVal = black[1];
int bluVal = black[2];
     
int loopCount = 60; 
int repeat = 3; 
int j = 0; 

// Initialisation des variables de couleurs
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

// Initialisation des pins de l'output
void setup() {
    lcd.begin(16, 2);
    lcd.print("Bienvenue");
    pinMode(redPin, OUTPUT);  
    pinMode(grnPin, OUTPUT);
    pinMode(bluPin, OUTPUT);
}

// les couleurs qu'on va visualiser sur le RGB LED
// [rouge, vert, bleu et finalement jaune] en boucle
void loop() {
    crossFade(red);
    crossFade(green);
    crossFade(blue);
    crossFade(yellow);
    
    if (repeat) { 
        j += 1;
        if (j >= repeat) { 
            exit(j);
        }
    }
}

// calculer le prochain saut ( prochaine couleur à visualiser)
int calculateStep(int prevValue, int endValue) {
    int step = endValue - prevValue; 
    if (step) {
        step = 1020 / step;
    }
    return step;
}

int calculateVal(int step, int val, int i) {
    
    if ((step) && i % step == 0) { 
        if (step > 0) {         
            val += 1;
            } else if (step < 0) {
            val -= 1;
        }
    }
    
    if (val > 255) {
        val = 255;
        } else if (val < 0) {
        val = 0;
    }
    return val;
}

// variation des couleurs à travers cette méthode
void crossFade(int color[3]) {
    // Convertir les codes des couleurs vers l'échelle [0 .. 255]
    int R = (color[0] * 255) / 100;
    int G = (color[1] * 255) / 100;
    int B = (color[2] * 255) / 100;
    
    int stepR = calculateStep(prevR, R);
    int stepG = calculateStep(prevG, G);
    int stepB = calculateStep(prevB, B);
    
    for (int i = 0; i <= 1020; i++) {
        redVal = calculateVal(stepR, redVal, i);
        grnVal = calculateVal(stepG, grnVal, i);
        bluVal = calculateVal(stepB, bluVal, i);
        
        // Mettre à jour les nouvelles valeurs des pins
        analogWrite(redPin, redVal);   
        analogWrite(grnPin, grnVal);
        analogWrite(bluPin, bluVal);
        
        delay(10);
        
            if (i == 0 or i % loopCount == 0) { 
                
                lcd.clear();
                lcd.print("R=");
                lcd.print(redVal);
                lcd.print(" G=");
                lcd.print(grnVal);
                lcd.print(" B=");
                lcd.print(bluVal);
                
                delay(500);

            }
    }

    // mettre à jour les nouvelles valeurs
    prevR = redVal;
    prevG = grnVal;
    prevB = bluVal;
}