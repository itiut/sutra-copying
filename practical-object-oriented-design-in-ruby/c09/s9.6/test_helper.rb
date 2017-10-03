module BicycleInterfaceTest
  [
    :chain, :size,
    :default_chain,
    :default_tire_size,
    :spares,
    :tire_size,
  ].each do |method_sym|
    define_method("test_responds_to_#{method_sym.to_s}") do
      assert_respond_to(@subject, method_sym)
    end
  end
end

module BicycleSubclassTest
  [
    :post_initialize,
    :local_spares,
    :default_tire_size,
  ].each do |method_sym|
    define_method("test_responds_to_#{method_sym.to_s}") do
      assert_respond_to(@subject, method_sym)
    end
  end
end
