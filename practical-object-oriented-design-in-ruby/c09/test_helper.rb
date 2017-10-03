module DiameterizableInterfaceTest
  def test_implements_the_diameterizable_interface
    assert_respond_to(@subject, :diameter)
  end
end
