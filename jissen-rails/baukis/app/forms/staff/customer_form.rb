class Staff::CustomerForm
  include ActiveModel::Model

  attr_accessor :customer, :inputs_home_address, :inputs_work_address
  delegate :persisted?, :save, to: :customer

  def initialize(customer = nil)
    @customer = customer
    @customer ||= Customer.new(gender: 'male')
    @customer.personal_phones.size.upto(1) do
      @customer.personal_phones.build
    end
    @inputs_home_address = @customer.home_address.present?
    @inputs_work_address = @customer.work_address.present?
    @customer.build_home_address unless @customer.home_address
    @customer.build_work_address unless @customer.work_address
    @customer.home_address.phones.size.upto(1) do
      @customer.home_address.phones.build
    end
    @customer.work_address.phones.size.upto(1) do
      @customer.work_address.phones.build
    end
  end

  def assign_attributes(params = {})
    @params = params
    @inputs_home_address = params[:inputs_home_address] == '1'
    @inputs_work_address = params[:inputs_work_address] == '1'

    customer.assign_attributes(customer_params)
    assign_phones_attributes(:customer)

    if @inputs_home_address
      customer.home_address.assign_attributes(home_address_params)
      assign_phones_attributes(:home_address)
    else
      customer.home_address.mark_for_destruction
    end
    if @inputs_work_address
      customer.work_address.assign_attributes(work_address_params)
      assign_phones_attributes(:work_address)
    else
      customer.work_address.mark_for_destruction
    end
  end

  private

  def assign_phones_attributes(record_name)
    requested_phones = phone_params(record_name).fetch(:phones)
    phones = case record_name
             when :customer
               @customer.personal_phones
             when :home_address
               @customer.home_address.phones
             when :work_address
               @customer.work_address.phones
             end
    phones.each_with_index do |phone, index|
      attributes = requested_phones[index.to_s]
      if attributes && attributes[:number].present?
        phone.assign_attributes(attributes)
      else
        phone.mark_for_destruction
      end
    end
  end

  def customer_params
    @params.require(:customer).permit(
      :email, :password,
      :family_name, :given_name, :family_name_kana, :given_name_kana,
      :birthday, :gender
    )
  end

  def phone_params(record_name)
    @params.require(record_name).permit(phones: [:number, :primary])
  end

  def home_address_params
    @params.require(:home_address).permit(
      :postal_code, :prefecture, :city, :address1, :address2
    )
  end

  def work_address_params
    @params.require(:work_address).permit(
      :postal_code, :prefecture, :city, :address1, :address2, :company_name, :division_name
    )
  end
end
