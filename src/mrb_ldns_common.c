/*
 *
 * common function 
 *
 *
 */
#include "mrb_ldns.h"
#include "mrb_ldns_common.h"


ldns_rr_list *mrb_getaddress_rr_list(mrb_state *mrb, ldns_resolver *resolver, char *name)
{
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records= NULL;
    ldns_rdf *domain = NULL;

    domain = ldns_dname_new_frm_str(name);
    if(!domain)
    {
        return NULL;
    }

    pkt = ldns_resolver_query(resolver,
                            domain,
                            LDNS_RR_TYPE_A,
                            LDNS_RR_CLASS_IN,
                            LDNS_RD);
    ldns_rdf_deep_free(domain);

    if(!pkt)
    {
        return NULL;
    }

    records =ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_A, LDNS_SECTION_ANSWER);
    ldns_pkt_free(pkt);
    if(!records)
    {
        return NULL;
    }
    return  records;

}

static char* reverse_addr(char *src)
{

    char *res = NULL,
         *str = (char *)malloc( sizeof(src) / sizeof(char) );
    char **arr = NULL;
    int i=0,
        c=0,
        len=0;
    strcpy(str, src);

    for(i=0; i < strlen(str); i++)
    {
        if(str[i] == '.')
        {
            len++;
        }
    }
    len++;

    arr = (char **)malloc((len + 1) * sizeof(char*));
    arr[len] = NULL;

    c =0;
    arr[c] = strtok(str,".");
    if( arr[c] == NULL)
    {
        free(arr);
        free(str);
        return NULL;
    }
    c++;

    while((res = strtok(NULL,".")) != NULL)
    {
        arr[c] = res;
        c++;
    }
    res = (char *)malloc( (strlen(str) + 1) * sizeof(char) );
    res[0] = NULL;

    c--;
    for(; c >0; c--)
    {
    strcat(res, arr[c]);
    strcat(res,".");
    }
    strcat(res, arr[c]);

    free(str);
    free(arr);

    return res;
}

ldns_rr_list *mrb_getname_rr_list(mrb_state *mrb, ldns_resolver *resolver,char *addr)
{
    char *rev = NULL,
         *query = NULL;
    const char *arpa = "in-addr.arpa";
    ldns_rdf *domain = NULL ;
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records = NULL;


    rev = reverse_addr(addr);
    if(!rev)
    {
        return NULL;
    }

    query = (char *)malloc( sizeof(query) / sizeof(char) + sizeof(arpa) / sizeof(char) + 4 * sizeof(char)); 
    strcat(query, rev);
    strcat(query,".");
    strcat(query,arpa);
    printf("query:%s\n",query);
    //free(rev);

    domain = ldns_dname_new_frm_str(query); 
    if(!domain)
    {
        MRB_LDNS_DEBUG("domain fail");
        return NULL;
    }
    //free(query);

    MRB_LDNS_DEBUG("brefore/query");
    pkt = ldns_resolver_query(resolver,
                             domain,
                             LDNS_RR_TYPE_PTR,
                             LDNS_RR_CLASS_IN,
                             LDNS_RD);
    ldns_rdf_deep_free(domain);
    if(!pkt)
    {
        return NULL;
    }

    records = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_PTR, LDNS_RR_CLASS_IN);
    ldns_pkt_free(pkt);
    if(!records)
    {
        return NULL;
    }

    return records;
}





/*
 *
 * helper function
 *
 */

ldns_rr_list* mrb_getrr_list(mrb_state *mrb, ldns_resolver *resolver, char *name, uint32_t rrtype,uint32_t rrclass, uint32_t opt, uint32_t rrsection)
{
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records= NULL;
    ldns_rdf *domain = NULL;

    domain = ldns_dname_new_frm_str(name);
    if(!domain)
    {
        return NULL;
    }

    pkt = ldns_resolver_query(resolver,
                            domain,
                            rrtype,
                            rrclass,
                            opt);

    ldns_rdf_deep_free(domain);
    if(!pkt)
    {
        return NULL;
    }

    records =ldns_pkt_rr_list_by_type(pkt, rrtype, rrsection);
    ldns_pkt_free(pkt);
    if(!records)
    {
        return NULL;
    }
    return  records;

}
