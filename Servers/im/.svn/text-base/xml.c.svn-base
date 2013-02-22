#include "jab.h"
 
char *
concat(char *string1, char *string2){
 
  int length1, length2;    /* holds length of strings */
 
  /* get the length of the second string */
  length2 = strlen(string2);
 
  /* if the second string is empty, we are done */
  if (length2==0)
       return string1;
 
  /* get the length of the first string */
  length1 = strlen(string1);
 
  /* expand string to hold the extra characters */
  if ((string1 = (char *) realloc(string1, length1 + length2 +1))){
 
    /* copy second string onto end of first string */
    strncpy (&string1[length1], string2, length2);
    string1[length1 + length2] = '\000';
 
    /* return the new string */
    return string1;
 
  } else {
    /* no memory, die */
    exit(1);
  }
 
}
                             

/*
 * Allocate memory for a string, copy the string into the memory and then return the pointer to the memory.
 */
 
char *
strnset (char *string, int length) {
 
  char *pointer_to_string;
 
//    printf("strnset >%d< >%s< \n", length, string);
  if (pointer_to_string = (char *) malloc (length+1))
    {
      strncpy (pointer_to_string, string, length);
      pointer_to_string[length]='\0';
      return (pointer_to_string);
    }
  else
    {
        /***  Handle this better ***/
        printf("***  no more memory left ***\n");
        return strnset("", 0);
    }
}  /* end strset */ 

/*
 * Get the data inside an xml tag.
 */

char *xmlgetdat(char *string) {

    char *begin, *end;
    int i;

    printf("xmlgetdat >%s< \n", string);
    /* Given an XML string return the values inside the tag */
    
    /* Looks like <TAG name="value" > abcd </TAG> */ 
    /* or         <TAG name="value" /> */ 
    /* or         <TAG /> */ 

    /* get the first > */
    begin = strstr(string, ">");

    if (begin==NULL) {
        /* If we can't find beginning, error out */
        /* return the empty string */
    } else if (begin-1 == "/") {
        /* if the previous character is a slash */
        /* return the empty string */
    } else {

        end = strstr(begin, "<");

        if (end != NULL) {
            return strnset(begin+1, end-begin-1);
        }
    }
    return strnset("",1);
}

/*
 * Get the value asociated with a name value pair attached
 * to the current tag.
 */

char *xmlgetval(char *string, char *name) {

    char *begin, *end, *temp;

    printf("xmlgetval >%s< >%s<\n", name, string);
    /* Given an XML string get the value associated with the name given in the location */
    
    /* Looks like <TAG name="value" > abcd </TAG> */ 
    /* or         <TAG name="value" /> */ 
    /* or         <TAG /> */ 

    /* get the first < */
    begin = strstr(string, "<");

    if (begin!=NULL) {

        /* get the first > */
        end = strstr(begin, ">");

        if (end==NULL) {
            /* If we can't find the end, */
            /* return an empty string */
        } else {
            /* we found the first tag and are now going to look for the value */
            /* pull value out temporatily so we don't accedently pull value out of 
               the wrong tag */
            temp=strnset(begin, end-begin);
            begin=strstr(temp, name);

            if (begin != NULL ) {
                begin=begin+strlen(name)+2;
                end=strstr(begin, "\'");
                if (end != NULL) {
                    begin = strnset(begin, end-begin);
                    free(temp);
                    return begin;
                }
            }
            free(temp);
        }
    }
    return strnset("",1);
}

/*
 * return the named tag.
 */

char *xmlgettag(char *string, char *location) {

    char *begin, *end, *loc_part, *begin_tag, *end_tag;
    int i;

    printf("xmlgettag >%s< >%s<\n", location, string);
    /* Given an XML string, return the tag given in the location */

    /* Looks like <TAG name="value" > abcd </TAG> */
    /* or         <TAG name="value" /> */ 
    /* Or         <TAG /> */
    
    /* setup the tags */
    begin_tag=strnset("<", 1);
    begin_tag=concat(begin_tag,location);
    end_tag=strnset("</",2);
    end_tag=concat(end_tag,location);
    end_tag=concat(end_tag,">");

    end=NULL;

    /* get the beginning of the tag */
    begin = strstr(string, begin_tag);
    free(begin_tag);

    if (begin != NULL) {

        /* get the end of the tag */
        end = strstr(string, end_tag);


        if (end == NULL) {
            /* If we can't find end look for /> ending... */
            end = strstr(begin, "/>")+2;
        } else {
            end=end+strlen(end_tag);
        }
    }

    free(end_tag);
    if (end != NULL) {
        /* we found the tag, return it. */
        return strnset(begin, end-begin);
    }

    return strnset("", 0);
}

