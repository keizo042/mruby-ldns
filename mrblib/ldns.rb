class Resolv
  def each_address(name, *proc)
    self.getaddresses(name).each do |address|
      proc.call(address)
    end
  end

  def each_name(address, *proc)
    self.getnames(address). each do | name|
      proc.call(name)
    end
  end

end
