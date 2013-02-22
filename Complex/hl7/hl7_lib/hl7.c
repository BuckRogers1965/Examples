/***************************************************************************
                          hl7.c  -  description
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

#include "hl7.h"


/*
   Allocate memory for a string, copy the string into the memory and
   then return the pointer to the memory.
 */

char *
strset (char *string)
{

  char *pointer_to_string;

  if (pointer_to_string = (char *) malloc (strlen (string)+1))
    {
      strcpy (pointer_to_string, string);
      return (pointer_to_string);
    }
  else
    {
      /* die */
      exit (1);
    }
}

struct hl7_part_t *
split (struct hl7_part_t *hl7_part, char *separators)
{

  struct hl7_part_t *head,	/* begining of the data list */
   *current;			/* tail of the data list */

  int begin = 0,		/* start of the current string */
    scan = 0;			/* current position in string */

  /* if the list of separators is empty, we have reached a leaf, return null */
  if (separators[0] == '\000'){
    return (struct hl7_part_t *) 0;
}

  /* setup structure for current level of operations */
  if (!(current = head = (struct hl7_part_t *) malloc (sizeof (struct hl7_part_t))))
      exit (1);

  /* initialize the structure to some sane values */
  current->data = (char *) 0;
  current->next = (struct hl7_part_t *) 0;
  current->lower = (struct hl7_part_t *) 0;


  /* start looking thru the string for current seperator */
  for (; hl7_part->data[scan]; scan++)
    {
      /* when we find the current seperator */
      if (hl7_part->data[scan] == separators[0])
	{
	  /* replace the seperator with a NULL */
	  hl7_part->data[scan] = '\000';

	  /* set a copy of the string that we found to current data element */
	  current->data = strset (&hl7_part->data[begin]);

	  /* split the string into substrings */
	  /* this is a little tricky */
	  /* I send the seperator string starting with its _second_ element */
	  current->lower = split (current, &separators[1]);

	  /* setup for the next string that we find */
	  if (!(current->next = (struct hl7_part_t *) malloc (sizeof (struct hl7_part_t))))
	      exit (1);

	  /* move the current pointer to the node that we just created */
	  current = current->next;

	  /* initialize the data to some sane values */
	  current->data = (char *) 0;
	  current->next = (struct hl7_part_t *) 0;
	  current->lower = (struct hl7_part_t *) 0;

	  /* set the begining of the string to follow the found string */
	  begin = scan + 1;
	}
    }

  /* We reached the end of the string without finding (another) seperator.
     But there is still a string that we need to take care of. */

  /* put a copy of the string in the current data element */
  current->data = strset (&hl7_part->data[begin]);

  /* split the data element into substrings */
  /* this is a little tricky */
  /* I send the seperator string starting with its _second_ element */
  current->lower = split (current, &separators[1]);

  /* get rid of the string from the parent, we stored it safely at this level */
  free (hl7_part->data);

  /* set the parent data element to the null pointer so that it won't be
     pointing to the place where the string used to be. */
  hl7_part->data = (char *) 0;

  /* return the list of substrings found to the parent. */
  return head;
}

struct hl7_part_t *
str2hl7 (char *message_string)
{

  struct hl7_part_t *message;	/* Message structure that we are working on */

  char delimiters[5],		/* list of delimiters from the message */
    separators[5],		/* list of separators in proper order */
    temp[5];			/* used to set the correct delimiters
				   in the final message structure */

  /* probably should check that the message begins with MSH
     and is longer than a minimum length... */

  /* if we don't have enough memory, quit.  This is kind of abrupt and
     I can probably shutdown a little nicer than this. */

  if (!(message = (struct hl7_part_t *) malloc (sizeof (struct hl7_part_t))))
      exit (1);

  /* put some sane values into the clean new structure */
  message->data=(char *)0;
  message->lower=(struct hl7_part_t *)0;
  message->next=(struct hl7_part_t *)0;

  /* put a copy of hl7_string into the proper place in the message structure */
  message->data = strset (message_string);

  /* copy the hl7 delimiters to a string to hold them for processing */
  strncpy (delimiters, &message->data[3], 5);

  /* close the end of the string with a terminator so that we don't dump core */
  delimiters[5] = '\000';

  /* reorder the delimiters into the proper order for seperation */
  separators[0] = '\r';
  separators[1] = delimiters[0];
  separators[2] = delimiters[4];
  separators[3] = delimiters[1];
  separators[4] = delimiters[2];
  separators[5] = '\000';

  /* remove the delimiters from the message so that we don't get confused */
  message->data[4] = 'X';
  message->data[5] = '|';
  message->data[6] = 'Z';
  message->data[7] = ' ';

  /* recursively call split to split the message on each seperator */
  message->lower = split (message, separators);

  /* put the delimiters into the proper place in the message structure */
  free (message->lower->lower->next->lower->lower->lower->data);
  strncpy (temp, &delimiters[0], 1);
  temp[1] = '\000';
  message->lower->lower->next->lower->lower->lower->data = strset (temp);

  free (message->lower->lower->next->next->lower->lower->lower->data);
  strncpy (temp, &delimiters[1], 4);
  temp[4] = '\000';
  message->lower->lower->next->next->lower->lower->lower->data = strset (temp);

  /* we are done, return the results */
  return message;
}

void
hl7_print (struct hl7_part_t *msgs)
{
  /* recursively traverse the tree, printing out data where ever we find it */

  if (msgs->data != '\000')
    printf (">%s<\n", msgs->data);

  /* look in each lower branch first */
  if (msgs->lower)
    {
      printf ("l ");
      hl7_print (msgs->lower);
    }

  /* then look in each next branch */
  if (msgs->next)
    {
      printf ("n ");
      hl7_print (msgs->next);
    }

}

struct hl7_part_t 
*hl7free (struct hl7_part_t *msgs)
{
  /* recursively travers the tree, printing out data where ever we find it */

  if (msgs->data != '\000'){
    free(msgs->data);
    msgs->data=(char *) 0;
  }

  /* look in each lower branch first */
  if (msgs->lower)
    {
      msgs->lower=hl7free (msgs->lower);
    }

  /* then look in each next branch */
  if (msgs->next)
    {
      msgs->next=hl7free (msgs->next);
    }

  free(msgs);

  return (struct hl7_part_t *) 0;

}


