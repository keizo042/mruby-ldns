#include "mruby.h"
#include "mruby/variable.h"


static mrb_value mrb_resolv_ipv4_init(mrb_state *mrb, mrb_value self)
{
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "address"), mrb_str_new_cstr(mrb,""));
    return self;
}

static mrb_value mrb_resolv_ipv4_to_name(mrb_state *mrb, mrb_value self)
{
    return mrb_nil_value();
}

static mrb_value mrb_resolv_ipv4_to_s(mrb_state *mrb, mrb_value self)
{
    return mrb_str_new_cstr(mrb, "");
}
static void mrb_define_resolv_ipv4(mrb_state *mrb)
{
    struct RClass *resolv, *ipv4;
    resolv = mrb_class_get(mrb, "Resolv");
    ipv4 = mrb_define_class(mrb, "IPv4", resolv);
    
    mrb_define_class_method(mrb, ipv4, "create", NULL, MRB_ARGS_NONE() );

    mrb_define_method(mrb, ipv4, "initalize", mrb_resolv_ipv4_init , MRB_ARGS_REQ(1) );
    // mrb_define_method(mrb, ipv4, "address", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv4, "to_name", mrb_resolv_ipv4_to_name, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv4, "to_s", mrb_resolv_ipv4_to_s, MRB_ARGS_NONE() );

    // mrb_define_const(mrb, ipv4, "Regex", NULL);
}

static mrb_value mrb_resolv_ipv6_init(mrb_state *mrb, mrb_value self)
{
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "address"), mrb_str_new_cstr(mrb,""));
    return self;
}
static void mrb_define_resolv_ipv6(mrb_state *mrb)
{
    struct RClass *resolv, *ipv6;
    resolv = mrb_class_get(mrb, "Resolv");
    ipv6 = mrb_define_class(mrb, "IPv6", resolv);
    
    mrb_define_class_method(mrb, ipv6, "create", NULL, MRB_ARGS_NONE() );

    mrb_define_method(mrb, ipv6, "initalize", mrb_resolv_ipv6_init, MRB_ARGS_REQ(1) );
    //mrb_define_method(mrb, ipv6, "address", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv6, "to_name", NULL, MRB_ARGS_NONE() );
    mrb_define_method(mrb, ipv6, "to_s", NULL, MRB_ARGS_NONE() );
}


void mrb_resolv_ip_define(mrb_state *mrb)
{
    mrb_define_resolv_ipv4(mrb);
    mrb_define_resolv_ipv6(mrb);
}
