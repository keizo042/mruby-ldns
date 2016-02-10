class Resolv

  def self.each_address(name, *proc)
    self.getaddresses(name).each do |address|
      yield address
    end
  end

  def self.each_name(address, *proc)
    self.getnames(address). each do | name|
      yield name
    end
  end

end
