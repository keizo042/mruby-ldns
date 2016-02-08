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
    if(!records)
    {
        ldns_pkt_free(pkt);
        ldns_rdf_deep_free(domain);
        return NULL;
    }
    return  records;

}

static void name_reverse(char *str)
{
    char *tmp = (char *)malloc(sizeof(str) / sizeof(char));
    int i, j;
    int count,
        before;
    before =0;
    count = 0;
    for(i =0; i < strlen(tmp); i++)
    {
        if( tmp[i] == '.' ){

            for(j = 0; j < count;j++)
            {
                str[before + j] = tmp[j];

            }
            tmp[j+1] = '.';
            before = before + count + 1;
            count = 0;

        }else
        {
            count++;
        }
    }
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


    name_reverse(addr);

    rev = (char *)mrb_malloc(mrb, sizeof(addr) + sizeof(arpa) + 2); 
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
    if(!records)
    {
        ldns_pkt_free(pkt);
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
