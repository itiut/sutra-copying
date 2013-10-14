def proc_factory
  Proc.new
end

block_proc = proc_factory { 'method block' }
p block_proc.call


proc_factory
