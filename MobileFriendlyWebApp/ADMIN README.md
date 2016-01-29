# Keeneland Concours Map Website Admin

## Login:

To log in to an area that you have authorization to, go to the page or link you want to access.  A box will pop up stating "Authentication Required."  Simply fill in your given username and password.  This will log you onto the system and allow you access to your areas.

## Security:

Several areas of the site are password protected in the following heiarchy from higest to lowest:

- Admin ->  Organizers -> Judges, Volunteers, and Exibitors

- Judges:   The default user name for judges is Judge.  The Judge username and password allows access to both the "Info for Judges" (/judge) area and the "Judging Info" (/judgeinfo) screens of the app.  Judges can also access the "Who to Contact?" (/contact) page as well.  These areas are otherwise protected areas and unvisible to general users.

- Volunteers:   The default user name for volunteers is Volunteer.  The Judge username and password allows access to both the 					"Info for Volunteers" (/volunteer) section as well as the "Volunteering Info" (/volunteerinfo) screens of the 					app.  Volunteers can also access the "Who to Contact?" (/contact) page as well.  These areas are otherwise 						protected areas and unvisible to general users.

- Exibitors:   The default user name for exibitors a is Exibitor.  Currently, Exibitors do not have a special section, however 					this security level was created as part of requirements and for further future development.

- Organizers:   The default user name for organizers a is Organizer.  Organziers can access all areas encompassed by Judges, 						Volunteers, and Exibitors.  These areas are otherwise protected areas and unvisible to general users.

- Admin:   The default user name for the administrator account is Admin.  Admin can access all levels and areas on the site.  				This includes all Judge, Volunteer, Exibitor, and Organizer pages, as well as the "Alerts" (/alert) page used to 				set, change, and cancel/delete Alerts for the site.  All of these areas are otherwise protected areas and unvisible 			to general users.  Admins can follow the directions in the next section for setting and clearing alerts

## Login:

To log in to the site, go to /alert and press enter.  A box will pop up stating "Authentication Required."  					Simply fill in your administrator username and password.  This will log you onto the system.

##Set Alert:

To set an alert message, make sure you are on the alerts page.  Where it states "Fill in the alert message below and 						submit." type in the message you want to post.  Next tap or press submit.  This will post your message.

#Clear Alert:

To clear an alert that was previously set, simply click the "Clear alert" button.  This will clear the alert.


## Deployment

It's a simple Sinatra app that can be deployed with Rack. Ruby version is in .ruby-version.
Run the app with `rackup`. Strongly recommend changing passwords to environment variables.
