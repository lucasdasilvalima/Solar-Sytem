#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "gl_viewer.h"
#include "timer.h"
#include "SOIL/SOIL.h"

class line_segment
{
public:
    line_segment(int x0, int y0, int x1, int y1) 
        : x0(x0), y0(y0), x1(x1), y1(y1)
    {}

    int x0, y0, x1, y1;
}; 

class application : public gl_viewer
{
public:
    application();
    ~application();
    void init_event();
    void draw_solid(double, GLuint);
    void draw_galaxy();
    void draw_sun();
    void draw_mercury();
    void draw_venus();
    void draw_earth();
    void draw_moon();
    void draw_event();
    void mouse_click_event(
        mouse_button button, mouse_button_state button_state, 
        int x, int y
    );
    void mouse_move_event(
        int x, int y
    );
    void keyboard_event(unsigned char key, int x, int y);
    bool load_gltextures();

private:
    const double radius_sun = 6.955;            // 695 500 km
    const double radius_mercury = 1.4397;         // 2.439,7 km
    const double radius_venus = 0.6051;         // 6.051 km
    const double radius_earth = 0.6371;         // 6.371 km
    const double radius_moon = 0.1737;          // 1.737,1 km
    const double distance_sun_earth = 14.9600;  //149.600.000 km
    const double distance_moon_earth = 3.84400;        //384.400 km
    bool solid;
    bool sun;
    bool galaxy;
    timer t;
    float mercury_x;
    float mercury_y;
    float mercury_z;
    float venus_x;
    float venus_y;
    float venus_z;
    float earth_x;
    float earth_y;
    float earth_z;
    float moon_x;
    float moon_y;
    float moon_z;
    GLuint  texture[4];
}; 

#endif
