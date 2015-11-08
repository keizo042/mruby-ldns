
assert('') do
  assert_equal(resolv.class,Class)
end

assert('') do
  Resolv.getname
end

assert('') do
  Resolv.getnames
end

assert('') do
  Resolv.getaddress
end

assert('') do
  Resolv.getaddresses
end

resolv =Resolv.new

assert('') do
resolv.getname 
end
