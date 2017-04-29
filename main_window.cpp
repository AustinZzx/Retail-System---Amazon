#include "main_window.h"
using namespace std;


MainWindow::MainWindow()
{}

MainWindow::MainWindow(MyDataStore* mydata)
	:MyData(mydata)
{
	// Title
	setWindowTitle("Amazon");

	//Log in Window
	loginLayout = new QVBoxLayout();
	lognameLabel = new QLabel("Username: ");
	loginLayout->addWidget(lognameLabel);
	lognameInput = new QLineEdit();
	loginLayout->addWidget(lognameInput);
	logpasswordLabel = new QLabel("Password: ");
	loginLayout->addWidget(logpasswordLabel);
	logpasswordInput = new QLineEdit();
	loginLayout->addWidget(logpasswordInput);
	loginButton = new QPushButton("&Log In");
	loginLayout->addWidget(loginButton);
	newuserButton  = new QPushButton("&Create new account");
	loginLayout->addWidget(newuserButton);
	quitloginButton = new QPushButton("&Quit");
	loginLayout->addWidget(quitloginButton);



	setLayout(loginLayout);

	// Main Window //
	bigwindowMain = new QWidget();
	// Overall layout
	overallLayout = new QHBoxLayout();

	// // User part
	// Layout
	userLayout = new QVBoxLayout();
	overallLayout->addLayout(userLayout);
	usersnameLabel = new QLabel("Users: ");
	userLayout->addWidget(usersnameLabel);
	usersList = new QListWidget();
	userLayout->addWidget(usersList);
	set<User*> unames = MyData->getusernames();
	set<User*>::iterator it1 = unames.begin();
	for(;it1!=unames.end();++it1)
	{
		usernames.push_back((*it1)->getName());
		QString qstr = QString::fromStdString((*it1)->getName());
		usersList->addItem(qstr);
	}
	currentusername = usernames.front();
	selectuserButton = new QPushButton("&Enter username to select:");
	//userLayout->addWidget(selectuserButton);
	usernameInput = new QLineEdit();
	//userLayout->addWidget(usernameInput);
	currentuserLabel = new QLineEdit(QString::fromStdString("&Current User: "+currentusername));
	currentcart = MyData->viewCart(MyData->getUser(currentusername));
	currentuserLabel->setReadOnly(true);
	userLayout->addWidget(currentuserLabel);
	string currentbalance;
	double tempbalance = MyData->getUser(currentusername)->getBalance();
	stringstream ss;
	ss<<tempbalance;
	ss>>currentbalance;
	currentcreditLabel = new QLineEdit(QString::fromStdString("Current credit: "+currentbalance));
	currentcreditLabel->setReadOnly(true);
	userLayout->addWidget(currentcreditLabel);
	recommendButton = new QPushButton("Product Recommendations");
	userLayout->addWidget(recommendButton);

	//search product part
	searchproductLayout = new QVBoxLayout();
	overallLayout->addLayout(searchproductLayout);
	searchproductLabel = new QLabel("Enter Terms to Search:");
	searchproductLayout->addWidget(searchproductLabel);
	searchproductInput = new QTextEdit();
	searchproductLayout->addWidget(searchproductInput);
	andorLayout = new QHBoxLayout();
	searchproductLayout->addLayout(andorLayout);
	andButton = new QPushButton("&AND");
	orButton = new QPushButton("&OR");
	andorLayout->addWidget(andButton);
	andorLayout->addWidget(orButton);
	sortproductLabel = new QLabel("Sort Product By:");
	searchproductLayout->addWidget(sortproductLabel);
	sortproductLayout = new QHBoxLayout();
	searchproductLayout->addLayout(sortproductLayout);
	alphabeticalButton = new QPushButton("&Alphabetical");
	ratingButton = new QPushButton("&Rating");
	sortproductLayout->addWidget(alphabeticalButton);
	sortproductLayout->addWidget(ratingButton);
	//not sure about the following savedialog
	saveDialog = new QFileDialog();
	saveButton = new QPushButton("&Save Data into File");
	searchproductLayout->addWidget(saveButton);

	//product results part
	productresultLayout = new QVBoxLayout();
	overallLayout->addLayout(productresultLayout);
	productresultLabel = new QLabel("Product Result:");
	productresultLayout->addWidget(productresultLabel);
	productresultList = new QListWidget;
	productresultLayout->addWidget(productresultList);

	//product details part
	productdetailsLayout = new QVBoxLayout();
	overallLayout->addLayout(productdetailsLayout);
	productdetailsLabel = new QLabel("Product Details:");
	productdetailsLayout->addWidget(productdetailsLabel);
	productdetailsOutput = new QTextEdit();
	productdetailsOutput->setReadOnly(true);
	productdetailsLayout->addWidget(productdetailsOutput);
	addtocartButton = new QPushButton("&Add to Cart");
	productdetailsLayout->addWidget(addtocartButton);
	viewcartButton = new QPushButton("&View Cart");
	productdetailsLayout->addWidget(viewcartButton);

	//review part
	reviewLayout = new QVBoxLayout();
	overallLayout->addLayout(reviewLayout);
	reviewLabel = new QLabel("Reviews:");
	reviewLayout->addWidget(reviewLabel);
	reviewOutput = new QTextEdit();
	reviewOutput->setReadOnly(true);
	reviewLayout->addWidget(reviewOutput);
	addreviewButton = new QPushButton("&Add Review");
	reviewLayout->addWidget(addreviewButton);
	closeamazonButton = new QPushButton("&Close");
	reviewLayout->addWidget(closeamazonButton);

	// Set overall layout
	bigwindowMain->setLayout(overallLayout);


	
	//Small Windows - CART//
	smallwindowcart = new QWidget();
	// Overall layout
	cartoverallLayout = new QHBoxLayout();

	//cart items part
	itemsLayout = new QVBoxLayout();
	cartoverallLayout->addLayout(itemsLayout);
	itemsLabel = new QLabel("User's Cart:");
	itemsLayout->addWidget(itemsLabel);
	itemsList = new QListWidget();
	itemsLayout->addWidget(itemsList);
	
	//item details part
	itemdetailsLayout = new QVBoxLayout();
	cartoverallLayout->addLayout(itemdetailsLayout);
	itemdetailsLabel = new QLabel("Item Details:");
	itemdetailsLayout->addWidget(itemdetailsLabel);
	itemdetailsOutput = new QTextEdit();
	itemdetailsOutput->setReadOnly(true);
	itemdetailsLayout->addWidget(itemdetailsOutput);
	removeitemButton = new QPushButton("&Remove item");
	itemdetailsLayout->addWidget(removeitemButton);
	buycartButton = new QPushButton("&Buy Cart");
	itemdetailsLayout->addWidget(buycartButton);
	closecartButton = new QPushButton("&Close");
	itemdetailsLayout->addWidget(closecartButton);

	smallwindowcart->setLayout(cartoverallLayout);


	//Small Windows - Add-Review//
	smallwindowaddreview = new QWidget();

	addreviewLayout = new QVBoxLayout();
	yearLayout = new QHBoxLayout();
	addreviewLayout->addLayout(yearLayout);
	yearLabel = new QLabel("Year(4 digits): ");
	yearLayout->addWidget(yearLabel);
	yearInput = new QLineEdit();
	yearLayout->addWidget(yearInput);
	monthLayout = new QHBoxLayout();
	addreviewLayout->addLayout(monthLayout);
	monthLabel = new QLabel("Month(2 digits): ");
	monthLayout->addWidget(monthLabel);
	monthInput = new QLineEdit();
	monthLayout->addWidget(monthInput);
	dayLayout = new QHBoxLayout();
	addreviewLayout->addLayout(dayLayout);
	dayLabel = new QLabel("Day(2 digits): ");
	dayLayout->addWidget(dayLabel);
	dayInput = new QLineEdit();
	dayLayout->addWidget(dayInput);
	ratingLayout = new QHBoxLayout();
	addreviewLayout->addLayout(ratingLayout);
	ratingLabel = new QLabel("Rating(1-5): ");
	ratingLayout->addWidget(ratingLabel);
	ratingInput = new QLineEdit();
	ratingLayout->addWidget(ratingInput);
	reviewtextLabel = new QLabel("Review Text:");
	addreviewLayout->addWidget(reviewtextLabel);
	reviewtextInput = new QTextEdit();
	addreviewLayout->addWidget(reviewtextInput);
	reviewokayButton = new QPushButton("&Add this review");
	addreviewLayout->addWidget(reviewokayButton);
	addreviewstatusOutput = new QLineEdit();
	addreviewstatusOutput->setReadOnly(true);
	addreviewLayout->addWidget(addreviewstatusOutput);
	closeaddreviewButton = new QPushButton("&Close");
	addreviewLayout->addWidget(closeaddreviewButton);

	smallwindowaddreview->setLayout(addreviewLayout);

	currentproduct = NULL;
	currentcartitem = NULL;


	//small-window-Recommendation
	smallwindowrecommend = new QWidget();
	recommendLayout = new QVBoxLayout();	
	recommendList = new QListWidget();
	recommendLayout->addWidget(recommendList);
	doneButton = new QPushButton("&Done");
	recommendLayout->addWidget(doneButton);

	smallwindowrecommend->setLayout(recommendLayout);

	//connect dunctions for login
	connect(quitloginButton, SIGNAL(clicked()), this, SLOT(closeamazon()));
	connect(loginButton, SIGNAL(clicked()), this, SLOT(checklogin()));
	connect(newuserButton, SIGNAL(clicked()), this, SLOT(createuser()));

	//all connect functions for main window
	//connect(usersList, SIGNAL(currentRowChanged(int)), this, SLOT(setuser(int)));
	//connect(selectuserButton, SIGNAL(clicked()), this, SLOT(selectuser()));
	connect(recommendButton, SIGNAL(clicked()), this, SLOT(recommend()));	
	connect(andButton, SIGNAL(clicked()), this, SLOT(andsearch()));
	connect(orButton, SIGNAL(clicked()), this, SLOT(orsearch()));
	connect(alphabeticalButton, SIGNAL(clicked()), this, SLOT(alphasort()));
	connect(ratingButton, SIGNAL(clicked()), this, SLOT(ratingsort()));	
	connect(saveButton, SIGNAL(clicked()), this, SLOT(savedatabase()));
	connect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	connect(addtocartButton, SIGNAL(clicked()), this, SLOT(addtocart()));
	connect(viewcartButton, SIGNAL(clicked()), this, SLOT(viewcart()));
	connect(addreviewButton, SIGNAL(clicked()), this, SLOT(addreview()));
	connect(closeamazonButton, SIGNAL(clicked()), this, SLOT(closeamazon()));

	//all connect functions for small window-cart
	connect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
	connect(removeitemButton, SIGNAL(clicked()), this, SLOT(removeitem()));
	connect(buycartButton, SIGNAL(clicked()), this, SLOT(buycart()));
	connect(closecartButton, SIGNAL(clicked()), this, SLOT(closecart()));

	//connect function for small window-addreview
	connect(reviewokayButton, SIGNAL(clicked()), this, SLOT(addthisreview()));
	connect(closeaddreviewButton, SIGNAL(clicked()), this, SLOT(closeaddreview()));

	//connect function for small wondow-recommend
	connect(doneButton, SIGNAL(clicked()), this, SLOT(donerecommend()));
}

