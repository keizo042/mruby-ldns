#ifndef MRB_LDSN_H
#define MRB_LDNS_H

#if defined(MRB_RESOLV_H)
#error "mruby-ldns can not use, together with mruby-resolv"
#endif


//#define MRB_LDNS_DEBUG
#ifdef MRB_LDNS_DEBUG
#define MRB_LDNS_DEBUG_PRINT(function) printf("file:%s,line:%s,function:%s", __FILE__, __LINE__, function)
#else
#define MRB_LDNS_DEBUG_PRINT(function) 
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
#endif
