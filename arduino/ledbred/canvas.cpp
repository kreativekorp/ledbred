#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "digitalWriteFast.h"
#include "config.h"
#include "canvas.h"
#include "pen.h"

#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
static Adafruit_NeoPixel canvas1 = Adafruit_NeoPixel(CANVAS_1_NUM, CANVAS_1_PIN, CANVAS_1_SET);
static long canvas1Buffer[CANVAS_1_NUM];
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
static Adafruit_NeoPixel canvas2 = Adafruit_NeoPixel(CANVAS_2_NUM, CANVAS_2_PIN, CANVAS_2_SET);
static long canvas2Buffer[CANVAS_2_NUM];
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
static Adafruit_NeoPixel canvas3 = Adafruit_NeoPixel(CANVAS_3_NUM, CANVAS_3_PIN, CANVAS_3_SET);
static long canvas3Buffer[CANVAS_3_NUM];
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
static Adafruit_NeoPixel canvas4 = Adafruit_NeoPixel(CANVAS_4_NUM, CANVAS_4_PIN, CANVAS_4_SET);
static long canvas4Buffer[CANVAS_4_NUM];
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
static Adafruit_NeoPixel canvas5 = Adafruit_NeoPixel(CANVAS_5_NUM, CANVAS_5_PIN, CANVAS_5_SET);
static long canvas5Buffer[CANVAS_5_NUM];
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
static Adafruit_NeoPixel canvas6 = Adafruit_NeoPixel(CANVAS_6_NUM, CANVAS_6_PIN, CANVAS_6_SET);
static long canvas6Buffer[CANVAS_6_NUM];
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
static Adafruit_NeoPixel canvas7 = Adafruit_NeoPixel(CANVAS_7_NUM, CANVAS_7_PIN, CANVAS_7_SET);
static long canvas7Buffer[CANVAS_7_NUM];
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
static Adafruit_NeoPixel canvas8 = Adafruit_NeoPixel(CANVAS_8_NUM, CANVAS_8_PIN, CANVAS_8_SET);
static long canvas8Buffer[CANVAS_8_NUM];
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
static Adafruit_NeoPixel canvas9 = Adafruit_NeoPixel(CANVAS_9_NUM, CANVAS_9_PIN, CANVAS_9_SET);
static long canvas9Buffer[CANVAS_9_NUM];
#endif
static Adafruit_NeoPixel preview = Adafruit_NeoPixel(PREVIEW_NUM, PREVIEW_PIN, PREVIEW_SET);
static long currentLevel = 32;
static long currentColor = -1;

void canvasBegin() {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvas1.begin();
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvas2.begin();
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvas3.begin();
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvas4.begin();
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvas5.begin();
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvas6.begin();
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvas7.begin();
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvas8.begin();
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvas9.begin();
#endif
  preview.begin();
  canvasClear();
  canvasPreview();
}

static void canvasShow() {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvas1.show();
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvas2.show();
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvas3.show();
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvas4.show();
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvas5.show();
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvas6.show();
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvas7.show();
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvas8.show();
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvas9.show();
#endif
}

static void canvasClear1(Adafruit_NeoPixel & canvas, long * canvasBuffer) {
  int n = canvas.numPixels();
  for (int i = 0; i < n; i++) {
    canvasBuffer[i] = 0;
    canvas.setPixelColor(i, 0);
  }
}

void canvasClear() {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvasClear1(canvas1, canvas1Buffer);
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvasClear1(canvas2, canvas2Buffer);
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvasClear1(canvas3, canvas3Buffer);
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvasClear1(canvas4, canvas4Buffer);
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvasClear1(canvas5, canvas5Buffer);
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvasClear1(canvas6, canvas6Buffer);
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvasClear1(canvas7, canvas7Buffer);
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvasClear1(canvas8, canvas8Buffer);
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvasClear1(canvas9, canvas9Buffer);
#endif
  canvasShow();
}

