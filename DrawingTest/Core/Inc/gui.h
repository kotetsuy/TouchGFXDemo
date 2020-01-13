/*
 * gui.h
 *
 *  Created on: Jan 2, 2020
 *      Author: Kotetsu Yamamoto
 *      Copyright: Kotetsu Yamamoto

MIT License

Copyright (c) 2020 Kotestu Yamamoto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

#ifndef INC_GUI_H_
#define INC_GUI_H_

#define GUI_WIDTH 320
#define GUI_HEIGHT 240

void GUI_FillScreen(uint16_t cl);
void GUI_WritePixel(uint16_t x, uint16_t y, uint16_t cl);
void GUI_WriteSquare(uint16_t x, uint16_t y, uint16_t cl);
void GUI_UpdateScreen(void);
void GUI_NormalizeXY(int16_t *x, int16_t *y);

#endif /* INC_GUI_H_ */