MainWindow::~MainWindow()
{
	delete MyData;
	//TODO the delete UI objects
}

void MainWindow::checklogin()
{
	QMessageBox mymsg(this);
	if(lognameInput->text().isEmpty())
	{
		mymsg.setText("please enter username");
      	mymsg.exec();
      	lognameInput->setText("");
      	logpasswordInput->setText("");
      	return;
	}
	string uname = lognameInput->text().toStdString();
	User* user = MyData->getUser(uname);
	if(user==NULL)
	{
		mymsg.setText("username doesn't exist");
      	mymsg.exec();
      	lognameInput->setText("");
      	logpasswordInput->setText("");
      	return;
	}
	string password = logpasswordInput->text().toStdString();
	if(user->getHashcode() != MyData->hash(password))
	{
		mymsg.setText("Wrong password");
      	mymsg.exec();
      	lognameInput->setText("");
      	logpasswordInput->setText("");
      	return;
	}
	else
	{
		currentusername = uname;
		currentuserLabel->setText(QString::fromStdString("Current User: "+currentusername));
		double tempbalance = MyData->getUser(currentusername)->getBalance();
		stringstream ss;
		string currentbalance;
		ss<<tempbalance;
		ss>>currentbalance;
		currentcreditLabel->setText(QString::fromStdString("Current credit: "+currentbalance));
		bigwindowMain->show();
		this->hide();
	}
}

