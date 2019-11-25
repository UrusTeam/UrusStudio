#pragma once

#include "gl_image.h"

class glDrawable
{
public:
    float x_trans, y_trans, angle, hotspotX, hotspotY;
    float xscale, yscale;
    Image* image;
    bool xflip, yflip;

    glDrawable();
    glDrawable(Image* image=(Image*)0);
    void setFlip(bool x, bool y);
    void move(int x, int y);
    void setHotspot(int x, int y);
    void scale(float x, float y);
    void scale(float k);
    void setImage(Image* image);
    void render();
    void rotate(float angle);

};

