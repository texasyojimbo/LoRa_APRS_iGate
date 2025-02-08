#include <Wire.h>
#include "configuration.h"
#include "board_pinout.h"
#include "display.h"


#ifdef HAS_DISPLAY
    #ifdef HAS_TFT
        #include <TFT_eSPI.h>

        TFT_eSPI tft = TFT_eSPI(); 
        TFT_eSprite sprite  = TFT_eSprite(&tft);

        #ifdef HELTEC_WIRELESS_TRACKER
            #define bigSizeFont     2
            #define smallSizeFont   1
            #define lineSpacing     10
        #endif
        #if defined(TTGO_T_DECK_GPS) || defined(TTGO_T_DECK_PLUS)
            #define bigSizeFont     5
            #define smallSizeFont   2
            #define lineSpacing     25
        #endif
        uint16_t redColor           = 0xc8a2;
    #else
        #ifdef HAS_EPAPER
            //
        #else
            #include <Adafruit_GFX.h>
            #include <Adafruit_SSD1306.h>
            #ifdef HELTEC_WSL_V3_DISPLAY
                Adafruit_SSD1306 display(128, 64, &Wire1, OLED_RST);
            #else
                Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST);
            #endif
        #endif
    #endif
#endif
    
extern  Configuration   Config;

bool    displayFound    = false;

void displaySetup() {
    #ifdef HAS_DISPLAY
        delay(500);
        #ifdef HAS_TFT
            tft.init();
            tft.begin();
            if (Config.display.turn180) {
                    tft.setRotation(3);
            } else {
                tft.setRotation(1);
            }
            pinMode(TFT_BL, OUTPUT);
            digitalWrite(TFT_BL, HIGH);
            tft.setTextFont(0);
            tft.fillScreen(TFT_BLACK);
            #if defined(TTGO_T_DECK_GPS) || defined(TTGO_T_DECK_PLUS)
                sprite.createSprite(320,240);
            #else
                sprite.createSprite(160,80);
            #endif
        #else
            #ifdef HAS_EPAPER
                //
            #else
                #ifdef OLED_DISPLAY_HAS_RST_PIN
                    pinMode(OLED_RST, OUTPUT);
                    digitalWrite(OLED_RST, LOW);
                    delay(20);
                    digitalWrite(OLED_RST, HIGH);
                #endif

                if(display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
                    displayFound = true;
                    if (Config.display.turn180) display.setRotation(2);
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setTextSize(1);
                    display.setCursor(0, 0);
                    display.ssd1306_command(SSD1306_SETCONTRAST);
                    display.ssd1306_command(1);
                    display.display();
                }
            #endif
        #endif
        delay(1000);
    #endif
}

void displayToggle(bool toggle) {
    #ifdef HAS_DISPLAY
        if (toggle) {
            #ifdef HAS_TFT
                digitalWrite(TFT_BL, HIGH);
            #else
                #ifdef HAS_EPAPER
                    // ... to be continued
                #else
                    if (displayFound) display.ssd1306_command(SSD1306_DISPLAYON);
                #endif
            #endif
        } else {
            #ifdef HAS_TFT
                digitalWrite(TFT_BL, LOW);
            #else
                #ifdef HAS_EPAPER
                    // ... to be continued
                #else
                    if (displayFound) display.ssd1306_command(SSD1306_DISPLAYOFF);
                #endif
            #endif
        }
    #endif
}

void displayShow(const String& header, const String& line1, const String& line2, const String& line3, int wait) {
    #ifdef HAS_DISPLAY
        const String* const lines[] = {&line1, &line2, &line3};
        #ifdef HAS_TFT
            sprite.fillSprite(TFT_BLACK);
            #if defined(HELTEC_WIRELESS_TRACKER)
                sprite.fillRect(0, 0, 160, 19, redColor);
            #endif
            #if defined(TTGO_T_DECK_GPS) || defined(TTGO_T_DECK_PLUS)
                sprite.fillRect(0, 0, 320, 43, redColor);
            #endif
            sprite.setTextFont(0);
            sprite.setTextSize(bigSizeFont);
            sprite.setTextColor(TFT_WHITE, redColor);
            sprite.drawString(header, 3, 3);

            sprite.setTextSize(smallSizeFont);
            sprite.setTextColor(TFT_WHITE, TFT_BLACK);

            for (int i = 0; i < 3; i++) {
                sprite.drawString(*lines[i], 3, (lineSpacing * (2 + i)) - 2);
            }

            sprite.pushSprite(0,0);
        #else
            #ifdef HAS_EPAPER
                // ... to be continued
            #else
                if (displayFound) {
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setTextSize(1);
                    display.setCursor(0, 0);
                    display.println(header);
                    for (int i = 0; i < 3; i++) {
                        display.setCursor(0, 8 + (8 * i));
                        display.println(*lines[i]);
                    }
                    display.ssd1306_command(SSD1306_SETCONTRAST);
                    display.ssd1306_command(1);
                    display.display();
                }
            #endif
        #endif
        delay(wait);
    #endif
}

void displayShow(const String& header, const String& line1, const String& line2, const String& line3, const String& line4, const String& line5, const String& line6, int wait) {
    #ifdef HAS_DISPLAY
        const String* const lines[] = {&line1, &line2, &line3, &line4, &line5, &line6};
        #ifdef HAS_TFT
            sprite.fillSprite(TFT_BLACK);
            #if defined(HELTEC_WIRELESS_TRACKER)
                sprite.fillRect(0, 0, 160, 19, redColor);
            #endif
            #if defined(TTGO_T_DECK_GPS) || defined(TTGO_T_DECK_PLUS)
                sprite.fillRect(0, 0, 320, 43, redColor);
            #endif
            sprite.setTextFont(0);
            sprite.setTextSize(bigSizeFont);
            sprite.setTextColor(TFT_WHITE, redColor);
            sprite.drawString(header, 3, 3);

            sprite.setTextSize(smallSizeFont);
            sprite.setTextColor(TFT_WHITE, TFT_BLACK);

            for (int i = 0; i < 6; i++) {
                sprite.drawString(*lines[i], 3, (lineSpacing * (2 + i)) - 2);
            }

            sprite.pushSprite(0,0);
        #else
            #ifdef HAS_EPAPER
                // ... to be continued
            #else
                if (displayFound) {
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setTextSize(2);
                    display.setCursor(0, 0);
                    display.println(header);
                    display.setTextSize(1);
                    for (int i = 0; i < 6; i++) {
                        display.setCursor(0, 16 + (8 * i));
                        display.println(*lines[i]);
                    }
                    display.ssd1306_command(SSD1306_SETCONTRAST);
                    display.ssd1306_command(1);
                    display.display();
                }
            #endif
        #endif
        delay(wait);
    #endif
}