def monthly_sales
  110
end

target_sales = 100

event "月刊売上が驚くほど高い" do
  monthly_sales > target_sales
end

event "月刊売上が底なしに低い" do
  monthly_sales < target_sales
end
