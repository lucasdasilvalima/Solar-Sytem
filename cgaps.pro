TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS +=-lGL
LIBS +=-lGLU
LIBS +=-lglut
SOURCES += \
        SOIL/SOIL.c \
        SOIL/image_DXT.c \
        SOIL/image_helper.c \
        SOIL/stb_image_aug.c \
        application.cpp \
        gl_camera.cpp \
        gl_viewer.cpp \
        main.cpp \
        timer.cpp

HEADERS += \
    SOIL/SOIL.h \
    SOIL/image_DXT.h \
    SOIL/image_helper.h \
    SOIL/stb_image_aug.h \
    SOIL/stbi_DDS_aug.h \
    SOIL/stbi_DDS_aug_c.h \
    application.h \
    gl_camera.h \
    gl_viewer.h \
    timer.h \
    vector3.h

DISTFILES += \
    cgaps.pro.user
