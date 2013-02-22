#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
 
#define BUFFSIZE 4096

char *httphost, *httpquery;
int httpport;

/*********************************************************************
*********************************************************************/
 
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
                             

/*********************************************************************
Allocate memory for a string, copy the string into the memory and
   then return the pointer to the memory.
*********************************************************************/
 
char *
strnset (char *string, int length) {
 
  char *pointer_to_string;
 
  if (pointer_to_string = (char *) malloc (length+1))
    {
      strncpy (pointer_to_string, string, length);
      pointer_to_string[length]='\0';
      return (pointer_to_string);
    }
  else
    {
      exit (1);
    }
}  /* end strset */ 

/*
 *
 */

char *xmlgetdat(char *string) {

    char *begin, *end;
    int i;

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

        begin = begin +1;

        /* find last < */
          for (i=strlen(begin)-1; begin[i] == '0' ; i--){
              printf("i >%d< begin[i] >%c<\n", i, begin[i]);
          }
//        for( end = begin + strlen(begin) ; end == "<" || end == begin ;end-- );
//        end=strstr(begin,"<");

          end = begin + i ;
        if (end == begin) {
            /* if the previous character is a slash */
            /* return the empty string */
        } else {
            if (end>0){
            /*  */
            return strnset(begin, end-begin);
            }
        }
    }
    return strnset("",1);
}

/*
 *
 */

char *xmlgetval(char *string, char *name) {

    char *begin, *end, *temp;

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
            begin=strstr(temp, name)+strlen(name)+2;

            if (begin != NULL ) {
                end=strstr(begin, "\"");
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
 *
 */

char *xmlgettag(char *string, char *location) {

    char *begin, *end, *loc_part, *begin_tag, *end_tag;
    int i;

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

    /* get the beginning of the tag */
    begin = strstr(string, begin_tag);
    free(begin_tag);

    if (begin != NULL) {

        /* get the end of the tag */
        end = strstr(string, end_tag);


        if (end == NULL) {
            /* If we can't find end look for /> ending... */
            end = strstr(begin, "/>");
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

    while (1) {

        next_loc = xmlgetloc(location);
        location = location+strlen(next_loc)+1;


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
 *  Used to load configuration file and to register authentication, registration and server modules
 */

int main() {

    FILE *stream;
    char configuration[BUFFSIZE]; 

    char *data, *tag, *httpport_tmp;
    int i;

    /* read configuration file */
    if((stream=fopen((char *)getenv("MOD_AUTH_XOH_CONF"), "r")) == NULL){
        printf("file not found\n");
        exit (1);
    }

    if(fgets(configuration, BUFFSIZE, stream) == (char *)NULL) {
        printf("cannot read from file\n");
        exit (1);
    }   

    printf("file: %s \n", configuration);
    fclose (stream);

    for(i=1;i;i--){

    httphost = xmlget(configuration, "xml.xml_over_http..host");
    httpquery = xmlget(configuration, "xml.xml_over_http..query");
    httpport_tmp = xmlget(configuration, "xml.xml_over_http..port");
    httpport = atoi(httpport_tmp);
    data = xmlget(configuration, "xml.xml_over_http.."); 
    tag = xmlget(configuration, "xml.xml_over_http"); 

    
    printf("host >%s<\n query >%s<\n port >%d<\n data >%s<\n tag >%s<\n\n", httphost, httpquery, httpport, data, tag);

    free (httphost);
    free (httpquery);
    free (httpport_tmp);
    free (data); 
    free (tag); 

    }

}