/*
 *
 */

char *xmlgetloc(char *location){

    char *next;

//    printf("xmlgetloc >%s<\n", location);

    /* Given an location string in the form of */
    /* "" */
    /* or tag */
    /* or tag.tag */
    /* or tag.tag.tag.. */
    /* or tag.tag.tag..name */
    /* return the first value */

    /* get the next period */
    next = strstr(location+1, ".");


    if (next==NULL){
        if (location[0]=='.'){
            if (location[1]=='\0'){
                return strnset(".", 1);
            } else {
                return strnset(location, strlen(location) );
            }
        } else {
            return strnset(location, strlen(location));
        }
    }

    if (next[0]=='.'&&next[1]=='\0'){
        return strnset(next+1, strlen(next) );
    }

    if (next!=NULL) {
        /* we found the tag, return it. */
        return strnset(location, next-location);
    }

}

/*
 *
 */

char *xmlget(char *string, char *location) {

    char *next_loc, *next_loc_a, *value, *next_tag, *tag;

    tag = strnset(string, strlen(string));

    printf("xmlget >%s<\n", tag);

    while (1) {

        if (tag[0]=='\0')
            return strnset("", 0);
        next_loc = xmlgetloc(location);
        location = location+strlen(next_loc);
        if (location[0]=='.')
                location=location+1;


        if (next_loc[0]=='.'){
            next_loc_a=next_loc;
            next_loc=strnset(next_loc_a+1, strlen(next_loc_a)-1 );
            free(next_loc_a);
            if (next_loc[0] == '\0'){
                value = xmlgetdat(tag);
            } else {
                value = xmlgetval(tag, next_loc);
            }
            free (next_loc);
            free(tag);
            return value;
        } else if (!strcmp(next_loc, "")){
            free (next_loc);
            return tag;
        } else {
            next_tag = xmlgettag(tag, next_loc);
            free (next_loc); 
            free(tag);
            tag=next_tag;
            if (location == "") {
                return tag;
            }
        }
    }
}


/*
 *
 */

char *xmlgetfirsttagname(char *string) {

    char *tag, *tag1, *tag2, *tag3, *begin, *end, *end1, *end2, *end3, *istag;
    ssize_t l, x, y, z;

    printf("xmlgetfirsttagname >%s<\n", string);

    /* get the first < */
    begin = strstr(string, "<");

    if (begin!=NULL) {

        l = strlen(begin);

        /* find each value that can follow a tag name */
        end1 = strstr(begin, " ");
        if (end1==NULL){
            x = l;
        } else {
            x = l - strlen(end1);
        }

        end2 = strstr(begin, "/");
        if (end2==NULL){
            y = l;
        } else {
            y = l - strlen(end2);
        }

        end3 = strstr(begin, ">");
        if (end3==NULL){
            z = l;
        } else {
            z = l - strlen(end3);
        }

        /* select which location is shortest */

        if (x<y){
            if (x<z)
                if (x==l)
                    end=NULL;
                else
                    end=end1;
            else
                if (z==l)
                    end=NULL;
                else
                    end=end3;
        } else {
            if (y<z)
                if (y==l)
                    end=NULL;
                else
                    end=end2;
            else
                if (z==l)
                    end=NULL;
                else
                    end=end3;
        }

        /* get the shortest string */
        if (end!=NULL) {
            return(strnset(begin+1,end-begin-1));
        }
    }

    return (strnset("",1));
}

/*
 *
 */

int isvalidxml(char *string) {

    char *tag, *istag, *begin, *end;

    printf("isvalidxml >%s<\n", string);

    tag=xmlgetfirsttagname(string);

    /* get the first tag */
    istag = xmlget(string, tag);
//    printf("****** isvalidxml istag ]%s[ ]%s[\n", tag, istag);

    /* allow the beginning and ending streams */
    if (!strcmp(tag,"stream:stream")||!strcmp(tag,"/stream:stream")) {
        begin=strstr(string+strlen(tag)+2, ">");
        if (begin!=NULL){
//            printf("isvalidxml B TRUE >%s<\n", istag);
            free (tag);
            free (istag);
            return TRUE;
        }
    }

    free(tag);

    if (!strcmp(string, "")) {
//        printf("isvalidxml A TRUE \n");
        free (istag);
        return TRUE;
    }

    /* if get an empty tag back, continue */
    if (strcmp(istag,"")) {
//        printf("isvalidxml B TRUE >%s<\n", istag);
        free (istag);
        return TRUE;
    }

//    printf("isvalidxml C FALSE >%s<\n", istag);
    free (istag);
    return FALSE;
}
