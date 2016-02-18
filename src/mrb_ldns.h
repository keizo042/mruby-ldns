#ifndef MRB_LDSN_H
#define MRB_LDNS_H

#if defined(MRB_RESOLV_H)
#error "mruby-ldns can not use, together with mruby-resolv"
#endif



#include "mruby.h"
#include "mruby/object.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/variable.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"

#include "ldns/ldns.h"
#include "stdint.h"
#include "stdbool.h"

#define MRB_LDNS_DEBUG_ENABLE
#ifdef MRB_LDNS_DEBUG_ENABLE
#define MRB_LDNS_DEBUG(function) printf("file:%s,line:%d,function:%s\n", __FILE__, __LINE__, function)
#else
#define MRB_LDNS_DEBUG(function) 
#endif
#endif
