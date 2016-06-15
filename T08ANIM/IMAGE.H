/* FILE NAME: IMAGE.H
 * PROGRAMMER: AS5
 * DATE: 13.06.2016
 * PURPOSE: Image handle decrlaration.
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "def.h"

/* Image represetation type */
typedef struct
{
  HBITMAP hImage; /* Image bitmap handle */
  INT W, H;       /* Image size */
  DWORD *Bits;    /* Image pixel color data */
} AS5IMG;

/* Load image function.
 * ARGUMENTS:
 *   - image store data pointer:
 *       as5IMG *Im;
 *   - image file name (*.BMP):
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AS5_ImageLoad( AS5IMG *Im, CHAR *FileName );

/* Free image function.
 * ARGUMENTS:
 *   - image store data pointer:
 *       as5IMG *Im;
 * RETURNS: None.
 */
VOID AS5_ImageFree( AS5IMG *Im );

/* Get image pixel color function.
 * ARGUMENTS:
 *   - image store data pointer:
 *       as5IMG *Im;
 *   - pixel coordinates:
 *       INT X, Y;
 * RETURNS:
 *   (DWORD) pixel color.
 */
DWORD AS5_ImageGetP( AS5IMG *Im, INT X, INT Y );


#endif /* __IMAGE_H_ */

/* END OF 'IMAGE.H' FILE */