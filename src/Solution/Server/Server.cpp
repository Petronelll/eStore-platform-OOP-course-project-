#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	for (auto &it : usr) {
		__UserID__ProductsCart__.insert ( std::pair<int,ShoppingCart*>(it->getUserID(), new ShoppingCart));
	}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{
	if (quantity <= 0) {
		return false;
	}

	User *user_cerut = NULL;
	//cauta utilizatorul, cu ID-ul primit ca parametru, in lista cu useri
	for (auto user_it : usr) {
		if (user_it->getUserID() == userID) {
			user_cerut = user_it;
			break;
		}
	}

	//verifica daca userul cerut exista in lista cu utilizatori
	if (user_cerut == NULL) {
		return false;
	}

	Product *produs_cerut = NULL;
	//cauta produsul, cu ID-ul primit ca parametru, in lista cu produse
	for (auto prod_it : prod) {
		if (prod_it->getId() == productID) {
			produs_cerut = prod_it;
			break;
		}
	}

	//verifica daca produsul cerut exista in lista cu produse
	if (produs_cerut == NULL) {
		return false;
	}

	//verifica daca cantitatea ceruta este disponibila
	if (produs_cerut->checkQuantity(quantity)) {
		produs_cerut->decreaseQuantity(quantity);
	} else {
		return false;
	}

	//adauga cantitatea ceruta in cosul de cumparaturi
	if (__UserID__ProductsCart__[userID]->getQuantity(productID) == -1) {
		__UserID__ProductsCart__[userID]->addProduct(productID, quantity);
	} else {
		__UserID__ProductsCart__[userID]->raiseQuantity(productID, quantity);		
	}

	return true;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	if (quantity <= 0) {
		return false;
	}

	User *user_cerut = NULL;
	//cauta utilizatorul, cu ID-ul primit ca parametru, in lista cu useri
	for (auto user_it : usr) {
		if (user_it->getUserID() == userID) {
			user_cerut = user_it;
			break;
		}
	}

	//verifica daca userul cerut exista in lista cu utilizatori
	if (user_cerut == NULL) {
		return false;
	}

	Product *produs_cerut = NULL;
	//cauta produsul, cu ID-ul primit ca parametru, in lista cu produse
	for (auto prod_it : prod) {
		if (prod_it->getId() == productID) {
			produs_cerut = prod_it;
			break;
		}
	}

	//verifica daca produsul cerut exista in lista cu produse
	if (produs_cerut == NULL) {
		return false;
	}

	//verifica daca produsul cerut exista in cosul de cumparaturi
	if (__UserID__ProductsCart__[userID]->getQuantity(productID) == -1) {
		return false;
	}

	//sterge cantitatea ceruta din cosul de cumparaturi
	if (__UserID__ProductsCart__[userID]->getQuantity(productID) <= quantity) {
		__UserID__ProductsCart__[userID]->deleteProduct(productID);
		produs_cerut->setQuantity(0);
	} else {
		__UserID__ProductsCart__[userID]->lowerQuantity(productID, quantity);
		produs_cerut->decreaseQuantity(quantity);
	}

	return true;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}