static void canvasUpdate1(Adafruit_NeoPixel & canvas, long * canvasBuffer) {
  int n = canvas.numPixels();
  for (int i = 0; i < n; i++) {
    long w = ((((canvasBuffer[i] >> 24) & 0xFF) * currentLevel) >> 8) << 24;
    long r = ((((canvasBuffer[i] >> 16) & 0xFF) * currentLevel) >> 8) << 16;
    long g = ((((canvasBuffer[i] >>  8) & 0xFF) * currentLevel) >> 8) <<  8;
    long b = ((((canvasBuffer[i] >>  0) & 0xFF) * currentLevel) >> 8) <<  0;
    canvas.setPixelColor(i, w|r|g|b);
  }
}

void canvasUpdate() {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvasUpdate1(canvas1, canvas1Buffer);
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvasUpdate1(canvas2, canvas2Buffer);
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvasUpdate1(canvas3, canvas3Buffer);
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvasUpdate1(canvas4, canvas4Buffer);
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvasUpdate1(canvas5, canvas5Buffer);
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvasUpdate1(canvas6, canvas6Buffer);
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvasUpdate1(canvas7, canvas7Buffer);
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvasUpdate1(canvas8, canvas8Buffer);
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvasUpdate1(canvas9, canvas9Buffer);
#endif
  canvasShow();
}

void canvasPreview() {
  long w = ((((currentColor >> 24) & 0xFF) * currentLevel) >> 8) << 24;
  long r = ((((currentColor >> 16) & 0xFF) * currentLevel) >> 8) << 16;
  long g = ((((currentColor >>  8) & 0xFF) * currentLevel) >> 8) <<  8;
  long b = ((((currentColor >>  0) & 0xFF) * currentLevel) >> 8) <<  0;
  preview.fill(w|r|g|b, 0, 0);
  preview.show();
}

static long levels[] = {
  16, 18, 20, 24, 28, 32,
  40, 48, 60, 72, 88, 108,
  128, 160, 192, 240
};

static long colors[] = {
  0,        // black
  0x222222, // dark gray
  0x666666, // gray
  -1,       // white
  0xFFFF00, // yellow
  0xFF6600, // orange
  0xFF0000, // red
  0xFF00FF, // pink
  0x6600FF, // purple
  0x0000FF, // blue
  0x00FFFF, // cyan
  0x00FF66, // aqua
  0x00FF00, // green
  0x002200, // dark green
  0x996633, // tan
  0x332211, // brown
};

static int levelIndex(long b) {
  int index = 0;
  long diff = 99999;
  int n = sizeof(levels) / sizeof(long);
  for (int i = 0; i < n; i++) {
    long d = levels[i] - b;
    if ((d *= d) < diff) {
      index = i;
      diff = d;
    }
  }
  return index;
}

static int colorIndex(long c) {
  int ci = 0;
  long cd = 999999;
  long cw = (c >> 24) & 0xFF;
  long cr = (c >> 16) & 0xFF;
  long cg = (c >>  8) & 0xFF;
  long cb = (c >>  0) & 0xFF;
  int n = sizeof(colors) / sizeof(long);
  for (int i = 0; i < n; i++) {
    long dw = ((colors[i] >> 24) & 0xFF) - cw;
    long dr = ((colors[i] >> 16) & 0xFF) - cr;
    long dg = ((colors[i] >>  8) & 0xFF) - cg;
    long db = ((colors[i] >>  0) & 0xFF) - cb;
    long d = dw*dw + dr*dr + dg*dg + db*db;
    if (d < cd) {
      ci = i;
      cd = d;
    }
  }
  return ci;
}

int canvasGetLevel() {
  return levelIndex(currentLevel);
}

void canvasSetLevel(int i) {
  int n = sizeof(levels) / sizeof(long);
  if (i >= 0 && i < n) {
    currentLevel = levels[i];
    canvasPreview();
    canvasUpdate();
  }
}

