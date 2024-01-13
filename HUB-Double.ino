/*#include <ElegantOTA.h>
#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);*/

#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#include "ESP32-VirtualMatrixPanel-I2S-DMA.h" 
 
#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.
#define NUM_ROWS 4 // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 1 // Number of INDIVIDUAL PANELS per ROW
#define SERPENT false
#define TOPDOWN false  
MatrixPanel_I2S_DMA dma_displayAsli;
VirtualMatrixPanel  *dma_display = 0;

void setup(){
    delay(250);  
    Serial.begin(9600);
    Serial.println("*****************************************************");
    Serial.println("*         Double Hub Demonstration              *");
    Serial.println("*****************************************************");

    HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,// DO NOT CHANGE THIS
                PANEL_RES_Y,// DO NOT CHANGE THIS
                NUM_ROWS*NUM_COLS// DO NOT CHANGE THIS
//,{2, 6, 10, 3, 7, 11, 39, 38, 37, 36, -1, 33, 35, 34, 5 ,9, 13}//r1 g1 b1 r2 g2 b2 a b c d e lat oe clk lat2 lat3 lat4-->ESP32-S3 DEFAULT PIN, CHANGE THIS WHATEVER YOU WANT TO OTHER PIN
,{19, 13, 18, 5, 12, 17, 16, 14, 4, 27, -1, 26, 15, 2, 22, 23, 25}//r1 g1 b1 r2 g2 b2 a b c d e lat oe clk lat2 lat3 lat4-->ORIGINAL ESP32,CHANGE THIS WHATEVER YOU WANT TO OTHER PIN
);
  
dma_displayAsli.tingkat=NUM_ROWS;//Total hub75 paralel
dma_displayAsli.begin(mxconfig);
dma_display = new VirtualMatrixPanel(dma_displayAsli, NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y,SERPENT,TOPDOWN);
dma_displayAsli.setPanelBrightness(57); dma_display->fillScreen(0);
    
/*WiFi.mode(WIFI_AP);
WiFi.softAP("tes","");
server.on("/", [](){server.send(200, "text/plain", "H= "+String(dma_displayAsli.tingkat));});
server.begin();
ElegantOTA.begin(&server);*/

dma_displayAsli.clearScreen();
dma_display->drawRect(0,0, 64, 32, dma_display->color565(255,255,255));
dma_display->setTextColor(dma_display->color565(255, 0, 0));
dma_display->setCursor(5, 5); dma_display->print("FLOOR-1");

dma_display->drawRect(0,32, 64, 64, dma_display->color565(255,255,0));
dma_display->drawLine(0,63, 63, 63, dma_display->color565(255,255,0));
dma_display->setTextColor(dma_display->color565(0, 255, 0));
dma_display->setCursor(5, 37); dma_display->print("FLOOR 2");

dma_display->drawRect(0,64, 64, 96, dma_display->color565(0,255,0));
dma_display->drawLine(0,95, 63, 95, dma_display->color565(0,255,0));
dma_display->setTextColor(dma_display->color565(0, 0, 255));
dma_display->setCursor(5, 69); dma_display->print("FLOOR 3");

dma_display->drawRect(0,96, 64, 129, dma_display->color565(255,0,255));
dma_display->drawLine(0,127, 63, 127, dma_display->color565(255,0,255));
dma_display->setTextColor(dma_display->color565(127, 255, 0));
dma_display->setCursor(5, 69+32); dma_display->print("FLOOR 4");
}

  
void loop() {
//server.handleClient(); delay(250);    
} 
