#include "mruby.h"

static void mrb_resolv_dns_define(mrb_state *mrb)
{
    struct RClass *resolv, *dns;
    resolv = mrb_class_get(mrb,"Resolv");
    dns = mrb_define_class(mrb,"DNS", resolv);


}

static void mrb_resolv_host_define(mrb_state *mrb)
{
    struct RClass *resolv, *host;
    resolv = mrb_class_get(mrb,"Resolv");
    host = mrb_define_class(mrb,"Host", resolv);
}


void mrb_resolv_classes(mrb_state *mrb) 
{
    mrb_resolv_dns_define(mrb);
    mrb_resolv_host_define(mrb);
}
