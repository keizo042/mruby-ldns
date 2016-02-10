resolv = Resolv.new

assert('Resolv') do
  assert_equal(resolv.class,Class)
end

assert('Resolv.getname') do
  Resolv.getname ""
end

assert('Resolv.getnames') do
  Resolv.getnames ""
end

assert('Resolv.getaddress') do
  Resolv.getaddress "google.com"
end

assert('Resolv.getaddresses') do
  Resolv.getaddresses "google.com"
end

resolv =Resolv.new

assert('Resolv::getname') do
  resolv.getname ""
end
