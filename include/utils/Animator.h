//
// Created by axels on 01/07/2022.
//

#ifndef CLOCK2_0_ANIMATOR_H
#define CLOCK2_0_ANIMATOR_H

#include "Arduino.h"
#include "hardware/TFTs.h"

struct FramedPixel {
    uint8_t x;
    uint8_t y;
    uint8_t frame;
    uint8_t color;
    uint8_t color_next;
};

static uint32_t colors[][5] = {
        {TFT_BLACK, TFT_WHITE, TFT_CYAN, TFT_NAVY, TFT_DARKCYAN},
        {TFT_BLACK, TFT_WHITE, TFT_PINK, TFT_PURPLE, TFT_RED},
};

class Animator {
public:
    Animator(FramedPixel *framedPixels, int size, TFTs *tfts, uint8_t screen, uint8_t timeOffset = 0)  {
        this->framedPixels = framedPixels;
        this->size = size;
        this->tfts = tfts;
        this->screen = screen;
        this->timeOffset = timeOffset;

        int max = 0;
        for(int i = 0 ; i < size; i++) {
            if(framedPixels[i].frame > max)
                max = framedPixels[i].frame;
        }
        frameCount = max;
        tfts->chip_select.select(screen);
        tfts->fillScreen(TFT_BLACK);

        reset();
    }

    void reset() {
        currentFrame = 0;
        scale = random(5,15);
        xOffset = random(-2, 2);
        yOffset = random(0, 4);
        colorIndex = random(0,2);
    }

    void draw();
    bool hasFinish() {
        return currentFrame == frameCount + 1;
    }

private:
    int currentFrame = 0;
    int frameCount;
    FramedPixel *framedPixels;
    int size;
    TFTs *tfts;
    uint8_t scale;
    uint8_t xOffset = 0;
    uint8_t yOffset = 0;
    uint8_t screen;
    uint8_t timeOffset;
    uint8_t colorIndex;

    void drawRect(uint16_t x, uint16_t y, uint8_t colorId);
    uint16_t getColor(int id) {
        return colors[colorIndex][id];
    }
};


#endif //CLOCK2_0_ANIMATOR_H
