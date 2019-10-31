MRuby::Gem::Specification.new('mruby-m5stickc') do |spec|
  spec.license = 'MIT'
  spec.author  = 'yamanekko'
  spec.summary = 'mruby for M5StickC'
  spec.add_dependency('mruby-sprintf', :core => 'mruby-sprintf')
  spec.add_dependency('mruby-io', :github => 'mruby-esp32/mruby-io', :branch => 'esp32')
end
