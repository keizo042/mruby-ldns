resolv = Resolv.new

assert('Resolv') do
  assert_equal(resolv.class,Class)
end

assert('') do
  Resolv.getname ""
end

assert('') do
  Resolv.getnames ""
end

assert('') do
  Resolv.getaddress "google.com"
end

assert('') do
  Resolv.getaddresses "google.com"
end

resolv =Resolv.new

assert('') do
  resolv.getname 
end
