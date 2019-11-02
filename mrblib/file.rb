class File < IO
  class FileError < Exception; end
  class NoFileError < FileError; end
  class UnableToStat < FileError; end
  class PermissionError < FileError; end

  attr_accessor :path

  def initialize(fd_or_path, mode = "r", perm = 0666)
    if fd_or_path.kind_of? Fixnum
      super(fd_or_path, mode)
    else
      @path = fd_or_path
      fd = IO.sysopen(@path, mode, perm)
      super(fd, mode)
    end
  end

  def self.directory?(file)
    FileTest.directory?(file)
  end

  def self.exist?(file)
    FileTest.exist?(file)
  end

  def self.exists?(file)
    FileTest.exists?(file)
  end

  def self.file?(file)
    FileTest.file?(file)
  end

  def self.pipe?(file)
    FileTest.pipe?(file)
  end

  def self.size(file)
    FileTest.size(file)
  end

  def self.size?(file)
    FileTest.size?(file)
  end

  def self.socket?(file)
    FileTest.socket?(file)
  end

  def self.symlink?(file)
    FileTest.symlink?(file)
  end

  def self.zero?(file)
    FileTest.zero?(file)
  end

  def self.extname(filename)
    fname = self.basename(filename)
    return '' if fname[0] == '.' || fname.index('.').nil?
    ext = fname.split('.').last
    ext.empty? ? '' : ".#{ext}"
  end

  def self.path(filename)
    if filename.kind_of?(String)
      filename
    elsif filename.respond_to?(:to_path)
      filename.to_path
    else
      raise TypeError, "no implicit conversion of #{filename.class} into String"
    end
  end
end
