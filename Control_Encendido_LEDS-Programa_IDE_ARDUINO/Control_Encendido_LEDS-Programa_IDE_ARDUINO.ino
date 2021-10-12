/* ********************************************************************
 * 
 *      PROGRAMA PARA MANEJAR EL ENCENDIDO DE 3 LEDS
 *                CON LA TARJETA "ESP32-CAM"
 * 
 * ********************************************************************
 *       Diplomado IoT                     octubre/12 - 2021
 * ********************************************************************
 * 
 * Descripción:
 * 
 * 1. Este programa controla el encendido de 3 LEDs cada
 *    1, 3 y 5 segundos, mediante la técnica no-bloqueante
 *    que se encuentra en el programa: 
 *    "Conexión básica por MQTT del NodeMCU"
 *    realizado por Hugo Escalpelo (28-julio-2021), que se
 *    encuentra en el REPOSITORIO (GitHub) de Codigo IoT
 * 
 * 2. Este programa envía controla el encendido y apagado de
 *    3 leds conectados a la tarjeta ESP32 en los siguientes
 *    pines: 
 * 
 *    Componente      PinESP32CAM       Estados lógicos
 *    ledStatus--------GPIO 33---------On=>LOW, Off=>HIGH
 *    ledFlash---------GPIO 4----------On=>HIGH, Off=>LOW
 *       
 *    ESPCAM32    ->  LEDS
 *    GPIO12----------LED 1 segundos
 *    GPIO13----------LED 3 segundos
 *    GPIO14----------LED 5 segundos
 *    GPIO15----------LED 7 segundos
 * 
 * ******************************************************************/

 /* -----------------------------------------------------------------
  *  
  *  ESTRUCTURA DEL PROGRAMA:
  *  
  *  100 - void setup()
  *  
  *  200 - void loop()
  *        210 - void controlar_tiempos_led()
  *        
  * ---------------------------------------------------------------*/

/**********************************
 *    Declaracion de VARIABLES
 * *******************************/
long timeNow, timeLast;   // Variables de control de tiempo no bloqueante
int wait = 5000;          // Espera cada 5 segundos para envío de mensajes MQTT

/**********************************
 *    Declaracion de pines - LED
 *    y TIEMPOS de encendido
 *    
 *    GPIO12 <- led_1_seg
 *    GPIO13 <- led_3_seg
 *    GPIO14 <- led_5_seg
 *    GPIO15 <- led_7_seg
 * *******************************/
int num_LEDs = 4;
int pin_LED[] = {12, 13, 14, 15};
int wait_LED[] = {1000, 3000, 5000, 7000};
long timeLast_LED[4];

/* ********************************************************************
 *  
 *                    100 - void setup()
 *                    
 * *******************************************************************/
void setup() {

  Serial.begin (115200);
  
  /* - 1 ----------------------------------------------------
   *               Inicializacion de LED's 
   * ------------------------------------------------------*/
  for ( int i = 0; i < num_LEDs; ++i ) {
    pinMode (pin_LED[i], OUTPUT);
    digitalWrite (pin_LED[i], LOW);
    timeLast_LED[i] =  millis();
  }
 
  Serial.println("Iniciando secuencia de encendido de leds . . .");

}


/* ********************************************************************
 *  
 *                      200 - void loop()
 *                      
 * *******************************************************************/
void loop() {

  /* -------------------------------------------------- *
   *     Verificar siempre que haya conexión al broker  *
   * ---------------------------------------------------*/
  controlar_secuencia_led();

}

/* ********************************************************************
 *  
 *                  210 - controlar_tiempos_led()
 *                      
 * *******************************************************************/
 void controlar_secuencia_led() {
  /* --------------------------------------------------------
   *     Encendido y apagado de leds cada "w" segundos 
   * ------------------------------------------------------*/
  for ( int i = 0; i < num_LEDs; ++i ) {
    timeNow = millis();
    if (timeNow - timeLast_LED[i] > wait_LED[i]) { 
      /* --- Se cumplieron los "w" segundos y se actualiza
          la variable "timeLast" para seguimiento del tiempo --- */
      timeLast_LED[i] = timeNow;

      if (digitalRead(pin_LED[i])) {
        digitalWrite(pin_LED[i], LOW);
        Serial.print("LED: ");
        Serial.print(i);
        Serial.println(" APAGADO");
      } else {
        digitalWrite(pin_LED[i], HIGH);
        Serial.print("LED: ");
        Serial.print(i);
        Serial.println(" ENCENDIDO");
      }
    }
  }
 }