void MainWindow::createuser()
{
	QMessageBox mymsg(this);
	if(lognameInput->text().isEmpty() || logpasswordInput->text().isEmpty())
	{
		mymsg.setText("please enter your info");
      	mymsg.exec();
      	lognameInput->setText("");
      	logpasswordInput->setText("");
      	return;
	}
	string uname = lognameInput->text().toStdString();
	User* user = MyData->getUser(uname);
	if(user!=NULL)
	{
		mymsg.setText("username already exist");
      	mymsg.exec();
      	lognameInput->setText("");
      	logpasswordInput->setText("");
      	return;
	}
	string password = logpasswordInput->text().toStdString();
	if(password.length()>8)
	{
		mymsg.setText("password too long");
      	mymsg.exec();
      	lognameInput->setText("");
      	logpasswordInput->setText("");
      	return;
	}
	unsigned long long hashcode = MyData->hash(password);
	User* u = new User(uname, 100, 0, hashcode);
	MyData->addUser(u);
	currentusername = uname;
	currentuserLabel->setText(QString::fromStdString("Current User: "+currentusername));
	currentcreditLabel->setText(QString::fromStdString("Current credit: 100"));
	QString qstr = QString::fromStdString(uname);
	usersList->addItem(qstr);
	usernames.push_back(uname);
	bigwindowMain->show();
	this->hide();
}

