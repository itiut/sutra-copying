class KeywordArgs
  def normal_method_allow_keyword_args(first_arg, second_arg, third_arg)
    [first_arg, second_arg, third_arg]
  end

  private

  def method_missing(name, *args)
    method_name = name.to_s + '_allow_keyword_args'
    super unless respond_to? method_name

    args_hash = args.first
    new_args = self.method(method_name).parameters.map do |_, arg_name|
      args_hash[arg_name]
    end
    __send__ method_name, *new_args
  end
end

p KeywordArgs.new.normal_method(third_arg: 1, first_arg: 2, second_arg: 3)
