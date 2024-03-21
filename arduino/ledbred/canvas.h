#ifndef CANVAS_H
#define CANVAS_H

void canvasBegin();
void canvasClear();
void canvasUpdate();
void canvasPreview();

int canvasGetLevel();
void canvasSetLevel(int i);
void canvasChangeLevel(int d);

int canvasGetColor();
void canvasSetColor(int i);
void canvasChangeColor(int d);

void canvasPenDetect();

void canvasReadPreview(Stream & in);
void canvasRead(Stream & in);
void canvasWrite(Stream & out);

void canvasDebug(int a);

#endif
