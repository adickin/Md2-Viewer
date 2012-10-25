
#ifndef MYGLWIDGET
#define MYGLWIDGET

#include <QGLWidget>
#include "MD2Wrapper.h"
#include "BMP.h"
#include "DrawingDefs.h"
#include "TextureManager.h"


class GLWidget : public QGLWidget 
{
   Q_OBJECT

public:
   GLWidget(QWidget *parent);
   ~GLWidget();

public slots:
   void openMd2File(QString& filePath);
   void openTextureFileBMP(QString& filePath);
   void changeDisplayMode(const QString& newMode);

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
   void drawModel();

private:
   MD2Wrapper md2Reader_;
   BMPImg bmpImageReader_;
   TextureManager* texManager_;

   int windowWidth_;
   int windowHeight_;

   GLuint texture_;
   DrawingDefines::Mode displayMode_;
   bool textureLoadedForMd2Model_;

};

#endif

