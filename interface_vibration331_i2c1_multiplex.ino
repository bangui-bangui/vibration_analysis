//so this is main.ino code (main part) it receive vibration data from another esp32 with protocol esp now and print it in the ui chart2.
//so basically the esp now protcol will send vibrationData.vibrationY and here is how  i manage to update the data 

#include <Wire.h>
#include <SPI.h>

#define USE_UI    //if you want to use the ui export from Squareline, please do not annotate this line.

#if defined USE_UI
#include <lvgl.h>
#include "ui.h"
#endif

#include <Arduino_GFX_Library.h>
#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
#include <esp_now.h>
#include <WiFi.h>
bool once = true;
lv_chart_series_t *ui_Chart1_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart2_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart3_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart4_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart5_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart6_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart7_series_1; // Declare chart series variable
lv_chart_series_t *ui_Chart8_series_1; // Declare chart series variable

//lv_coord_t ui_Chart2_series_1_array[20]; // Define array to hold datavariable
unsigned long initEspNowStartTime = 0;
bool initEspNowStarted = false;

void initEspNow();


/******Please define a corresponding line based on your development board.************/
//#define Display_43
//#define Display_50
#define Display_70
/*******************************************************************************
   Screen Driver Configuration
*******************************************************************************/
#if defined (Display_43)         //4.3INCH 480x272
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
  45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
  5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
  8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
  bus,
  480 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
  272 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
  1 /* pclk_active_neg */, 7000000 /* prefer_speed */, true /* auto_flush */);

#elif defined (Display_50)         //5.0INCH 800x480
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
  45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
  5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
  8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
  bus,
  800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
  480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
  1 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

#elif defined (Display_70)       //7.0INCH 800x480
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
  14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
  9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
  15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
  bus,
  800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 1 /* hsync_pulse_width */, 46 /* hsync_back_porch */,
  480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 1 /* vsync_pulse_width */, 23 /* vsync_back_porch */,
  0 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);
#endif

/*******************************************************************************
   Screen Driver Configuration  end
*******************************************************************************/


/*******************************************************************************
   Please config the touch panel in touch.h
 ******************************************************************************/
#include "touch.h"

#ifdef USE_UI
/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[800 * 480 / 10];      //5,7inch: lv_color_t disp_draw_buf[800*480/10]            4.3inch: lv_color_t disp_draw_buf[480*272/10]
//static lv_color_t disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  lcd->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      Serial.print( "Data x :" );
      //Serial.println( touch_last_x );

      Serial.print( "Data y :" );
      //Serial.println( touch_last_y );
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
  delay(15);
}
#endif

// //////////////////////////////////////////////////////////////////////////////////////////////////////structure for the vibration data
typedef struct struct_message {
  int16_t magnitude0;
  int16_t magnitude1;
  int16_t magnitude2;
  int16_t magnitude3;
  int16_t magnitude4;
  int16_t magnitude5;
  int16_t magnitude6;
  int16_t magnitude7;
} struct_message;

struct_message vibrationData;

// Fonction de callback will be executed when we receive data
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  // Copier les données reçues dans la structure VibrationData
  memcpy(&vibrationData, incomingData, sizeof(vibrationData));
  
  // prit vibration data in the serial monitor
//  Serial.print("magnitude1 : ");
//  Serial.println(vibrationData.magnitude1);
//  Serial.print("magnitude4 : ");
//  Serial.println(vibrationData.magnitude4);
//  Serial.print("Vibration Z: ");
//  Serial.println(vibrationData.vibrationZ);
//  Serial.println();
}

//////////////////////////////////////////////////////////////////////////////////////setup//////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Serial.println("LVGL Widgets Demo");
#if defined(Display_50) || defined(Display_70)
  //IO Port Pins
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW);
#elif defined(Display_43)
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  pinMode(35, OUTPUT);
  digitalWrite(35, LOW);
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(0, OUTPUT);//TOUCH-CS
#endif

  // Init Display
  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  delay(200);

#ifdef USE_UI
  lv_init();

  delay(100);
  touch_init();

  screenWidth = lcd->width();
  screenHeight = lcd->height();

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);
  //  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, 480 * 272 / 10);
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
#endif

#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif

#ifdef USE_UI
  ui_init();//ui from Squareline or GUI Guider
#else
  lcd->fillScreen(RED);
  delay(800);
  lcd->fillScreen(BLUE);
  delay(800);
  lcd->fillScreen(YELLOW);
  delay(800);
  lcd->fillScreen(GREEN);
  delay(800);
#endif
  Serial.println( "Setup done" );


  // attendre 5 s

  initEspNowStartTime = millis() + 5000; // Attendre 5 secondes


//******************************************************************Setup for the chart*****************************************************************************************//
lv_setup_TempChart_1();
lv_setup_TempChart_2();
lv_setup_TempChart_3();
lv_setup_TempChart_4();
lv_setup_TempChart_5();
lv_setup_TempChart_6();
lv_setup_TempChart_7();
lv_setup_TempChart_8();

}
//fonction pour initialiser l'ecran esp apres 5second
void initEspNow(){

  // Configurer le périphérique en tant que station Wi-Fi
  WiFi.mode(WIFI_STA);

  // Initialiser ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur lors de l'initialisation d'ESP-NOW");
    return;
  }
  
  // Une fois ESPNow initialisé avec succès, nous nous enregistrerons pour le callback de réception
  esp_now_register_recv_cb(OnDataRecv); 
}

