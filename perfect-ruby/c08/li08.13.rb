def create_proc
  str = 'from create_proc'
  Proc.new { str }
end

proc_obj = create_proc
str = 'from toplevel'
p proc_obj.call


top_level_proc = Proc.new { str }

p top_level_proc.call

str += ' append strings'

p top_level_proc.call
