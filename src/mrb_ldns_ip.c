#include "mruby.h"

static void mrb_define_resolv_ipv4(mrb_state *mrb)
{
    struct RClass *resolv, *ipv4;
    resolv = mrb_class_get(mrb, "Resolv");
    ipv4 = mrb_define_class(mrb, "IPv4", resolv);
    
    mrb_define_class_method(mrb, ipv4, "create", NULL, MRB_ARGS_NONE() );

    mrb_define_method(mrb, ipv4, "initalize", NULL, MRB_ARGS_REQ(1) );
    mrb_define_method(mrb, ipv4, "address", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv4, "to_name", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv4, "to_s", NULL, MRB_ARGS_NONE() );

    // mrb_define_const(mrb, ipv4, "Regex", NULL);
}

static void mrb_define_resolv_ipv6(mrb_state *mrb)
{
    struct RClass *resolv, *ipv6;
    resolv = mrb_class_get(mrb, "Resolv");
    ipv6 = mrb_define_class(mrb, "IPv6", resolv);
    
    mrb_define_class_method(mrb, ipv6, "create", NULL, MRB_ARGS_NONE() );

    mrb_define_method(mrb, ipv6, "initalize", NULL, MRB_ARGS_REQ(1) );
    mrb_define_method(mrb, ipv6, "address", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv6, "to_name", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv6, "to_s", NULL, MRB_ARGS_NONE() );
}


void mrb_resolv_ip_define(mrb_state *mrb)
{
    mrb_define_resolv_ipv4(mrb);
    mrb_define_resolv_ipv6(mrb);
}
