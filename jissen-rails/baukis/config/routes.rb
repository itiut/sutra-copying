Rails.application.routes.draw do
  namespace :staff do
    root 'top#index'
    get 'login', to: 'sessions#new', as: :login
    post 'session', to: 'sessions#create', as: :session
    delete 'session', to: 'sessions#destory'
  end

  namespace :admin do
    root 'top#index'
  end

  namespace :customer do
    root 'top#index'
  end

  root 'errors#not_found'
  get '*anything' => 'errors#not_found'
end
