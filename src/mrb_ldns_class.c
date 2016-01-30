#include "mrb_ldns_common.h"
#include "mruby.h"
#include "mruby/compile.h"

mrb_value mrb_ldns_dns_open(mrb_state *mrb, mrb_value self)
{
    return self;
}

mrb_value mrb_ldns_dns_init(mrb_state *mrb, mrb_value self)
{

    return self;
}

mrb_value mrb_ldns_dns_close(mrb_state *mrb, mrb_value self)
{
    return self;
}


static void mrb_resolv_dns_define(mrb_state *mrb)
{
    struct RClass *resolv, *dns;
    resolv = mrb_class_get(mrb,"Resolv");
    dns = mrb_define_class(mrb,"DNS", resolv);

    mrb_define_class_method(mrb, dns, "open", mrb_ldns_dns_open, MRB_ARGS_OPT(2) );

    mrb_define_method(mrb, dns, "initialize", mrb_ldns_dns_init, MRB_ARGS_OPT(1));

    mrb_define_method(mrb, dns, "close", mrb_ldns_dns_close, MRB_ARGS_NONE() );
    mrb_define_method(mrb, dns, "each_resource", NULL, MRB_ARGS_REQ(2) );
    mrb_define_method(mrb, dns, "getresource", NULL, MRB_ARGS_REQ(1) );
    mrb_define_method(mrb, dns, "timeout=", NULL, MRB_ARGS_REQ(1) );

}

static void mrb_resolv_host_define(mrb_state *mrb)
{
    struct RClass *resolv, *hosts;
    resolv = mrb_class_get(mrb,"Resolv");
    hosts = mrb_define_class(mrb,"Hosts", resolv);

}


void mrb_resolv_classes(mrb_state *mrb) 
{
    mrb_resolv_dns_define(mrb);
    mrb_resolv_host_define(mrb);
}
