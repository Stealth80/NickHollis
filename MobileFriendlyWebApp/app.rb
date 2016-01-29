require 'sinatra'
require 'json'

helpers do
  def protected!(security_level)
    return if authorized?(security_level)
    headers['WWW-Authenticate'] = 'Basic realm="Restricted Area"'
    halt 401, "Not authorized\n"
  end

  def authorized?(security_level)
    @auth ||=  Rack::Auth::Basic::Request.new(request.env)
    if @auth.provided? and @auth.basic? and @auth.credentials
      # Rewrite this if there is time, good enough for now

      # Misc passwords and 'security levels'
      if security_level == 'admin'
        if @auth.credentials == ['admin', 'admin']
          return true
        end
      elsif security_level == 'organizer'
        if (@auth.credentials == ['admin', 'admin'] or @auth.credentials == ['organizer', 'organizer'])
          return true
        end
      elsif security_level == 'judge'
        if (@auth.credentials == ['admin', 'admin'] or @auth.credentials == ['judge', 'judge'] or @auth.credentials == ['organizer', 'organizer'])
          return true
        end
      elsif security_level == 'volunteer'
        if (@auth.credentials == ['admin', 'admin'] or @auth.credentials == ['volunteer', 'volunteer'] or @auth.credentials == ['organizer', 'organizer'])
          return true
        end
      elsif security_level == 'exhibitor'
        if (@auth.credentials == ['admin', 'admin'] or @auth.credentials == ['exhibitor', 'exhibitor'] or @auth.credentials == ['organizer', 'organizer'])
          return true
        end
      elsif security_level == 'vip'
        if (@auth.credentials == ['admin', 'admin'] or @auth.credentials == ['vip', 'vip'] or @auth.credentials == ['organizer', 'organizer'])
          return true
        end
      else
        return false
      end
    else
      return false
    end
  end
end

alert = ""

get "/" do
  @alert = alert
  erb :index, layout: :no_nav_layout
end

get "/map*" do
  @alert = alert
  erb :map
end

get "/help*" do
  @alert = alert
  erb :help
end

get "/guestservices" do
  @alert = alert
  erb :guestservices
end

get "/guestinfo" do
  @alert = alert
  erb :guestinfo
end

get "/judge" do
  protected!('judge')
  @alert = alert
  erb :judge
end

get "/judgeinfo" do
  protected!('judge')
  @alert = alert
  erb :judgeinfo
end

get "/volunteerinfo*" do
  protected!('volunteer')
  @alert = alert
  erb :volunteerinfo
end

get "/volunteer*" do
  protected!('volunteer')
  @alert = alert
  erb :volunteer
end

get "/schedule*" do
  @alert = alert
  erb :schedule
end

get "/info*" do
  @alert = alert
  erb :info
end

get "/contact*" do
  @alert = alert
  erb :contact
end

get '/alert*' do
  @alert = alert
  # Auth check
  protected!('admin')

  erb :alert
end

get '/update_alert' do
  alert = params[:alert_message].to_s
  @alert = alert
  erb :update_alert
end

get '/alert_data.json' do
  content_type :json
  {alert_text: alert.to_s}.to_json
end
