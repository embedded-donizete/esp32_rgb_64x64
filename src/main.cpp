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

#define FPS_PER_SECOND 60
#define FPS_DRAW_TIME (1000000 / FPS_PER_SECOND)

void setup()
{
  dma_display.begin();
  dma_display.setBrightness8(3);
}

inline void draw_pixel(uint8_t x, uint8_t y, uint16_t color)
{
  dma_display.drawPixel((HEIGHT - 1) - y, (HEIGHT - 1) - x, color);
}

inline void draw_picture(const uint16_t *picture)
{
  unsigned long start = micros();
  for (uint16_t y = 0; y < HEIGHT; y++)
  {
    const uint16_t *line = picture + (y * WIDTH);
    for (uint16_t x = 0; x < WIDTH; x++)
    {
      uint16_t color = line[x];
      draw_pixel(y, x, color);
    }
  }
  unsigned long end = micros();
  delayMicroseconds(FPS_DRAW_TIME - (end - start));
}

void loop()
{
  for (const uint16_t *data : datas)
  {
    draw_picture(data);
  }
}