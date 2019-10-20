MRuby::Build.new do |conf|
  toolchain :gcc

  [conf.cc, conf.objc, conf.asm].each do |cc|
    cc.command = 'gcc'
    cc.flags = [%w(-g -std=gnu99 -O3 -Wall -Werror-implicit-function-declaration -Wdeclaration-after-statement -Wwrite-strings)]
  end

  conf.cxx do |cxx|
    cxx.command = 'g++'
    cxx.flags = [%w(-g -O3 -Wall -Werror-implicit-function-declaration)]
  end

  conf.linker do |linker|
    linker.command = 'gcc'
    linker.flags = [%w()]
    linker.libraries = %w(m)
    linker.library_paths = []
  end

  conf.archiver do |archiver|
    archiver.command = "ar"
  end

  conf.gembox 'default'
end

MRuby::CrossBuild.new('esp32') do |conf|
  toolchain :gcc

  conf.cc do |cc|
    if ENV["COMPONENT_INCLUDES"]
      cc.include_paths << ENV["COMPONENT_INCLUDES"].split(';')
    end

    cc.flags << '-Wno-maybe-uninitialized'
    cc.flags << '-Wno-char-subscripts'
    cc.flags << '-Wno-pointer-sign'
    cc.flags << '-ffunction-sections'
    cc.flags << '-fdata-sections'
    cc.flags << '-fstrict-volatile-bitfields'
    cc.flags << '-mlongcalls'
    cc.flags << '-Wno-undef'
    cc.flags << '-Wno-declaration-after-statement'

    cc.flags.reject!{ |x| x == '-MP' }

    cc.defines << %w(MRB_HEAP_PAGE_SIZE=64)
    cc.defines << %w(MRB_USE_IV_SEGLIST)
    cc.defines << %w(KHASH_DEFAULT_SIZE=8)
    cc.defines << %w(MRB_STR_BUF_MIN_SIZE=20)
    cc.defines << %w(MRB_GC_STRESS)

    cc.defines << %w(ESP_PLATFORM)
    cc.defines << %w(ESP32)
  end

  conf.cxx do |cxx|
    cxx.include_paths = conf.cc.include_paths.dup
    cxx.flags = conf.cc.flags.dup

    cxx.flags << "-std=gnu++11"
    cxx.flags << "-fno-rtti"
    cxx.flags << "-fno-exceptions"
    cxx.flags << "-nostdlib"
    cxx.flags << "-Wall"
    cxx.flags << "-Werror=all"
    cxx.flags << "-Wno-error=unused-function"
    cxx.flags << "-Wno-error=unused-but-set-variable"
    cxx.flags << "-Wno-error=unused-variable"
    cxx.flags << "-Wno-error=deprecated-declarations"
    cxx.flags << "-Wextra"
    cxx.flags << "-Wno-unused-parameter"
    cxx.flags << "-Wno-sign-compare"
    cxx.flags << "-ggdb"


    cxx.flags.reject!{ |x| x == '-MP' }

    cxx.defines = conf.cc.defines.dup
  end

  conf.bins = []
  conf.build_mrbtest_lib_only
  conf.disable_cxx_exception

  conf.gem :core => "mruby-print"
  conf.gem :core => "mruby-compiler"
  conf.gem :core => "mruby-pack"
  conf.gem :path => ".."
  conf.gem :github => "mruby-esp32/mruby-esp32-system"
  conf.gem :github => "mruby-esp32/mruby-esp32-wifi"
  conf.gem :github => "mruby-esp32/mruby-io", :branch => "esp32"
end
