module M5StickC
  class Display
    def printf(*args)
      print(sprintf(*args))
    end
  end
end
