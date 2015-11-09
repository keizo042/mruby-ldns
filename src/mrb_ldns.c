#include "mruby.h"
#include "mruby/object.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/string.h"

#include "ldns/ldns.h"

#include "mrb_ldns_resource.h"
#include "mrb_ldns_class.h"


typedef struct {
    ldns_resolver *resolver;
}mrb_ldns_data;

static void mrb_ldns_free(mrb_state *mrb, void *p)
{
    ldns_resolver_deep_free((ldns_resolver*)p);
}

static const mrb_data_type mrb_ldns_data_type = {
    "mrb_ldns_data", mrb_ldns_free,
};


mrb_value mrb_ldns_init(mrb_state *mrb, mrb_value self)
{
    //mrb_value args;
    mrb_ldns_data *data= (mrb_ldns_data*)DATA_PTR(self);
    ldns_resolver *resolver ; 
    ldns_status s;
    if(data)
    {
        mrb_free(mrb, data);
    }
    mrb_data_init(self, NULL, &mrb_ldns_data_type);
    data = (mrb_ldns_data *)mrb_malloc(mrb, sizeof(mrb_ldns_data) );


    s = ldns_resolver_new_frm_file(&resolver, NULL);
    if(s != LDNS_STATUS_OK)
    {
        mrb_raise(mrb, E_RUNTIME_ERROR, "ldns cause some error");
    }

    data->resolver = resolver;
    mrb_data_init(self, data, &mrb_ldns_data_type);


    //mrb_get_agrs("|A",&args);
    return self;
}

/*
 *
 * Resolv.each_address("name") do |address|
 * 
 * somethingdo... 
 * end
 * => nil
 */

static mrb_value mrb_resolv_each_address(mrb_state *mrb, mrb_value self)
{
    char *name = NULL;
    mrb_value block = {};
    mrb_ldns_data *data = (mrb_ldns_data*)DATA_PTR(self);
    ldns_pkt *pkt;
    ldns_rdf *domain;
    mrb_get_args(mrb, "z*",name,&block);

    return self;
}

/*
 *
 * Resolv.getaddress("name")
 * => "address"
 */

static mrb_value mrb_resolv_getaddress(mrb_state *mrb, mrb_value self)
{
    char *name;
         
    ldns_pkt *pkt = NULL;
    ldns_rdf *domain = NULL, *addr = NULL;
    ldns_rr_list *records = NULL;
    ldns_rr *record = NULL;

    ldns_resolver *resolver = NULL;
    ldns_status s = ldns_resolver_new_frm_file(&resolver, NULL);
    if(s != LDNS_STATUS_OK)
    {
        return mrb_nil_value();
    }
    
    mrb_get_args(mrb,"z",&name);

    domain = ldns_dname_new_frm_str(name);
    if(!domain)
    {
        return mrb_nil_value();
    }

    pkt = ldns_resolver_query(resolver,
                            domain,
                            LDNS_RR_TYPE_A,
                            LDNS_RR_CLASS_IN,
                            LDNS_RD);
    ldns_rdf_deep_free(domain);
    if(!pkt)
    {
        return mrb_nil_value();
    }

    records = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_A, LDNS_SECTION_ANSWER);

    if(!records)
    {
        ldns_pkt_free(pkt);
        ldns_rdf_deep_free(domain);
        return mrb_nil_value();
    }

    record = ldns_rr_list_rr(records, 0);
    addr = ldns_rr_rdf(record, 0);

    ldns_pkt_free(pkt);
    return mrb_str_new_cstr(mrb, ldns_rdf2str(addr));

}

/*
 *
 * Resolv.getaddresses("name")
 * => ["address"]
 */

static mrb_value mrb_resolv_getaddresses(mrb_state *mrb, mrb_value self)
{
    char *name = NULL;
    mrb_ldns_data *data = (mrb_ldns_data *)DATA_PTR(self);
    mrb_get_args(mrb,"z",name);
    return mrb_str_new_cstr(mrb,"");
}