void canvasChangeLevel(int d) {
  canvasSetLevel(canvasGetLevel() + d);
}

int canvasGetColor() {
  return colorIndex(currentColor);
}

void canvasSetColor(int i) {
  int n = sizeof(colors) / sizeof(long);
  if ((i %= n) < 0) i += n;
  currentColor = colors[i];
  canvasPreview();
}

void canvasChangeColor(int d) {
  canvasSetColor(canvasGetColor() + d);
}

void canvasPenDetect() {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvas1.clear();
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvas2.clear();
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvas3.clear();
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvas4.clear();
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvas5.clear();
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvas6.clear();
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvas7.clear();
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvas8.clear();
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvas9.clear();
#endif
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvas1.show();
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvas2.show();
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvas3.show();
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvas4.show();
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvas5.show();
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvas6.show();
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvas7.show();
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvas8.show();
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvas9.show();
#endif
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  int i1 = penDetect(canvas1);
  if (i1 >= 0) canvas1Buffer[i1] = (canvas1Buffer[i1] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  int i2 = penDetect(canvas2);
  if (i2 >= 0) canvas2Buffer[i2] = (canvas2Buffer[i2] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  int i3 = penDetect(canvas3);
  if (i3 >= 0) canvas3Buffer[i3] = (canvas3Buffer[i3] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  int i4 = penDetect(canvas4);
  if (i4 >= 0) canvas4Buffer[i4] = (canvas4Buffer[i4] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  int i5 = penDetect(canvas5);
  if (i5 >= 0) canvas5Buffer[i5] = (canvas5Buffer[i5] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  int i6 = penDetect(canvas6);
  if (i6 >= 0) canvas6Buffer[i6] = (canvas6Buffer[i6] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  int i7 = penDetect(canvas7);
  if (i7 >= 0) canvas7Buffer[i7] = (canvas7Buffer[i7] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  int i8 = penDetect(canvas8);
  if (i8 >= 0) canvas8Buffer[i8] = (canvas8Buffer[i8] == currentColor) ? 0 : currentColor;
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  int i9 = penDetect(canvas9);
  if (i9 >= 0) canvas9Buffer[i9] = (canvas9Buffer[i9] == currentColor) ? 0 : currentColor;
#endif
  canvasUpdate();
}

static void canvasReadPreview1(Adafruit_NeoPixel & canvas, Stream & in) {
  long pixels[BUFFER_PIXELS];
  long w, r, g, b;
  int i = 0;
  int n = canvas.numPixels();
  while (i < n) {
    in.readBytes((char *)pixels, (sizeof(long)) * BUFFER_PIXELS);
    for (int p = 0; i < n && p < BUFFER_PIXELS; i++, p++) {
      w = ((((pixels[p] >> 24) & 0xFF) * currentLevel) >> 8) << 24;
      r = ((((pixels[p] >> 16) & 0xFF) * currentLevel) >> 8) << 16;
      g = ((((pixels[p] >>  8) & 0xFF) * currentLevel) >> 8) <<  8;
      b = ((((pixels[p] >>  0) & 0xFF) * currentLevel) >> 8) <<  0;
      canvas.setPixelColor(i, w|r|g|b);
    }
  }
}

void canvasReadPreview(Stream & in) {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvasReadPreview1(canvas1, in);
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvasReadPreview1(canvas2, in);
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvasReadPreview1(canvas3, in);
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvasReadPreview1(canvas4, in);
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvasReadPreview1(canvas5, in);
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvasReadPreview1(canvas6, in);
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvasReadPreview1(canvas7, in);
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvasReadPreview1(canvas8, in);
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvasReadPreview1(canvas9, in);
#endif
  canvasShow();
}

void canvasRead(Stream & in) {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  in.readBytes((char *)canvas1Buffer, (sizeof(long)) * CANVAS_1_NUM);
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  in.readBytes((char *)canvas2Buffer, (sizeof(long)) * CANVAS_2_NUM);
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  in.readBytes((char *)canvas3Buffer, (sizeof(long)) * CANVAS_3_NUM);
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  in.readBytes((char *)canvas4Buffer, (sizeof(long)) * CANVAS_4_NUM);
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  in.readBytes((char *)canvas5Buffer, (sizeof(long)) * CANVAS_5_NUM);
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  in.readBytes((char *)canvas6Buffer, (sizeof(long)) * CANVAS_6_NUM);
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  in.readBytes((char *)canvas7Buffer, (sizeof(long)) * CANVAS_7_NUM);
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  in.readBytes((char *)canvas8Buffer, (sizeof(long)) * CANVAS_8_NUM);
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  in.readBytes((char *)canvas9Buffer, (sizeof(long)) * CANVAS_9_NUM);
#endif
  canvasUpdate();
}

void canvasWrite(Stream & out) {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  out.write((char *)canvas1Buffer, (sizeof(long)) * CANVAS_1_NUM);
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  out.write((char *)canvas2Buffer, (sizeof(long)) * CANVAS_2_NUM);
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  out.write((char *)canvas3Buffer, (sizeof(long)) * CANVAS_3_NUM);
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  out.write((char *)canvas4Buffer, (sizeof(long)) * CANVAS_4_NUM);
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  out.write((char *)canvas5Buffer, (sizeof(long)) * CANVAS_5_NUM);
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  out.write((char *)canvas6Buffer, (sizeof(long)) * CANVAS_6_NUM);
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  out.write((char *)canvas7Buffer, (sizeof(long)) * CANVAS_7_NUM);
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  out.write((char *)canvas8Buffer, (sizeof(long)) * CANVAS_8_NUM);
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  out.write((char *)canvas9Buffer, (sizeof(long)) * CANVAS_9_NUM);
#endif
}

static void canvasDebug1(Adafruit_NeoPixel & canvas, long color, int a) {
  int n = canvas.numPixels();
  if ((a %= n) < 0) a += n;
  for (int i = 0; i < n; i++) {
    canvas.setPixelColor(i, ((i == a) ? color : 0));
  }
}

void canvasDebug(int a) {
#if defined(CANVAS_1_NUM) || defined(CANVAS_1_PIN) || defined(CANVAS_1_SET)
  canvasDebug1(canvas1, colors[4], a);
#endif
#if defined(CANVAS_2_NUM) || defined(CANVAS_2_PIN) || defined(CANVAS_2_SET)
  canvasDebug1(canvas2, colors[5], a);
#endif
#if defined(CANVAS_3_NUM) || defined(CANVAS_3_PIN) || defined(CANVAS_3_SET)
  canvasDebug1(canvas3, colors[6], a);
#endif
#if defined(CANVAS_4_NUM) || defined(CANVAS_4_PIN) || defined(CANVAS_4_SET)
  canvasDebug1(canvas4, colors[7], a);
#endif
#if defined(CANVAS_5_NUM) || defined(CANVAS_5_PIN) || defined(CANVAS_5_SET)
  canvasDebug1(canvas5, colors[8], a);
#endif
#if defined(CANVAS_6_NUM) || defined(CANVAS_6_PIN) || defined(CANVAS_6_SET)
  canvasDebug1(canvas6, colors[9], a);
#endif
#if defined(CANVAS_7_NUM) || defined(CANVAS_7_PIN) || defined(CANVAS_7_SET)
  canvasDebug1(canvas7, colors[10], a);
#endif
#if defined(CANVAS_8_NUM) || defined(CANVAS_8_PIN) || defined(CANVAS_8_SET)
  canvasDebug1(canvas8, colors[11], a);
#endif
#if defined(CANVAS_9_NUM) || defined(CANVAS_9_PIN) || defined(CANVAS_9_SET)
  canvasDebug1(canvas9, colors[12], a);
#endif
  canvasShow();
}
