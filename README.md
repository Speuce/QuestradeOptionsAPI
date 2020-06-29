# Questrade Options API
An (example) usage of the Questrade REST API to get options chain prices.

This will work for anyone with a Questrade account 'in good standing'. 
Questrade provides free API access to any clients

##Dependencies
This project uses [cpprestsdk](https://github.com/microsoft/cpprestsdk) to make requests to Questrade's REST Api. Follow the instructions **[here](https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial)** for installation.

**Mac Users** make sure you have the latest XCode installed on your system

##Questrade Credentials
In order to allow API access, you must do the following:

1. Log in to Questrade
2. In the top right corner, you should see your name, click on it
3. Click 'App Hub' in the resulting dropdown menu
4. Click 'Register a Personal App'
5. Enter any name and description you would like.
6. Ensure that at the bottom "Retrieve Delayed and Real-Time Market Data" is checked.
7. Click "Save" or "Submit"
