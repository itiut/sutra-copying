class AttrClass
  def initialize
    @attr = 'attr'
  end

  def add_reader(instance_val_name)
    eval <<-EOF
      def #{instance_val_name}
        @#{instance_val_name}
      end
    EOF
  end

  def add_writer(instance_val_name)
    eval <<-EOF
      def #{instance_val_name}=(val)
        @#{instance_val_name} = val
      end
    EOF
  end
end

attr_obj = AttrClass.new

p attr_obj.respond_to? :attr
attr_obj.add_reader :attr

p attr_obj.respond_to? :attr
p attr_obj.attr

p attr_obj.respond_to? 'attr='
attr_obj.add_writer 'attr'

p attr_obj.respond_to? 'attr='
attr_obj.attr = 'new val'
p attr_obj.attr