void MainWindow::setuser(int userIndex)
{
	currentusername = usernames[userIndex];
	currentuserLabel->setText(QString::fromStdString("Current User: "+currentusername));
	string currentbalance;
	double tempbalance = MyData->getUser(currentusername)->getBalance();
	stringstream ss;
	ss<<tempbalance;
	ss>>currentbalance;
	currentcreditLabel->setText(QString::fromStdString("Current credit: "+currentbalance));
	if(smallwindowcart->isVisible())   viewcart();
}

void MainWindow::selectuser()
{
	if(usernameInput->text().isEmpty()) return;
	for(unsigned int i=0; i<usernames.size();++i)
	{
		if(usernameInput->text().toStdString() == usernames[i])
		{
			currentusername = usernames[i];
			currentuserLabel->setText(QString::fromStdString("Current User: "+currentusername));
			string currentbalance;
			double tempbalance = MyData->getUser(currentusername)->getBalance();
			stringstream ss;
			ss<<tempbalance;
			ss>>currentbalance;
			currentcreditLabel->setText(QString::fromStdString("Current credit: "+currentbalance));
			if(smallwindowcart->isVisible())   viewcart();
			return;
		}
	}
}

void MainWindow::recommend()
{
	recommendList->clear();
	vector<pair<string, double> > recommendations = MyData->makeSuggestion(currentusername);
	stringstream ss;
	ss<<std::setprecision(2)<<std::fixed;
	string temp;
	string score;
	string uname;
	ofstream ofile("rec.txt");
	ofile<<currentusername<<endl;
	for(unsigned int i=0;i<recommendations.size();++i)
	{
		temp = "";
		uname = recommendations[i].first;
		//cout<<recommendations[i].second<<endl;
		ss<<recommendations[i].second<<" ";
		ss>>score;
		//cout<<score<<endl;
		temp += score;
		temp += "  ";
		temp += uname;
		QString qstr = QString::fromStdString(temp);
		recommendList->addItem(qstr);
		ofile<<temp<<endl;
	}
	smallwindowrecommend->show();
}

void MainWindow::andsearch()
{
	productdetailsOutput->setPlainText("");
	reviewOutput->setPlainText("");
	if(searchproductInput->toPlainText().isEmpty()) return;
	vector<string> terms;
	stringstream ss(searchproductInput->toPlainText().toStdString());
	string temp;
	while(ss>>temp)
	{
		terms.push_back(temp);
	}
	productresult = MyData->search(terms, 0);
	disconnect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	productresultList->clear();
	currentproduct = NULL;
	if(productresult.empty())  return;
	stringstream ss2;
	for(unsigned int i=0; i<productresult.size();++i)
	{
		ss2<<productresult[i]->getPrice()<<" ";
		ss2>>temp;
		string qtemp = productresult[i]->getName()+"   "+temp;
		productresultList->addItem(QString::fromStdString(qtemp));
	}
	connect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	//currentproduct = productresult[0];
	//productdetailsOutput->setPlainText(QString::fromStdString(currentproduct->displayString()));
	//reviewOutput->setPlainText(QString::fromStdString(MyData->getReview(currentproduct)));
}

