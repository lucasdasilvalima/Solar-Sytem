#include "application.h"

#define WIDTH 1920
#define HEIGHT 1060

int main(int argc, char* argv[])
{
    application app;
    app.init(argc, argv, WIDTH, HEIGHT);
    app.run();
}
