
/*   using the jabber xml test */
/*   James M. Rogers */

/*

*/

#include <libxode.h>
#include "jabberd.h"

int
xmlnode_print(xmlnode start){

    if (start) {
        printf("No data in file.\n");
        return 0;
    }

    /* print the current tag */

    /* move to the next lower tag */

    /* if the child tag doesn't exist, move to next sibling tag */

    /* if the next sibling tag doesn't exist, move to the next sibling tag of the parent */

    return 0;

}

int
main(){

xmlnode point;
xmlnode conf;

    conf=xmlnode_file("./test.xml");
    point=conf;

    printf("\n");
    printf("Tagname is %s.\n", xmlnode_get_name(point));
    printf("Data is \"%s\"\n", xmlnode_get_data(point));
    printf("Type is %d.\n", xmlnode_get_type(point));

    point = xmlnode_get_firstchild(point);

    printf("\n");
    printf("Tagname is %s.\n", xmlnode_get_name(point));
    printf("Data is \"%s\"\n", xmlnode_get_data(point));
    printf("Type is %d.\n", xmlnode_get_type(point));

    point = xmlnode_get_nextsibling(point);

    printf("\n");
    printf("Tagname is %s.\n", xmlnode_get_name(point));
    printf("Data is %s.\n", xmlnode_get_data(point));
    printf("Type is %d.\n", xmlnode_get_type(point));

    point = xmlnode_get_nextsibling(point);

    printf("\n");
    printf("Tagname is %s.\n", xmlnode_get_name(point));
    printf("Data is %s.\n", xmlnode_get_data(point));
    printf("Type is %d.\n", xmlnode_get_type(point));

    point = xmlnode_get_nextsibling(point);

    printf("\n");
    printf("Tagname is %s.\n", xmlnode_get_name(point));
    printf("Data is %s.\n", xmlnode_get_data(point));
    printf("Type is %d.\n", xmlnode_get_type(point));

    point = xmlnode_get_nextsibling(point);


/*
    point = xmlnode_get_nextsibling(point);
    point = xmlnode_get_firstchild(point);
    point = xmlnode_get_nextsibling(xmlnode_get_parent(point));
*/

   xmlnode_free(conf);

} /* END MAIN */
