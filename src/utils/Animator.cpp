//
// Created by axels on 01/07/2022.
//

#include "utils/Animator.h"

void Animator::drawText() {
    tfts->setTextWrap(false, false);
    tfts->setCursor(0, tfts->height()/2-tfts->fontHeight());
    tfts->printf("%c%c", text[0], text[1]);
    tfts->setCursor(0, tfts->height()/2+5);
    tfts->printf("%c%c", text[2], text[3]);
}

void Animator::draw()  {
    if(hasFinish())
        return;

    if(timeOffset > 0) {
        timeOffset--;
        return;
    }

    tfts->chip_select.select(screen);
    for(int i = 0 ; i < size; i ++) {
        if(this->framedPixels[i].frame == currentFrame - 1 && this->framedPixels[i].color_next != 255) {
            drawRect(this->framedPixels[i].x, this->framedPixels[i].y, this->framedPixels[i].color_next);
        }
        else if (this->framedPixels[i].frame == currentFrame) {
            drawRect(this->framedPixels[i].x, this->framedPixels[i].y, this->framedPixels[i].color);
        }
    }

    currentFrame++;

    tfts->setTextColor(TFT_WHITE);
    tfts->setTextSize(12);
    drawText();
}

void Animator::drawRect(uint16_t x, uint16_t y, uint8_t colorId)  {
    this->tfts->fillRect(
            (x+xOffset)*this->scale,
            this->tfts->height()-(y+yOffset)*this->scale,
            scale,
            scale,
            getColor(colorId)
    );
}

