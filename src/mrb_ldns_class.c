/*
 *
 * class DNS::Resolv 
 *
 *
 */
#include "mrb_ldns_common.h"

static mrb_value mrb_ldns_dns_open(mrb_state *mrb, mrb_value self)
{
    return self;
}

static mrb_value mrb_ldns_dns_init(mrb_state *mrb, mrb_value self)
{

    return self;
}

static mrb_value mrb_ldns_dns_close(mrb_state *mrb, mrb_value self)
{
    return self;
}

static mrb_value mrb_ldns_dns_each_resource(mrb_state *mrb, mrb_value self)
{
    return self;
}

static mrb_value mrb_ldns_dns_getresource(mrb_state *mrb, mrb_value self)
{
    return self;
}

static mrb_value mrb_ldns_dns_getresources(mrb_state *mrb, mrb_value self)
{
    return self;
}

static mrb_value mrb_ldns_dns_timeout(mrb_state *mrb, mrb_value self)
{
    return self;
}

static void mrb_define_resolv_dns(mrb_state *mrb)
{
    struct RClass *resolv, *dns;
    resolv = mrb_class_get(mrb,"Resolv");
    dns = mrb_define_class_under(mrb, resolv, "DNS", mrb->object_class);

    mrb_define_class_method(mrb, dns, "open", mrb_ldns_dns_open, MRB_ARGS_OPT(2) );

    mrb_define_method(mrb, dns, "initialize", mrb_ldns_dns_init, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, dns, "close", mrb_ldns_dns_close, MRB_ARGS_NONE() );
    mrb_define_method(mrb, dns, "each_resource", mrb_ldns_dns_each_resource, MRB_ARGS_REQ(2) );
    mrb_define_method(mrb, dns, "getresource", mrb_ldns_dns_getresource, MRB_ARGS_REQ(1) );
    mrb_define_method(mrb, dns, "getresources", mrb_ldns_dns_getresources, MRB_ARGS_REQ(1) );
    mrb_define_method(mrb, dns, "timeout=", mrb_ldns_dns_timeout, MRB_ARGS_REQ(1) );

}

static void mrb_define_resolv_dns_name(mrb_state *mrb)
{
    struct RClass *resolv, *dns, *name;
    resolv = mrb_class_get(mrb, "Resolv");
    dns = mrb_class_get_under(mrb, resolv,"DNS");
    name = mrb_define_class_under(mrb, dns, "Name", mrb->object_class);
    
    mrb_define_class_method(mrb, name, "create", NULL, MRB_ARGS_NONE());

    mrb_define_method(mrb, name, "initalize", NULL, MRB_ARGS_REQ(1) );
}

static mrb_value mrb_ldns_resolv_host_init(mrb_state *mrb, mrb_value self)
{
    return self;
}

static void mrb_define_resolv_host(mrb_state *mrb)
{
    struct RClass *resolv, *hosts;
    resolv = mrb_class_get(mrb,"Resolv");
    hosts = mrb_define_class(mrb,"Hosts", resolv);

    mrb_define_method(mrb, hosts, "initialize", mrb_ldns_resolv_host_init, MRB_ARGS_NONE() );

}


void mrb_resolv_classes(mrb_state *mrb) 
{
    mrb_define_resolv_dns(mrb);
    mrb_define_resolv_host(mrb);
    mrb_define_resolv_dns_name(mrb);
}
