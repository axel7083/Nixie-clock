//
// Created by axels on 01/07/2022.
//

#include "utils/Animator.h"

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

