#include <QGLWidget>

#ifndef MYGLWIDGET
#define MYGLWIDGET

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
    ~GLWidget();

protected:
   float x, y, scale;
   float width, height;

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif
