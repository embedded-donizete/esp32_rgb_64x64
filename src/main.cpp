#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "Image.hpp"

#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13
#define A_PIN 23
#define B_PIN 22
#define C_PIN 5
#define D_PIN 17
#define E_PIN 32
#define LAT_PIN 4
#define OE_PIN 15
#define CLK_PIN 16
#define WIDTH 64
#define HEIGHT 64
#define CHAIN 1

HUB75_I2S_CFG::i2s_pins pins = {
    R1_PIN,
    G1_PIN,
    B1_PIN,
    R2_PIN,
    G2_PIN,
    B2_PIN,
    A_PIN,
    B_PIN,
    C_PIN,
    D_PIN,
    E_PIN,
    LAT_PIN,
    OE_PIN,
    CLK_PIN,
};
HUB75_I2S_CFG mxconfig(WIDTH, HEIGHT, CHAIN, pins);
MatrixPanel_I2S_DMA dma_display(mxconfig);

void setup()
{
  dma_display.begin();
  dma_display.setBrightness8(3);
}

inline void draw_pixel(uint8_t x, uint8_t y, uint16_t color)
{
  dma_display.drawPixel((HEIGHT - 1) - y, (HEIGHT - 1) - x, color);
}

void loop()
{
  dma_display.clearScreen();
  for (int y = 0; y < HEIGHT; y++)
  {
    unsigned char *start = rgb565data_bin + (y * WIDTH * 2);
    for (int x = 0; x < WIDTH; x++)
    {
      unsigned char lower = start[x * 2];
      unsigned char higher = start[(x * 2) + 1];
      uint16_t color = (higher << 8) | lower;
      draw_pixel(y, x, color);
    }
  }
  sleep(1000);
}