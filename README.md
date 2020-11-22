# Jome'e Bazar
impelmentation of a shopping website by following Object Oriented Programming concepts.

this application uses [AP HTTP](https://github.com/UTAP/APHTTP/) as http server

there is three type of users in website:
* `Admin`: admin can login with 'admin@gmail.com' as mail and 'admin' as passowrd. in admin pannel you can
add three type of object to website (by selecting type and choosing csv file that contains items information. chosen file must be in `/website/productsData` directory and you should type exactly the file's name):
    * `Car`: you can add another cars to `/website/productsData/Car.csv`
    * `Mobile`: you can add another mobile phones to `/website/productsData/Mobile.csv`
    * `TV`: you can add another TVs to `/website/productsData/TV.csv`
* `Seller`: sellers can do following:
    * `Create Offer`: sellers can set offers on items that are available in website (created by admin)
    * `Edit Offers`: sellers can change prices and charge available amount of their offers
    * `Wallet`: sellers can view their recent wallet activities and incomes
    * `Create Discounts`
* `Buyer`: buyers can do following:
    * `Search For Items`
    * `View Offers Of Different Sellers On Items`
    * `View An Item Details`
    * `Compare An Item With Other Products`
    * `View Comments On Items And Add Comments`: a naive bayes classifier filters offensive comments (you   can read specifications of classifier in `Assignment 7(AI).pdf`)
    * `Add Items To Cart, View and Finalize Order`
    * `Charge Wallet And View Recent Wallet Activities`

you can read full specifications of domain codes in `Assignment 7(Domain).pdf`
models and comment classifier:`/website/domain`
views are in `/website/template`

## How to run
In `/webiste` directory just run
```bash
make
```

and then
```bash
./myserver.out [port]
```

and open 'localhost:port' in browser