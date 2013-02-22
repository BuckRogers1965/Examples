/***************************************************************************
                          hl7.h  -  description
                             -------------------
    begin                : Mon Jan 31 2000
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

#include <stdio.h>
#include <stdlib.h>


/*

the data structure is as follows

Message
  NEXT
  LOWER -> Segment
             NEXT
             LOWER -> Field
                        NEXT
                        LOWER -> Repeating Field
                                   NEXT
                                   LOWER -> Component
                                              NEXT
                                              LOWER -> Subcomponent
                                                         NEXT
                                                         DATA -> string of data
NEXT is the next element of the same type
LOWER is the first element of a list of subordinate data structures
Both NEXT and LOWER point to a structure of type hl7_part_t

*/

struct hl7_part_t {
    char *data;
    struct hl7_part_t *next;
    struct hl7_part_t *lower;
} ;

char *strset (char *);
struct hl7_part_t *split (struct hl7_part_t *, char *);
struct hl7_part_t *str2hl7 (char *);
void hl7_print (struct hl7_part_t *);
struct hl7_part_t *hl7free (struct hl7_part_t *);




