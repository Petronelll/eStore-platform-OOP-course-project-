#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a(){
  
  list<Product*> espressoare_reduse;

  for (auto it : server->getProductsList()) {

    if (it->getCategory() == "espressor" && it->getProductType() == "redus") {
      espressoare_reduse.push_back(it);
    }
  }
  return espressoare_reduse;
}

list<User*> QuerySolver::Query_3b(){
  
  list<User*> utilizatori_nonpremium;

  for (auto it : server->getUsersList()) {

    if (it->getUserType() == "nonPremium" && it->getTransportCost() <= 11.5) {
      utilizatori_nonpremium.push_back(it);
    }
  }
  return utilizatori_nonpremium;
}

list<Product*> QuerySolver::Query_3c(){
  
  list<Product*> produse_resigilate;
  ResealedProduct *rp;

  for (auto it : server->getProductsList()) {

    if (it->getProductType() == "resigilat") {
      rp = dynamic_cast<ResealedProduct*>(it);

      if (rp != NULL && rp->getReason() == "lipsa_accesorii") {
          produse_resigilate.push_back(it);
      }
    }
  }

  produse_resigilate.sort(
      [](Product *p1, Product *p2) {
        ResealedProduct *rp1, *rp2;
        rp1 = dynamic_cast<ResealedProduct*>(p1);
        rp2 = dynamic_cast<ResealedProduct*>(p2);
        return rp1->getPrice() < rp2->getPrice();
      }
  );

  return produse_resigilate;
}

list<Product*> QuerySolver::Query_3d(){

  list<Product*> produse_alimentare;

  for (auto it : server->getProductsList()) {

    if (it->getProductType() == "alimentar") {
        produse_alimentare.push_back(it);
    }
  }

  produse_alimentare.sort(
    [](Product *p1, Product *p2) -> bool {
        FoodProduct *fp1, *fp2;
        fp1 = dynamic_cast<FoodProduct*>(p1);
        fp2 = dynamic_cast<FoodProduct*>(p2);
      
        if (fp1->getName() < fp2->getName()) return true;
        if (fp1->getName() > fp2->getName()) return false;

        if (fp1->getCountryOfOrigin() < fp2->getCountryOfOrigin()) return true;
        if (fp1->getCountryOfOrigin() > fp2->getCountryOfOrigin()) return false;

        if (fp1->getLeiPerKg() < fp2->getLeiPerKg()) return true;
        return false;
    }
  );

  return produse_alimentare;
}

list<User*> QuerySolver::Query_3e(){

  //memoreaza cati utilizatori se afla in fiecare judet
  map<string, int> judet_NrUseri; 

  for (auto it : server->getUsersList()) {
    judet_NrUseri[it->getDeliveryData().getCounty()] ++;
  }

  //gaseste judetul cu cei mai multi utilizatori
  auto pr = std::max_element
  (
    judet_NrUseri.begin(), judet_NrUseri.end(), 
    [] (pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
  );

  string cel_mai_populat_judet = pr->first;

  list<User*> utilizatori_la_casa;
  
  //populeaza lista de utilizatori conform criteriilor din cerinta
  for (auto it : server->getUsersList()) {
    if (
      it->getDeliveryData().getCounty() == cel_mai_populat_judet &&
      it->getDeliveryData().getBlock() == "-" &&
      it->getDeliveryData().getApartment() == 0 &&
      it->getBillingData().getBlock() == "-" &&
      it->getBillingData().getApartment() == 0
      )
      utilizatori_la_casa.push_back(it);
  }

  //Sortare lista de utilizatori in functie de ID
  utilizatori_la_casa.sort(
      [](User *u1, User *u2) {
        return u1->getUserID() < u2->getUserID();
      }
  );

  return utilizatori_la_casa;
}

list<User*> QuerySolver::Query_3f() {
  
  list<User*> utilizatori_premium_doriti;

  //cauta utilizatorii premium din lista cu utilizatori
  for (auto it : server->getUsersList()) {

    if (it->getUserType() == "premium") {

      PremiumUser *p_user = dynamic_cast<PremiumUser*>(it);
      map<int, int> temp_discounts = p_user->getDiscounts();

      //parcurgere reduceri ale unui utilizator premium
      for (auto discounts_it : temp_discounts) {

        bool gasit_id_produs = false; //verifica daca a fost gasit produsul
                                      //care are ID ul dorit
        Product *temp;

        //cauta produsul cu ID ul din cuponul de reducere
        //in lista cu produse
        for (auto products_it : server->getProductsList()) {

          if (products_it->getId() == discounts_it.first) {
            gasit_id_produs = true;
            temp = products_it;
            break;
          }
        }

        //verifica daca a fost gasit produsul cu reducere
        if (!gasit_id_produs) continue;


          if ((temp->getCategory() == "telefon") || (temp->getCategory() == "imprimanta")) {
          utilizatori_premium_doriti.push_back(it);
          break;
        }
      }
    }
  }

  //Sortare lista de utilizatori in functie de ID
  utilizatori_premium_doriti.sort(
      [](User *u1, User *u2) {
        return u1->getUserID() < u2->getUserID();
      }
  );

  return utilizatori_premium_doriti;
}
