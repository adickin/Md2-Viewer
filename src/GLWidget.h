
#ifndef MYGLWIDGET
#define MYGLWIDGET

#include <QGLWidget>
#include "MD2Wrapper.h"


class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
    ~GLWidget();

public slots:
    void openMd2File(QString& filePath);

signals:
    void fileLoadSuccess(bool sucess);

protected:
   float x, y, scale;

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void drawWireFrame();

    void updateOrthoMatrix();
private:
    MD2Wrapper md2Reader_;

    int windowWidth_;
    int windowHeight_;

};

#endif

