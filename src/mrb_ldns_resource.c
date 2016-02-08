/*
 *
 *
 * class Resolv::DNS::Resource
 * module Resolv::DNS::Resource::IN
 * class Resolv::DNS::Resource::IN::A
 * class Resolv::DNS::Resource::IN::AAAA
 * class Resolv::DNS::Resource::IN::MX
 * class Resolv::DNS::Resource::IN::TXT
 * class Resolv::DNS::Resource::IN::SOA
 * class Resolv::DNS::Reosurce::IN::SRV
 * class Resolv::DNS::Reosurce::IN::MINFO
 * class Resolv::DNS::Resource::IN::ANY
 *
 *
 */
#include "mruby.h"
#include "ldns/ldns.h"

static void mrb_define_resolv_in_a(mrb_state *mrb);
static void mrb_define_resolv_in_minfo(mrb_state *mrb);
static void mrb_define_resolv_in_ptr(mrb_state *mrb);
static void mrb_define_resolv_in_soa(mrb_state *mrb);
static void mrb_define_resolv_in_srv(mrb_state *mrb);
static void mrb_define_resolv_in_txt(mrb_state *mrb);
static void mrb_define_resolv_in_aaaa(mrb_state *mrb);
void mrb_define_resolv_resource(mrb_state *mrb);

void mrb_define_resolv_resource(mrb_state *mrb)
{
    struct RClass *resolv, *dns, *resource;
    resolv = mrb_class_get(mrb, "Resolv");
    dns = mrb_class_get_under(mrb, resolv, "DNS" ); 
    resource = mrb_define_class_under(mrb, dns, "Resource",  mrb->object_class);
    mrb_define_module_under(mrb, resource, "IN");
    mrb_define_resolv_in_a(mrb);
    mrb_define_resolv_in_minfo(mrb);
    mrb_define_resolv_in_ptr(mrb);
    mrb_define_resolv_in_soa(mrb);
    mrb_define_resolv_in_srv(mrb);
    mrb_define_resolv_in_txt(mrb);
    mrb_define_resolv_in_aaaa(mrb);
}


static struct RClass *mrb_define_class_under_resource_in(mrb_state *mrb, const char *name)
{
    struct RClass *resolv, *dns, *resource, *in, *class;
    resolv = mrb_class_get(mrb, "Resolv");
    dns = mrb_class_get_under(mrb, resolv, "DNS");
    resource = mrb_class_get_under(mrb, dns, "Resource");
    in = mrb_module_get_under(mrb, resource, "IN");

    class = mrb_define_class_under(mrb,  in, name, mrb->object_class);

    return  class;
}

static void mrb_define_in_consts(mrb_state* mrb, struct RClass *class, int rtype, int rclass)
{
    mrb_define_const(mrb, class, "TypeValue", mrb_fixnum_value(rtype));
    mrb_define_const(mrb, class, "ClassValue", mrb_fixnum_value(rclass));
}

static void mrb_define_resolv_in_ptr(mrb_state *mrb)
{
    struct RClass *ptr = mrb_define_class_under_resource_in(mrb,"PTR");
    mrb_define_in_consts(mrb, ptr, LDNS_RR_TYPE_PTR,  LDNS_RR_CLASS_IN);
}

static void mrb_define_resolv_in_a(mrb_state *mrb)
{
    struct RClass *a = mrb_define_class_under_resource_in(mrb,"A");
    mrb_define_in_consts(mrb, a, LDNS_RR_TYPE_A,  LDNS_RR_CLASS_IN);
}

static void mrb_define_resolv_in_srv(mrb_state *mrb)
{
    struct RClass *srv = mrb_define_class_under_resource_in(mrb,"SRV");
    mrb_define_in_consts(mrb, srv, LDNS_RR_TYPE_SRV,  LDNS_RR_CLASS_IN);
}

static void mrb_define_resolv_in_soa(mrb_state *mrb)
{
    struct RClass *soa = mrb_define_class_under_resource_in(mrb,"SOA");
    mrb_define_in_consts(mrb, soa, LDNS_RR_TYPE_SOA,  LDNS_RR_CLASS_IN);
}

static void mrb_define_resolv_in_txt(mrb_state *mrb)
{
    struct RClass *txt = mrb_define_class_under_resource_in(mrb,"TXT");
    mrb_define_in_consts(mrb, txt, LDNS_RR_TYPE_TXT,  LDNS_RR_CLASS_IN);
}

static void mrb_define_resolv_in_minfo(mrb_state *mrb)
{
    struct RClass *minfo = mrb_define_class_under_resource_in(mrb,"MINFO");
    mrb_define_in_consts(mrb, minfo, LDNS_RR_TYPE_MINFO,  LDNS_RR_CLASS_IN);
}

static void mrb_define_resolv_in_aaaa(mrb_state *mrb)
{
    struct RClass *aaaa = mrb_define_class_under_resource_in(mrb,"AAAA");
    mrb_define_in_consts(mrb, aaaa, LDNS_RR_TYPE_AAAA,  LDNS_RR_CLASS_IN);
}
