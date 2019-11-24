#include "gl_drawable.h"
#include <iostream>

#ifdef __WXMAC__
#include "OpenGL/gl.h"
#else
#include <GL/gl.h>
#endif

#include "wx/wx.h"

glDrawable::glDrawable()
{
}

glDrawable::glDrawable(Image* image_arg)
{
    x_trans = 0;
    y_trans = 0;
    hotspotX = 0;
    hotspotY = 0;
    angle = 0;

    xscale = 1;
    yscale = 1;

    xflip = false;
    yflip = false;

    if(image_arg != NULL) setImage(image_arg);
    else image = NULL;
}

void glDrawable::setFlip(bool x, bool y)
{
    xflip = x;
    yflip = y;
}

void glDrawable::setHotspot(int x, int y)
{
    hotspotX = x;
    hotspotY = y;
}

void glDrawable::move(int x, int y)
{
    glDrawable::x_trans = x;
    glDrawable::y_trans = y;
}

void glDrawable::scale(float x, float y)
{
    glDrawable::xscale = x;
    glDrawable::yscale = y;
}

void glDrawable::scale(float k)
{
    glDrawable::xscale = k;
    glDrawable::yscale = k;
}

void glDrawable::setImage(Image* image)
{
    glDrawable::image = image;
}

void glDrawable::rotate(float angle)
{
    glDrawable::angle = angle;
}

void glDrawable::render()
{
    assert(image != NULL);

    glLoadIdentity();

    glTranslatef(x_trans + (image->width / 2), y_trans + (image->height / 2), 0);

    if ((xscale != 1) || (yscale != 1)) {
        glScalef(xscale, yscale, 1);
    }

    if (angle != 0.0) {
        glRotatef(angle, 0, 0, 1);
    }

    glTranslatef(x_trans - (image->width / 2), y_trans - (image->height / 2), 0);

    //glTranslatef(x_trans - 150, y_trans - 150, 0);

    glBindTexture(GL_TEXTURE_2D, image->getID()[0]);

    glBegin(GL_QUADS);

    glTexCoord2f(xflip ? image->tex_coord_x : 0, yflip ? 0 : image->tex_coord_y);
    glVertex2f(-hotspotX, -hotspotY);

    glTexCoord2f(xflip ? 0 : image->tex_coord_x, yflip ? 0 : image->tex_coord_y);
    glVertex2f(image->width - hotspotX, -hotspotY);

    glTexCoord2f(xflip ? 0 : image->tex_coord_x, yflip ? image->tex_coord_y : 0);
    glVertex2f(image->width - hotspotX, image->height - hotspotY);

    glTexCoord2f(xflip ? image->tex_coord_x : 0, yflip ? image->tex_coord_y : 0);
    glVertex2f(-hotspotX, image->height - hotspotY);

/*
    glTexCoord2d(0, image->tex_coord_y);
    glVertex2f(-hotspotX / 2, -hotspotY / 2);

    glTexCoord2d(image->tex_coord_x, image->tex_coord_y);
    glVertex2f(image->width-hotspotX / 2, -hotspotY / 2);

    glTexCoord2d(image->tex_coord_x, 0);
    glVertex2f(image->width-hotspotX / 2, image->height-hotspotY / 2);

    glTexCoord2d(0, 0);
    glVertex2f(-hotspotX / 2, image->height-hotspotY / 2);
*/
    glEnd();
}
