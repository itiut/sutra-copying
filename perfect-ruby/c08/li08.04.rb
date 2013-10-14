def convert_proc(&block)
  block
end

proc_obj = convert_proc { 1 }
p proc_obj.call
