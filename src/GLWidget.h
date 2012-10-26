
#ifndef MYGLWIDGET
#define MYGLWIDGET

#include <QGLWidget>
#include "MD2Wrapper.h"
#include "DrawingDefs.h"
#include "TextureManager.h"


class GLWidget : public QGLWidget 
{
   Q_OBJECT

public:
   GLWidget(QWidget *parent);
   ~GLWidget();

public slots:
   void openModelFile(QString& filePath);
   void openModelTextureFile(QString& filePath);
   void openWeaponFile(QString& filePath);
   void openWeaponTextureFile(QString& filePath);
   void changeDisplayMode(const QString& newMode);
   void showVertexNormals(int state);

signals:
   

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
   void drawVertexNormals();
   void drawModel();
   void drawWeapon();

private:
   MD2Wrapper modelReader_;
   MD2Wrapper weaponReader_;
   TextureManager* texManager_;

   int windowWidth_;
   int windowHeight_;

   GLuint modelTexture_;
   GLuint weaponTexture_;
   DrawingDefines::Mode displayMode_;
   bool weaponLoaded_;
   bool textureLoadedForMd2Model_;
   bool textureLoadedForWeapon_;

   bool drawVertexNormals_;
   bool drawFaceNormals_;

};

#endif

