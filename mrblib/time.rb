class Time
  def iso8601
    sprintf("%02d-%02d-%02dT%02d:%02d:%02d+00:00", self.year,self.mon,self.mday,self.hour, self.min, self.sec)   
  end

  alias_method :xmlschema, :iso8601
end
