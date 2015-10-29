class Staff::CustomerSearchForm
  include ActiveModel::Model
  include StringNormalizer

  attr_accessor :family_name_kana, :given_name_kana,
                :birth_year, :birth_month, :birth_mday, :gender,
                :address_type, :prefecture, :city, :phone_number, :last_four_digits, :postal_code

  def search
    normalize_values

    rel = Customer
    if family_name_kana.present?
      rel = rel.where(family_name_kana: family_name_kana)
    end
    if given_name_kana.present?
      rel = rel.where(given_name_kana: given_name_kana)
    end
    rel = rel.where(birth_year: birth_year) if birth_year.present?
    rel = rel.where(birth_month: birth_month) if birth_month.present?
    rel = rel.where(birth_mday: birth_mday) if birth_mday.present?
    rel = rel.where(gender: gender) if gender.present?

    if prefecture.present? || city.present? || postal_code.present?
      joins_rel = case address_type
                  when 'home'
                    [:home_address, HomeAddress]
                  when 'work'
                    [:work_address, WorkAddress]
                  when ''
                    [:addresses, Address]
                  else
                    fail
                  end
      rel = rel.joins(joins_rel[0])
      rel = rel.merge(joins_rel[1].where(prefecture: prefecture)) if prefecture.present?
      rel = rel.merge(joins_rel[1].where(city: city)) if city.present?
      rel = rel.merge(joins_rel[1].where(postal_code: postal_code)) if postal_code.present?
    end

    if phone_number.present? || last_four_digits.present?
      rel = rel.joins(:phones)
      rel = rel.merge(Phone.where(number_for_index: phone_number)) if phone_number.present?
      rel = rel.merge(Phone.where(last_four_digits: last_four_digits)) if last_four_digits.present?
    end

    rel.order(:family_name_kana, :given_name_kana)
  end

  private

  def normalize_values
    self.family_name_kana = normalize_as_furigana(family_name_kana)
    self.given_name_kana  = normalize_as_furigana(given_name_kana)
    self.city = normalize_as_name(city)
    self.phone_number = normalize_as_phone_number(phone_number).try(:gsub, /\D/, '')
    self.postal_code = normalize_as_postal_code(postal_code)
  end
end
