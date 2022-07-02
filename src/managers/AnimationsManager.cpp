//
// Created by axels on 01/07/2022.
//

#include "managers/AnimationsManager.h"
#include "Clock.h"

void AnimationsManager::begin(TFTs *config) {
    Serial.println("[AnimationsManager] begin");
    tfts = config;
    createAnimators();
}

void AnimationsManager::end() {
    Serial.println("[AnimationsManager] End");
    for(Animator* animator : animators) {
        delete animator;
        animator = nullptr;
    }
    tfts = nullptr;
}

void AnimationsManager::loop() {
    if(millis() - millis_last_draw > 175) {
        for (Animator* animator : animators) {
            if(animator == nullptr)
            {
                Serial.println("[AnimationsManager] Error trying to use a nullptr animator");
                return;
            }
            if (animator->hasFinish())
                animator->reset();
            animator->draw();
        }
        millis_last_draw = millis();
    }
}

int computeLongerLine(const char *message) {
    int i = 0;
    int top = 0;
    int bottom = 0;
    bool topEnded = false;
    while(message[i] != '\0') {
        if(message[i] == '\n')
            topEnded = true;
        else {
            if(topEnded)
                bottom++;
            else
                top++;
        }
        i++;
    }
    return (top>bottom)?top:bottom;
}

/**
 * This function will transform an input char array (max len 24)
 * Into 6 char array of len 4.
 * We can display 4 characters per screen, therefore we store them and
 * then send them to the animator.
 * TODO: EXTENSIVE TESTING ON THIS FUNCTION / Move to utils ?
 */
char ** parse(const char * message) {
    char ** output = (char **) malloc(6*(sizeof(char *)));
    for(int i = 0 ; i < 6; i++)
        output[i] = (char *) malloc(4 * sizeof(char));


    int maxLength = computeLongerLine(message);
    int offset = 0;
    if(maxLength < 12 && (12-maxLength)/4 > 0) {
        offset = (12-maxLength)/2 - maxLength%2;
        for(int i = 0 ; i < offset; i++) {
            output[i][0] = output[i][1] = output[i][2] = output[i][3] = ' ';
        }
    }

    int defaultLineReturn = 12;
    bool finish = false;
    for(int i = 0 ; i < 12 - offset; i++) {
        if(!finish && message[i] == '\n') {
            defaultLineReturn = i + 1;
            finish = true;
        }

        if(finish)
            output[(i+offset)/2][i%2] = ' ';
        else
            output[(i+offset)/2][i%2] = message[i];
    }
    finish = false;
    for(int i = defaultLineReturn; i < defaultLineReturn+12- offset; i++) {
        if(!finish && message[i] == '\0')
            finish = true;

        if(finish)
            output[((i+offset)-defaultLineReturn)/2][(i+defaultLineReturn%2)%2+2] = ' ';
        else
            output[((i+offset)-defaultLineReturn)/2][(i+defaultLineReturn%2)%2+2] = message[i];
    }

    return output;
}

/**
 * This function will create the animators
 * First it will use the parse function to
 * transform the Event Message into a displayable
 * message on the clock
 */
void AnimationsManager::createAnimators() {
    Event * event = Clock::getInstance().alarmsManager.getCurrentEvent();
    if(event == nullptr)
        return;

    Serial.println("[AnimationsManager] Start parsing");
    char ** parsedText = parse(event->message);
    Serial.println("[AnimationsManager] parsing finish");
    int pixelCount = sizeof(pixels)/sizeof(FramedPixel);
    for(int i = 0 ; i < 6; i ++) {
        animators[i] = new Animator(
                &pixels[0],
                pixelCount,
                tfts,
                i,
                parsedText[i],
                random(0, 10)
        );
    }

    free(parsedText); // Free the container
}
