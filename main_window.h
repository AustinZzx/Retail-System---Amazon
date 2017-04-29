#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>
#include <QComboBox>
#include <QApplication>
#include <QMessageBox>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "review.h"
#include "mydatastore.h"

using namespace std;

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	MainWindow(MyDataStore* mydata);
	~MainWindow();

private slots:
	void checklogin();
	void createuser();
	void setuser(int userIndex);
	void selectuser();
	void recommend();
	void andsearch();
	void orsearch();
	void alphasort();
	void ratingsort();
	void showprodetail(int productIndex);
	void addtocart();
	void viewcart();
	void addreview();
	void closeamazon();
	void showitemdetail(int itemIndex);
	void removeitem();
	void buycart();
	void closecart();
	void addthisreview();
	void closeaddreview();
	void savedatabase();
	void donerecommend();

private:
	//data
	MyDataStore* MyData;
	vector<string> usernames;
	string currentusername;
	vector<Product*> productresult;
	Product* currentproduct;
	vector<Product*> currentcart;
	Product* currentcartitem;
	

	//Log in WIndow
	QVBoxLayout* loginLayout;
	QLabel* lognameLabel;
	QLabel* logpasswordLabel;
	QLineEdit* lognameInput;
	QLineEdit* logpasswordInput;
	QPushButton* loginButton;
	QPushButton* newuserButton;
	QPushButton* quitloginButton;


	// // UI main window

	// main Layout
	QWidget* bigwindowMain;
	QHBoxLayout* overallLayout;

	// user
	QVBoxLayout* userLayout;
	QLabel* usersnameLabel;
	QListWidget* usersList;
	QLineEdit* usernameInput;
	QPushButton* selectuserButton;
	QLineEdit* currentuserLabel;
	QLineEdit* currentcreditLabel;
	QPushButton* recommendButton;

	// search product
	QVBoxLayout* searchproductLayout;
	QLabel* searchproductLabel;
	QTextEdit* searchproductInput;
	QHBoxLayout* andorLayout;
	QPushButton* andButton;
	QPushButton* orButton;
	QLabel* sortproductLabel;
	QHBoxLayout* sortproductLayout;
	QPushButton* alphabeticalButton;
	QPushButton* ratingButton;
	QFileDialog* saveDialog;
	QPushButton* saveButton;

	//product result
	QVBoxLayout* productresultLayout;
	QLabel* productresultLabel;
	QListWidget* productresultList;

	//product details
	QVBoxLayout* productdetailsLayout;
	QLabel* productdetailsLabel;
	QTextEdit* productdetailsOutput;
	QPushButton* addtocartButton;
	QPushButton* viewcartButton;

	//review
	QVBoxLayout* reviewLayout;
	QLabel* reviewLabel;
	QTextEdit* reviewOutput;
	QPushButton* addreviewButton;
	QPushButton* closeamazonButton;


	// // UI small window 1 - CART
	QWidget* smallwindowcart;
	// main Layout
	QHBoxLayout* cartoverallLayout;

	//cart items
	QVBoxLayout* itemsLayout;
	QLabel* itemsLabel;
	QListWidget* itemsList;

	//cart details
	QVBoxLayout* itemdetailsLayout;
	QLabel* itemdetailsLabel;
	QTextEdit* itemdetailsOutput;
	QPushButton* buycartButton;
	QPushButton* removeitemButton;
	QPushButton* closecartButton;

	// // UI small window 2 - Add-Review
	QWidget* smallwindowaddreview;
	QVBoxLayout* addreviewLayout;
	QHBoxLayout* yearLayout;
	QLabel* yearLabel;
	QLineEdit* yearInput;
	QHBoxLayout* monthLayout;
	QLabel* monthLabel;
	QLineEdit* monthInput;
	QHBoxLayout* dayLayout;
	QLabel* dayLabel;
	QLineEdit* dayInput;
	QHBoxLayout* ratingLayout;
	QLabel* ratingLabel;
	QLineEdit* ratingInput;
	QLabel* reviewtextLabel;
	QTextEdit* reviewtextInput;
	QPushButton* reviewokayButton;
	QLineEdit* addreviewstatusOutput;
	QPushButton* closeaddreviewButton;


	// // UI small window 3 - Recommendation
	QWidget* smallwindowrecommend;
	QVBoxLayout* recommendLayout;
	QListWidget* recommendList;
	QPushButton* doneButton;

};
