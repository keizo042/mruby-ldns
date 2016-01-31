
#ifndef MRB_LDNS_COMMON_H
#define MRB_LDNS_COMMON_H

#include "ldns/ldns.h"
#include "mruby.h"
#include "mruby/compile.h"

ldns_rr_list *mrb_getaddress_rr_list(mrb_state *mrb, ldns_resolver *resolver, char *name);
ldns_rr_list* mrb_getname_rr_list(mrb_state *mrb, ldns_resolver *resolver, char *addr);
#endif
