/***************************************************************************
                          main.c  -  description
                             -------------------
    begin                : Mon Jan 31 05:32:15 PST 2000
    copyright            : (C) 2000 by James M. Rogers
    email                : jrogers@visnetinc.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "hl7.h"

int
main ()
{
  struct hl7_part_t *msgs;
  char s[16000];
  FILE *stream;

    if((stream = fopen ("msg.hl7", "r")) != (FILE *)0) {
       while((fgets(s, 16000, stream)) != (char *) 0 ) {

         msgs = str2hl7 (s);
         hl7_print (msgs);
         hl7free(msgs);
/*
         printf("\n\n>%s<\n\n", s);
*/
       }
    } else {
         exit(1);
    }

  exit (0);
}