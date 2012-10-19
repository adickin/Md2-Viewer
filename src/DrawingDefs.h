/*
*********************************************************************
*  Adam Dickin
*  10016859
*  CPSC 453
*  Assignment 2
*********************************************************************
*/

#ifndef DRAWINGDEFS_H
#define DRAWINGDEFS_H

#include <QString>

namespace DrawingDefines
{
   enum Mode
   {
      WIREFRAME,
      FLAT_SHADING,
      SMOOTH_SHADING,
      TEXTURE
   };
   static const QString WIREFRAME_STRING("Wire Frame");
   static const QString FLAT_SHADING_STRING("Flat Shading");
   static const QString SMOOTH_SHADING_STRING("Smooth Shading with Lighting");
   static const QString TEXTURE_STRING("Textured");
}

#endif