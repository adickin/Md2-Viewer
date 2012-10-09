#include<QKeyEvent>
#include<QMouseEvent>
#include "GLWidget.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget (parent) {
    scale = 1;
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() {
    glClearColor(0.1,.5,0.1,1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat position[] = { 0,1,-1,1 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void GLWidget::resizeGL(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    this->width = width;
    this->height = height;

    glViewport(0,0,width, height);

    float ratio;
    if (width > height) {
        ratio = (float)width/(float)height;
        glOrtho(-ratio, ratio, -1, 1, -1, 1);
    } else {
        ratio = (float)height/(float)width;
        glOrtho(-1, 1, -ratio, ratio, -1, 1);
    }

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() {
    GLUquadricObj *q = gluNewQuadric();

    glClear(GL_COLOR_BUFFER_BIT);   

    glLoadIdentity();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glRotated(30, 0, 1, 0);
    glTranslated(x,-y,0);
    glScaled(scale,scale,scale);

    gluSphere(q, 0.2, 12, 12);
    
    glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MidButton) {
        close();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    x = event->x();
    y = event->y();

    x = ((x-(width/2.0))/width)*2.0;
    y = ((y-(height/2.0))/height)*2.0;

    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Q) {
        close();
    }
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    if (event->orientation() == Qt::Vertical) {
        if (event->delta() > 0) scale += 0.1;
        else scale -= 0.1;

        updateGL();
    }
}