//**********************************************************************************loop*******************************************************************************************//
void loop(){
 
  while (1)
  {
    
    lv_update_TempChart_1();
    lv_update_TempChart_2();
    lv_update_TempChart_3();
    lv_update_TempChart_4();
    lv_update_TempChart_5();
    lv_update_TempChart_6();
    lv_update_TempChart_7();
    lv_update_TempChart_8();

      // Vérifier si le temps imparti pour initEspNow() s'est écoulé // ce code retarde le lancement de la communication espnow
  if (!initEspNowStarted && millis() >= initEspNowStartTime) {
    // Appeler la fonction pour initialiser ESP-NOW
    initEspNow();
    initEspNowStarted = true; // Marquer que l'initialisation a été effectuée
  }
#ifdef USE_UI
//    lv_update_TempChart_1();
//    lv_update_TempChart_2();
//    lv_update_TempChart_3();
//    lv_update_TempChart_4();
//    lv_update_TempChart_5();
//    lv_update_TempChart_6();
//    lv_update_TempChart_7();
//    lv_update_TempChart_8();

//update chart screen3 loop

    lv_timer_handler();
    delay(1);
    //Serial.println("Loop iteration complete.");
}
#endif
}
  
//***************************************************************setup maj chart************************************************************************************//

//setup updating the ui chart2 with vibration data
//chart1 broyeur
void lv_setup_TempChart_1(void) {
    // Create a global series
    ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart1, 500);
    lv_chart_set_update_mode( ui_Chart1, LV_CHART_UPDATE_MODE_SHIFT );
}


//chart2 Ventilateur
void lv_setup_TempChart_2(void) {
    // Create a global series
    ui_Chart2_series_1 = lv_chart_add_series(ui_Chart2, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart2, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart2, 500);
    lv_chart_set_update_mode( ui_Chart2, LV_CHART_UPDATE_MODE_SHIFT );
}
//chart3 Vibrant
void lv_setup_TempChart_3(void) {
    // Create a global series
    ui_Chart3_series_1 = lv_chart_add_series(ui_Chart3, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart3, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart3, 500);
    lv_chart_set_update_mode( ui_Chart3, LV_CHART_UPDATE_MODE_SHIFT );
}
//chart4 Vis A
void lv_setup_TempChart_4(void) {
    // Create a global series
    ui_Chart4_series_1 = lv_chart_add_series(ui_Chart4, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart4, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart4, 500);
    lv_chart_set_update_mode( ui_Chart4, LV_CHART_UPDATE_MODE_SHIFT );
}
//chart5 Tamis
void lv_setup_TempChart_5(void) {
    // Create a global series
    ui_Chart5_series_1 = lv_chart_add_series(ui_Chart5, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart5, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart5, 500);
    lv_chart_set_update_mode( ui_Chart5, LV_CHART_UPDATE_MODE_SHIFT );
}
//chart6 Vis B
void lv_setup_TempChart_6(void) {
    // Create a global series
    ui_Chart6_series_1 = lv_chart_add_series(ui_Chart6, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart6, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart6, 500);
    lv_chart_set_update_mode( ui_Chart6, LV_CHART_UPDATE_MODE_SHIFT );
}
//chart7 Elevateur
void lv_setup_TempChart_7(void) {
    // Create a global series
    ui_Chart7_series_1 = lv_chart_add_series(ui_Chart7, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart7, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart7, 500);
    lv_chart_set_update_mode( ui_Chart7, LV_CHART_UPDATE_MODE_SHIFT );
}
//chart7 Vis Dosage
void lv_setup_TempChart_8(void) {
    // Create a global series
    ui_Chart8_series_1 = lv_chart_add_series(ui_Chart8, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ui_Chart8, LV_CHART_AXIS_PRIMARY_Y, -3000, 3000);

    lv_chart_set_point_count(ui_Chart8, 500);
    lv_chart_set_update_mode( ui_Chart8, LV_CHART_UPDATE_MODE_SHIFT );
}


//***************************************************************************************loop updating data**************************************************************//
//chart 1
void lv_update_TempChart_1(void) {
    lv_chart_set_next_value(ui_Chart1, ui_Chart1_series_1, vibrationData.magnitude0);
    lv_chart_refresh(ui_Chart1); /*Required after direct set*/
}
//chart2
void lv_update_TempChart_2(void) {
    lv_chart_set_next_value(ui_Chart2, ui_Chart2_series_1, vibrationData.magnitude1);
    lv_chart_refresh(ui_Chart2); /*Required after direct set*/
}
//chart 3
void lv_update_TempChart_3(void) {
    lv_chart_set_next_value(ui_Chart3, ui_Chart3_series_1, vibrationData.magnitude2);
    lv_chart_refresh(ui_Chart3); /*Required after direct set*/
}
//chart4
void lv_update_TempChart_4(void) {
    lv_chart_set_next_value(ui_Chart4, ui_Chart4_series_1, vibrationData.magnitude3);
    lv_chart_refresh(ui_Chart4); /*Required after direct set*/
}
//chart 5
void lv_update_TempChart_5(void) {
    lv_chart_set_next_value(ui_Chart5, ui_Chart5_series_1, vibrationData.magnitude4);
    lv_chart_refresh(ui_Chart5); /*Required after direct set*/
}
//chart6
void lv_update_TempChart_6(void) {
    lv_chart_set_next_value(ui_Chart6, ui_Chart6_series_1, vibrationData.magnitude5);
    lv_chart_refresh(ui_Chart6); /*Required after direct set*/
}
//chart 7
void lv_update_TempChart_7(void) {
    lv_chart_set_next_value(ui_Chart7, ui_Chart7_series_1, vibrationData.magnitude6);
    lv_chart_refresh(ui_Chart7); /*Required after direct set*/
}
//chart 8
void lv_update_TempChart_8(void) {
    lv_chart_set_next_value(ui_Chart8, ui_Chart8_series_1, vibrationData.magnitude7);
    lv_chart_refresh(ui_Chart8); /*Required after direct set*/
}
