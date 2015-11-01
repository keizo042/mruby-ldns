
MRuby::Gem::Specification.new('mruby-ldns') do |spec|
  spec.license = 'MIT'
  spec.authors = 'keizo'
  spec.version = '0.0.1'
  spec.summary = 'Resolv Class library, powerd by ldns'
  spec.linker.libraries << ['ldns','crypto']
  #spec.add_dependency('')

  #spec.linker.flags_before_libraries << 
  #spec.cc.flags << "-I#{}/"
end
