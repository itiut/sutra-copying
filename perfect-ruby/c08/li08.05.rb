def yield_proc
  yield
end

proc_obj = Proc.new { 1 }
p yield_proc &proc_obj