/*
 * Resolv.getname("address")
 * => "name"
 */

static mrb_value mrb_resolv_getname(mrb_state *mrb, mrb_value self)
{
    char addr[1024];
    char *rev = NULL;
    const char *arpa = "in-addr.arpa";
    ldns_rdf *domain = NULL ;
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records = NULL;
    ldns_rr *record = NULL;

    ldns_resolver *resolver;
    ldns_status s = ldns_resolver_new_frm_file(&resolver, NULL);
    if(s != LDNS_STATUS_OK)
    {
        return mrb_nil_value();
    }


    mrb_get_args(mrb, "z", &addr);

    rev = (char *)mrb_malloc(mrb, sizeof(addr) + sizeof(arpa) + 1);
    strcpy(rev,addr);
    strcat(rev,arpa);
    domain = ldns_dname_new_frm_str(rev);
    mrb_free(mrb, rev);

    puts("1");

    if(!domain)
    {
        return mrb_nil_value();
    }
    puts("1");

    pkt = ldns_resolver_query(resolver,
                             domain,
                             LDNS_RR_TYPE_PTR,
                             LDNS_RR_CLASS_IN,
                             LDNS_RD);
    ldns_rdf_deep_free(domain);
    if(!pkt)
    {
        return mrb_nil_value();
    }

    records = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_PTR, LDNS_RR_CLASS_IN);
    if(!records)
    {
        ldns_pkt_free(pkt);
        return mrb_nil_value();
    }

    if(ldns_rr_list_rr_count(records) < 0)
    {
        ldns_pkt_free(pkt);
        ldns_rr_list_deep_free(records);
        return mrb_nil_value();
    }

    record = ldns_rr_list_rr(records, 0);

    puts("3");

    rev = (char *)malloc( sizeof( ldns_rr2str(record) ) );
    strcpy(rev, ldns_rr2str(record));

    ldns_pkt_free(pkt);
    ldns_rr_list_deep_free(records);
    return mrb_str_new_cstr(mrb, rev);
}

/*
 * Resolv.getnames "address"
 * => ["name"]
 */

static mrb_value mrb_resolv_getnames(mrb_state *mrb, mrb_value self)
{
    char *name = NULL;
    mrb_ldns_data *data = DATA_PTR(self);
    mrb_get_args(mrb, "z",name);

    return self;
}

void mrb_mruby_ldns_gem_init(mrb_state *mrb)
{
    struct RClass *resolv;

    resolv = mrb_define_class(mrb, "Resolv", mrb->object_class);
    mrb_resolv_resource_define(mrb);


    /*
     * Resolc Class 
     */

    //mrb_deine_method(mrb, reoslv, "initalize", mrb_resolv_init, MRB_ARG_OPT(2));
    mrb_define_method(mrb, resolv, "initalize", mrb_ldns_init , MRB_ARGS_NONE());


    mrb_define_class_method(mrb, resolv, "each_address",    mrb_resolv_getaddress,      MRB_ARGS_REQ(2));
    mrb_define_class_method(mrb, resolv, "getaddress",      mrb_resolv_getaddress,      MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, resolv, "getaddresses",    mrb_resolv_getaddresses,    MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, resolv, "getname",         mrb_resolv_getname,         MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, resolv, "getnames",        mrb_resolv_getnames,        MRB_ARGS_REQ(1));
    
    mrb_define_method(mrb, resolv, "each_address", mrb_resolv_each_address, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, resolv, "getaddress", mrb_resolv_getaddress,MRB_ARGS_REQ(1));
    mrb_define_method(mrb, resolv, "getaddresses", mrb_resolv_getaddresses, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, resolv, "getname", mrb_resolv_getname, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, resolv, "getnames", mrb_resolv_getnames, MRB_ARGS_REQ(1));

}


void mrb_mruby_ldns_gem_final(mrb_state *mrb)
{
}