void MainWindow::orsearch()
{
	productdetailsOutput->setPlainText("");
	reviewOutput->setPlainText("");
	if(searchproductInput->toPlainText().isEmpty()) return;
	vector<string> terms;
	stringstream ss(searchproductInput->toPlainText().toStdString());
	string temp;
	while(ss>>temp)
	{
		terms.push_back(temp);
	}
	productresult = MyData->search(terms, 1);
	disconnect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	productresultList->clear();
	currentproduct = NULL;
	if(productresult.empty())  return;
	stringstream ss2;
	for(unsigned int i=0; i<productresult.size();++i)
	{
		ss2<<productresult[i]->getPrice()<<" ";
		ss2>>temp;
		string qtemp = productresult[i]->getName()+"   "+temp;
		productresultList->addItem(QString::fromStdString(qtemp));
	}
	connect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	//currentproduct = productresult[0];
	//productdetailsOutput->setPlainText(QString::fromStdString(currentproduct->displayString()));
	//reviewOutput->setPlainText(QString::fromStdString(MyData->getReview(currentproduct)));
}

void MainWindow::alphasort()
{
	if(productresult.empty())  return;
	productresult = MyData->alphasort(productresult);
	disconnect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	productresultList->clear();
	stringstream ss;
	string temp;
	for(unsigned int i=0; i<productresult.size();++i)
	{
		ss<<productresult[i]->getPrice()<<" ";
		ss>>temp;
		string qtemp = productresult[i]->getName()+"   "+temp;
		productresultList->addItem(QString::fromStdString(qtemp));
	}
	connect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	//currentproduct = productresult[0];
	//productdetailsOutput->setPlainText(QString::fromStdString(currentproduct->displayString()));
	//reviewOutput->setPlainText(QString::fromStdString(MyData->getReview(currentproduct)));
}

void MainWindow::ratingsort()
{
	if(productresult.empty())  return;
	productresult = MyData->ratingsort(productresult);
	disconnect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	productresultList->clear();
	stringstream ss;
	string temp;
	for(unsigned int i=0; i<productresult.size();++i)
	{
		ss<<productresult[i]->getPrice()<<" ";
		ss>>temp;
		string qtemp = productresult[i]->getName()+"   "+temp;
		productresultList->addItem(QString::fromStdString(qtemp));
	}
	connect(productresultList, SIGNAL(currentRowChanged(int)), this, SLOT(showprodetail(int)));
	//currentproduct = productresult[0];
	//productdetailsOutput->setPlainText(QString::fromStdString(currentproduct->displayString()));
	//reviewOutput->setPlainText(QString::fromStdString(MyData->getReview(currentproduct)));
}

void MainWindow::showprodetail(int productIndex)
{
	if(productresult.empty())  return;
	currentproduct = productresult[productIndex];
	productdetailsOutput->setPlainText(QString::fromStdString(currentproduct->displayString()));
	reviewOutput->setPlainText(QString::fromStdString(MyData->getReview(currentproduct)));
}

void MainWindow::addtocart()
{
	if(currentproduct!=NULL)
	{
		MyData->addCart(MyData->getUser(currentusername), currentproduct);
	}
	//currentcart.push_back(currentproduct);
}

void MainWindow::viewcart()
{
	smallwindowcart->show();
	currentcart = MyData->viewCart(MyData->getUser(currentusername));
	disconnect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
	itemsList->clear();
	itemdetailsOutput->setPlainText("");
	if(currentcart.empty())  return;
	for(unsigned int i=0; i<currentcart.size();++i)
	{
		stringstream ss;
		string temp;
		ss<<currentcart[i]->getPrice();
		ss>>temp;
		string qtemp = currentcart[i]->getName()+"   "+temp;
		itemsList->addItem(QString::fromStdString(qtemp));
	}
	connect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
	//currentcartitem = currentcart[0];
	//itemdetailsOutput->setPlainText(QString::fromStdString(currentcartitem->displayString()));
}

void MainWindow::addreview()
{
	if(currentproduct == NULL) return;
	smallwindowaddreview->show();
}

