# Software Design CIS 3296
## Lab 4

### Khai Nguyen and Rathanank A. Onn

#### Lab Requirements

This lab required that the team members involved make use of git and github, while protecting the master branch. This lab is an add on to the previous PayStation Lab, this time we had to implement a main function with the following requirements :
1) Accept coins for payment : 5, 10, 25 cents
2) Show time bought on display
3) When buying a parting ticket, print parking time receipts
4) When cancel option is selected, print total returned coin values and number of each coin type
5) Implement three rate strategies for three clients: Linear rate for Alphatown, progressive rate for Betatown and alternating rate for Gammatown. Rate strategy selection and change can be done on the fly, i.e. in run-time.

6) A main() program should be developed to simulate the PayStation operation. It puts up a menu to allow a customer to select a choice:

* Deposit Coins
* Display
* Buy Ticket
* Cancel
* Change Rate Strategy

The requirements for this program was pretty straightfoward, we decided to go with the design of "Model number 4: Compositional Solution." The main method runs a forever while loop, while the user is able to enter coins, which only accepts the values of 5, 10, and 25 cents respectively. And in doing so, the user can decide to view how much time they'll have, buy the ticket, or cancel the ticket, which will return the mapping of the coins they entered. There is another option where an employee can change the rate of the system with options of Alpha, Beta, or Gamma town, each town has their own method of calculating the time. This was done by created classes for each different Rate for each town. Thus the reason we chose to go with method number 4, we wanted to have each class/object have their own responsibily and not have one class contain all the logic and do everything. 

#### UML Diagram

![UML Diagram](https://github.com/3296Spring2020/paystationmain-02-onn-nguyen/blob/onnbranchv3/UMLver4.1.png)

#### Teamwork

* Rathanank A Onn

We got together and deciding to make classes as needed. I contributed towards the project by :
1) Creating/Updating the UML
2) Wrote skeleton code in main
3) Made AlternateRateHardCode Class, which is used for testing AlternateRate
4) Wrote test cases for the following
* AlternateStrategyImplTest
* LinearStrategyImplTest
* ProgressiveStrategyImplTest
5) Added documention to code for ease of readability 
6) Revised some of my partner's work, while he also revised mine

* Khai Nguyen
1) Collaborated with Rathanank to design and edit the UML diagram
2) Planned the organization of classes and how to implement new classes for additional rate strategy
3) Fixed addPayment() method
4) Built LinearStrategyImpl()
5) Built ProgressiveStrategyImpl()
6) Built AlternateStrategyImpl()
7) Troubleshot issues with git "rebase"
8) Built main() and test the methods with the test cases built by Rathanank


#### Testing

The testing is done in classes inside the folder named test.paystation.domain
The classes that we wrote makes use of the "assertEquals" function and when writing each individual test, we would:
* Purposely write a failing test
* Test the whole class 
* See the failing test fail
* Revise and fix it
* Test just the unit Test and see it pass
* Test the whole class and see all Test pass

This is the core of the algorithm that we did for testing
We did discover a bug while testing, the old logic in progressive rate would return 60 minutes when entering 50 coin value, which should not happen, therefore leading us to change the logic of the if else statements, testing the 3 hour mark first, then 2 hour and then 1 hour mark. Which did fix the bug. Rathanank Onn has written all of the source code for testing and did so after the main source code was written.
