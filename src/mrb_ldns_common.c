/*
 *
 * common function 
 *
 *
 */
#include "mrb_ldns_common.h"


ldns_rr_list *mrb_getaddress_rr_list(mrb_state *mrb, ldns_resolver *resolver, char *name)
{
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records= NULL;
    ldns_rdf *domain = NULL;

    ldns_status s = ldns_resolver_new_frm_file(&resolver, NULL);
    if(s != LDNS_STATUS_OK)
    {
        return NULL;
    }

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
    ldns_rdf_deep_free(domain);
    if(!records)
    {
        return NULL;
    }
    return  records;

}

static char* reverse_addr(const char *src)
{
    char *res = NULL,
         *str = NULL;
    char **arr = NULL;
    int i=0,
        c=0,
        len=0;

    str = (char *)malloc( (strlen(src) + 1) * sizeof(char));
    strncpy(str, src, strlen(src) + 1);

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
    if( *arr == NULL)
    {
        return NULL;
    }
    c++;

    while((res = strtok(NULL,".")) != NULL)
    {
        arr[c] = res;
        c++;
    }
    res = (char *)malloc( (strlen(str) + 1) * sizeof(char) );
    *res = NULL;

    c--;
    for(; c >0; c--)
    {
    strcat(res, arr[c]);
    strcat(res,".");
    }
    strcat(res, arr[c]);

    return res;
}

ldns_rr_list *mrb_getname_rr_list(mrb_state *mrb, ldns_resolver *resolver,char *addr)
{
    char *rev = NULL;
    const char *arpa = "in-addr.arpa";
    ldns_rdf *domain = NULL ;
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records = NULL;

    ldns_status s = ldns_resolver_new_frm_file(&resolver, NULL);
    if(s != LDNS_STATUS_OK)
    {
        return NULL;
    }



    rev = (char *)malloc( sizeof(addr) + sizeof(arpa) + 2); 
    puts(reverse_addr(addr));
    sprintf(rev, "%s.%s",reverse_addr(addr), arpa);
    puts(rev);
    domain = ldns_dname_new_frm_str(rev); 


    if(!domain)
    {
        return NULL;
    }

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


ldns_rr_list* mrb_getrr_list(mrb_state *mrb, ldns_resolver *resolver, char *name, uint32_t rrtype,uint32_t rrclass, uint32_t opt, uint32_t rrsection)
{
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records= NULL;
    ldns_rdf *domain = NULL;

    ldns_status s = ldns_resolver_new_frm_file(&resolver, NULL);
    if(s != LDNS_STATUS_OK)
    {
        return NULL;
    }

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
    if(!records)
    {
        ldns_pkt_free(pkt);
        ldns_rdf_deep_free(domain);
        return NULL;
    }
    return  records;
}
