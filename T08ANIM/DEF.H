/*Shvetz Andrei 10-5 07.08.2015*/
/* FILE NAME: def.H
 * PROGRAMMER: AS5
 * PURPOSE: malloc & MATR lib  */

#pragma warning(disable: 4244)
#pragma warning(disable: 4028)
#pragma warning(disable: 4305)
#ifndef __DEF_H_
#define __DEF_H_


/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((VOID)0)

#endif /* _DEBUG */

#include <stdlib.h>
#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "VEC.H" 




#endif /* __DEF_H_ */