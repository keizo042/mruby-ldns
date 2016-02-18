mruby-ldns
====


## Descriotion

Ruby Resolv class powered by ldns.

read TODO.md ,implemented method&class&module.

## sample
Resolv.getaddress ""
Resolv.getname ""

resolver = Resolv.new

resolver.getaddress ""
resolver.getname ""

Resolv.getaddress ""
=> nil

Resolv::DNS.new.getresource

## Requirement
on your system
ldns

mruby

## Install
add build_config.rb

    conf.gem :github => "KeizoBookman/mruby-ldns"

## LICENSE
MITL

## AUTHOR

[keizo](https://github.com/KeizoBookman)


## Contact me
twitter : @keizo_bookman  
mail: keizo.bookman at gmail.com  
