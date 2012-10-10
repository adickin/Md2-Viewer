#include <QKeyEvent>
#include <QMouseEvent>
#include "GLWidget.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget (parent) 
{
    scale = 1;
    bool loadSucessful = md2Reader_.LoadModel("./models-5/stormtrooper/stormtrooperweapon.md2");
    if(!loadSucessful)
    {
        fprintf(stderr, "getting here\n");
        //fprintf(stderr, "verticies: %d, triangles %d\n, frames %d", md2Reader_.num_xyz, md2Reader_.num_tris, md2Reader_.num_frames);
    }
}

GLWidget::~GLWidget() { }

void GLWidget::initializeGL() {
    glClearColor(1.0,1.0,1.0,1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);

    //GLfloat position[] = { 0,1,-1,1 };
    //glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void GLWidget::resizeGL(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    this->width = width;
    this->height = height;

    glViewport(0,0,width, height);

    glOrtho(-10, 10, -10, 10, -20, 20);
    //float ratio;
    // if (width > height) {
    //     ratio = (float)width/(float)height;
    //     glOrtho(-ratio, ratio, -1, 1, -1, 1);
    // } else {
    //     ratio = (float)height/(float)width;
    //     glOrtho(-1, 1, -ratio, ratio, -1, 1);
    // }

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() {
    // GLUquadricObj *q = gluNewQuadric();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   

    glLoadIdentity();

    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_LINES);
    for (int i = 0; i < md2Reader_.num_tris; ++i)
    {
        triangle_t triangle = md2Reader_.tris[i];
        short vertexOne = triangle.index_xyz[0];
        short vertexTwo = triangle.index_xyz[1];
        short vertexThree = triangle.index_xyz[2];
        // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexOne][0]);
        // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexOne][1]);
        // fprintf(stderr, "%f\n\n", md2Reader_.m_vertices[vertexOne][2]);

        // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexTwo][0]);
        // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexTwo][1]);
        // fprintf(stderr, "%f\n\n", md2Reader_.m_vertices[vertexTwo][2]);

        // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexThree][0]);
        // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexThree][1]);
        // fprintf(stderr, "%f\n\n", md2Reader_.m_vertices[vertexThree][2]);
        glVertex3f(md2Reader_.m_vertices[vertexOne][0],
            md2Reader_.m_vertices[vertexOne][1],
            md2Reader_.m_vertices[vertexOne][2]);
        glVertex3f(md2Reader_.m_vertices[vertexTwo][0],
            md2Reader_.m_vertices[vertexTwo][1],
            md2Reader_.m_vertices[vertexTwo][2]);

        glVertex3f(md2Reader_.m_vertices[vertexOne][0],
            md2Reader_.m_vertices[vertexOne][1],
            md2Reader_.m_vertices[vertexOne][2]);
        glVertex3f(md2Reader_.m_vertices[vertexThree][0],
            md2Reader_.m_vertices[vertexThree][1],
            md2Reader_.m_vertices[vertexThree][2]);

        glVertex3f(md2Reader_.m_vertices[vertexTwo][0],
            md2Reader_.m_vertices[vertexTwo][1],
            md2Reader_.m_vertices[vertexTwo][2]);
        glVertex3f(md2Reader_.m_vertices[vertexThree][0],
            md2Reader_.m_vertices[vertexThree][1],
            md2Reader_.m_vertices[vertexThree][2]);
    }
    glEnd();

    // glBegin(GL_TRIANGLES);
    // for (int i = 0; i < md2Reader_.num_tris; ++i)
    // {
    //     triangle_t triangle = md2Reader_.tris[i];
    //     short vertexOne = triangle.index_xyz[0];
    //     short vertexTwo = triangle.index_xyz[1];
    //     short vertexThree = triangle.index_xyz[2];
    //     // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexOne][0]);
    //     // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexOne][1]);
    //     // fprintf(stderr, "%f\n\n", md2Reader_.m_vertices[vertexOne][2]);

    //     // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexTwo][0]);
    //     // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexTwo][1]);
    //     // fprintf(stderr, "%f\n\n", md2Reader_.m_vertices[vertexTwo][2]);

    //     // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexThree][0]);
    //     // fprintf(stderr, "%f\n", md2Reader_.m_vertices[vertexThree][1]);
    //     // fprintf(stderr, "%f\n\n", md2Reader_.m_vertices[vertexThree][2]);
    //     glVertex3f(md2Reader_.m_vertices[vertexOne][0],
    //         md2Reader_.m_vertices[vertexOne][1],
    //         md2Reader_.m_vertices[vertexOne][2]);
    //     glVertex3f(md2Reader_.m_vertices[vertexTwo][0],
    //         md2Reader_.m_vertices[vertexTwo][1],
    //         md2Reader_.m_vertices[vertexTwo][2]);
    //     glVertex3f(md2Reader_.m_vertices[vertexThree][0],
    //         md2Reader_.m_vertices[vertexThree][1],
    //         md2Reader_.m_vertices[vertexThree][2]);
    // }
    // glEnd();

    //glColor3f(0.0, 0.0, 0.0);
    // //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // //glRotated(30, 0, 1, 0);
    // glTranslated(x,-y,0);
    // glScaled(scale,scale,scale);

    // gluSphere(q, 0.2, 12, 12);
    
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