void MainWindow::closeamazon()
{
	bigwindowMain->hide();
	smallwindowcart->hide();
	smallwindowaddreview->hide();
	this->close();	
}

void MainWindow::showitemdetail(int itemIndex)
{
	currentcartitem = currentcart[itemIndex];
	itemdetailsOutput->setPlainText(QString::fromStdString(currentcartitem->displayString()));
}

void MainWindow::removeitem()
{
	if(currentcartitem == NULL)  return;
	MyData->removeItem(MyData->getUser(currentusername), currentcartitem);
	currentcart = MyData->viewCart(MyData->getUser(currentusername));
	disconnect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
	itemsList->clear();
	itemdetailsOutput->setPlainText("");
	for(unsigned int i=0; i<currentcart.size();++i)
	{
		stringstream ss;
		string temp;
		ss<<currentcart[i]->getPrice();
		ss>>temp;
		string qtemp = currentcart[i]->getName()+"   "+temp;
		itemsList->addItem(QString::fromStdString(qtemp));
	}
	connect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
	//currentcartitem = currentcart[0];
	//itemdetailsOutput->setPlainText(QString::fromStdString(currentcartitem->displayString()));
}

void MainWindow::buycart()
{
	MyData->buyCart(MyData->getUser(currentusername));
	disconnect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
	itemsList->clear();
	itemdetailsOutput->setPlainText("");
	productdetailsOutput->setPlainText(QString::fromStdString(currentproduct->displayString()));
	currentcartitem = NULL;
	currentcart = MyData->viewCart(MyData->getUser(currentusername));
	string currentbalance;
	double tempbalance = MyData->getUser(currentusername)->getBalance();
	stringstream ss;
	ss<<tempbalance;
	ss>>currentbalance;
	currentcreditLabel->setText(QString::fromStdString("Current credit: "+currentbalance));
	if(currentcart.empty())  return;
	for(unsigned int i=0; i<currentcart.size();++i)
	{
		stringstream ss;
		string temp;
		ss<<currentcart[i]->getPrice();
		ss>>temp;
		string qtemp = currentcart[i]->getName()+"   "+temp;
		itemsList->addItem(QString::fromStdString(qtemp));
	}
	connect(itemsList, SIGNAL(currentRowChanged(int)), this, SLOT(showitemdetail(int)));
}

void MainWindow::closecart()
{
	smallwindowcart->hide();
}

void MainWindow::addthisreview()
{
	if(yearInput->text().isEmpty() || monthInput->text().isEmpty() || dayInput->text().isEmpty()
		|| ratingInput->text().isEmpty() || reviewtextInput->toPlainText().isEmpty() )
	{
		addreviewstatusOutput->setText("Review cannot be added");
		return;
	}
	bool ok;
	if(yearInput->text().toInt(&ok,10)>=2016 && yearInput->text().toInt(&ok,10)<=2030 && 
		monthInput->text().toInt(&ok,10)>=1 && monthInput->text().toInt(&ok,10)<=12 && 
		dayInput->text().toInt(&ok,10)>=1 && dayInput->text().toInt(&ok,10)<=31 &&
		ratingInput->text().toInt(&ok,10)>=1 && ratingInput->text().toInt(&ok,10)<=5)
	{
		string tempdate=yearInput->text().toStdString()+"-"+monthInput->text().toStdString()
						+"-"+dayInput->text().toStdString();
		Review* r = new Review(currentproduct->getName(), ratingInput->text().toInt(),
			currentusername,tempdate,reviewtextInput->toPlainText().toStdString());
		MyData->addReview(r);
		addreviewstatusOutput->setText("Review successfully added");
		reviewOutput->setPlainText(QString::fromStdString(MyData->getReview(currentproduct)));
		return;
	}
	addreviewstatusOutput->setText("Review cannot be added");
	return;
}

void MainWindow::closeaddreview()
{
	smallwindowaddreview->hide();
}

void MainWindow::savedatabase()
{
	QString filename = QFileDialog::getSaveFileName(0, "Save Database",
					"/home/student/cs104/github/hw-zexiazha/hw5/database.txt",
					"Text files (*.txt)");
	ofstream ofile(filename.toStdString().c_str());
	MyData->dump(ofile);
	ofile.close();
}

void MainWindow::donerecommend()
{
	smallwindowrecommend->hide();
}