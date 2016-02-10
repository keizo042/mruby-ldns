/*
 *
 * class Resolv 
 *
 *
 */

#include "mrb_ldns.h"
#include "mrb_ldns_resource.h"
#include "mrb_ldns_class.h"
#include "mrb_ldns_common.h"



typedef struct mrb_ldns_data{
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
 * Resolv.getaddress("name")
 * => "address"
 */

static mrb_value mrb_resolv_getaddress(mrb_state *mrb, mrb_value self)
{
    char *name;
         
    ldns_pkt *pkt = NULL;
    ldns_rdf  *addr = NULL;
    ldns_rr_list *records = NULL;

    ldns_resolver *resolver = NULL;
    
    mrb_get_args(mrb,"z",&name);

    records = mrb_getaddress_rr_list(mrb,resolver,name);
    if(!records)
    {
        return mrb_nil_value();
    }


    addr = ldns_rr_rdf(ldns_rr_list_rr(records, 0), 0);

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
    int i;
    ldns_rr_list *records;
    ldns_rdf *rdf;
    mrb_ldns_data *data = (mrb_ldns_data *)DATA_PTR(self);
    mrb_value ary;
    mrb_get_args(mrb,"z",&name);

    records = mrb_getaddress_rr_list(mrb, (ldns_resolver *)data->resolver, name);

    ary = mrb_ary_new(mrb);

    for(i=0; i < ldns_rr_list_rr_count(records); i++)
    {
        rdf = ldns_rr_rdf(ldns_rr_list_rr(records,i), 0);
        mrb_ary_push(mrb, ary, mrb_str_new_cstr(mrb, ldns_rdf2str(rdf)));
    }
    return ary;
}

/*
 * Resolv.getname("address")
 * => "name"
 */


static mrb_value mrb_resolv_getname(mrb_state *mrb, mrb_value self)
{
    char *addr = NULL;
    ldns_pkt *pkt = NULL;
    ldns_rr_list *records = NULL;
    ldns_rr *record = NULL;

    ldns_resolver *resolver;

    mrb_get_args(mrb, "z", &addr);

    records = mrb_getname_rr_list(mrb, resolver, addr);

    if(!records)
    {
        return mrb_nil_value();
    }
    if(ldns_rr_list_rr_count(records) < 0)
    {
        return mrb_nil_value();
    }

    record = ldns_rr_list_rr(records, 0);
    ldns_pkt_free(pkt);

    return mrb_str_new_cstr(mrb, ldns_rdf2str(ldns_rr_rdf((record), 0)));
}

/*
 * Resolv.getnames "address"
 * => ["name"]
 */

static mrb_value mrb_resolv_getnames(mrb_state *mrb, mrb_value self)
{
    char *addr = NULL;
    mrb_value ary;
    int i;
    ldns_rr_list *records = NULL;
    mrb_ldns_data *data = DATA_PTR(self);
    ldns_resolver *resolver = data->resolver;
    mrb_get_args(mrb, "z", &addr);

    records = mrb_getname_rr_list(mrb, resolver, addr);


    ary = mrb_ary_new(mrb);
    for(i =0; i < ldns_rr_list_rr_count(records) ; i++)
    {
        mrb_ary_push(mrb, ary, mrb_str_new_cstr(mrb, 
                    ldns_rdf2str( 
                        ldns_rr_rdf( 
                            ldns_rr_list_rr(records,i),0))));

    }
    return ary;
}

void mrb_mruby_ldns_gem_init(mrb_state *mrb)
{
    struct RClass *resolv;

    resolv = mrb_define_class(mrb, "Resolv", mrb->object_class);
    mrb_resolv_classes(mrb);
    mrb_define_resolv_resource(mrb);


    /*
     * Resolc Class 
     */

    //mrb_deine_method(mrb, reoslv, "initalize", mrb_resolv_init, MRB_ARG_OPT(2));
    mrb_define_method(mrb, resolv, "initalize", mrb_ldns_init , MRB_ARGS_NONE());


    mrb_define_class_method(mrb, resolv, "getaddress",      mrb_resolv_getaddress,      MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, resolv, "getaddresses",    mrb_resolv_getaddresses,    MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, resolv, "getname",         mrb_resolv_getname,         MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, resolv, "getnames",        mrb_resolv_getnames,        MRB_ARGS_REQ(1));
    
    mrb_define_method(mrb, resolv, "getaddress", mrb_resolv_getaddress,MRB_ARGS_REQ(1));
    mrb_define_method(mrb, resolv, "getaddresses", mrb_resolv_getaddresses, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, resolv, "getname", mrb_resolv_getname, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, resolv, "getnames", mrb_resolv_getnames, MRB_ARGS_REQ(1));

}


void mrb_mruby_ldns_gem_final(mrb_state *mrb)
{
}
