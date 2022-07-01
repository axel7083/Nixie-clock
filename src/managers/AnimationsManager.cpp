//
// Created by axels on 01/07/2022.
//

#include "managers/AnimationsManager.h"

void AnimationsManager::begin(TFTs *config) {
    tfts = config;
    int pixelCount = sizeof(pixels)/sizeof(FramedPixel);
    for(int i = 0 ; i < 6; i ++) {
        animators[i] = new Animator(&pixels[0], pixelCount, tfts, i, random(0, 10));
    }
}

void AnimationsManager::end() {
    for(Animator* animator : animators) {
        delete animator;
    }
    tfts = nullptr;
}

void AnimationsManager::loop() {
    if(millis() - millis_last_draw > 175) {
        for (Animator* animator : animators) {
            if (animator->hasFinish())
                animator->reset();
            animator->draw();
        }
        millis_last_draw = millis();
    }
}
