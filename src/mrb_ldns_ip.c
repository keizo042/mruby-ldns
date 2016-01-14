
static void mrb_resolv_ipv4_define(mrb_state *mrb)
{
    struct RClass *resolv, *ipv4;
    resolv = mrb_class_get(mrb, "Resolv");
    host = mrb_define_class(mrb, "IPv4", resolv);
}

static void mrb_resolv_ipv6_define(mrb_state *mrb)
{
    struct RClass *resolv, *ipv6;
    resolv = mrb_class_get(mrb, "Resolv");
    host = mrb_define_class(mrb, "IPv6", resolv);
}


void mrb_resolv_ip_define(mrb_state *mrb)
{
    mrb_resolv_ipv4_define(mrb);
    mrb_resolv_ipv6_define(mrb);
}
}
