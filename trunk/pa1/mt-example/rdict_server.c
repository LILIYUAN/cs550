/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rdict.h"

int initw(void),insertw(char *),deletew(char *),lookupw(char *);
bool_t
insertw_1_svc(char **w,int *ptr_retcode,struct svc_req *rqstp)
{
    *ptr_retcode=insertw(*(char **)w);
    return(TRUE);
}
bool_t
initw_1_svc(void *w,int *ptr_retcode,struct svc_req *rqstp)
{
    printf("Calling initw()\n");
    *ptr_retcode=initw();
    printf("Ccompleted initw()\n");
    return(TRUE);
}
bool_t
deletew_1_svc(char **w,int *ptr_retcode,struct svc_req *rqstp)
{
    *ptr_retcode=deletew(*(char **)w);
    return(TRUE);
}
bool_t
lookupw_1_svc(char **w,int *ptr_retcode,struct svc_req *rqstp)
{
    *ptr_retcode=lookupw(*(char **)w);
    return(TRUE);
}
